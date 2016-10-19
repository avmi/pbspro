/*
 * Copyright (C) 1994-2016 Altair Engineering, Inc.
 * For more information, contact Altair at www.altair.com.
 *  
 * This file is part of the PBS Professional ("PBS Pro") software.
 * 
 * Open Source License Information:
 *  
 * PBS Pro is free software. You can redistribute it and/or modify it under the
 * terms of the GNU Affero General Public License as published by the Free 
 * Software Foundation, either version 3 of the License, or (at your option) any 
 * later version.
 *  
 * PBS Pro is distributed in the hope that it will be useful, but WITHOUT ANY 
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU Affero General Public License for more details.
 *  
 * You should have received a copy of the GNU Affero General Public License along 
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 *  
 * Commercial License Information: 
 * 
 * The PBS Pro software is licensed under the terms of the GNU Affero General 
 * Public License agreement ("AGPL"), except where a separate commercial license 
 * agreement for PBS Pro version 14 or later has been executed in writing with Altair.
 *  
 * Altair’s dual-license business model allows companies, individuals, and 
 * organizations to create proprietary derivative works of PBS Pro and distribute 
 * them - whether embedded or bundled with other software - under a commercial 
 * license agreement.
 * 
 * Use of Altair’s trademarks, including but not limited to "PBS™", 
 * "PBS Professional®", and "PBS Pro™" and Altair’s logos is subject to Altair's 
 * trademark licensing policies.
 *
 */
/**
 * @file	pbs_locjob.c
 * @brief
 * This function does the LocateJob request.
 */

#include <pbs_config.h>   /* the master config generated by configure */

#include <string.h>
#include <stdio.h>
#include "libpbs.h"
#include "dis.h"
#include "pbs_ecl.h"


/**
 * @brief
 *      This function does the LocateJob request.
 *
 * @param[in] c - connection handler
 * @param[in] jobid - job identifier
 * @param[in] extend - string to encode req
 *
 * @return      string
 * @retval      destination name	success
 * @retval      NULL      		error
 *
 */
char *
__pbs_locjob(int c, char *jobid, char *extend)
{
	int	rc;
	struct batch_reply *reply;
	char       *ploc = (char *)0;
	int sock;


	if ((jobid == (char *)0) || (*jobid == '\0')) {
		pbs_errno = PBSE_IVALREQ;
		return (ploc);
	}

	sock = connection[c].ch_socket;

	/* initialize the thread context data, if not already initialized */
	if (pbs_client_thread_init_thread_context() != 0)
		return (char *) NULL;

	/* lock pthread mutex here for this connection */
	/* blocking call, waits for mutex release */
	if (pbs_client_thread_lock_connection(c) != 0)
		return (char *) NULL;

	/* setup DIS support routines for following DIS calls */

	DIS_tcp_setup(sock);

	if ((rc = encode_DIS_ReqHdr(sock, PBS_BATCH_LocateJob, pbs_current_user)) ||
		(rc = encode_DIS_JobId(sock, jobid))	   ||
		(rc = encode_DIS_ReqExtend(sock, extend))) {
		connection[c].ch_errtxt = strdup(dis_emsg[rc]);
		if (connection[c].ch_errtxt == NULL) {
			pbs_errno = PBSE_SYSTEM;
		} else {
			pbs_errno = PBSE_PROTOCOL;
		}
		(void)pbs_client_thread_unlock_connection(c);
		return (char *)NULL;
	}

	/* write data over tcp stream */

	if (DIS_tcp_wflush(sock)) {
		pbs_errno = PBSE_PROTOCOL;
		(void)pbs_client_thread_unlock_connection(c);
		return (char *)NULL;
	}

	/* read reply from stream */

	reply = PBSD_rdrpy(c);
	if (reply == NULL) {
		pbs_errno = PBSE_PROTOCOL;
	} else if (reply->brp_choice != BATCH_REPLY_CHOICE_NULL &&
		reply->brp_choice != BATCH_REPLY_CHOICE_Text &&
		reply->brp_choice != BATCH_REPLY_CHOICE_Locate) {
		advise("pbs_locjob", "Unexpected reply choice");
		pbs_errno = PBSE_PROTOCOL;
	} else if (connection[c].ch_errno == 0) {
		if ((ploc = strdup(reply->brp_un.brp_locate)) == NULL) {
			pbs_errno = PBSE_SYSTEM;
		}
	}

	PBSD_FreeReply(reply);

	/* unlock the thread lock and update the thread context data */
	if (pbs_client_thread_unlock_connection(c) != 0)
		return (char *) NULL;

	return ploc;
}
