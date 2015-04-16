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
#ifndef PX_PHYSICS_NXPHYSICSWITHVEHICLEEXTENSIONS_API
#define PX_PHYSICS_NXPHYSICSWITHVEHICLEEXTENSIONS_API

#include "PxExtensionsCommon.h"

static DisabledPropertyEntry gDisabledProperties[] = {
	DisabledPropertyEntry( "PxVehicleWheelsDynData", "MTireForceCalculators" ),	
	DisabledPropertyEntry( "PxVehicleWheelsDynData", "TireForceShaderData" ),
	DisabledPropertyEntry( "PxVehicleWheelsDynData", "UserData" ),
	DisabledPropertyEntry( "PxVehicleWheels", "MActor" ),
};

//Append these properties to this type.
static CustomProperty gCustomProperties[] = {
#define DEFINE_VEHICLETIREDATA_INDEXED_PROPERTY( propName, propType, fieldName ) CustomProperty("PxVehicleTireData", #propName,	#propType, "PxReal " #propName "[3][2];", "PxMemCopy( "#propName ", inSource->"#fieldName", sizeof( "#propName" ) );" )
	DEFINE_VEHICLETIREDATA_INDEXED_PROPERTY( MFrictionVsSlipGraph, MFrictionVsSlipGraphProperty, mFrictionVsSlipGraph),
#undef DEFINE_VEHICLETIREDATA_INDEXED_PROPERTY
	
	CustomProperty( "PxVehicleEngineData",	"MTorqueCurve",			"MTorqueCurveProperty", "", "" ),
};

static const char* gUserPhysXTypes[] = 
{
	"PxVehicleWheels",
	"PxVehicleWheelsSimData",
	"PxVehicleWheelsDynData",
	"PxVehicleDrive4W",
	"PxVehicleWheels4SimData",
	"PxVehicleDriveSimData4W",
	"PxVehicleWheelData",
	"PxVehicleSuspensionData",
	"PxVehicleDriveDynData",
	"PxVehicleDifferential4WData",
	"PxVehicleDifferentialNWData",
	"PxVehicleAckermannGeometryData",
	"PxVehicleTireLoadFilterData",
	"PxVehicleEngineData",
	"PxVehicleGearsData",
	"PxVehicleClutchData",
	"PxVehicleAutoBoxData",
	"PxVehicleTireData",
	"PxVehicleChassisData",
	"PxTorqueCurvePair",
	"PxVehicleDriveTank",	
	"PxVehicleNoDrive",
	"PxVehicleDriveSimDataNW",
	"PxVehicleDriveNW",
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
#include "PxVehicleSuspWheelTire4.h"
#endif
