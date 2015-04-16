/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#include "SampleInputAsset.h"
#include "ODBlock.h"
#include <PsFile.h>
#include <PsPrintString.h>

using namespace SampleFramework;

SampleInputAsset::SampleInputAsset(File* file, const char *path)
: SampleAsset(SampleAsset::ASSET_INPUT, path)
, m_SettingsBlock(NULL)
, m_File(file)
{
	m_SampleInputData.reserve(128);	

	PX_ASSERT(file);

	if (!m_Mapping.loadScript(file))
	{
		shdfnd::printFormatted("ODS parse error: %s in file: %s\n", m_Mapping.lastError, path);		
		PX_ASSERT(0);
	}	

	m_SettingsBlock = m_Mapping.getBlock("InputMapping");
	if (!m_SettingsBlock)
	{
		shdfnd::printFormatted("No \"InputEventSettings\" block found!\n");
		PX_ASSERT(0);
	}
	else
	{
		LoadData(m_SettingsBlock);
	}
}

SampleInputAsset::~SampleInputAsset()
{
	if(m_File)
	{
		fclose(m_File);
	}
}

void SampleInputAsset::LoadData(ODBlock* odsSettings)
{	
	odsSettings->reset();
	while (odsSettings->moreSubBlocks())
	{
		ODBlock* subBlock = odsSettings->nextSubBlock();
		subBlock->reset();

		SampleInputData inputData;
		if (!strcmp(subBlock->ident(), "map"))
		{
			if (subBlock->moreTerminals())	
			{ 
				const char* p = subBlock->nextTerminal();
				strcpy(inputData.m_UserInputName, p);
			}
			if (subBlock->moreTerminals())	
			{ 
				const char* p = subBlock->nextTerminal();
				strcpy(inputData.m_InputEventName, p);
			}

			m_SampleInputData.push_back(inputData);
		}
	}
}

bool SampleInputAsset::isOk(void) const
{
	return true;
}
