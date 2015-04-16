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
	sprintf(buffer, "%s", path);
	for(int i = 0; i < maxRecursion; i++)
	{
		if(stat(buffer, &sb))
		{
			sprintf(tmpBuffer, "../%s", buffer);
			strcpy(buffer, tmpBuffer);
		}
		else 
			return true;
	}
	return false;
}
