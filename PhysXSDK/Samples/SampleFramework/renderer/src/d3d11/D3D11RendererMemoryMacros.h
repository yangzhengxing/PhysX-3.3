/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef D3D11_RENDERER_MEMORY_MACROS_H
#define D3D11_RENDERER_MEMORY_MACROS_H

namespace SampleRenderer
{

template<class T> 
PX_INLINE void dxSafeRelease( T*& t ) { if(t) { t->Release(); t = NULL; } }

template<class T>
PX_INLINE void deleteSafe( T*& t ) { if(t) { delete t; t = NULL; } }

template<class T>
PX_INLINE bool deleteAndReturnTrue( T& t ) { deleteSafe(t); return true; }

template<class T>
PX_INLINE bool dxReleaseAndReturnTrue( T& t ) { dxSafeRelease(t); return true; }

template<class T>
PX_INLINE void deleteAll( T& t ) { std::remove_if(t.begin(), t.end(), deleteAndReturnTrue<typename T::value_type>); };

template<class T>
PX_INLINE void dxSafeReleaseAll( T& t ) { std::remove_if(t.begin(), t.end(), dxReleaseAndReturnTrue<typename T::value_type>); };

template<class T>
PX_INLINE void resizeIfSmallerThan( T& t, typename T::size_type s, typename T::value_type v = typename T::value_type() ) 
{
	if (s > t.size())
		t.resize(s, v);
}

}

#endif
