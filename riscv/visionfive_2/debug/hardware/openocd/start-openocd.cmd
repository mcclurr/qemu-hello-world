@echo off

set "SCRIPT_DIR=%~dp0"

openocd -f "%SCRIPT_DIR%visionfive2.cfg"

pause