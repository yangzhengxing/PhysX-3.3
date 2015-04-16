@echo off

call get_extension_settings.bat

set CMD=%EXE% %COMMON_FLAGS% %ANDROID_DEFINES% %INCLUDES% %ANDROID_SYS_PATH% %SRCPATH% -o %TARGETDIR%
echo %CMD% >>clangCommandLine_android.txt
%CMD%

set TARGETDIR=

EXIT /B %ERRORLEVEL% 

	