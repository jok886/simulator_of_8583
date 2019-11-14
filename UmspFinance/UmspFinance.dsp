# Microsoft Developer Studio Project File - Name="UmspFinance" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=UmspFinance - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "UmspFinance.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "UmspFinance.mak" CFG="UmspFinance - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "UmspFinance - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "UmspFinance - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "UmspFinance - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "UmspFinance - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "UmspFinance - Win32 Release"
# Name "UmspFinance - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Des.cpp
# End Source File
# Begin Source File

SOURCE=.\EncryptorRelate.cpp
# End Source File
# Begin Source File

SOURCE=.\HDSYC8583Digram.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TransLogDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\TransLogView.cpp
# End Source File
# Begin Source File

SOURCE=.\UmspAdap.cpp
# End Source File
# Begin Source File

SOURCE=.\UmspCliAdap.cpp
# End Source File
# Begin Source File

SOURCE=.\UmspEBAdap.cpp
# End Source File
# Begin Source File

SOURCE=.\UmspEBTrans.cpp
# End Source File
# Begin Source File

SOURCE=.\UmspEnvironment.cpp
# End Source File
# Begin Source File

SOURCE=.\UmspFinance.cpp
# End Source File
# Begin Source File

SOURCE=.\UmspFinance.rc
# End Source File
# Begin Source File

SOURCE=.\UmspFinanceDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\UmspFinanceView.cpp
# End Source File
# Begin Source File

SOURCE=.\UmspFormat.cpp
# End Source File
# Begin Source File

SOURCE=.\UmspInitEnv.cpp
# End Source File
# Begin Source File

SOURCE=.\UmspPOSPAdap.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\CommonHead.h
# End Source File
# Begin Source File

SOURCE=.\Des.h
# End Source File
# Begin Source File

SOURCE=.\EncryptorRelate.h
# End Source File
# Begin Source File

SOURCE=.\HDSYC8583Digram.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TransLogDoc.h
# End Source File
# Begin Source File

SOURCE=.\TransLogView.h
# End Source File
# Begin Source File

SOURCE=.\UmspAdap.h
# End Source File
# Begin Source File

SOURCE=.\UmspCliAdap.h
# End Source File
# Begin Source File

SOURCE=.\UmspEBAdap.h
# End Source File
# Begin Source File

SOURCE=.\UmspEBTrans.h
# End Source File
# Begin Source File

SOURCE=.\UmspEnvironment.h
# End Source File
# Begin Source File

SOURCE=.\umspErrorCode.h
# End Source File
# Begin Source File

SOURCE=.\UmspFinance.h
# End Source File
# Begin Source File

SOURCE=.\UmspFinanceDoc.h
# End Source File
# Begin Source File

SOURCE=.\UmspFinanceView.h
# End Source File
# Begin Source File

SOURCE=.\UmspFormat.h
# End Source File
# Begin Source File

SOURCE=.\UmspInitEnv.h
# End Source File
# Begin Source File

SOURCE=.\UmspPOSPAdap.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\UmspFinance.ico
# End Source File
# Begin Source File

SOURCE=.\res\UmspFinance.rc2
# End Source File
# Begin Source File

SOURCE=.\res\UmspFinanceDoc.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
