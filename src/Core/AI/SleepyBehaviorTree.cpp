#include "SleepyBehaviorTree.h"

SleepyBehaviorTree::SleepyBehaviorTree(std::shared_ptr<SleepyBehaviorTreeNode> root): rootNode(std::move(root))
{
	
}

void SleepyBehaviorTree::tick()
{
	if (rootNode) {
		rootNode->tick();
	}
}
