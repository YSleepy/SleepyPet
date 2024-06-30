#pragma once
#include <functional>
#include <memory>
#include <random>
#include <vector>
#include <QWidget>

//节点运行状态,成功，失败，运行中，终止，无效
enum class ENodeStatus { Success, Failure, Running, Aborted, Invalid };

//AI行为树节点基类
class SleepyBehaviorTreeNode :public QObject
{
public:

	explicit SleepyBehaviorTreeNode(QObject* parent = nullptr) :QObject(parent){}
	~SleepyBehaviorTreeNode() override = default;

	bool isRunning() const { return status == ENodeStatus::Running; }
	bool isFailure() const { return status == ENodeStatus::Failure; }
	bool isSuccess() const { return status == ENodeStatus::Success; }
	bool isTerminated() const { return status == ENodeStatus::Aborted; }

	virtual ENodeStatus tick();
	virtual void addChild(SleepyBehaviorTreeNode* child){}
	void reSet(){status = ENodeStatus::Invalid;}
	void Abort()
	{
		OnTerminate();
		status = ENodeStatus::Aborted;
	}

protected:
	virtual void OnInitialize() {}
	virtual void OnTerminate() {}
	virtual ENodeStatus OnUpdate() = 0;

protected:
	ENodeStatus status = ENodeStatus::Invalid;
};

/////////////////////////////////////////////////////////////

//控制器基类
class SleepyCompositeNode : public SleepyBehaviorTreeNode
{
public:
	SleepyCompositeNode(std::initializer_list<SleepyBehaviorTreeNode*> actions,QObject* parent = nullptr)
	:SleepyBehaviorTreeNode(parent),
	children(new std::vector<SleepyBehaviorTreeNode*>(actions))
	{}

	void addChild(SleepyBehaviorTreeNode* child)override;

protected:
	std::vector<SleepyBehaviorTreeNode*>* children;
};

//顺序节点
class SleepySequenceNode : public SleepyCompositeNode {
public:
	using SleepyCompositeNode::SleepyCompositeNode;

	void OnInitialize()override;
	ENodeStatus OnUpdate() override;

protected:
	std::vector<SleepyBehaviorTreeNode*>::iterator currentChild ;
};

//选择节点
class SleepySelectorNode : public SleepySequenceNode
{
public:
	using SleepySequenceNode::SleepySequenceNode;

		ENodeStatus OnUpdate()override
		{
			while (true)
			{
				const auto status = (*currentChild)->tick();
				if (status != ENodeStatus::Failure)
					return status;
				currentChild = ++currentChild;
				if (currentChild == children->end())
					return ENodeStatus::Failure;
			}
		}

};

//随机选择节点
class SleepyRandomSelectorNode : public SleepySequenceNode {
public:
	using SleepySequenceNode::SleepySequenceNode;

	ENodeStatus tick() override {
		// 随机选择一个动作执行
		const int index = std::uniform_int_distribution<int>(0, children->size() - 1)(generator);
		const ENodeStatus re = (*children)[index]->tick();
		return re;
	}

protected:
	std::mt19937 generator{ std::random_device{}() };
};

//////////////////////////////////////////////////////////////////

class SleepyDecoratorNode : SleepyBehaviorTreeNode
{
public:
	SleepyDecoratorNode(SleepyBehaviorTreeNode* child, QObject* parent = nullptr)
		:SleepyBehaviorTreeNode(parent), child(child) {}

protected:
	SleepyBehaviorTreeNode* child;
};

//重复执行节点，当limit为-1时，无限重复
class SleepyRePeatNode : public SleepyDecoratorNode
{
public:
	SleepyRePeatNode(SleepyBehaviorTreeNode* node, int limit, QObject* parent = nullptr)
	:SleepyDecoratorNode(node), limit(limit), count(0) {}
protected:
	void OnInitialize()override
	{
		count = 0;//进入时，将次数清零
	}
private:
	int limit;
	int count;
};

/////////////////////////////////////////////////////////////////
class ActionNode : public SleepyBehaviorTreeNode {
public:
	ActionNode(std::function<ENodeStatus()> action, SleepyBehaviorTreeNode* nextNode = nullptr , QObject* parent = nullptr)
	: SleepyBehaviorTreeNode(parent),
	action(std::move(action)),
	nextNode(nextNode)
	{
		
	}

	ENodeStatus tick() override {
		return action();
	}

private:
	std::function<ENodeStatus()> action;
	SleepyBehaviorTreeNode* nextNode ;
};




