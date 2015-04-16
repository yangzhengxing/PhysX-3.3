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
#ifndef PX_PHYSICS_NXPHYSICSWITHEXTENSIONS_API
#define PX_PHYSICS_NXPHYSICSWITHEXTENSIONS_API

#include "PxExtensionsCommon.h"

//Property overrides will output this exact property name instead of the general
//property name that would be used.  The properties need to have no template arguments
//and exactly the same initialization as the classes they are overriding.
static PropertyOverride gPropertyOverrides[] = {
	PropertyOverride( "PxShape", "Geometry", "PxShapeGeometryProperty" ),
	PropertyOverride( "PxShape", "Materials", "PxShapeMaterialsProperty" ),
	PropertyOverride( "PxRigidActor", "Shapes", "PxRigidActorShapeCollection" ),
	PropertyOverride( "PxArticulation", "Links", "PxArticulationLinkCollectionProp" ),
};

static DisabledPropertyEntry gDisabledProperties[] = {
	DisabledPropertyEntry( "PxSceneLimits", "IsValid" ),
	DisabledPropertyEntry( "PxSceneDesc", "TolerancesScale" ),
	DisabledPropertyEntry( "PxShape", "Actor" ),
	DisabledPropertyEntry( "PxArticulationLink", "Articulation" ),
	DisabledPropertyEntry( "PxRigidActor", "IsRigidActor" ),
	DisabledPropertyEntry( "PxRigidActor", "ClassName" ),
	DisabledPropertyEntry( "PxRigidStatic", "ClassName" ),
	DisabledPropertyEntry( "PxRigidDynamic", "ClassName" ),
	DisabledPropertyEntry( "PxRigidBody", "IsRigidBody" ),
	DisabledPropertyEntry( "PxActor", "IsRigidStatic" ),
	DisabledPropertyEntry( "PxActor", "Type" ),
	DisabledPropertyEntry( "PxActor", "ClassName" ),
	DisabledPropertyEntry( "PxActor", "IsRigidDynamic" ),
	DisabledPropertyEntry( "PxActor", "IsParticleSystem" ),
	DisabledPropertyEntry( "PxActor", "IsParticleFluid" ),
	DisabledPropertyEntry( "PxActor", "IsDeformable" ),
	DisabledPropertyEntry( "PxActor", "IsArticulationLink" ),
	DisabledPropertyEntry( "PxActor", "IsRigidActor" ),
	DisabledPropertyEntry( "PxActor", "IsRigidBody" ),
	DisabledPropertyEntry( "PxActor", "IsParticleBase" ),
	DisabledPropertyEntry( "PxActor", "IsCloth" ),
	DisabledPropertyEntry( "PxMeshScale", "Inverse" ),
	DisabledPropertyEntry( "PxMeshScale", "IsIdentity" ),
	DisabledPropertyEntry( "PxGeometry", "Type" ),
	DisabledPropertyEntry( "PxBoxGeometry", "IsValid" ),
	DisabledPropertyEntry( "PxPlaneGeometry", "IsValid" ),
	DisabledPropertyEntry( "PxCapsuleGeometry", "IsValid" ),
	DisabledPropertyEntry( "PxConvexMeshGeometry", "IsValid" ),
	DisabledPropertyEntry( "PxTriangleMeshGeometry", "IsValid" ),
	DisabledPropertyEntry( "PxHeightFieldGeometry", "IsValid" ),
#if PX_USE_PARTICLE_SYSTEM_API
	DisabledPropertyEntry( "PxParticleBase", "IsParticleBase" ),
#endif
#if PX_USE_CLOTH_API
	DisabledPropertyEntry( "PxCloth", "WorldBounds" ),
	DisabledPropertyEntry( "PxCloth", "Fabric" ),
#endif
	DisabledPropertyEntry( "PxJoint", "ClassName" ),
	DisabledPropertyEntry( "PxDistanceJoint", "ClassName" ),
	DisabledPropertyEntry( "PxFixedJoint", "ClassName" ),
	DisabledPropertyEntry( "PxRevoluteJoint", "ClassName" ),
	DisabledPropertyEntry( "PxPrismaticJoint", "ClassName" ),
	DisabledPropertyEntry( "PxSphericalJoint", "ClassName" ),
	DisabledPropertyEntry( "PxD6Joint", "ClassName" ),
	DisabledPropertyEntry( "PxJointLimitParameters", "IsValid" ),
	DisabledPropertyEntry( "PxJointLimitParameters", "IsSoft" ),
	DisabledPropertyEntry( "PxJointLinearLimit", "IsValid" ),
	DisabledPropertyEntry( "PxJointLinearLimitPair", "IsValid" ),
	DisabledPropertyEntry( "PxJointAngularLimitPair", "IsValid" ),
	DisabledPropertyEntry( "PxJointLimitCone", "IsValid" ),
	DisabledPropertyEntry( "PxD6JointDrive", "IsValid" ),
};

//Append these properties to this type.
static CustomProperty gCustomProperties[] = {
#define DEFINE_SIM_STATS_DUAL_INDEXED_PROPERTY( propName, propType, fieldName ) CustomProperty("PxSimulationStatistics", #propName,	#propType, "PxU32 " #propName "[PxGeometryType::eGEOMETRY_COUNT][PxGeometryType::eGEOMETRY_COUNT];", "PxMemCopy( "#propName ", inSource->"#fieldName", sizeof( "#propName" ) );" )
	DEFINE_SIM_STATS_DUAL_INDEXED_PROPERTY( NbDiscreteContactPairs, NbDiscreteContactPairsProperty, nbDiscreteContactPairs ),
	DEFINE_SIM_STATS_DUAL_INDEXED_PROPERTY( NbModifiedContactPairs, NbModifiedContactPairsProperty, nbModifiedContactPairs),
	DEFINE_SIM_STATS_DUAL_INDEXED_PROPERTY( NbCCDPairs, NbCCDPairsProperty, nbCCDPairs),
	DEFINE_SIM_STATS_DUAL_INDEXED_PROPERTY( NbTriggerPairs, NbTriggerPairsProperty, nbTriggerPairs),
#undef DEFINE_SIM_STATS_DUAL_INDEXED_PROPERTY
	CustomProperty( "PxSimulationStatistics",	"NbBroadPhaseAdds",		"NbBroadPhaseAddsProperty", "PxU32 NbBroadPhaseAdds[PxSimulationStatistics::eVOLUME_COUNT];", "PxMemCopy( NbBroadPhaseAdds, inSource->nbBroadPhaseAdds, sizeof( NbBroadPhaseAdds ) );" ),
	CustomProperty( "PxSimulationStatistics",	"NbBroadPhaseRemoves",	"NbBroadPhaseRemovesProperty", "PxU32 NbBroadPhaseRemoves[PxSimulationStatistics::eVOLUME_COUNT];", "PxMemCopy( NbBroadPhaseRemoves, inSource->nbBroadPhaseRemoves, sizeof( NbBroadPhaseRemoves ) );" ),
	CustomProperty( "PxSimulationStatistics",	"NbShapes",				"NbShapesProperty", "PxU32 NbShapes[PxGeometryType::eGEOMETRY_COUNT];", "PxMemCopy( NbShapes, inSource->nbShapes, sizeof( NbShapes ) );" ),
	CustomProperty( "PxScene",					"SimulationStatistics",	"SimulationStatisticsProperty", "PxSimulationStatistics SimulationStatistics;", "inSource->getSimulationStatistics(SimulationStatistics);"  ),
#if PX_USE_PARTICLE_SYSTEM_API
	CustomProperty( "PxParticleBase",			"ProjectionPlane",		"ProjectionPlaneProperty", "PxMetaDataPlane ProjectionPlane;", "inSource->getProjectionPlane( ProjectionPlane.normal, ProjectionPlane.distance );" ),
#endif
};

static const char* gImportantPhysXTypes[] = 
{
	"PxRigidStatic",
	"PxRigidDynamic",
	"PxShape",
	"PxArticulation",
	"PxArticulationLink",
	"PxMaterial",
	"PxArticulationJoint",
	"PxScene",
	"PxPhysics",
	"PxHeightFieldDesc",
	"PxMeshScale",
	"PxConstraint",
	"PxTolerancesScale",
	"PxSimulationStatistics",
	"PxSceneDesc",
	"PxSceneLimits",
	"PxBroadPhaseDesc",
#if PX_USE_PARTICLE_SYSTEM_API
	"PxParticleSystem",
	"PxParticleFluid",
	"PxParticleReadData",
#endif
#if PX_USE_CLOTH_API
	"PxCloth",
	"PxClothFabric",
	"PxClothFabricPhase",
	"PxClothParticleData",
	"PxClothParticle",
	"PxClothStretchConfig",
	"PxClothBendingConfig",
	"PxClothTetherConfig",
	"PxClothMotionConstraintConfig",
#endif
    "PxAggregate",
	//The mesh and heightfield buffers will need to be
	//handled by hand; they are very unorthodox compared
	//to the rest of the objects.
};

static const char* gExtensionPhysXTypes[] = 
{
	"PxD6JointDrive",
	"PxJointLinearLimit",
	"PxJointLinearLimitPair",
	"PxJointAngularLimitPair",
	"PxJointLimitCone",
	"PxD6Joint",
	"PxDistanceJoint",
	"PxFixedJoint",
	"PxPrismaticJoint",
	"PxRevoluteJoint",
	"PxSphericalJoint",
};

//We absolutely never generate information about these types, even if types
//we do care about are derived from these types.
static const char* gAvoidedPhysXTypes[] = 
{
	"PxSerializable",
    "PxObservable",
	"PxBase",
    "PxBaseFlag::Enum",
};

#include "PxPhysicsAPI.h"
#include "extensions/PxExtensionsAPI.h"
#if PX_USE_CLOTH_API
#include "cloth/PxCloth.h"
#include "cloth/PxClothParticleData.h"
#include "cloth/PxClothFabric.h"
#endif

#endif
