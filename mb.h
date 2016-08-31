/**
 * @file mb.h
 * @author Taka Wang
 * @brief modbus daemon API(Interface)
*/

#ifndef MB_H
#define MB_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <stdbool.h>

#include <modbus.h>
#include "uthash.h"
#include "log.h"
#include "json.h"

/* ==================================================
 *  struct
================================================== */

/**
 * @brief `structure key` for modbus tcp hash table
 *
 * Hash key. Ip v4/v6 address and port composition.
 */
typedef struct 
{
    char ip[50];        /** IP v4/v6 address or hostname */
    char port[50];      /** service name/port number to connect to */
} mbtcp_key_s;

/**
 * @brief hashable mbtcp handle type
 *
 * Hashable tcp handle strucut for keeping connection.
 */
typedef struct 
{
    mbtcp_key_s key;    /** key */
    bool connected;     /** is connect to modbus slave? */
    modbus_t *ctx;      /** modbus context pointer */
    UT_hash_handle hh;  /** makes this structure hashable */
} mbtcp_handle_s;


/**
 * @brief Function pointer of modbus tcp function code
 *
 * Function pointer to `modbus tcp function code request` for `generic command handle`.
 *
 * @param handle Mbtcp handle.
 * @param req cJSON request object.
 * @return Modbus response string in JSON format.
 */
typedef char * (*mbtcp_fc)(mbtcp_handle_s *handle, cJSON *req);


/* ==================================================
 *  api
================================================== */

/**
 * @brief Set modbusd success response string without data (i.e., write func)
 *
 * @param tid Transaction ID.
 * @return Modbus ok response string in JSON format.
 */ 
char * set_modbus_success_resp_str(char * tid);

/**
 * @brief Set modbusd success response string with data (i.e., read func)
 *
 * @param tid Transaction ID.
 * @param json_arr cJSON pointer to data array
 * @return Modbus ok response string in JSON format.
 */ 
char * set_modbus_success_resp_str_with_data(char * tid, cJSON * json_arr);

/**
 * @brief Set modbusd fail response string.
 *
 * @param tid Transaction ID.
 * @param reason Fail reason string.
 * @return Modbus response string in JSON format.
 */
char * set_modbus_fail_resp_str(char * tid, const char *reason);

/**
 * @brief Set modbusd fail response string with error number.
 *
 * @param tid Transaction ID.
 * @param handle Mbtcp handle.
 * @param errnum Error number from modbus tcp handle.
 * @return Modbus error response string in JSON format.
 */ 
char * set_modbus_fail_resp_str_with_errno(char * tid, mbtcp_handle_s *handle, int errnum);

/* ==================================================
 *  modbus tcp (mbtcp)
================================================== */

/**
 * @brief Init mbtcp handle (to hashtable) and try to connect
 *
 * @param ptr_handle Pointer to mbtcp handle.
 * @param ip IP address string.
 * @param port Modbus TCP server port string.
 * @return Success or not.
 */
bool mbtcp_init_handle(mbtcp_handle_s **ptr_handle, char *ip, char *port);

/**
 * @brief Get mbtcp handle from hashtable
 *
 * @param ptr_handle Pointer to mbtcp handle.
 * @param ip IP address string.
 * @param port Modbus TCP server port string or service name.
 * @return Success or not.
 */
bool mbtcp_get_handle(mbtcp_handle_s **ptr_handle, char *ip, char *port);

/**
 * @brief List all handles in mbtcp hash table
 *
 * @return Void.
 */
void mbtcp_list_handles();

/**
 * @brief Connect to mbtcp slave via mbtcp hashed handle
 *
 * @param handle Mbtcp handle.  
 * @param reason Fail reason string.
 * @return Success or not.
 */
bool mbtcp_do_connect(mbtcp_handle_s *handle, char ** reason);

/**
 * @brief Get mbtcp handle's connection status
 *
 * @param handle Mbtcp handle.
 * @return Success or not. 
 */
bool mbtcp_get_connection_status(mbtcp_handle_s *handle);

/**
 * @brief Generic mbtcp command handler
 *
 * @param req cJSON request object.
 * @param fc Function pointer to modbus tcp FC handler.
 * @return Modbus response string in JSON format.
 */
char * mbtcp_cmd_hanlder(cJSON *req, mbtcp_fc fc);


/**
 * @brief Set mbtcp response timeout in usec
 *
 * @param tid Transaction ID.
 * @param timeout Timeout in usec.
 * @return Modbus response string in JSON format.
 */
char * mbtcp_set_response_timeout(char * tid, long timeout);

/**
 * @brief Get mbtcp response timeout
 *
 * @param tid Transaction ID.
 * @return Modbus response string in JSON format.
 */
char * mbtcp_get_response_timeout(char * tid);

/**
 * @brief Modbus TCP Read coils.
 *
 * @param handle Mbtcp handle.
 * @param req cJSON request object.
 * @return Modbus response string in JSON format.
 */
char * mbtcp_fc1_req(mbtcp_handle_s *handle, cJSON *req);

/**
 * @brief Modbus TCP Read discrete input.
 *
 * @param handle Mbtcp handle.
 * @param req cJSON request object.
 * @return Modbus response string in JSON format.
 */
char * mbtcp_fc2_req(mbtcp_handle_s *handle, cJSON *req);

/**
 * @brief Modbus TCP Read holding registers.
 *
 * @param handle Mbtcp handle.
 * @param req cJSON request object.
 * @return Modbus response string in JSON format.
 */
char * mbtcp_fc3_req(mbtcp_handle_s *handle, cJSON *req);

/**
 * @brief Modbus TCP Read input registers.
 *
 * @param handle Mbtcp handle.
 * @param req cJSON request object.
 * @return Modbus response string in JSON format.
 */
char * mbtcp_fc4_req(mbtcp_handle_s *handle, cJSON *req);

/**
 * @brief Modbus TCP Write single coil.
 *
 * @param handle Mbtcp handle.
 * @param req cJSON request object.
 * @return Modbus response string in JSON format.
 */
char * mbtcp_fc5_req(mbtcp_handle_s *handle, cJSON *req);

/**
 * @brief Modbus TCP Write single register.
 *
 * @param handle Mbtcp handle.
 * @param req cJSON request object.
 * @return Modbus response string in JSON format.
 */
char * mbtcp_fc6_req(mbtcp_handle_s *handle, cJSON *req);

/**
 * @brief Modbus TCP Write multiple coils.
 *
 * @param handle Mbtcp handle.
 * @param req cJSON request object.
 * @return Modbus response string in JSON format.
 */
char * mbtcp_fc15_req(mbtcp_handle_s *handle, cJSON *req);

/**
 * @brief Modbus TCP Write multiple registers.
 *
 * @param handle Mbtcp handle.
 * @param req cJSON request object.
 * @return Modbus response string in JSON format.
 */
char * mbtcp_fc16_req(mbtcp_handle_s *handle, cJSON *req);

#endif  // MB_H