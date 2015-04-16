/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef _SAMPLE_TREE_H
#define	_SAMPLE_TREE_H

#include "foundation/Px.h"

namespace SampleFramework
{

class Tree
{
public:
	class Node
	{
	public:
		Node() : mParent(NULL), mHead(NULL), mTail(NULL), mPrev(NULL), mNext(NULL)
		{
		}

	private:
		Node(const Node& node);
		Node& operator=(const Node& node);

	public:
		PX_FORCE_INLINE	bool	isRoot()			const	{ return NULL == mParent; }
		PX_FORCE_INLINE	bool	isLeaf()			const	{ return NULL == mHead; }

		PX_FORCE_INLINE	Node*	getParent()			const	{ return mParent; }
		PX_FORCE_INLINE	Node*	getFirstChild()		const	{ return mHead; }
		PX_FORCE_INLINE	Node*	getLastChild()		const	{ return mTail; }
		PX_FORCE_INLINE	Node*	getPrevSibling()	const	{ return mPrev; }
		PX_FORCE_INLINE	Node*	getNextSibling()	const	{ return mNext; }

		PX_FORCE_INLINE	Node*	getFirstLeaf()		const	{ return NULL == mHead ? const_cast<Node*>(this) : mHead->getFirstLeaf(); }
		PX_FORCE_INLINE	Node*	getLastLeaf()		const	{ return NULL == mTail ? const_cast<Node*>(this) : mTail->getLastLeaf(); }

		bool	isOffspringOf(const Node& node)		const
		{
			return (this == &node) || (NULL != mParent && mParent->isOffspringOf(node));
		}

	public:
		bool appendChild(Node& node);
		bool removeChild(Node& node);

	private:
		Node*	mParent;
		Node*	mHead;
		Node*	mTail;
		Node*	mPrev;
		Node*	mNext;
	};
};

} // namespace SampleFramework

#endif
