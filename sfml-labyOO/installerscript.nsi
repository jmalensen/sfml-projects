; Define the name and output file for the installer
Name "SFML Laby Appli Installer"
OutFile "SFMLLabyAppliInstaller.exe"

; Define the default installation directory
InstallDir "$PROGRAMFILES\SFML Laby Appli"

; Define the pages displayed in the installer
Page directory
Page instfiles

; Define the custom icon for the installer
Icon "bin\labyicon.ico"

; Define the dependencies
Section "VC++ Redistributable"
  SetOutPath $INSTDIR
  
	; Check if the Visual C++ Redistributable is already installed
  ReadRegStr $0 HKLM "SOFTWARE\Microsoft\VisualStudio\14.0\VC\Runtimes\x64" "Version"
  StrCmp $0 "" VCRedistNotInstalled

  ; If the Visual C++ Redistributable is installed, display a message
  MessageBox MB_OK "The installed version of vc_redist is usable."
  Goto VCRedistEnd

	VCRedistNotInstalled:
		; If the Visual C++ Redistributable is not installed, copy it to the installation directory
		;File "dependencies\vc_redist_x86.exe"
		File "dependencies\vc_redist_x64.exe"

		; Install the Visual C++ Redistributable
		;ExecWait '"$INSTDIR\vc_redist_x86.exe" /install /passive /norestart'
		ExecWait '"$INSTDIR\vc_redist_x64.exe" /install /passive /norestart'

		; Delete the Visual C++ Redistributable from the installation directory
		;Delete "$INSTDIR\vc_redist_x86.exe"
		Delete "$INSTDIR\vc_redist_x64.exe"
	VCRedistEnd:

SectionEnd

; Define the sections of the installer
Section "SFML Laby Appli"
  SetOutPath $INSTDIR

  ; Copy the SFML libraries
  File "C:\Devc++\SFML-2.5.1\bin\*.*"

	; Copy the application's executable
  File "bin\sfml-labyOO.exe"

	; Copy the application's icon
  File "bin\labyicon.ico"

	; Copy the specific dependencies
  ;File "bin\libgcc_s_seh-1.dll"

  ; Write the installation directory to the registry
  WriteRegStr HKLM "Software\SFML Laby Appli" "Install_Dir" "$INSTDIR"

	WriteUninstaller $INSTDIR\uninstaller.exe

	; Create a shortcut to the application in the Start menu
  CreateDirectory "$SMPROGRAMS\SFML Laby Appli"
  CreateShortCut "$SMPROGRAMS\SFML Laby Appli\SFML Laby Appli.lnk" "$INSTDIR\sfml-labyOO.exe" "" "$INSTDIR\labyicon.ico"
  CreateShortCut "$SMPROGRAMS\SFML Laby Appli\Uninstaller SFML Laby Appli.lnk" "$INSTDIR\uninstaller.exe"
SectionEnd

; Define the uninstaller
Section Uninstall
	; Remove the Start menu shortcut
  Delete "$SMPROGRAMS\SFML Laby Appli\SFML Laby Appli.lnk"
  Delete "$SMPROGRAMS\SFML Laby Appli\Uninstaller SFML Laby Appli.lnk"
  RMDir "$SMPROGRAMS\SFML Laby Appli"

  ; Remove the installation directory
  RMDir /r $INSTDIR

  ; Remove the registry key
  DeleteRegKey HKLM "Software\SFML Laby Appli"
SectionEnd

; Define the configs
Section "Config"
  SetOutPath $INSTDIR\config

  ; Copy the config files
  File "bin\config\*.*"
SectionEnd

; Define the fonts
Section "Fonts"
  SetOutPath $INSTDIR\fonts

  ; Copy the font files
  File "bin\fonts\*.*"
SectionEnd

; Define the images
Section "Images"
  SetOutPath $INSTDIR\images

  ; Copy the images files
  File "bin\images\*.*"
SectionEnd

; Define the sounds
Section "Sounds"
  SetOutPath $INSTDIR\sounds

  ; Copy the sound files
  File "bin\sounds\*.*"
SectionEnd

; The installer is ready, now compile it using NSIS