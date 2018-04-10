; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "vsscode.h"
LastPage=0

ClassCount=6
Class1=CVsscodeApp
Class2=CVsscodeDoc
Class3=CVsscodeView
Class4=CMainFrame

ResourceCount=4
Resource1=IDD_DLG_CERTIFICATE
Class5=CAboutDlg
Resource2=IDD_ABOUTBOX
Class6=CDlgCSR
Resource3=IDR_MAINFRAME
Resource4=IDD_TIME

[CLS:CVsscodeApp]
Type=0
HeaderFile=vsscode.h
ImplementationFile=vsscode.cpp
Filter=N

[CLS:CVsscodeDoc]
Type=0
HeaderFile=vsscodeDoc.h
ImplementationFile=vsscodeDoc.cpp
Filter=N

[CLS:CVsscodeView]
Type=0
HeaderFile=vsscodeView.h
ImplementationFile=vsscodeView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CVsscodeView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_CHANGE_PASSWD
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=vsscode.cpp
ImplementationFile=vsscode.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342308480
Control2=IDC_STATIC,static,1342308352
Control3=IDOK,button,1342373889
Control4=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_CREATE_CSR
Command2=ID_INSTALL_CERT
Command3=ID_IMPORT_CERT
Command4=ID_EXPORT_CERT
Command5=ID_APP_EXIT
Command6=ID_ONLY_SIGN
Command7=ID_SIGN_FILE
Command8=ID_SIGNATURE_PROPERTIES
Command9=ID_CHANGE_PASSWD
Command10=ID_APP_ABOUT
CommandCount=10

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[CLS:CDlgCSR]
Type=0
HeaderFile=DlgCSR.h
ImplementationFile=DlgCSR.cpp
BaseClass=CDialog
Filter=D
LastObject=IDOK
VirtualFilter=dWC

[DLG:IDD_DLG_CERTIFICATE]
Type=1
Class=CDlgCSR
ControlCount=4
Control1=IDE_CERTIFICATE,edit,1352736836
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_DESC,static,1342308352

[DLG:IDD_TIME]
Type=1
Class=?
ControlCount=4
Control1=IDC_CURRENT_TIME,button,1342308361
Control2=IDC_DIFF_TIME,button,1342177289
Control3=IDC_DATETIME,SysDateTimePick32,1342242857
Control4=IDC_STATIC,static,1342308352

