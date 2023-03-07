#pragma once

#include <QThread>
#include "Connetion.h"
#include "TestmakerWindow.h"
#include "RiskerWindow.h"

class MyThread : public QThread
{
	Q_OBJECT

public:
	MyThread(QObject *parent);
	~MyThread();
	void get_win(TestmakerWindow *__Test_Win);
	void get_win(RiskerWindow * __Risk_Win);
protected:
	virtual void run();
private:
	TestmakerWindow *Test_Win;//�����ҹ�
	RiskerWindow *Risk_Win;//�����ҹ�
	int win_type;
	std::string name;
	Connetion *force_sk;

};
