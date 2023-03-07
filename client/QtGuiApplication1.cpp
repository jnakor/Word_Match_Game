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
	ui.login->setShortcut(Qt::Key_Return);//回车绑登录
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
		//产生一个sock句柄，若不能登录则会直接delete
		//否则会传入我所登录的窗口中的user对象，
		//当窗口关闭user析构会delete sock
		//*/
		//if (!sk->Connect_to_Server()) {
		//	QMessageBox::warning(NULL, QStringLiteral("通知"), QStringLiteral("你已经断开连接，请检查你的网络"), QMessageBox::Yes, QMessageBox::Yes);
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
		//	QMessageBox::warning(NULL, QStringLiteral("通知"), QStringLiteral("正在玩哦"), QMessageBox::Yes, QMessageBox::Yes);
		//	delete sk;
		//	ui.force_button->show();
		//	return;
		//}
		//else {
		//	QMessageBox::warning(NULL, QStringLiteral("通知"), QStringLiteral("服务器错误"), QMessageBox::Yes, QMessageBox::Yes);
		//	delete sk;
		//	return;
		//}
		/*接下来分情况打开窗口*/
		if (user_for_check->get_type() == Player::type_testmaker) {//testmaker
			TesmW = new TestmakerWindow();
			TesmW->setAttribute(Qt::WA_DeleteOnClose, true);
			TesmW->user_login(string_name);//login的时候刷新新窗口的信息，刷完才显示
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
		QMessageBox::warning(NULL, QStringLiteral("通知"), QStringLiteral("用户名不存在或者密码错误哦"), QMessageBox::Yes, QMessageBox::Yes);
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
//		产生一个sock句柄，若不能登录则会直接delete
//		否则会传入我所登录的窗口中的user对象，
//		当窗口关闭user析构会delete sock
//		*/
//		if (!sk->Connect_to_Server()) {
//			QMessageBox::warning(NULL, QStringLiteral("通知"), QStringLiteral("你已经断开连接，请检查你的网络"), QMessageBox::Yes, QMessageBox::Yes);
//			delete sk;
//			return;
//		}
//		sk->send_force(string_name);//强登后删除交给新窗口
//		if (sk->Receive_Info_Pack().type == Connetion::OFFLINE_TYPE)
//			/*接下来分情况打开窗口*/
//		{
//			if (user_for_check->get_type() == Player::type_testmaker) {//testmaker
//				TesmW = new TestmakerWindow();
//				TesmW->setAttribute(Qt::WA_DeleteOnClose, true);
//				TesmW->user_login(string_name);//login的时候刷新新窗口的信息，刷完才显示
//				TesmW->get_sock(sk);
//				TesmW->show();
//				MyThread *win_thread = new MyThread(TesmW);//父子一起死
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
//			QMessageBox::warning(NULL, QStringLiteral("通知"), QStringLiteral("系统繁忙，等一下再尝试哦"), QMessageBox::Yes, QMessageBox::Yes);
//			return;
//		}
//	}
//	else {
//		QMessageBox::warning(NULL, QStringLiteral("通知"), QStringLiteral("用户名不存在或者密码错误哦"), QMessageBox::Yes, QMessageBox::Yes);
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
