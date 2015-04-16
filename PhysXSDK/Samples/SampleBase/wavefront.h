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

#ifndef WAVEFRONT_OBJ_H
#define WAVEFRONT_OBJ_H

class WavefrontObj
{
public:

	WavefrontObj(void);
	~WavefrontObj(void);

	unsigned int loadObj(const char *fname, bool textured); // load a wavefront obj returns number of triangles that were loaded.  Data is persists until the class is destructed.

	int mVertexCount;
	int mTriCount;
	int* mIndices;
	float* mVertices;
	float* mTexCoords;
};

	bool LoadWavefrontBinary(const char* filename, WavefrontObj& wfo);
	bool SaveWavefrontBinary(const char* filename, const WavefrontObj& wfo);

#endif
