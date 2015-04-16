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

#ifndef PHYSX_SNIPPET_PULLEY_JOINT_EXTENSION_H
#define PHYSX_SNIPPET_PULLEY_JOINT_EXTENSION_H

#include "PxSerialFramework.h"

void registerPulleyJointBinaryExtension(physx::PxSerializationRegistry& sr);
void unregisterPulleyJointBinaryExtension(physx::PxSerializationRegistry& sr);

void registerPulleyJointRepXExtension(physx::PxSerializationRegistry& sr);
void unregisterPulleyJointRepXExtension(physx::PxSerializationRegistry& sr);

#endif