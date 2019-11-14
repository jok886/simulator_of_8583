; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CLeftViewOne
LastTemplate=CTreeView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "PSAMOPDEMO.h"
LastPage=0

ClassCount=10
Class1=CPSAMOPDEMOApp
Class2=CPSAMOPDEMODoc
Class3=CPSAMOPDEMOView
Class4=CMainFrame
Class9=CAboutDlg

ResourceCount=5
Resource1=IDR_TOOLBAR1
Resource2=IDR_MAINFRAME
Resource3=IDD_DIALOG1
Resource4=IDD_ABOUTBOX
Class10=CLeftViewOne
Resource5=IDD_DIALOG2

[CLS:CPSAMOPDEMOApp]
Type=0
HeaderFile=PSAMOPDEMO.h
ImplementationFile=PSAMOPDEMO.cpp
Filter=N

[CLS:CPSAMOPDEMODoc]
Type=0
HeaderFile=PSAMOPDEMODoc.h
ImplementationFile=PSAMOPDEMODoc.cpp
Filter=N

[CLS:CPSAMOPDEMOView]
Type=0
HeaderFile=PSAMOPDEMOView.h
ImplementationFile=PSAMOPDEMOView.cpp
Filter=C


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T




[CLS:CAboutDlg]
Type=0
HeaderFile=PSAMOPDEMO.cpp
ImplementationFile=PSAMOPDEMO.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_OPEN
Command2=ID_APP_EXIT
Command3=MENU_POWERON
Command4=MEMU_SET_DELAY
Command5=MENU_POWEROFF
Command6=MENU_CARD_RESET
Command7=MENU_CARD_IN
Command8=MENU_PSAM_CMD
Command9=MEMU_CREATE_MF
Command10=MENU_SELECT_MF
Command11=MENU_CREATE_EF_CARD_KEY
Command12=MENU_WRITE_EF_MK
Command13=MENU_CREATE_EF_DIR
Command14=MENU_WRITE_EF_DIR
Command15=MENU_CREATE_EF_PUB
Command16=MENU_WRITE_EF_PUB
Command17=MENU_CREATE_DF_APP
Command18=MENU_CREATE_ADF_KEY_FILE
Command19=MENU_WRITE_ADF_WORK_KEY
Command20=MENU_WRITE_APP_MK
Command21=MENU_END_CREATE_MF
Command22=MENU_END_CREATE_ADF
Command23=MENU_MAKE_NEW_CARD
Command24=MENU_SETTING_ENV
Command25=MENU_WASH_CARD
Command26=MENU_FILLL_AWK
Command27=MENU_CHANGE_AWK
Command28=ID_VIEW_TOOLBAR
Command29=ID_VIEW_STATUS_BAR
Command30=ID_APP_ABOUT
CommandCount=30

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_VIEW_LARGEICON
Command9=ID_VIEW_SMALLICON
Command10=ID_VIEW_LIST
Command11=ID_VIEW_DETAILS
Command12=ID_APP_ABOUT
Command13=TB_SHUT_COM1
CommandCount=13

[TB:IDR_TOOLBAR1]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_FILE_SAVE
Command3=ID_APP_ABOUT
Command4=MENU_MAKE_NEW_CARD
Command5=MENU_WASH_CARD
Command6=MENU_FILLL_AWK
Command7=TB_Check_Card
Command8=TB_SHUT_COM1
CommandCount=8

[DLG:IDD_DIALOG1]
Type=1
Class=?
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1352728644
Control4=IDC_EDIT2,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,button,1342177287
Control8=EDT_COMX,edit,1350631552
Control9=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG2]
Type=1
Class=?
ControlCount=27
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,static,1342308352
Control5=EDT_ENCRYPTOR_IP,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=EDT_ENCRYPTOR_PORT,edit,1350631552
Control8=IDC_STATIC,button,1342177287
Control9=IDC_STATIC,static,1342308352
Control10=EDT_PSAM_SID,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=EDT_PSAM_CMK,edit,1350631584
Control13=IDC_STATIC,static,1342308352
Control14=EDT_PSAM_AMK,edit,1350631584
Control15=IDC_STATIC,static,1342308352
Control16=EDT_ENCRYPTOR_TMK_IND,edit,1350631552
Control17=IDC_STATIC,static,1342308352
Control18=EDT_ENCRYPTOR_TTK_IND,edit,1350631552
Control19=IDC_STATIC,button,1342177287
Control20=EDT_COMX,edit,1350631552
Control21=IDC_STATIC,static,1342308352
Control22=EDT_PSAM_CMK2,edit,1350631584
Control23=EDT_PSAM_AMK2,edit,1350631584
Control24=EDT_ENCRYPTOR_TMK_GRP,edit,1350631552
Control25=EDT_ENCRYPTOR_TTK_GRP,edit,1350631552
Control26=EDT_ENCRYPTOR_TMK_VER,edit,1350631552
Control27=EDT_ENCRYPTOR_TTK_VER,edit,1350631552

[CLS:CLeftViewOne]
Type=0
HeaderFile=LeftViewOne.h
ImplementationFile=LeftViewOne.cpp
BaseClass=CTreeView
Filter=C

