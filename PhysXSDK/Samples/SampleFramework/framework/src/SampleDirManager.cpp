/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#include "SampleDirManager.h"
#include "SampleAssetManager.h"
#include "SamplePlatform.h"
#include "PsUtilities.h"
#include "PsFile.h"
#include "PsPrintString.h"

using namespace SampleFramework;

static void FixPathSeparator(char* pathBuffer)
{
	char separator = SampleFramework::SamplePlatform::platform()->getPathSeparator()[0];

	const size_t length = strlen(pathBuffer);
	for(size_t i=0; i<length ; ++i)
	{
		if ('/' == pathBuffer[i] || '\\' == pathBuffer[i])
			pathBuffer[i] = separator;
	}
}

SampleDirManager::SampleDirManager(const char* relativePathRoot, bool isReadOnly, int maxRecursion) : mIsReadOnly(isReadOnly)
{
	if(!relativePathRoot || !SampleFramework::searchForPath(relativePathRoot, mPathRoot, PX_ARRAY_SIZE(mPathRoot), isReadOnly, maxRecursion))
	{
		shdfnd::printFormatted("path \"%s\" not found\n", relativePathRoot);
		mPathRoot[0] = '\0';
	}
}

#define MAX_PATH_LENGTH 256

const char* SampleDirManager::getFilePath(const char* relativeFilePath, char* pathBuffer, bool testFileValidity)
{
	PX_ASSERT(pathBuffer);

	bool flattenRelativeFilePaths = false;
#if defined (RENDERER_IOS)
	//iOS doesn't allow to share files in folders...
	flattenRelativeFilePaths = !mIsReadOnly;
#endif
	
	strcpy(pathBuffer, getPathRoot());
	strcat(pathBuffer, "/");
	
	if (flattenRelativeFilePaths)
	{
		char flattendPath[MAX_PATH_LENGTH];
		strcpy(flattendPath, relativeFilePath);
		for (size_t i = 0; i < strlen(flattendPath); ++i)
		{
			if ('/' == flattendPath[i] || '\\' == flattendPath[i])
				flattendPath[i] = '_';
		}
		strcat(pathBuffer, flattendPath);
	}
	else
	{
		strcat(pathBuffer, relativeFilePath);
		if (!mIsReadOnly)
		{
			FixPathSeparator(pathBuffer);
			//strip file from path and make sure the output directory exists
			const char* ptr = strrchr(pathBuffer, '/');
			if (!ptr)
				ptr = strrchr(pathBuffer, '\\');
			
			if (ptr)
			{
				char dir[MAX_PATH_LENGTH];
				assert(MAX_PATH_LENGTH >= strlen(pathBuffer));
				strcpy(dir, pathBuffer);
				dir[ptr - pathBuffer] = '\0';
				FixPathSeparator(dir);
				SampleFramework::SamplePlatform::platform()->makeSureDirectoryPathExists(dir);
			}
		}
	}

	FixPathSeparator(pathBuffer);

	if(testFileValidity)
	{
		File* fp = NULL;
		Fnd::fopen_s(&fp, pathBuffer, "rb");
		if(!fp)
		{
			// Kai: user can still get full path in the path buffer (side effect)
			return NULL;
		}
		fclose(fp);
	}

	return pathBuffer;
}
