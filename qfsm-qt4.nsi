; Qfsm-Qt4.nsi

!include "registerExtension.nsh"
!include "FileFunc.nsh"

!insertmacro RefreshShellIcons
!insertmacro un.RefreshShellIcons


Name "qfsm-qt4-2015-01-25"

; The file to write
OutFile "qfsm-0.54.exe"

; The default installation directory
InstallDir $PROGRAMFILES\Qfsm

InstallDirRegKey HKLM "Software\Qfsm" "Install_Dir"

; Request application privileges for Windows Vista
RequestExecutionLevel admin
SetOverWrite try

Icon "desktop/qfsm.ico"

;--------------------------------

; Pages

Page directory
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

;--------------------------------


; The stuff to install
Section "installation"

  SectionIn RO
  
  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  
  ; Put file there
  File /r *.*
  
  ; Write the installation path into the registry
  WriteRegStr HKLM SOFTWARE\Qfsm "Install_Dir" "$INSTDIR"
  
  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Qfsm" "DisplayName" "Qfsm"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Ex" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Qfsm" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Qfsm" "NoRepair" 1
  WriteUninstaller "uninstall.exe"
  
SectionEnd

;Start Menu

Section "Start Menu Shortcuts"

  CreateDirectory "$SMPROGRAMS\Qfsm"
  CreateShortCut "$SMPROGRAMS\Qfsm\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
  CreateShortCut "$SMPROGRAMS\Qfsm\Qfsm.lnk" "$INSTDIR\qfsm.exe" "" "$INSTDIR\qfsm.ico"
  
SectionEnd


Section "FSM Extension"

  ${registerExtension} "$INSTDIR\qfsm.exe" ".fsm" "Qfsm File"
  WriteRegStr HKCR "Qfsm File\DefaultIcon" "" "$INSTDIR\qfsm.exe,1" 
  ${RefreshShellIcons}
SectionEnd


; Uninstaller

Section "Uninstall"
  
  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Qfsm"
  DeleteRegKey HKLM SOFTWARE\Qfsm

  ; Unregister extension
  ${unregisterExtension} ".fsm" "Qfsm File"

  ; Remove files and uninstaller
  Delete $INSTDIR\*.*
  Delete $INSTDIR\doc\user\*.*
  Delete $INSTDIR\examples\*.*
  Delete $INSTDIR\po\*.*


  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\Qfsm\*.*"

  ; Remove directories used
  RMDir "$SMPROGRAMS\Qfsm"
  RMDir "$INSTDIR\doc\user"
  RMDir "$INSTDIR\doc"
  RMDir "$INSTDIR\examples"
  RMDir "$INSTDIR\po"
  RMDir "$INSTDIR"

  ${un.RefreshShellIcons}

SectionEnd
