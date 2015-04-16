@echo off

set EXTERNALS=%~p0
:externalsLoop
if exist "%EXTERNALS%\externals" goto :haveExtnalsPath
set EXTERNALS=%EXTERNALS%..\
goto :externalsLoop

:haveExtnalsPath

rem Find SDK_ROOT by searching backwards from cwd for SDKs
set SDK_ROOT=%~p0
:sdkloop
if exist "%SDK_ROOT%\Source" goto :havesdkpath
set SDK_ROOT=%SDK_ROOT%..\
goto :sdkloop

:havesdkpath

if not defined NDK_VERSION (set NDK_VERSION=android-ndk-r9d)
if not defined NDK_ROOT (set NDK_ROOT=%EXTERNALS%\externals)

set NDK_GCC_VER=4.8
set ANDROID_PLATFORM=android-9
set NDK_CURRENT=%NDK_ROOT%\%NDK_VERSION%\platforms\%ANDROID_PLATFORM%

set INCLUDES=-I"%SDK_ROOT%/Include/foundation"
set INCLUDES=%INCLUDES% -I"%SDK_ROOT%/Include/physxprofilesdk"
set INCLUDES=%INCLUDES% -I"%SDK_ROOT%/Include/physxvisualdebuggersdk"
set INCLUDES=%INCLUDES% -I"%SDK_ROOT%/pxtask/include"
set INCLUDES=%INCLUDES% -I"%SDK_ROOT%/Include/common"		
set INCLUDES=%INCLUDES% -I"%SDK_ROOT%/Include/geometry"		
set INCLUDES=%INCLUDES% -I"%SDK_ROOT%/Include/pvd"		
set INCLUDES=%INCLUDES% -I"%SDK_ROOT%/Include/particles"		
set INCLUDES=%INCLUDES% -I"%SDK_ROOT%/Include/cloth"		
set INCLUDES=%INCLUDES% -I"%SDK_ROOT%/Include/physxvisualdebuggersdk"
set INCLUDES=%INCLUDES% -I"%SDK_ROOT%/Include/gpu"
set INCLUDES=%INCLUDES% -I"%SDK_ROOT%/Include"
set INCLUDES=%INCLUDES% -I"%SDK_ROOT%/Source/PhysXCommon/src"		
set INCLUDES=%INCLUDES% -I"%SDK_ROOT%/Source/GeomUtils/headers"		
set INCLUDES=%INCLUDES% -I"%SDK_ROOT%/Source/GeomUtils/src"		
set INCLUDES=%INCLUDES% -I"%SDK_ROOT%/Source/GeomUtils/Opcode"		
set INCLUDES=%INCLUDES% -I"%SDK_ROOT%/Source/PhysX/src"
set INCLUDES=%INCLUDES% -I"%SDK_ROOT%/Source/PhysX/src/buffering"
set INCLUDES=%INCLUDES% -I"%SDK_ROOT%/Source/PhysX/src/particles"
set INCLUDES=%INCLUDES% -I"%SDK_ROOT%/Source/PhysX/src/cloth"		
set INCLUDES=%INCLUDES% -I"%SDK_ROOT%/Source/SimulationController/src"		
set INCLUDES=%INCLUDES% -I"%SDK_ROOT%/Source/SimulationController/src/framework"	
set INCLUDES=%INCLUDES% -I"%SDK_ROOT%/Source/SimulationController/include"		
set INCLUDES=%INCLUDES% -I"%SDK_ROOT%/Source/PhysXCooking/include"		
set INCLUDES=%INCLUDES% -I"%SDK_ROOT%/Source/SceneQuery"		
set INCLUDES=%INCLUDES% -I"%SDK_ROOT%/Source/PvdRuntime/src"		
set INCLUDES=%INCLUDES% -I"%SDK_ROOT%/Source/PhysXMetaData/core/include"	
set INCLUDES=%INCLUDES% -I"%SDK_ROOT%/Source/PhysXGpu/include"
set INCLUDES=%INCLUDES% -I"%SDK_ROOT%/Tools/PhysXMetaDataGenerator"
                          
set XBOX360_SYS_PATH=-isystem"%XEDK%/include/xbox"

set XBOXONE_SYS_PATH=-isystem"%Console_SdkIncludeRoot%/um"
set XBOXONE_SYS_PATH=%XBOXONE_SYS_PATH% -isystem"%Console_SdkIncludeRoot%/shared"
set XBOXONE_SYS_PATH=%XBOXONE_SYS_PATH% -isystem"%Console_SdkIncludeRoot%/winrt"

set PS3_SYS_PATH=-isystem"%SCE_PS3_ROOT%/target/common/include"
set PS3_SYS_PATH=%PS3_SYS_PATH% -isystem"%SCE_PS3_ROOT%/target/ppu/include"
set PS3_SYS_PATH=%PS3_SYS_PATH% -isystem"%SN_PS3_PATH%/ppu/include/sn"
set PS3_SYS_PATH=%PS3_SYS_PATH% -isystem"%SCE_PS3_ROOT%/host-win32/ppu/lib/gcc/ppu-lv2/4.1.1/include"

set PS4_SYS_PATH=-isystem"%SCE_ORBIS_SDK_DIR%/target/include"
set PS4_SYS_PATH=%PS4_SYS_PATH% -isystem"%SCE_ORBIS_SDK_DIR%/host_tools/lib/clang/include"
set PS4_SYS_PATH=%PS4_SYS_PATH% -isystem"%SCE_ORBIS_SDK_DIR%/target/include_common"

set WIIU_SYS_PATH=-isystem"%CAFE_ROOT%/system/include"    
set WIIU_SYS_PATH=%WIIU_SYS_PATH% -isystem"%GHS_ROOT%/include/ppc"
set WIIU_SYS_PATH=%WIIU_SYS_PATH% -isystem"%GHS_ROOT%/ansi"

set PSP2_SYS_PATH=-isystem"%SCE_PSP2_SDK_DIR%/target/include"
set PSP2_SYS_PATH=%PSP2_SYS_PATH% -isystem"%SCE_PSP2_SDK_DIR%/target/include_common"

set NDK_TOOLCHAIN=arm-linux-androideabi-%NDK_GCC_VER%
set ANDROID_SYS_PATH=-isystem"%NDK_CURRENT%\arch-arm\usr\include"
set ANDROID_SYS_PATH=%ANDROID_SYS_PATH% -isystem"%NDK_ROOT%\%NDK_VERSION%\toolchains\%NDK_TOOLCHAIN%\prebuilt\windows\lib\gcc\arm-linux-androideabi\%NDK_GCC_VER%\include"
rem set ANDROID_SYS_PATH=%ANDROID_SYS_PATH% -isystem"%NDK_ROOT%\toolchains\%NDK_TOOLCHAIN%\prebuilt\windows\lib\gcc\arm-linux-androideabi\%NDK_GCC_VER%\include"
set ANDROID_SYS_PATH=%ANDROID_SYS_PATH% -isystem"%NDK_CURRENT%\arch-arm\usr\include\linux"

set NDK_TOOLCHAIN_X86=x86-%NDK_GCC_VER%
set ANDROID_X86_SYS_PATH=-isystem"%NDK_CURRENT%\arch-x86\usr\include"
set ANDROID_X86_SYS_PATH=%ANDROID_X86_SYS_PATH% -isystem"%NDK_ROOT%\%NDK_VERSION%\toolchains\%NDK_TOOLCHAIN_X86%\prebuilt\windows\lib\gcc\i686-linux-android\%NDK_GCC_VER%\include"
rem set ANDROID_X86_SYS_PATH=%ANDROID_X86_SYS_PATH% -isystem"%NDK_ROOT%\toolchains\%NDK_TOOLCHAIN_X86%\prebuilt\windows\lib\gcc\arm-linux-androideabi\%NDK_GCC_VER%\include"
set ANDROID_X86_SYS_PATH=%ANDROID_X86_SYS_PATH% -isystem"%NDK_CURRENT%\arch-x86\usr\include\linux"

if not defined BOILERPLATE_FILE (set BOILERPLATE_FILE="%SDK_ROOT%/Tools/Validation/boilerplate.txt")
set COMMON_FLAGS=-cc1 -x c++-header -fms-extensions -w -nobuiltininc -boilerplate-file %BOILERPLATE_FILE%
set WINDOWS_DEFINES=-DNDEBUG -DWIN32 -DPX_VC -std=c++0x
set XBOX360_DEFINES=-DNDEBUG -DPX_X360 -std=c++0x -fdiagnostics-ignore-system
set XBOXONE_DEFINES=-DNDEBUG -DPX_XBOXONE -std=c++0x -fdiagnostics-ignore-system

set PS3_DEFINES=-DNDEBUG -DSN_TARGET_PS3 -D__CELLOS_LV2__ -D__GCC__  -std=c++0x
set PS4_DEFINES=-DNDEBUG -DPX_PS4 -std=c++0x -nostdinc -nostdinc++ -D__ORBIS__ -fdiagnostics-ignore-system
set WIIU_DEFINES=-DNDEBUG -D__ppc  -DPX_WIIU -std=c++0x -fdiagnostics-ignore-system
set PSP2_DEFINES=-DNDEBUG -D__SNC__ -DSN_TARGET_PSP2 -DPX_PSP2 -D_HAS_C9X -std=c++98 -fdiagnostics-ignore-system
set ANDROID_DEFINES=-nostdinc -nostdinc++ -std=c++0x -DNDEBUG -DPX_ANDROID -D__ARM_EABI__
set ANDROID_X86_DEFINES=-nostdinc -nostdinc++ -std=c++0x -DNDEBUG -DPX_ANDROID

set EXE="%EXTERNALS%\externals\clang\3.3.2\win32\bin\clang.exe"

