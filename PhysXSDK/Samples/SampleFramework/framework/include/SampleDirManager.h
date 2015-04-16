/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef _SAMPLE_DIR_MANAGER_H
#define	_SAMPLE_DIR_MANAGER_H

namespace SampleFramework
{
	class SampleDirManager
	{
	public:
		SampleDirManager(const char* relativePathRoot, bool isReadOnly = true, int maxRecursion = 20);

	public:
		const char*	getPathRoot() const	{ return mPathRoot; }
		const char*	getFilePath(const char* relativeFilePath, char* pathBuffer, bool testFileValidity = true);

	private:
		char	mPathRoot[256];
		bool	mIsReadOnly;
	};
}

#endif
