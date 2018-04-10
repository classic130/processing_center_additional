/**
*  Header file for Logging
**/

#include <stdio.h>

void vs_cvm_genlib_set_fp(FILE *logFP);
void vs_cvm_genlib_log_message(char* severity, char *fmt, ...);
void vs_cvm_genlib_sdk_log_message(void* handle, char *fmt, ...);
void vs_cvm_genlib_sdk_log_null_message(void* handle, char *fmt, ...);

