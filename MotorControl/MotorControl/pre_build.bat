
rem generate settings
cd /D ".\Configurations\MCUConfiguration"
C:\Python36\python.exe "generate_mcu_configuration_sources.py"
IF %ERRORLEVEL% NEQ 0 exit 2

