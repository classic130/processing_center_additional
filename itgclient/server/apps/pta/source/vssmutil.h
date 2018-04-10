/* 
 * vssmutil.h
 * 
 * Header file for utility functions used for PTA Siteminder authentication scheme
 * 
 */
#ifdef __cplusplus
extern "C" {
#endif
int vsSmAuthInit(const char * lpszServerParam);
int vsSmAuthQuery(char * buffer,const char*   lpszSharedSecret);
int vsSmAuthenticate(const char *postedToSign,const char * postedSignature,char * outBuffer, int maxBufferLen, const char*   lpszSharedSecret);
void vsSmAuthRelease();
#ifdef __cplusplus
}
#endif
