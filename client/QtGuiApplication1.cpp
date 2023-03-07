#include "QtGuiApplication1.h"
#include<stdio.h>
#include<random>
QtGuiApplication1::QtGuiApplication1(QWidget *parent)
	: QMainWindow(parent)
{
	user_for_check = new Player();
	ui.setupUi(this);
	QObject::connect(ui.login, SIGNAL(clicked()), this, SLOT(ClickLogin()));
	QObject::connect(ui.force_button, SIGNAL(clicked()), this, SLOT(ForceLogin()));
	ui.login->setShortcut(Qt::Key_Return);//�س����¼
	QObject::connect(ui.regis, SIGNAL(clicked()), this, SLOT(ClickRegister()));
	ui.passwd->setEchoMode(QLineEdit::Password);

	ui.force_button->hide();
}
QtGuiApplication1::~QtGuiApplication1() {
	std::cout << "~QtGuiApplication1" << std::endl;
	delete user_for_check;
}
void QtGuiApplication1::ClickLogin()
{
	//what you want to do
	QString Qsname = ui.username->text();
	QString Qspasswd = ui.passwd->text();
	std::string string_name = Qsname.toStdString();
	std::string string_passwd = Qspasswd.toStdString();
	if (user_for_check->Player_login(string_name) && check_passwd(string_name, string_passwd))
	{
		//Connetion *sk = new Connetion;
		///*
		//����һ��sock����������ܵ�¼���ֱ��delete
		//����ᴫ��������¼�Ĵ����е�user����
		//�����ڹر�user������delete sock
		//*/
		//if (!sk->Connect_to_Server()) {
		//	QMessageBox::warning(NULL, QStringLiteral("֪ͨ"), QStringLiteral("���Ѿ��Ͽ����ӣ������������"), QMessageBox::Yes, QMessageBox::Yes);
		//	delete sk;
		//	return;
		//}
		////sk->send_force(string_name);
		//sk->send_name(string_name);
		//int line_type = sk->Receive_Info_Pack().type;
		//if (line_type == Connetion::OFFLINE_TYPE) {
		//	printf("OK\n");
		//}
		//else if (line_type == Connetion::ONLINE_TYPE) {
		//	printf("BOMM\n");
		//	QMessageBox::warning(NULL, QStringLiteral("֪ͨ"), QStringLiteral("������Ŷ"), QMessageBox::Yes, QMessageBox::Yes);
		//	delete sk;
		//	ui.force_button->show();
		//	return;
		//}
		//else {
		//	QMessageBox::warning(NULL, QStringLiteral("֪ͨ"), QStringLiteral("����������"), QMessageBox::Yes, QMessageBox::Yes);
		//	delete sk;
		//	return;
		//}
		/*������������򿪴���*/
		if (user_for_check->get_type() == Player::type_testmaker) {//testmaker
			TesmW = new TestmakerWindow();
			TesmW->setAttribute(Qt::WA_DeleteOnClose, true);
			TesmW->user_login(string_name);//login��ʱ��ˢ���´��ڵ���Ϣ��ˢ�����ʾ
			//TesmW->get_sock(sk);
			TesmW->show();
			//MyThread *win_thread = new MyThread(TesmW);
			//win_thread->get_win(TesmW);
			//win_thread->start();
		}
		else {//player
			RskW = new RiskerWindow();
			RskW->setAttribute(Qt::WA_DeleteOnClose, true);
			RskW->user_login(string_name);
			//RskW->get_sock(sk);
			RskW->show();
			///MyThread *win_thread = new MyThread(RskW);
			//win_thread->get_win(RskW);
			//win_thread->start();
		}
	}
	else {
		QMessageBox::warning(NULL, QStringLiteral("֪ͨ"), QStringLiteral("�û��������ڻ����������Ŷ"), QMessageBox::Yes, QMessageBox::Yes);
	}
}
//void QtGuiApplication1::ForceLogin() {
//	QString Qsname = ui.username->text();
//	QString Qspasswd = ui.passwd->text();
//	std::string string_name = Qsname.toStdString();
//	std::string string_passwd = Qspasswd.toStdString();
//	if (user_for_check->Player_login(string_name) && check_passwd(string_name, string_passwd))
//	{
//		Connetion *sk = new Connetion;
//		/*
//		����һ��sock����������ܵ�¼���ֱ��delete
//		����ᴫ��������¼�Ĵ����е�user����
//		�����ڹر�user������delete sock
//		*/
//		if (!sk->Connect_to_Server()) {
//			QMessageBox::warning(NULL, QStringLiteral("֪ͨ"), QStringLiteral("���Ѿ��Ͽ����ӣ������������"), QMessageBox::Yes, QMessageBox::Yes);
//			delete sk;
//			return;
//		}
//		sk->send_force(string_name);//ǿ�Ǻ�ɾ�������´���
//		if (sk->Receive_Info_Pack().type == Connetion::OFFLINE_TYPE)
//			/*������������򿪴���*/
//		{
//			if (user_for_check->get_type() == Player::type_testmaker) {//testmaker
//				TesmW = new TestmakerWindow();
//				TesmW->setAttribute(Qt::WA_DeleteOnClose, true);
//				TesmW->user_login(string_name);//login��ʱ��ˢ���´��ڵ���Ϣ��ˢ�����ʾ
//				TesmW->get_sock(sk);
//				TesmW->show();
//				MyThread *win_thread = new MyThread(TesmW);//����һ����
//				win_thread->get_win(TesmW);
//				win_thread->start();
//			}
//			else {//player
//				RskW = new RiskerWindow();
//				RskW->setAttribute(Qt::WA_DeleteOnClose, true);
//				RskW->user_login(string_name);
//				RskW->get_sock(sk);
//				RskW->show();
//				MyThread *win_thread = new MyThread(RskW);
//				win_thread->get_win(RskW);
//				win_thread->start();
//			}
//		}
//		else {//COLLD_TYPE
//			QMessageBox::warning(NULL, QStringLiteral("֪ͨ"), QStringLiteral("ϵͳ��æ����һ���ٳ���Ŷ"), QMessageBox::Yes, QMessageBox::Yes);
//			return;
//		}
//	}
//	else {
//		QMessageBox::warning(NULL, QStringLiteral("֪ͨ"), QStringLiteral("�û��������ڻ����������Ŷ"), QMessageBox::Yes, QMessageBox::Yes);
//		return;
//	}
//}
void QtGuiApplication1::ClickRegister()
{
	//this->hide();
	RgsW = new RegisterWindow();
	RgsW->setAttribute(Qt::WA_DeleteOnClose, true);
	RgsW->show();
}
