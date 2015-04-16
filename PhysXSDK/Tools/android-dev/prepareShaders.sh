#! /bin/sh +x
set -e

# This is relative to the vertex/fragment folders, containing shaders in the media directory
CGC=../../../../../externals/cg/cgc.exe
VERTEXPROFILE=vs_3_0
PIXELPROFILE=ps_3_0
PASSES=(PASS_UNLIT PASS_AMBIENT_LIGHT PASS_DIRECTIONAL_LIGHT PASS_POINT_LIGHT PASS_SPOT_LIGHT_NO_SHADOW PASS_SPOT_LIGHT PASS_NORMALS PASS_DEPTH PASS_DEFERRED)
# change directory to shaders
MEDIA=../../media/SampleRenderer/4/shaders

pushd $MEDIA

if [ ! -d "../compiledshaders" ]; then mkdir "../compiledshaders"; fi
if [ ! -d "../compiledshaders/android" ]; then mkdir "../compiledshaders/android"; fi
if [ ! -d "../compiledshaders/android/vertex" ]; then mkdir "../compiledshaders/android/vertex"; fi
if [ ! -d "../compiledshaders/android/fragment" ]; then mkdir "../compiledshaders/android/fragment"; fi

# iterate over vertex and fragment shaders
for shaderType in vertex fragment
do
	# select vertex/fragment directory
	pushd $shaderType
	# list all shaders
	FILES=`ls *.cg`
	echo [Processing $shaderType shaders]
	# convert each shader
	for file in $FILES
	do
		echo "       "$file
		if [ $shaderType = vertex ]
		then
			for PASSNAME in "${PASSES[@]}"
			do
				echo "Cooking VERTEX shader '$file' for the $PASSNAME"
				$CGC -entry vmain -profile $VERTEXPROFILE -I../include -DGLSL_COMPILER -D$PASSNAME -DNO_SUPPORT_DDX_DDY -o "$PWD/../../compiledshaders/android/vertex/"`basename $file .cg`$PASSNAME.cg $file > /dev/null
			done
		else
			for PASSNAME in "${PASSES[@]}"
			do
				echo "Cooking FRAGMENT shader '$file' for the $PASSNAME"
				$CGC -entry fmain -profile $PIXELPROFILE  -I../include -DGLSL_COMPILER -D$PASSNAME -DNO_SUPPORT_DDX_DDY -o "$PWD/../../compiledshaders/android/fragment/"`basename $file .cg`$PASSNAME.cg $file > /dev/null
			done
		fi
	done
	popd
done
popd # media
