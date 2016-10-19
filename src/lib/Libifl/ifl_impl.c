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
 * @file    ifl_impl.c
 *
 * @brief
 * 		Pass-through call to send batch_request to server. Interfaces can
 * 		be overridden by the developer, to implement their own definition.
 */

#include <pbs_config.h>   /* the master config generated by configure */
#include "ifl_internal.h"

/**
 * @brief
 *	-Pass-through call to send async run job batch request.
 *
 * @param[in] c - connection handle
 * @param[in] jobid- job identifier
 * @param[in] location - string of vnodes/resources to be allocated to the job
 * @param[in] extend - extend string for encoding req
 *
 * @return      int
 * @retval      0       success
 * @retval      !0      error
 *
 */
int
pbs_asyrunjob(int c, char *jobid, char *location, char *extend) {
	return __pbs_asyrunjob(c, jobid, location, extend);
}

/**
 * @brief
 *	-Pass-through call to send alter Job request
 *	really an instance of the "manager" request.
 *
 * @param[in] c - connection handle
 * @param[in] jobid- job identifier
 * @param[in] attrib - pointer to attribute list
 * @param[in] extend - extend string for encoding req
 *
 * @return	int
 * @retval	0	success
 * @retval	!0	error
 *
 */
int
pbs_alterjob(int c, char *jobid, struct attrl *attrib, char *extend) {
	return __pbs_alterjob(c, jobid, attrib, extend);
}

/**
 * @brief
 *	Pass-through call to connect to pbs server
 *	passing any 'extend' data to the connection.
 *
 * @param[in] server - server - the hostname of the pbs server to connect to.
 *
 * @retval int	- return value of pbs_connect_extend().
 */
int
pbs_connect(char *server) {
	return __pbs_connect(server);
}

/**
 * @brief
 *	Pass-through call to make a PBS_BATCH_Connect request to 'server'.
 *
 * @param[in]   server - the hostname of the pbs server to connect to.
 * @param[in]   extend_data - a string to send as "extend" data.
 *
 * @return int
 * @retval >= 0	index to the internal connection table representing the
 *		connection made.
 * @retval -1	error encountered setting up the connection.
 */
int
pbs_connect_extend(char *server, char *extend_data) {
	return __pbs_connect_extend(server, extend_data);
}

/**
 * @brief
 *	- Pass-through call to get default server name.
 *
 * @return	string
 * @retval	dflt srvr name	success
 * @retval	NULL		error
 *
 */
char *
pbs_default() {
	return __pbs_default();
}

/**
 * @brief
 *	Pass-through call to send the delete Job request
 * 	really just an instance of the manager request
 *
 * @param[in] c - connection handler
 * @param[in] jobid - job identifier
 * @param[in] extend - string to encode req
 *
 * @return	int
 * @retval	0	success
 * @retval	!0	error
 *
 */
int
pbs_deljob(int c, char *jobid, char *extend) {
	return __pbs_deljob(c, jobid, extend);
}


/**
 * @brief
 *	-Pass-through call to send close connection batch request
 *
 * @param[in] connect - socket descriptor
 *
 * @return	int
 * @retval	0	success
 * @retval	-1	error
 *
 */
int
pbs_disconnect(int connect) {
	return __pbs_disconnect(connect);
}

/**
 * @brief
 *	-Pass-through call to get last error message the server returned on
 *	this connection.
 *
 * @param[in] connect - soket descriptor
 *
 * @return	string
 * @retval	connection contexts
 *		TLS			multithread
 *		STRUCTURE		single thread
 * @retval	errmsg			error
 *
 */
char *
pbs_geterrmsg(int connect) {
	return __pbs_geterrmsg(connect);
}

/**
 * @brief
 *	- Pass-through call to send Hold Job request to the server --
 *	really just an instance of the "manager" request.
 *
 * @param[in] c - connection handler
 * @param[in] jobid - job identifier
 * @param[in] holdtype - value for holdtype
 * @param[in] extend - string to encode req
 *
 * @return      int
 * @retval      0       success
 * @retval      !0      error
 *
 */
int
pbs_holdjob(int c, char *jobid, char *holdtype, char *extend) {
	return __pbs_holdjob(c, jobid, holdtype, extend);
}

/**
* @brief
*      Pass-through call to send LocateJob request.
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
pbs_locjob(int c, char *jobid, char *extend) {
	return __pbs_locjob(c, jobid, extend);
}


/**
 * @brief
 *	- Basically a pass-thru to PBS_manager
 *
 * @param[in] c - connection handle
 * @param[in] command - mgr command with respect to obj
 * @param[in] objtype - object type
 * @param[in] objname - object name
 * @param[in] attrib -  pointer to attropl structure
 * @param[in] extend - extend string to encode req
 *
 * @return	int
 * @retval	0	success
 * @retval	!0	error
 *
 */
int
pbs_manager(int c, int command, int objtype, char *objname,
		struct attropl *attrib, char *extend) {
	return __pbs_manager(c, command, objtype, objname,
		attrib, extend);
}

/**
 * @brief
 *	Pass-through call to send move job request
 *
 * @param[in] c - connection handler
 * @param[in] jobid - job identifier
 * @param[in] destin - job moved to
 * @param[in] extend - string to encode req
 *
 * @return      int
 * @retval      0       success
 * @retval      !0      error
 *
 */
int
pbs_movejob(int c, char *jobid, char *destin, char *extend) {
	return __pbs_movejob(c, jobid, destin, extend);
}

/**
 * @brief
 *	-Pass-through call to send the MessageJob request and get the reply.
 *
 * @param[in] c - socket descriptor
 * @param[in] jobid - job id
 * @param[in] fileopt - which file
 * @param[in] msg - msg to be encoded
 * @param[in] extend - extend string for encoding req
 *
 * @return	int
 * @retval	0	success
 * @retval	!0	error
 *
 */
int
pbs_msgjob(int c, char *jobid, int fileopt, char *msg, char *extend) {
	return __pbs_msgjob(c, jobid, fileopt, msg, extend);
}

/**
 * @brief
 *	-Pass-through call to send order job batch request
 *
 * @param[in] c - connection handler
 * @param[in] job1 - job identifier
 * @param[in] job2 - job identifier
 * @param[in] extend - string to encode req
 *
 * @return      int
 * @retval      0       success
 * @retval      !0      error
 *
 */
int
pbs_orderjob(int c, char *job1, char *job2, char *extend) {
	return __pbs_orderjob(c, job1, job2, extend);
}

/**
 * @brief
 *	-Pass-through call to send rerun batch request
 *
 * @param[in] c - connection handler
 * @param[in] jobid - job identifier
 * @param[in] extend - string to encode req
 *
 * @return      int
 * @retval      0       success
 * @retval      !0      error
 *
 */
int
pbs_rerunjob(int c, char *jobid, char *extend) {
	return __pbs_rerunjob(c, jobid, extend);
}

/**
 * @brief
 *	-Pass-through call to release a hold on a job.
 * 	really just an instance of the "manager" request.
 *
 * @param[in] c - connection handler
 * @param[in] jobid - job identifier
 * @param[in] holdtype - type of hold
 * @param[in] extend - string to encode req
 *
 * @return      int
 * @retval      0       success
 * @retval      !0      error
 *
 */
int
pbs_rlsjob(int c, char *jobid, char *holdtype, char *extend) {
	return __pbs_rlsjob(c, jobid, holdtype, extend);
}

/**
 * @brief
 *	-Pass-through call to send runjob batch request
 *
 * @param[in] c - communication handle
 * @param[in] jobid - job identifier
 * @param[in] location - location where job running
 * @param[in] extend - extend string to encode req
 *
 * @return      int
 * @retval      DIS_SUCCESS(0)  success
 * @retval      error code      error
 *
 */
int
pbs_runjob(int c, char *jobid, char *location, char *extend) {
	return __pbs_runjob(c, jobid, location, extend);
}

/**
 * @brief
 *	-Pass-through call to send SelectJob request
 *	Return a list of job ids that meet certain selection criteria.
 *
 * @param[in] c - communication handle
 * @param[in] attrib - pointer to attropl structure(selection criteria)
 * @param[in] extend - extend string to encode req
 *
 * @return	string
 * @retval	job ids		success
 * @retval	NULL		error
 *
 */
char **
pbs_selectjob(int c, struct attropl *attrib, char *extend) {
	return __pbs_selectjob(c, attrib, extend);
}

/**
 * @brief
 *	Pass-through call to sends and reads signal job batch request.
 *
 * @param[in] c - communication handle
 * @param[in] jobid - job identifier
 * @param[in] signal - signal
 * @param[in] extend - extend string for request
 *
 * @return	int
 * @retval	0	success
 * @retval	!0	error
 *
 */
int
pbs_sigjob(int c, char *jobid, char *signal, char *extend) {
	return __pbs_sigjob(c, jobid, signal, extend);
}


/**
 * @brief
 *	-Pass-through call to deallocates a "batch_status" structure
 *
 * @param[in] bsp - pointer to batch request.
 *
 * @return	Void
 *
 */
void
pbs_statfree(struct batch_status *bsp) {
	__pbs_statfree(bsp);
}

/**
 * @brief
 *	Pass-through call to get status of one or more resources.
 *
 * @param[in] c - communication handle
 * @param[in] id - object id
 * @param[in] attrib - pointer to attribute list
 * @param[in] extend - extend string for encoding req
 *
 * @return      structure handle
 * @retval      pointer to batch_status struct          Success
 * @retval      NULL                                    error
 *
 */
struct batch_status *
pbs_statrsc(int c, char *id, struct attrl *attrib, char *extend) {
	return __pbs_statrsc(c, id, attrib, extend);
}

/**
 * @brief
 *	-Pass-through call to get status of a job.
 *
 * @param[in] c - communication handle
 * @param[in] id - job id
 * @param[in] attrib - pointer to attribute list
 * @param[in] extend - extend string for req
 *
 * @return	structure handle
 * @retval	pointer to batch_status struct		success
 * @retval	NULL					error
 *
 */
struct batch_status *
pbs_statjob(int c, char *id, struct attrl *attrib, char *extend) {
	return __pbs_statjob(c, id, attrib, extend);
}

/**
 * @brief
 *	-Pass-through call to SelectJob request
 *	Return a list of job ids that meet certain selection criteria.
 *
 * @param[in] c - communication handle
 * @param[in] attrib - pointer to attropl structure(selection criteria)
 * @param[in] extend - extend string to encode req
 *
 * @return	string
 * @retval	job ids		success
 * @retval	NULL		error
 *
 */
struct batch_status *
pbs_selstat(int c, struct attropl *attrib, struct attrl   *rattrib, char *extend) {
	return __pbs_selstat(c, attrib, rattrib, extend);
}

/**
 * @brief
 *	-Pass-through call to get status of a queue.
 *
 * @param[in] c - communication handle
 * @param[in] id - object id
 * @param[in] attrib - pointer to attribute list
 * @param[in] extend - extend string for encoding req
 *
 * @return      structure handle
 * @retval      pointer to batch_status struct          Success
 * @retval      NULL                                    error
 *
 */
struct batch_status *
pbs_statque(int c, char *id, struct attrl *attrib, char *extend) {
	return __pbs_statque(c, id, attrib, extend);
}

/**
 * @brief
 *	- Pass-through call to return the status of a server.
 *
 * @param[in] c - communication handle
 * @param[in] attrib - pointer to attribute list
 * @param[in] extend - extend string for encoding req
 *
 * @return      structure handle
 * @retval      pointer to batch_status struct          Success
 * @retval      NULL                                    error
 *
 */
struct batch_status *
pbs_statserver(int c, struct attrl *attrib, char *extend) {
	return __pbs_statserver(c, attrib, extend);
}

/**
 * @brief
 *	- Pass-through call to return the status of sched objects.
 *
 * @param[in] c - communication handle
 * @param[in] attrib - pointer to attribute list
 * @param[in] extend - extend string for encoding req
 *
 * @return      structure handle
 * @retval      pointer to batch_status struct          Success
 * @retval      NULL                                    error
 *
 */
struct batch_status *
pbs_statsched(int c, struct attrl *attrib, char *extend) {
	return __pbs_statsched(c, attrib, extend);
}

/**
 * @brief
 * 	- Pass-through call to return the status of all possible hosts.
 *
 * @param[in] con - communication handle
 * @param[in] hid - hostname to filter
 * @param[in] attrib - pointer to attribute list
 * @param[in] extend - extend string for encoding req
 *
 * @return      structure handle
 * @retval      pointer to batch_status struct          Success
 * @retval      NULL                                    error
 *
 */
struct batch_status *
pbs_stathost(int con, char *hid, struct attrl *attrib, char *extend) {
	return __pbs_stathost(con, hid, attrib, extend);
}

/**
 * @brief
 * 	-Pass-through call to returns status of host
 *	maintained for backward compatibility
 *
 * @param[in] c - communication handle
 * @param[in] id - object id
 * @param[in] attrib - pointer to attribute list
 * @param[in] extend - extend string for encoding req
 *
 * @return      structure handle
 * @retval      pointer to batch_status struct          Success
 * @retval      NULL					error
 *
 */
struct batch_status *
pbs_statnode(int c, char *id, struct attrl *attrib, char *extend) {
	return __pbs_statnode(c, id, attrib, extend);
}

/**
 * @brief
 * 	-Pass-through call to to get information about virtual nodes (vnodes)
 *
 * @param[in] c - communication handle
 * @param[in] id - object id
 * @param[in] attrib - pointer to attribute list
 * @param[in] extend - extend string for encoding req
 *
 * @return	structure handle
 * @retval	pointer to batch_status struct		Success
 * @retval	NULL					error
 *
 */
struct batch_status *
pbs_statvnode(int c, char *id, struct attrl *attrib, char *extend) {
	return __pbs_statvnode(c, id, attrib, extend);
}


/**
 * @brief
 *	-Pass-through call to get the status of a reservation.
 *
 * @param[in] c - communication handle
 * @param[in] id - object id
 * @param[in] attrib - pointer to attribute list
 * @param[in] extend - extend string for encoding req
 *
 * @return      structure handle
 * @retval      pointer to batch_status struct          Success
 * @retval      NULL                                    error
 *
 */
struct batch_status *
pbs_statresv(int c, char *id, struct attrl *attrib, char *extend) {
	return __pbs_statresv(c, id, attrib, extend);
}


/**
 * @brief
 *	Pass-through call to get status of a hook.
 *
 * @param[in] c - communication handle
 * @param[in] id - object name
 * @param[in] attrib - pointer to attrl structure(list)
 * @param[in] extend - extend string for req
 *
 * @return	structure handle
 * @retval	pointer to attr list	success
 * @retval	NULL			error
 *
 */
struct batch_status *
pbs_stathook(int c, char *id, struct attrl *attrib, char *extend) {
	return __pbs_stathook(c, id, attrib, extend);
}

/**
 * @brief
 *	-Pass-through call to get the attributes that failed verification
 *
 * @param[in] connect - socket descriptor
 *
 * @return	structure handle
 * @retval	pointer to ecl_attribute_errors struct		success
 * @retval	NULL						error
 *
 */
struct ecl_attribute_errors *
pbs_get_attributes_in_error(int connect) {
	return __pbs_get_attributes_in_error(connect);
}

/**
 * @brief
 *	-Pass-through call to submit job request
 *
 * @param[in] c - communication handle
 * @param[in] attrib - ponter to attr list
 * @param[in] script - job script
 * @param[in] destination - host where job submitted
 * @param[in] extend - buffer to hold cred info
 *
 * @return      string
 * @retval      jobid   success
 * @retval      NULL    error
 *
 */
char *
pbs_submit(int c, struct attropl  *attrib, char *script, char *destination, char *extend) {
	return __pbs_submit(c, attrib, script, destination, extend);
}

/**
 * @brief
 *	Pass-through call to submit reservation request
 *
 * @param[in]   c - socket on which connected
 * @param[in]   attrib - the list of attributes for batch request
 * @parma[in]   extend - extension of batch request
 *
 * @return char*
 * @retval SUCCESS returns the reservation ID
 * @retval ERROR NULL
 */
char *
pbs_submit_resv(int c, struct attropl *attrib, char *extend) {
	return __pbs_submit_resv(c, attrib, extend);
}

/**
 * @brief
 *      Pass-through call to Delete reservation
 *
 * @param[in] c - connection handler
 * @param[in] resv_id - reservation identifier
 * @param[in] extend - string to encode req
 *
 * @return      int
 * @retval      0       success
 * @retval      !0      error
 *
 */
int
pbs_delresv(int c, char *resv_id, char *extend) {
	return __pbs_delresv(c, resv_id, extend);
}

/**
 * @brief
 *	-Pass-through call to send termination batch_request to server.
 *
 * @param[in] c - communication handle
 * @param[in] manner - manner in which server to be terminated
 * @param[in] extend - extension string for request
 *
 * @return	int
 * @retval	0		success
 * @retval	pbs_error	error
 *
 */
int
pbs_terminate(int c, int manner, char *extend) {
	return __pbs_terminate(c, manner, extend);
}
