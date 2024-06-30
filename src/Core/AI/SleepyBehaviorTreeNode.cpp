#include "SleepyBehaviorTreeNode.h"

ENodeStatus SleepyBehaviorTreeNode::tick()
{
	if (!isRunning())
		OnInitialize();
	status = OnUpdate();
	if (!isRunning())
		OnTerminate();
	return status;
}

void CompositeNode::removeChild(SleepyBehaviorTreeNode* child)
{
	children->remove(child);
}

void CompositeNode::clearChildren() const
{
	children->clear();
}

void CompositeNode::addChild(SleepyBehaviorTreeNode* child)
{
	children->push_back(child);
}
