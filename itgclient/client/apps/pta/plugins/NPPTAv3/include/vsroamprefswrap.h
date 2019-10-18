#include "roamprefs.h"
#include "ptav3.h"

EXTERN_C IVSRoamPrefs* RoamPrefs_GetInstance(IVSPTA* pPTA);


EXTERN_C unsigned int RoamPrefs_set_NumOfSrvrs(IVSRoamPrefs *pRoamPrefs, short NumOfSrvrs);
EXTERN_C short RoamPrefs_get_NumOfSrvrs (IVSRoamPrefs *pRoamPrefs);

EXTERN_C unsigned int RoamPrefs_set_StorageSrvr(IVSRoamPrefs *pRoamPrefs, wchar_t* pwstStorageSrvr, int nLen);
EXTERN_C wchar_t* RoamPrefs_get_StorageSrvr (IVSRoamPrefs *pRoamPrefs);

EXTERN_C unsigned int RoamPrefs_set_RoamingServers (IVSRoamPrefs *pRoamPrefs, wchar_t** stringArray, int* nLenArray, int arraySize);
EXTERN_C wchar_t** RoamPrefs_get_RoamingSrvrs (IVSRoamPrefs *pRoamPrefs, int* nLenArray);

EXTERN_C unsigned int RoamPrefs_set_ClientInfo(IVSRoamPrefs *pRoamPrefs, wchar_t* pwstClientInfo, int nLen);
EXTERN_C wchar_t* RoamPrefs_get_ClientInfo (IVSRoamPrefs *pRoamPrefs);

EXTERN_C unsigned int RoamPrefs_set_ClientInfoSig(IVSRoamPrefs *pRoamPrefs, wchar_t* pwstClientInfoSig, int nLen);
EXTERN_C wchar_t* RoamPrefs_get_ClientInfoSig (IVSRoamPrefs *pRoamPrefs);
