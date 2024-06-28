#pragma once

#include <QObject>

class SleepyAnimation  : public QObject
{
	Q_OBJECT

public:
	SleepyAnimation(QObject *parent,bool bIsUsedIFGArray,float IFG);
	~SleepyAnimation();
	void setAnimationWithBedinEnd(int animationBegin, int animationEnd);

	//使用序列号加每帧间隔时长组成动画
	void setIFGArray(const QVector<float>& IFGArray);
	void setSequenceArray(const QVector<int>& SequenceArray);

	void setIsUsedSequenceArray(bool isUsed);
	float getIFG() const { return IFG; }
	void resetAnimation();

public:
	bool bIsUsedIFGArray;
	//bool bUsedGif;
	int animationBegin;
	int animationEnd;
	QVector<int> SequenceArray;
	QVector<float> IFGArray;
	float IFG;
	int current;
	int SequenceArraycursor;
};
