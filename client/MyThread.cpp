#include "MyThread.h"

MyThread::MyThread(QObject *parent)
	: QThread(parent)
{
}

MyThread::~MyThread()
{
	this->terminate();
	delete force_sk;
}


void MyThread::run()
{
	force_sk = new Connetion;
	force_sk->Connect_to_Server();
	force_sk->send_thread(name);
	Info_Pack tp;
	while (1)
	{
		tp = force_sk->Receive_Info_Pack();
		switch (tp.type) {

		case Connetion::KILL_TYPE: {
			//强行关闭
			printf("get_kill\n");
			if (win_type == Player::type_risker)Risk_Win->close();
			else Test_Win->close();
			break;//任务结束，离开
		}
		case Connetion::BUMP_TYPE: {
			force_sk->send_bump(name);
			printf("bump send\n");
			break;
		}
		case Connetion::ACCEPT_TYPE: {
			Risk_Win->he_accept_you();
			break;
		}
		case Connetion::CHALLEGE_TYPE: {
			Risk_Win->he_challege_you(tp.name);
			break;
		}
		case Connetion::BUSY_TYPE: {
			Risk_Win->he_is_busy();
			break;
		}
		case Connetion::REFUSE_TYPE: {
			Risk_Win->he_refuse_you();
			break;
		}
		case Connetion::END_TYPE: {
			Risk_Win->set_result_flag();
			Risk_Win->show_he_result(tp.score);
			break;
		}
		case Connetion::OFFLINE_TYPE: {
			Risk_Win->he_offline();
			break;
		}
		}
	}

}

void MyThread::get_win(TestmakerWindow *__Test_Win) {
	win_type = Player::type_testmaker;
	this->Test_Win = __Test_Win;
	name = Test_Win->get_name();
}

void MyThread::get_win(RiskerWindow * __Risk_Win) {
	win_type = Player::type_risker;
	this->Risk_Win = __Risk_Win;
	name = Risk_Win->get_name();
}