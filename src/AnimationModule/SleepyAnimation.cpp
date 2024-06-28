#include "SleepyAnimation.h"

SleepyAnimation::SleepyAnimation(QObject *parent, bool bIsUsedIFGArray, float IFG)
	: QObject(parent),bIsUsedIFGArray(bIsUsedIFGArray),IFG(IFG)
{}

SleepyAnimation::~SleepyAnimation()
{}

void SleepyAnimation::setAnimationWithBedinEnd(int animationBegin, int animationEnd)
{
	this->animationBegin = animationBegin;
	this->current = animationBegin;
	this->animationEnd = animationEnd;
}

void SleepyAnimation::setIFGArray(const QVector<float>& IFGArray)
{
	this->IFGArray = IFGArray;
}

void SleepyAnimation::setSequenceArray(const QVector<int>& SequenceArray)
{
	if(!SequenceArray.isEmpty())
	{
		this->SequenceArray = SequenceArray;
		this->current = this->SequenceArray.at(0);
		this->SequenceArraycursor = 0;
	}
}

void SleepyAnimation::setIsUsedSequenceArray(bool isUsed)
{
	this->bIsUsedIFGArray = isUsed;
}

void SleepyAnimation::resetAnimation()
{
	if(!SequenceArray.isEmpty())
	{
		this->current = this->SequenceArray.at(0);
		this->SequenceArraycursor = 0;
	}else
	{
		this->current = this->animationBegin;
	}
}

