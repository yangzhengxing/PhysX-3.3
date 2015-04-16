/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef _SAMPLE_XML_H
#define	_SAMPLE_XML_H

#include "PsFastXml.h"
#include "PsPrintString.h"
#include "SampleTree.h"

namespace FAST_XML
{

class xml_node : private SampleFramework::Tree::Node
{
public:
	xml_node(const char* name, const char* data, const physx::shdfnd::FastXml::AttributePairs& attr)
		: mName(name), mData(data)
	{
		PX_ASSERT( (attr.getNbAttr()*2+1) < MAX_ARGS);
		for(physx::PxI32 i=0; i<attr.getNbAttr(); i++)
		{
			mArgv[i*2] = attr.getKey(i);
			mArgv[i*2+1] = attr.getValue(i);
		}
		physx::shdfnd::FastXml::AttributePairs tmp(attr.getNbAttr()*2, mArgv);
		mAttr = tmp;
	}

	~xml_node()
	{
		xml_node* node = first_node();
		while (node != NULL)
		{
			xml_node* child = node;
			node = node->next_sibling();
			delete child;
		}
	}

public:
	xml_node* parent() const { return static_cast<xml_node*>(getParent()); }
	xml_node* first_node() const { return static_cast<xml_node*>(getFirstChild()); }
	xml_node* next_sibling() const { return static_cast<xml_node*>(getNextSibling()); }
	bool append_node(xml_node& node) { return appendChild(node); }

	xml_node* first_node(const char* name) const
	{
		for (xml_node* node = first_node(); node != NULL; node = node->next_sibling())
		{
			if (0 == strcmp(node->name(), name))
			{
				return node;
			}
		}

		return NULL;
	}

public:
	const char* name() const { return mName; }
	const char* value() const { return mData; }
	const char *getXMLAttribute(const char *attr) const
	{
		return mAttr.get(attr);
	}

private:
	static const physx::PxI32 MAX_ARGS = 50;

	const char*		mName;
	const char*		mData;	
	const char*		mArgv[MAX_ARGS];
	physx::shdfnd::FastXml::AttributePairs mAttr;
};

class XmlBuilder : public physx::shdfnd::FastXml::Callback
{
public:
	XmlBuilder() : mRoot(NULL), mThis(NULL) {}
	virtual ~XmlBuilder()
	{
		delete mRoot;
	}

public:
	xml_node* rootnode() const { return mRoot; }

	virtual bool processComment(const char *comment)
	{
		return true;
	}

	virtual bool processClose(const char *element, physx::PxU32 depth, bool &isError)
	{
		mThis = mThis->parent();
		return true;
	}

	virtual bool processElement(
			const char *elementName,   // name of the element
			const char  *elementData,  // element data, null if none
			const physx::shdfnd::FastXml::AttributePairs& attr,      // attributes
			physx::PxI32 lineno)
	{
		xml_node* node = new xml_node(elementName, elementData, attr);

		if (NULL != mThis)
			mThis->append_node(*node);
		else if (NULL == mRoot)
			mRoot = node;
		else
		{
			physx::shdfnd::printFormatted("error: more than 1 root node in xml file\n");
			return false;
		}

		mThis = node;
		return true;
	}

	virtual void*	allocate(physx::PxU32 size)
	{
		return malloc(size);
	}

	virtual void	deallocate(void *mem)
	{
		free(mem);
	}

private:
	xml_node*	mRoot;
	xml_node*	mThis;
};

}

#endif
