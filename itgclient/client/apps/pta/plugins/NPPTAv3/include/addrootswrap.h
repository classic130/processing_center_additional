//#include 
#include "ptav3.h"

EXTERN_C IVSRootsUpdate* AddRoots_CreateInstance();
EXTERN_C unsigned int AddRoots_Initialize(IVSRootsUpdate* pAddRoots);
EXTERN_C unsigned int AddRoots_CreateStandardTrustProfile(IVSRootsUpdate* pAddRoots);
EXTERN_C unsigned int AddRoots_CreateVerisignTrustProfile(IVSRootsUpdate* pAddRoots);
