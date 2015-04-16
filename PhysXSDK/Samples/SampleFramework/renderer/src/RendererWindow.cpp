/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */
#include <RendererWindow.h>
#include <RendererMemoryMacros.h>
#include <SamplePlatform.h>
#include <stdio.h>

using namespace SampleRenderer;

RendererWindow::RendererWindow(void) : m_platform(NULL), m_isOpen(false)
{
	m_platform = SampleFramework::createPlatform(this);
}

bool RendererWindow::hasFocus() const
{
	return m_platform->hasFocus();
}

void RendererWindow::setFocus(bool b) 
{
	m_platform->setFocus(b);
}

RendererWindow::~RendererWindow(void)
{
	DELETESINGLE(m_platform);
}

bool RendererWindow::open(PxU32 width, PxU32 height, const char *title, bool fullscreen)
{
	bool ok         = false;
	RENDERER_ASSERT(width && height, "Attempting to open a window with invalid width and/or height.");
	if(width && height)
	{
		ok = m_platform->openWindow(width, height, title, fullscreen);
#if !defined(RENDERER_WINDOWS)
		m_isOpen = true;
#endif
	}
	return ok;
}

void RendererWindow::close(void)
{
	m_platform->closeWindow();
#if !defined(RENDERER_WINDOWS)
	if(isOpen())
	{
		m_isOpen = false;
		onClose();
	}
#endif
}

bool RendererWindow::isOpen(void) const
{
	bool open = m_platform->isOpen();
#if !defined(RENDERER_WINDOWS)
	open = m_isOpen;
#endif
	return open;
}

// update the window's state... handle messages, etc.
void RendererWindow::update(void)
{
	m_platform->update();

#if defined(RENDERER_ANDROID)
	if (!m_platform->isOpen())
		return;
#endif
}

void RendererWindow::setSize(PxU32 width, PxU32 height)
{
	m_platform->setWindowSize(width, height);
}

// get the window's title...
void RendererWindow::getTitle(char *title, PxU32 maxLength) const
{
	m_platform->getTitle(title, maxLength);
}

// set the window's title...
void RendererWindow::setTitle(const char *title)
{
	m_platform->setTitle(title);
}
