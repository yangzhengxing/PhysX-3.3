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


#ifndef SAMPLE_VEHICLE_CONTROL_INPUTS_H
#define SAMPLE_VEHICLE_CONTROL_INPUTS_H

#include "common/PxPhysXCommonConfig.h"

using namespace physx;

class SampleVehicle_ControlInputs
{
public:

	SampleVehicle_ControlInputs();
	~SampleVehicle_ControlInputs();

	//Camera inputs
	void					setRotateY(const PxF32 f) 					{mCameraRotateInputY=f;}
	void					setRotateZ(const PxF32 f) 					{mCameraRotateInputZ=f;}
	PxF32					getRotateY() const							{return mCameraRotateInputY;}
	PxF32					getRotateZ() const							{return mCameraRotateInputZ;}

	//Keyboard driving inputs - (car + tank)
	void					setAccelKeyPressed(const bool b) 			{mAccelKeyPressed=b;}
	void					setGearUpKeyPressed(const bool b) 			{mGearUpKeyPressed=b;}
	void					setGearDownKeyPressed(const bool b)			{mGearDownKeyPressed=b;}
	bool					getAccelKeyPressed() const					{return mAccelKeyPressed;}
	bool					getGearUpKeyPressed() const					{return mGearUpKeyPressed;}
	bool					getGearDownKeyPressed() const				{return mGearDownKeyPressed;}

	//Keyboard driving inputs - (car only)
	void					setBrakeKeyPressed(const bool b) 			{mBrakeKeyPressed=b;}
	void					setHandbrakeKeyPressed(const bool b)		{mHandbrakeKeyPressed=b;}
	void					setSteerLeftKeyPressed(const bool b)		{mSteerLeftKeyPressed=b;}
	void					setSteerRightKeyPressed(const bool b)		{mSteerRightKeyPressed=b;}
	bool					getBrakeKeyPressed() const					{return mBrakeKeyPressed;}
	bool					getHandbrakeKeyPressed() const				{return mHandbrakeKeyPressed;}
	bool					getSteerLeftKeyPressed() const				{return mSteerLeftKeyPressed;}
	bool					getSteerRightKeyPressed() const				{return mSteerRightKeyPressed;}

	//Keyboard driving inputs - (tank only)
	void					setBrakeLeftKeyPressed(const bool b) 		{mBrakeLeftKeyPressed=b;}
	void					setBrakeRightKeyPressed(const bool b) 		{mBrakeRightKeyPressed=b;}
	void					setThrustLeftKeyPressed(const bool b) 		{mThrustLeftKeyPressed=b;}
	void					setThrustRightKeyPressed(const bool b) 		{mThrustRightKeyPressed=b;}
	bool					getBrakeLeftKeyPressed() const				{return mBrakeLeftKeyPressed;}
	bool					getBrakeRightKeyPressed() const	 			{return mBrakeRightKeyPressed;}
	bool					getThrustLeftKeyPressed() const	 			{return mThrustLeftKeyPressed;}
	bool					getThrustRightKeyPressed() const	 		{return mThrustRightKeyPressed;}

	//Gamepad driving inputs (car + tank)
	void					setAccel(const PxF32 f) 					{mAccel=f;}
	void					setGearUp(const bool b) 					{mGearup=b;}
	void					setGearDown(const bool b) 					{mGeardown=b;}
	PxF32					getAccel() const							{return mAccel;}
	bool					getGearUp() const							{return mGearup;}
	bool					getGearDown() const							{return mGeardown;}

	//Gamepad driving inputs (car only)
	void					setBrake(const PxF32 f) 					{mBrake=f;}
	void					setSteer(const PxF32 f) 					{mSteer=f;}
	void					setHandbrake(const bool b) 					{mHandbrake=b;}
	PxF32					getBrake() const							{return mBrake;}
	PxF32					getSteer() const							{return mSteer;}
	bool					getHandbrake() const						{return mHandbrake;}

	//Gamepad driving inputs (tank only)
	void					setThrustLeft(const PxF32 f)				{mThrustLeft=f;}
	void					setThrustRight(const PxF32 f)				{mThrustRight=f;}
	PxF32					getThrustLeft() const						{return mThrustLeft;}
	PxF32					getThrustRight() const						{return mThrustRight;}
	void					setBrakeLeft(const PxF32 f)					{mBrakeLeft=f;}
	void					setBrakeRight(const PxF32 f)				{mBrakeRight=f;}
	PxF32					getBrakeLeft() const						{return mBrakeLeft;}
	PxF32					getBrakeRight() const						{return mBrakeRight;}

private:

	//Camera inputs.
	PxF32			mCameraRotateInputY;
	PxF32			mCameraRotateInputZ;

	//keyboard inputs (car and tank)
	bool			mAccelKeyPressed;
	bool			mGearUpKeyPressed;
	bool			mGearDownKeyPressed;

	//keyboard inputs (car only)
	bool			mBrakeKeyPressed;
	bool			mHandbrakeKeyPressed;
	bool			mSteerLeftKeyPressed;
	bool			mSteerRightKeyPressed;

	//keyboard inputs (tank only)
	bool mBrakeLeftKeyPressed;
	bool mBrakeRightKeyPressed;
	bool mThrustLeftKeyPressed;
	bool mThrustRightKeyPressed;

	//gamepad inputs (car and tank)
	PxF32			mAccel;
	bool			mGearup;
	bool			mGeardown;

	//gamepad inputs (car only)
	PxF32			mBrake;
	PxF32			mSteer;
	bool			mHandbrake;

	//gamepad inputs (tank only)
	PxF32			mThrustLeft;
	PxF32			mThrustRight;
	PxF32			mBrakeLeft;
	PxF32			mBrakeRight;
};

#endif //SAMPLE_VEHICLE_CONTROL_INPUTS_H