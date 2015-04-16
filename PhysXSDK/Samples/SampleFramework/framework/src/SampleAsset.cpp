/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#include <SampleAsset.h>

// for PsString.h
namespace physx
{
	namespace string
	{}
}
#include <PsString.h>

using namespace SampleFramework;

SampleAsset::SampleAsset(Type type, const char *path) :
	m_type(type)
{
	size_t len = strlen(path)+1;
	m_path = new char[len];
	physx::string::strcpy_s(m_path, len, path);
	m_numUsers = 0;
}

SampleAsset::~SampleAsset(void)
{
	if(m_path) delete [] m_path;
}
