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


#ifndef RENDERER_MEMORY_MACROS_H
#define RENDERER_MEMORY_MACROS_H

	// PT: if you don't like those macros, don't use them. But don't touch/remove them!
	#define	DELETESINGLE(x)	if(x){ delete x; x = NULL;		}
	#define	DELETEARRAY(x)	if(x){ delete []x; x = NULL;	}
	#define	SAFE_RELEASE(x)	if(x){ x->release(); x = NULL;	}

#endif
