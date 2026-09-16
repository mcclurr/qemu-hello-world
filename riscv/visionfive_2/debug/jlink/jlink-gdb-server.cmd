@echo off

"C:\Program Files\SEGGER\JLink_V976\JLinkGDBServerCL.exe" ^
  -JLinkScriptFile "%~dp0jlink_u74.JLinkScript" ^
  -device U74-MC ^
  -if JTAG ^
  -speed 100 ^
  -port 2331 ^
  -nolocalhostonly

pause