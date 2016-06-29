/**
 * @file json.c
 * @author taka-wang
 * @brief cJSON utility wrapper header
*/

#include <stdio.h>
#include <stdlib.h>
#include "json.h"

char *json_get_char(cJSON *inJson, const char *key)
{
    return cJSON_GetObjectItem(inJson, key)->valuestring;
}

int json_get_int(cJSON *inJson, const char *key)
{
    return cJSON_GetObjectItem(inJson, key)->valueint;
}

void json_set_int(cJSON *inJson, const char *key, int value)
{
    cJSON_GetObjectItem(inJson, key)->valueint = value;
}

double json_get_double(cJSON *inJson, const char *key)
{
    return cJSON_GetObjectItem(inJson, key)->valuedouble;
}

void json_set_double(cJSON *inJson, const char *key, double value)
{
    cJSON_GetObjectItem(inJson, key)->valuedouble = value;
}

int file_to_json(const char *fname, cJSON **outJson)
{
    FILE *fPtr = fopen(fname,"rb");
    if (fPtr) 
    {
        fseek(fPtr, 0, SEEK_END);
        long len = ftell(fPtr);
        fseek(fPtr, 0, SEEK_SET);
        char *data = (char*) malloc (len+1);
        int _ = fread(data, 1, len, fPtr); _=_;
        fclose(fPtr);
        *outJson = cJSON_Parse(data);
        free(data);
        return outJson ? 0 : 1;
    }
    else
    {
        return -1;
    }
}

int json_to_file(const char *fname, cJSON *inJson)
{
    FILE *fPtr = fopen(fname, "w");
    if (fPtr)
    {
        fprintf(fPtr, "%s", cJSON_Print(inJson));
        fclose(fPtr);
        return 0;
    }
    else
    {
        return -1;
    }
}
