/**
 * @file json.h
 * @author taka-wang
 * @brief cJSON utility wrapper header
*/

#ifndef JSON_H
#define JSON_H

#include "json/cJSON.h"

/**
 * @brief Get char string via key from cJSON object
 *
 * @param inJson cJSON object.
 * @param key Json key.
 * @return Char string.
 */
char * json_get_char(cJSON *inJson, const char *key);

/**
 * @brief Get integer value via key from cJSON object
 *
 * @param inJson cJSON object.
 * @param key Json key.
 * @return Integer.
 */
int json_get_int(cJSON *inJson, const char *key);


/**
 * @brief Set integer value via key to existed cJSON object
 *
 * @param inJson cJSON object.
 * @param key Json key.
 * @param Integer.
 * @return Void.
 */
void json_set_int(cJSON *inJson, const char *key, int value);

/**
 * @brief Get double value via key from cJSON object
 *
 * @param inJson cJSON object.
 * @param key Json key.
 * @return Double.
 */
double json_get_double(cJSON *inJson, const char *key);

/**
 * @brief Set double value via key to existed cJSON object
 *
 * @param inJson cJSON object.
 * @param key Json key.
 * @param Double.
 * @return Void.
 */
void json_set_double(cJSON *inJson, const char *key, double value);

/**
 * @brief Get long value via key from cJSON object
 *
 * @param inJson cJSON object.
 * @param key Json key.
 * @return Long.
 */
long json_get_long(cJSON *inJson, const char *key);

/**
 * @brief Get unsigned long value via key from cJSON object
 *
 * @param inJson cJSON object.
 * @param key Json key.
 * @return unsigned long.
 */
unsigned long json_get_ulong(cJSON *inJson, const char *key);

/**
 * @brief Load json file to cJSON
 *
 * @param fname File name string.
 * @param outJson Pointer to cJSON output object.
 * @return Success or not. 
 */ 
int file_to_json(const char *fname, cJSON **outJson);

/**
 * @brief Save cJSON to json file
 *
 * @param fname File name string.
 * @param inJson cJSON input object.
 * @return Success or not. 
 */
int json_to_file(const char *fname, cJSON *inJson);

#endif // JSON_H