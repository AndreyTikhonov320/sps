
rem generate settings
cd /D ".\Configurations\MCUConfiguration"
C:\Python36\python.exe "generate_mcu_configuration_sources.py"

rem generate parameters json
cd /D "..\..\Modules\Parameters"
C:\Python36\python.exe "sps_parameters.py"

IF %ERRORLEVEL% NEQ 0 exit 2

