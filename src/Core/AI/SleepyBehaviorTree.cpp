#include "SleepyBehaviorTree.h"

SleepyBehaviorTree::SleepyBehaviorTree(SleepyBehaviorTreeNode* root): rootNode(root)
{
	
}

void SleepyBehaviorTree::tick()const
{
	if (rootNode) {
		rootNode->tick();
	}
}
