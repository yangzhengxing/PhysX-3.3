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

#define NOMINMAX
#include <windows.h>


bool SampleFramework::searchForPath(const char* path, char* buffer, int bufferSize, bool isReadOnly, int maxRecursion)
{
	char* tmpBuffer = (char*)alloca(bufferSize);
	strcpy_s(buffer, bufferSize, path);
	for(int i = 0; i < maxRecursion; i++)
	{
		if(GetFileAttributes(buffer) == INVALID_FILE_ATTRIBUTES)
		{
			sprintf_s(tmpBuffer, bufferSize, "../%s", buffer);
			strcpy_s(buffer, bufferSize, tmpBuffer);
		}
		else 
			return true;
	}
	return false;
}
