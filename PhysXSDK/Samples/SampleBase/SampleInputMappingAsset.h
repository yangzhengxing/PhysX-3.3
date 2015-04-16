/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
// Copyright (c) 2004-2008 AGEIA Technologies, Inc. All rights reserved.
// Copyright (c) 2001-2004 NovodeX AG. All rights reserved.  

#ifndef SAMPLE_INPUT_MAPPING_ASSET_H
#define SAMPLE_INPUT_MAPPING_ASSET_H

#include <SampleUserInput.h>
#include <ODBlock.h>
#include "SampleAllocator.h"

class SampleInputMappingAsset : public SampleAllocateable
{	
public:
	SampleInputMappingAsset(SampleFramework::File* file, const char *path, bool empty,PxU32 userInputCS, PxU32 inputEventCS);
	virtual ~SampleInputMappingAsset(void);
	
	virtual bool isOk(void) const;

	const SampleFramework::T_SampleInputData& getSampleInputData() const { return mSampleInputData; }

	void	addMapping(const char* uiName, const char* ieName);
	void	saveMappings();

private:
	void loadData(ODBlock* odsSettings);	
	bool createNewFile(bool rewriteFile);
	bool checksumCheck();

private:
	SampleFramework::T_SampleInputData mSampleInputData;
	ODBlock*				mSettingsBlock;
	ODBlock*				mMapping;
	SampleFramework::File*	mFile;
	const char*				mPath;
	bool					mIsOk;
	PxU32					mUserInputCS;
	PxU32					mInputEventCS;
};	

#endif
