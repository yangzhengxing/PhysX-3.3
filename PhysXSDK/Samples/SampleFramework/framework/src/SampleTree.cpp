/*
 * Copyright (c) 2008-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#include "SampleTree.h"

using namespace SampleFramework;

bool Tree::Node::appendChild(Node& node)
{
	if (!node.isRoot() || isOffspringOf(node))
		return false;

	node.mParent = this;
	node.mPrev = mTail;

	if (NULL == mTail)
		mHead = &node;
	else
		mTail->mNext = &node;

	mTail = &node;

	return true;
}

bool Tree::Node::removeChild(Node& node)
{
	if (this != node.mParent)
		return false;

	Node*	prev = node.mPrev;
	Node*	next = node.mNext;

	if (NULL == prev)
		mHead = next;
	else
		prev->mNext = next;

	if (NULL == next)
		mTail = prev;
	else
		next->mPrev = prev;

	node.mParent = NULL;
	return true;
}
