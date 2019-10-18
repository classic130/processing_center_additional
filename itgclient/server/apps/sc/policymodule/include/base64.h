#ifndef _BASE64_H_
#define _BASE64_H_

#ifdef __cplusplus
extern "C" {
#endif

char * Base64Encode(const char *str, unsigned int iLen);

char * Base64Decode(const char *str, unsigned int *oLen);

#ifdef  __cplusplus
}
#endif

#endif /* _BASE64_H */
