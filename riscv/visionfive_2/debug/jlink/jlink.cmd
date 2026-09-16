@echo off

"C:\Program Files\SEGGER\JLink_V976\JLink.exe" ^
  -JLinkScriptFile "%~dp0jlink_u74.JLinkScript" ^
  -device U74-MC ^
  -if JTAG ^
  -speed 100 ^
  -jtagconf -1,-1 ^
  -AutoConnect 1

pause