/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#include <SampleAssetManager.h>

#include <string.h>
#include <stdio.h>
#include <sys/stat.h>


bool SampleFramework::searchForPath(const char* path, char* buffer, int bufferSize, bool isReadOnly, int maxRecursion)
{
	struct stat sb;
	char* tmpBuffer = (char*)alloca(bufferSize);
	sprintf(tmpBuffer, "/sdcard/%s", path);
	if(!stat(tmpBuffer, &sb))
	{	
		strcpy(buffer, tmpBuffer);
		return true;
	}
	return false;
}
