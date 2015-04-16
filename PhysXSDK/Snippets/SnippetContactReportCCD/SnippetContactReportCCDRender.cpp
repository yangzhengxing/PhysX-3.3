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

#ifdef RENDER_SNIPPET

#include <vector>

#include "PxPhysicsAPI.h"
#include "../SnippetRender/SnippetRender.h"
#include "../SnippetRender/SnippetCamera.h"

using namespace physx;

extern void initPhysics(bool interactive);
extern void stepPhysics(bool interactive);	
extern void cleanupPhysics(bool interactive);

extern std::vector<PxVec3> gContactPositions;
extern std::vector<PxVec3> gContactImpulses;
extern std::vector<PxVec3> gContactSphereActorPositions;
std::vector<PxVec3> gContactVertices;

namespace
{
Snippets::Camera*	sCamera;

void motionCallback(int x, int y)
{
	sCamera->handleMotion(x, y);
}

void keyboardCallback(unsigned char key, int x, int y)
{
	if(key==27)
		exit(0);

	sCamera->handleKey(key, x, y);
}

void mouseCallback(int button, int state, int x, int y)
{
	sCamera->handleMouse(button, state, x, y);
}

void idleCallback()
{
	glutPostRedisplay();
}

void renderCallback()
{
	stepPhysics(true);

	Snippets::startRender(sCamera->getEye(), sCamera->getDir());

	PxScene* scene;
	PxGetPhysics().getScenes(&scene,1);
	PxU32 nbActors = scene->getNbActors(PxActorTypeSelectionFlag::eRIGID_DYNAMIC | PxActorTypeSelectionFlag::eRIGID_STATIC);
	if(nbActors)
	{
		std::vector<PxRigidActor*> actors(nbActors);
		scene->getActors(PxActorTypeSelectionFlag::eRIGID_DYNAMIC | PxActorTypeSelectionFlag::eRIGID_STATIC, (PxActor**)&actors[0], nbActors);
		Snippets::renderActors(&actors[0], PxU32(actors.size()), true);
	}

	if(gContactPositions.size())
	{
		gContactVertices.clear();
		for(PxU32 i=0; i < gContactPositions.size(); i++)
		{
			gContactVertices.push_back(gContactPositions[i]);
			gContactVertices.push_back(gContactPositions[i]-gContactImpulses[i]*0.0001f);
		}
		glDisable(GL_LIGHTING);
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, &gContactVertices[0]);
		glDrawArrays(GL_LINES, 0, GLint(gContactVertices.size()));
		glDisableClientState(GL_VERTEX_ARRAY);
		glEnable(GL_LIGHTING);
	}

	if(gContactSphereActorPositions.size())
	{
		gContactVertices.clear();
		for(PxU32 i=0; i < gContactSphereActorPositions.size() - 1; i++)
		{
			gContactVertices.push_back(gContactSphereActorPositions[i]);
			gContactVertices.push_back(gContactSphereActorPositions[i+1]);
		}
		glDisable(GL_LIGHTING);
		glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, &gContactVertices[0]);
		glDrawArrays(GL_LINES, 0, GLint(gContactVertices.size()));
		glDisableClientState(GL_VERTEX_ARRAY);
		glEnable(GL_LIGHTING);
	}

	Snippets::finishRender();
}

void exitCallback(void)
{
	delete sCamera;
	cleanupPhysics(true);
}
}

void renderLoop()
{
	sCamera = new Snippets::Camera(PxVec3(-1.5f, 6.0f, 14.0f), PxVec3(-0.1f,0.0f,-0.7f));

	Snippets::setupDefaultWindow("PhysX Snippet ContactReport CCD");
	Snippets::setupDefaultRenderState();

	glutIdleFunc(idleCallback);
	glutDisplayFunc(renderCallback);
	glutKeyboardFunc(keyboardCallback);
	glutMouseFunc(mouseCallback);
	glutMotionFunc(motionCallback);
	motionCallback(0,0);

	atexit(exitCallback);

	initPhysics(true);
	glutMainLoop();
}
#endif
