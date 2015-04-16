/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */


#ifndef SAMPLE_INPUT_ASSET_H
#define SAMPLE_INPUT_ASSET_H


#include <SampleAssetManager.h>
#include <SampleAsset.h>
#include <SampleUserInput.h>
#include <ODBlock.h>

namespace SampleFramework
{	

	class SampleInputAsset : public SampleAsset
	{
		friend class SampleAssetManager;
	protected:
		SampleInputAsset(File* file, const char *path);
		virtual ~SampleInputAsset(void);
	
	public:
		virtual bool isOk(void) const;

		const T_SampleInputData& GetSampleInputData() const { return m_SampleInputData; }

	private:
		void LoadData(ODBlock* odsSettings);		

	private:
		T_SampleInputData m_SampleInputData;
		ODBlock*			m_SettingsBlock;
		ODBlock				m_Mapping;
		File*				m_File;
	};

} // namespace SampleFramework



#endif
