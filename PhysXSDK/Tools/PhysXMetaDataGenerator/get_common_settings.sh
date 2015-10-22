#!/bin/bash
#search sdk root

SCRIPT_DIR="$( cd -P "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
if [ ! "$SDK_ROOT" ]; then
	sdk_root=$SCRIPT_DIR;
	while [ ! -e $sdk_root"/Source" ]; do
		sdk_root="$sdk_root""/.."
	done
	export SDK_ROOT="$sdk_root"
fi

echo SDK_ROOT is $SDK_ROOT

if [ ! "$EXTERNALS" ]; then
	externals=$SCRIPT_DIR;
	while [ ! -e $externals"/externals" ]; do
		externals="$externals""/.."
	done
	export EXTERNALS="$externals"
fi

INCLUDES="$INCLUDES -I"$SDK_ROOT/Include/foundation""
INCLUDES="$INCLUDES -I"$SDK_ROOT/Include/physxprofilesdk""
INCLUDES="$INCLUDES -I"$SDK_ROOT/Include/physxvisualdebuggersdk""
INCLUDES="$INCLUDES -I"$SDK_ROOT/pxtask/include""
INCLUDES="$INCLUDES -I"$SDK_ROOT/Include/common""		
INCLUDES="$INCLUDES -I"$SDK_ROOT/Include/geometry""		
INCLUDES="$INCLUDES -I"$SDK_ROOT/Include/pvd""		
INCLUDES="$INCLUDES -I"$SDK_ROOT/Include/particles""		
INCLUDES="$INCLUDES -I"$SDK_ROOT/Include/cloth""		
INCLUDES="$INCLUDES -I"$SDK_ROOT/Include/physxvisualdebuggersdk""
INCLUDES="$INCLUDES -I"$SDK_ROOT/Include/gpu""
INCLUDES="$INCLUDES -I"$SDK_ROOT/Include""
INCLUDES="$INCLUDES -I"$SDK_ROOT/Source/PhysXCommon/src""		
INCLUDES="$INCLUDES -I"$SDK_ROOT/Source/GeomUtils/headers""	
INCLUDES="$INCLUDES -I"$SDK_ROOT/Source/GeomUtils/src""		
INCLUDES="$INCLUDES -I"$SDK_ROOT/Source/GeomUtils/Opcode""		
INCLUDES="$INCLUDES -I"$SDK_ROOT/Source/PhysX/src""
INCLUDES="$INCLUDES -I"$SDK_ROOT/Source/PhysX/src/buffering""
INCLUDES="$INCLUDES -I"$SDK_ROOT/Source/PhysX/src/particles""
INCLUDES="$INCLUDES -I"$SDK_ROOT/Source/PhysX/src/cloth""		
INCLUDES="$INCLUDES -I"$SDK_ROOT/Source/SimulationController/src""		
INCLUDES="$INCLUDES -I"$SDK_ROOT/Source/SimulationController/src/framework""	
INCLUDES="$INCLUDES -I"$SDK_ROOT/Source/SimulationController/include""		
INCLUDES="$INCLUDES -I"$SDK_ROOT/Source/PhysXCooking/include""		
INCLUDES="$INCLUDES -I"$SDK_ROOT/Source/SceneQuery""		
INCLUDES="$INCLUDES -I"$SDK_ROOT/Source/PvdRuntime/src""		
INCLUDES="$INCLUDES -I"$SDK_ROOT/Source/PhysXMetaData/core/include""	
INCLUDES="$INCLUDES -I"$SDK_ROOT/Source/PhysXGpu/include""
INCLUDES="$INCLUDES -I"$SDK_ROOT/Tools/PhysXMetaDataGenerator""

if [ ! "$BOILERPLATE_FILE" ]; then
  BOILERPLATE_FILE="$SDK_ROOT/Tools/Validation/boilerplate.txt"
fi

COMMON_FLAGS="-fms-extensions -w -boilerplate-file $BOILERPLATE_FILE"
LINUX_DEFINES="-x c++-header -DNDEBUG -std=c++0x"
OSX_DEFINES="-x c++-header -DNDEBUG -std=c++0x"

export OSX_EXE="$EXTERNALS/externals/clang/3.3.3/osx/bin/clang"

export LINUX_EXE="$EXTERNALS/externals/clang/3.3.3/linux32/bin/clang"



