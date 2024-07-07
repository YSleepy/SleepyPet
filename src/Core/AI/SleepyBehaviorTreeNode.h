#pragma once
#include <functional>
#include <memory>
#include <random>
#include <vector>
#include <QWidget>
#include <QObject>

//节点运行状态,成功，失败，运行中，终止，无效
enum class ENodeStatus { Success, Failure, Running, Aborted, Invalid };

//AI行为树节点基类
class SleepyBehaviorTreeNode :public QObject
{
	Q_OBJECT
public:

	SleepyBehaviorTreeNode(QObject* parent = nullptr) :QObject(parent){}
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
	SleepyCompositeNode(QObject* parent = nullptr)
	:SleepyBehaviorTreeNode(parent),
	children(new std::vector<SleepyBehaviorTreeNode*>()){}

	SleepyCompositeNode(std::initializer_list<SleepyBehaviorTreeNode*> actions,QObject* parent = nullptr)
	:SleepyBehaviorTreeNode(parent),
	children(new std::vector<SleepyBehaviorTreeNode*>(actions))
	{}

	void addChild(SleepyBehaviorTreeNode* child)override;
	void addChildren(std::initializer_list<SleepyBehaviorTreeNode*> actions)const;

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
	std::vector<SleepyBehaviorTreeNode*>::iterator staging;
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

	ENodeStatus OnUpdate() override {
		// 随机选择一个动作执行
		const int index = std::uniform_int_distribution<int>(0, static_cast<int>(children->size() - 1))(generator);
		currentChild = children->begin() + index;
		const ENodeStatus re = (*children)[index]->tick();
		return re;
	}

protected:
	std::mt19937 generator{ std::random_device{}() };
};

//////////////////////////////////////////////////////////////////

class SleepyDecoratorNode :public SleepyBehaviorTreeNode
{
public:
	SleepyDecoratorNode(QObject* parent = nullptr)
		:SleepyBehaviorTreeNode(parent), child(nullptr) {}

	void setChild(SleepyBehaviorTreeNode* childNode) { this->child = childNode; }
protected:
	SleepyBehaviorTreeNode* child;
};

//重复执行节点，当limit为-1时，无限重复
class SleepyRePeatNode : public SleepyDecoratorNode
{
public:
	SleepyRePeatNode(int limit, QObject* parent = nullptr)
	:SleepyDecoratorNode(parent), limit(limit), count(0) {}
protected:
	void OnInitialize()override
	{
		count = 0;//进入时，将次数清零
	}
	ENodeStatus OnUpdate()override;
private:
	int limit;
	int count;
};

/////////////////////////////////////////////////////////////////
class SleepyActionNode : public SleepyBehaviorTreeNode {
public:
	SleepyActionNode(QObject* parent = nullptr)
	:SleepyBehaviorTreeNode(parent),
	action(nullptr)
	{
		
	}

	SleepyActionNode(std::function<ENodeStatus()> action, QObject* parent = nullptr)
	: SleepyBehaviorTreeNode(parent),
	action(std::move(action))
	{
		
	}

	void setAction(std::function<ENodeStatus()> actionFun) { this->action = std::move(actionFun); }

protected:
	ENodeStatus OnUpdate() override {
		return action();
	}

private:
	std::function<ENodeStatus()> action;
};




