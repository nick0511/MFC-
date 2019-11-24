; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPvDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "pv.h"

ClassCount=3
Class1=CPvApp
Class2=CPvDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_PV_DIALOG

[CLS:CPvApp]
Type=0
HeaderFile=pv.h
ImplementationFile=pv.cpp
Filter=N

[CLS:CPvDlg]
Type=0
HeaderFile=pvDlg.h
ImplementationFile=pvDlg.cpp
Filter=D
LastObject=CPvDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=pvDlg.h
ImplementationFile=pvDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_PV_DIALOG]
Type=1
Class=CPvDlg
ControlCount=6
Control1=Father,button,1342242816
Control2=Daughter,button,1342242816
Control3=Mom,button,1342242816
Control4=Son,button,1342242816
Control5=IDC_STATIC,static,1342308865
Control6=Pan,static,1342308865

