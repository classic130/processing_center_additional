/**
*  Header file for Solaris based CRL Thread
**/

/**
*   Function to start the thread which refreshes the CRL at predefined intervals.
**/
#include "vsvalsdk.h"

int vs_cvm_genlib_start_crl_thread(unsigned long int *globalLastUpdate, 
								   unsigned long int globalUpdateSeconds, 
								   int globalLogInfo, 
								   VSVAL_SDK *globalValSDK);

/**
*   Function to stop the thread and release critical sections.
**/
void vs_cvm_genlib_stop_crl_thread();

/**
*   Function to create mutexes.
**/
int vs_cvm_genlib_create_mutexes();

