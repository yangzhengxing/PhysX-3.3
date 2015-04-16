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

#ifndef SAMPLE_ALLOCATOR_H
#define SAMPLE_ALLOCATOR_H

#include "foundation/PxAllocatorCallback.h"
#include "common/PxPhysXCommonConfig.h"
#include "PsMutex.h"
#include "PxTkNamespaceMangle.h"

using namespace physx;

	class PxSampleAllocator : public PxAllocatorCallback
	{
		public:
						PxSampleAllocator();
						~PxSampleAllocator();

		virtual void*	allocate(size_t size, const char* typeName, const char* filename, int line);
				void*	allocate(size_t size, const char* filename, int line)	{ return allocate(size, NULL, filename, line); }
		virtual void	deallocate(void* ptr);

		protected:
				Ps::MutexT<Ps::RawAllocator> mMutex;

				void**		mMemBlockList;
				PxU32		mMemBlockListSize;
				PxU32		mFirstFree;
				PxU32		mMemBlockUsed;

		public:
				PxI32		mNbAllocatedBytes;
				PxI32		mHighWaterMark;
				PxI32		mTotalNbAllocs;
				PxI32		mNbAllocs;
	};

	void				initSampleAllocator();
	void				releaseSampleAllocator();
	PxSampleAllocator*	getSampleAllocator();

	class SampleAllocateable
	{
		public:
		PX_FORCE_INLINE	void*	operator new		(size_t, void* ptr)													{ return ptr;	}
		PX_FORCE_INLINE	void*	operator new		(size_t size, const char* handle, const char * filename, int line)	{ return getSampleAllocator()->allocate(size, handle, filename, line);	}
		PX_FORCE_INLINE	void*	operator new[]		(size_t size, const char* handle, const char * filename, int line)	{ return getSampleAllocator()->allocate(size, handle, filename, line);	}
		PX_FORCE_INLINE	void	operator delete		(void* p)															{ getSampleAllocator()->deallocate(p);	}
		PX_FORCE_INLINE	void	operator delete		(void* p, PxU32, const char*, int)									{ getSampleAllocator()->deallocate(p);	}
		PX_FORCE_INLINE	void	operator delete		(void* p, const char*, const char *, int)							{ getSampleAllocator()->deallocate(p);	}
		PX_FORCE_INLINE	void	operator delete[]	(void* p)															{ getSampleAllocator()->deallocate(p);	}
		PX_FORCE_INLINE	void	operator delete[]	(void* p, PxU32, const char*, int)									{ getSampleAllocator()->deallocate(p);	}
		PX_FORCE_INLINE	void	operator delete[]	(void* p, const char*, const char *, int)							{ getSampleAllocator()->deallocate(p);	}
	};

	#define SAMPLE_ALLOC(x)	getSampleAllocator()->allocate(x, 0, __FILE__, __LINE__)
	#define	SAMPLE_FREE(x)	if(x)	{ getSampleAllocator()->deallocate(x); x = NULL;	}
	#define SAMPLE_NEW(x)	new(#x, __FILE__, __LINE__) x

#endif
