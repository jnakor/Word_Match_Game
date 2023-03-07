#include "Online_Window.h"

Online_Window::Online_Window(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	QObject::connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(display_names()));
}

Online_Window::~Online_Window()
{
}

void Online_Window::get_sock(Connetion *__sk) {
	this->sk = __sk;
}

void Online_Window::get_online_people() {

	sk->send_online();
	Users_Pack tp = sk->Receive_Users_Pack();
	for (int i = 0; i < tp.number; i++) {
		names_list.push_back(tp.user_names[i]);
	}
}

void Online_Window::refresh_clear() {
	ui.online_list->clear();
	names_list.clear();
	get_online_people();
}

void Online_Window::display_names() {
	refresh_clear();
	for (int i = 0; i < names_list.size(); i++)
	{
		ui.online_list->addItem(QString::fromStdString(names_list[i]));
	}
}