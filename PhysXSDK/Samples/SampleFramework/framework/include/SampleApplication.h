/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef SAMPLE_APPLICATION_H
#define SAMPLE_APPLICATION_H

#include <Renderer.h>
#include <RendererWindow.h>
#include <RendererDesc.h>

#include <FrameworkFoundation.h>

#include <SampleAssetManager.h>
#include <PsTime.h>
#include <PsPrintString.h>
#include "foundation/PxMat44.h"
#include <SampleUserInput.h>

namespace physx { 
	class PxProfileZone;
	class PxProfileZoneManager;
	class PxProfileEventSender;
}

#define SMOOTH_CAM

namespace SampleFramework
{

	class SampleCommandLine;

	template <typename T>
	class Transform
	{
	public:
		Transform() : m_dirty(true) {}

		void         setForwardTransform( const T& t )
		{ 
			m_fwd = t;
			m_dirty = true;
		}

		void         setInverseTransform( const T& t )
		{ 
			m_inv = t;
			m_fwd = t.inverseRT();
			m_dirty = false;
		}

		const T&	getForwardTransform() const
		{ 
			return m_fwd;
		}

		const T&	getInverseTransform() const
		{
			if(m_dirty)
			{
				m_inv = m_fwd.inverseRT();
				m_dirty = false;
			}
			return m_inv;
		}

	private:
		T    m_fwd;
		mutable T    m_inv;
		mutable bool m_dirty;
	};

	class SampleApplication : public SampleRenderer::RendererWindow
	{
	public:
		SampleApplication(const SampleCommandLine& cmdline, const char* assetPathPrefix="media", PxI32 camMoveButton = -1);
		virtual								~SampleApplication(void);
		SampleRenderer::Renderer*	getRenderer(void)								{ return m_renderer; }
		SampleAssetManager*			getAssetManager(void)							{ return m_assetManager; }
		inline const char*			getAssetPathPrefix(void)				const	{ return m_assetPathPrefix; }

		const PxMat44&				getEyeTransform(void)					const	{ return m_worldToView.getInverseTransform(); }
		void						setEyeTransform(const PxMat44& eyeTransform);
		void						setEyeTransform(const PxVec3& pos, const PxVec3& rot);
		void						setViewTransform(const PxMat44& viewTransform);
		const PxMat44&				getViewTransform(void)					const;

		const SampleCommandLine&	getCommandLine(void)					const	{ return m_cmdline; }

		virtual	void						onInit(void) = 0;
		virtual	void						onShutdown(void) = 0;

		virtual	float						tweakElapsedTime(float dtime)	{ return dtime;	}
		virtual	void						onTickPreRender(float dtime) = 0;
		virtual	void						onRender(void) = 0;
		virtual	void						onTickPostRender(float dtime) = 0;

		virtual	void						onOpen(void);
		virtual	bool						onClose(void);

		virtual	void						onDraw(void);

		virtual void						onAnalogInputEvent(const InputEvent& , float val);
		virtual void						onDigitalInputEvent(const InputEvent& , bool val);
		virtual void						onPointerInputEvent(const InputEvent&, physx::PxU32 x, physx::PxU32 y, physx::PxReal dx, physx::PxReal dy, bool val);

		virtual void						rotateCamera(PxF32 dx, PxF32 dy);
		virtual void						moveCamera(PxF32 dx, PxF32 dy);

		virtual	void						doInput(void);
		virtual void						fatalError(const char * msg);

		virtual PxF32						getRotationSpeedScale(void)		const	{ return m_rotationSpeedScale;	}
		virtual void						setRotationSpeedScale(PxF32 scale)		{ m_rotationSpeedScale = scale;	}
		virtual PxF32						getMoveSpeedScale(void)			const	{ return m_moveSpeedScale;		}
		virtual void						setMoveSpeedScale(PxF32 scale)			{ m_moveSpeedScale = scale;	}

		virtual bool						getRightStickRotate(void)		const	{ return m_rightStickRotate;	}
		virtual void						setRightStickRotate(bool rsr)			{ m_rightStickRotate = rsr;	}

		//Must be called when foundation is setup.
		virtual physx::PxProfileZone*			getOrCreateProfileZone(PxFoundation& inFoundation);
		virtual physx::PxProfileZone*			getOrCreateProfileZone(physx::PxProfileZoneManager& zoneManager);
		virtual physx::PxProfileZone*			getProfileZone() { return mProfileZone; }
		//Must be called when foundation is setup.
		virtual void							releaseProfileZone();
		virtual physx::PxProfileEventSender*	getEventBuffer();

	protected:

		virtual void						setupRendererDescription(SampleRenderer::RendererDesc& renDesc);

		const SampleCommandLine&			m_cmdline;

		physx::PxProfileZone*				mProfileZone;

		PxF32						m_sceneSize;

		SampleRenderer::Renderer*	m_renderer;

		char						m_assetPathPrefix[256];
		SampleAssetManager*			m_assetManager;

		PxVec3						m_eyeRot;
		Transform<PxMat44>			m_worldToView;

		PxI32						m_camMoveButton;

#if defined(SMOOTH_CAM)
		PxVec3						m_targetEyeRot;
		PxVec3						m_targetEyePos;
#endif
		physx::PxU64				m_timeCounter;
		physx::shdfnd::Time			m_time;
		PxF32						m_lastDTime;
		bool						m_disableRendering;

		void*						android_window_ptr;
		PxF32						m_rotationSpeedScale;
		PxF32						m_moveSpeedScale;

		bool						m_rightStickRotate;
		bool						m_rewriteBuffers;

	private:
		// get rid of C4512
		void						operator=(const SampleApplication&);
	};

} //namespace SampleFramework

#endif
