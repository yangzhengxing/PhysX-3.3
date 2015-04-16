/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef SAMPLE_ASSET_H
#define SAMPLE_ASSET_H

#include "FrameworkFoundation.h"

namespace SampleFramework
{

	class SampleAsset
	{
		friend class SampleAssetManager;
	public:
		enum Type
		{
			ASSET_MATERIAL = 0,
			ASSET_TEXTURE,
			ASSET_INPUT,

			NUM_TYPES
		}_Type;

		virtual bool isOk(void) const = 0;

		Type        getType(void) const { return m_type; }
		const char *getPath(void) const { return m_path; }

	protected:
		SampleAsset(Type type, const char *path);
		virtual ~SampleAsset(void);

		virtual void release(void) { delete this; }

	private:
		SampleAsset &operator=(const SampleAsset&) { return *this; }

		const Type m_type;
		char      *m_path;
		PxU32      m_numUsers;
	};

} // namespace SampleFramework

#endif
