#pragma once

#include <QWidget>
#include <QLabel>

class SleepyPet : public QWidget
{
	Q_OBJECT

public:
	SleepyPet(QWidget *parent = nullptr);
	~SleepyPet();

	void updateRoleAnimation();
	bool eventFilter(QObject* watched, QEvent* event) override;

private:
	QTimer* longPressTimer;
	QLabel* mainShow;
	bool canMove;
	int current;

private slots:
	inline void allowMove();
};
