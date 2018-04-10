//-----------------------------------------------------------------------------
//
// GPEDIT.H - Definitions and prototypes for Group Policy
//
// Copyright 1997-1998, Microsoft Corporation
//
//-----------------------------------------------------------------------------

//
// Terminology
//
// Group Policy Editor  -  The tool to view a Group Policy Object.
//
// Group Policy Object  -  A collection of administrator defined policies.
//                         Each Group Policy Object (GPO) has both file system
//                         and Active Directory storage available to it.
//
// IGPEInformation      -  The interface MMC Snapin Extensions use to
//                         talk to the Group Policy Editor.
//


//
// Group Policy Editor MMC SnapIn GUID
//
// {8FC0B734-A0E1-11d1-A7D3-0000F87571E3}

DEFINE_GUID(CLSID_GPESnapIn, 0x8fc0b734, 0xa0e1, 0x11d1, 0xa7, 0xd3, 0x0, 0x0, 0xf8, 0x75, 0x71, 0xe3);


//
// Group Policy Editor node ids
//

// Root of the name space  --  {8FC0B736-A0E1-11d1-A7D3-0000F87571E3}
DEFINE_GUID(NODEID_GPERoot, 0x8fc0b736, 0xa0e1, 0x11d1, 0xa7, 0xd3, 0x0, 0x0, 0xf8, 0x75, 0x71, 0xe3);

// Computer Settings       --  {8FC0B737-A0E1-11d1-A7D3-0000F87571E3}
DEFINE_GUID(NODEID_Machine, 0x8fc0b737, 0xa0e1, 0x11d1, 0xa7, 0xd3, 0x0, 0x0, 0xf8, 0x75, 0x71, 0xe3);

// User Settings           --  {8FC0B738-A0E1-11d1-A7D3-0000F87571E3}
DEFINE_GUID(NODEID_User, 0x8fc0b738, 0xa0e1, 0x11d1, 0xa7, 0xd3, 0x0, 0x0, 0xf8, 0x75, 0x71, 0xe3);


//
// IGPEInformation interface id
//
// {8FC0B735-A0E1-11d1-A7D3-0000F87571E3}

DEFINE_GUID(IID_IGPEInformation, 0x8fc0b735, 0xa0e1, 0x11d1, 0xa7, 0xd3, 0x0, 0x0, 0xf8, 0x75, 0x71, 0xe3);


#ifndef _GPEDIT_H_
#define _GPEDIT_H_

#include <objbase.h>


//
// Group Policy Object Section flags
//

#define GPO_SECTION_ROOT                 0  // Root
#define GPO_SECTION_USER                 1  // User
#define GPO_SECTION_MACHINE              2  // Machine


//
// Group Policy Editor option flags
//

#define GPE_OPTION_ADVANCED     0x00000001  // Show advanced features
#define GPE_OPTION_NOCONFIRM    0x00000002  // No confirmation dialogs


//
// Group Policy Object types
//

typedef enum _GROUP_POLICY_OBJECT_TYPE {
    GPOTypeLocal = 0,                       // GPO on the local machine
    GPOTypeRemote,                          // GPO on a remote machine
    GPOTypeDS                               // GPO in the DS
} GROUP_POLICY_OBJECT_TYPE, *PGROUP_POLICY_OBJECT_TYPE;


//
// Group Policy Hint types
//

typedef enum _GROUP_POLICY_HINT_TYPE {
    GPHintUnknown = 0,                      // No link information available
    GPHintMachine,                          // GPO linked to a machine (local or remote)
    GPHintSite,                             // GPO linked to a site
    GPHintDomain,                           // GPO linked to a domain
    GPHintOrganizationalUnit                // GPO linked to a organizational unit
} GROUP_POLICY_HINT_TYPE, *PGROUP_POLICY_HINT_TYPE;


#undef INTERFACE
#define INTERFACE   IGPEInformation
DECLARE_INTERFACE_(IGPEInformation, IUnknown)
{
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;


    // *** IGPEInformation methods ***

    //
    // Returns the unique Group Policy Object name (a GUID)
    //
    // pszName contains the name on return
    // cchMaxLength is the max number of characters that can be stored in pszName
    //

    STDMETHOD(GetName) (THIS_ LPOLESTR pszName, int cchMaxLength) PURE;


    //
    // Returns the friendly display name for this Group Policy Object
    //
    // pszName contains the name on return
    // cchMaxLength is the max number of characters that can be stored in pszName
    //

    STDMETHOD(GetDisplayName) (THIS_ LPOLESTR pszName, int cchMaxLength) PURE;


    //
    // Returns a registry key handle for the requested section.  The returned
    // key is the root of the registry, not the Policies subkey.  To set / read
    // a value in the Policies subkey, you will need to call RegOpenKeyEx to
    // open Software\Policies subkey first.
    //
    // The handle has been opened with ALL ACCESS rights.  Call RegCloseKey
    // on the handle when finished.
    //
    // dwSection is either GPO_SECTION_USER or GPO_SECTION_MACHINE
    // hKey contains the registry key on return
    //

    STDMETHOD(GetRegistryKey) (THIS_ DWORD dwSection, HKEY *hKey) PURE;


    //
    // Returns the Active Directory path to the root of the request section.
    // The path is in ADSI name format.
    //
    // dwSection is one of the GPO_SECTION_* flags
    // pszPath contains the path on return
    // cchMaxPath is the max number of characters that can be stored in pszPath
    //

    STDMETHOD(GetDSPath) (THIS_ DWORD dwSection, LPOLESTR pszPath, int cchMaxPath) PURE;


    //
    // Returns the UNC path to the root of the requested section.
    //
    // dwSection is one of the GPO_SECTION_* flags
    // pszPath contains the path on return
    // cchMaxPath is the number of characters that can be stored in pszPath.
    //

    STDMETHOD(GetFileSysPath) (THIS_ DWORD dwSection, LPOLESTR pszPath, int cchMaxPath) PURE;


    //
    // Returns the user preferences (options)
    //
    // For example:  Show advanced features, Disable confirmation dialogs
    //
    // dwOptions receives the GPE_OPTION_* flags
    //

    STDMETHOD(GetOptions) (THIS_ DWORD *dwOptions) PURE;


    //
    // Returns the type of GPO being edited.
    //
    // The three types are:  a GPO in the DS, the GPO on the local machine,
    // and the GPO on a remote machine.
    //
    // Machine GPOs only have file system storage (no DS storage available).
    // If GetDSPath is called for a machine GPO, the function will succeed
    // and the returned buffer will be the empty string ""
    //
    // DS GPOs have both file system and DS storage available to them.
    //
    // gpoType receives one of the type flags listed above.
    //

    STDMETHOD(GetType) (THIS_ GROUP_POLICY_OBJECT_TYPE *gpoType) PURE;


    //
    // Returns the type of DS object (or machine) that could be linked to
    // this GPO
    //
    // This is a hint api only.  The GPE does not know which DS objects are
    // linked to a particular GPO, but it can offer a hint based upon how the
    // user started the GPE.
    //
    // Use this method with great caution.  Some extensions might want to
    // customize their user interface based upon the scoping for this GPO,
    // but it is easy to offer the wrong namespace.  Best advice is to
    // always offer your full user interface, but if you choose to use this
    // method, always offer your full user interface if you recieve the
    // unknown hint back.
    //
    // gpHint receives one of the hint flags listed above.
    //

    STDMETHOD(GetHint) (THIS_ GROUP_POLICY_HINT_TYPE *gpHint) PURE;


    //
    // Informs the Group Policy Editor that policy settings have changed.
    // Extensions MUST call this methold every time a change is made
    // to a Group Policy Object.
    //

    STDMETHOD(PolicyChanged) (THIS_) PURE;
};
typedef IGPEInformation *LPGPEINFORMATION;


#endif  /* _GPEDIT_H_ */
