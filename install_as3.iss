; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
AppName = "HP_ID_Print_App"
AppVersion = 0.0.82
DefaultDirName = "C:\HP_ID_Print_App\"
AppCopyright = Copyright 2013 HP, Corp.
AppPublisher = HP, Corp.
AppPublisherURL = http://www.hp.com

[Types]

[Files]
Source: "C:\Users\yangboz\Documents\GitHub\petulant-octo-dubstep\MXML\Main\*.*"; DestDir: "{app}\"; Flags :ignoreversion recursesubdirs; CopyMode: alwaysoverwrite;
; NOTE: Don't use "Flags: ignoreversion" on any shared system files 

[Tasks] 
; NOTE: The following entry contains English phrases ("Create a desktop icon" and "Additional icons"). You are free to translate them into another language if required. 
Name: "desktopicon"; Description: "Create a &desktop icon"; GroupDescription: "Additional icons:" 

[Icons] Name: "{group}\HP_ID_Print_App"; Filename: "{app}\Main.exe" Name: "{userdesktop}\HP_ID_Print_App"; Filename: "{app}\Main.exe"; Tasks: desktopicon 

[INI]

;[Registry]

[UninstallDelete]

[Run]