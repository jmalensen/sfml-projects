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

; Define the sections of the installer
Section "SFML Laby Appli"
  SetOutPath $INSTDIR

  ; Copy the SFML libraries
  File "C:\Devc++\SFML-2.5.1\bin\*.*"

	; Copy the application's executable
  File "bin\sfml-labyOO.exe"

	; Copy the application's icon
  File "bin\labyicon.ico"

  ; Install the Visual C++ Redistributable
  ExecWait '"$INSTDIR\vc_redist_x64.exe" /install /quiet /norestart'

  ; Write the installation directory to the registry
  WriteRegStr HKLM "Software\SFML Laby Appli" "Install_Dir" "$INSTDIR"

	WriteUninstaller $INSTDIR\uninstaller.exe
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

; Define the dependencies
Section "VC++ Redistributable"
  SetOutPath $INSTDIR
  
  ; Copy the Visual C++ Redistributable to the installation directory
  File "dependencies\vc_redist_x64.exe"
SectionEnd

; Define the uninstaller
Section Uninstall
  ; Remove the installation directory
  RMDir /r $INSTDIR

  ; Remove the registry key
  DeleteRegKey HKLM "Software\SFML Laby Appli"
SectionEnd

; The installer is ready, now compile it using NSIS