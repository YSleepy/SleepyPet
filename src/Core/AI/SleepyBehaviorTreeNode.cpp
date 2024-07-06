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



void SleepyCompositeNode::addChild(SleepyBehaviorTreeNode* child)
{
	children->push_back(child);
}

void SleepyCompositeNode::addChildren(std::initializer_list<SleepyBehaviorTreeNode*> actions)const
{
	children->assign(actions);
}

void SleepySequenceNode::OnInitialize()
{
	currentChild = children->begin();//从第一个子节点开始
}

ENodeStatus SleepySequenceNode::OnUpdate()
{
	while (true)
	{
		const auto status = (*currentChild)->tick();
		if (status != ENodeStatus::Success) return status;
		currentChild = ++currentChild;
		if (currentChild == children->end())return ENodeStatus::Success;
	}
}

ENodeStatus SleepyRePeatNode::OnUpdate()
{
	while (true)
	{
		child->tick();
		if(child->isRunning())return ENodeStatus::Running;
		if(child->isFailure())return ENodeStatus::Failure;
		//if (limit == -1)return ENodeStatus::Running;
		if(child->isSuccess()&&limit == -1)
		{
			continue;
		}
		if (++count == limit)return ENodeStatus::Success;
	}
}
