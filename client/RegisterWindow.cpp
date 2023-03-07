#include "RegisterWindow.h"
#include "Testmaker.h"
#include "Risker.h"
RegisterWindow::RegisterWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QObject::connect(ui.testmaker_regis, SIGNAL(clicked()), this, SLOT(testmaker_ClickRegister()));
	QObject::connect(ui.risker_regis, SIGNAL(clicked()), this, SLOT(risker_ClickRegister()));
}

RegisterWindow::~RegisterWindow()
{

}
void RegisterWindow::testmaker_ClickRegister()
{
	Testmaker newuser;
	QString str = ui.username->text();
	QString pass_str = ui.passwd->text();
	std::string string_name = str.toStdString();
	std::string string_passwd = pass_str.toStdString();
	if (string_name == "" || string_passwd == "") {
		QMessageBox::warning(NULL, QStringLiteral("֪ͨ~"), QStringLiteral("���ܲ�����Ŷ"), QMessageBox::Yes, QMessageBox::Yes);
	}
	else if (newuser.testmaker_register(string_name, string_passwd)) {
		QMessageBox::warning(NULL, QStringLiteral("֪ͨ~"), QStringLiteral("ע��ɹ���"), QMessageBox::Yes, QMessageBox::Yes);
		this->hide();
	}
	else {
		QMessageBox::warning(NULL, QStringLiteral("֪ͨ"), QStringLiteral("�����Ѿ��������أ���һ����"), QMessageBox::Yes, QMessageBox::Yes);
	}
}
void RegisterWindow::risker_ClickRegister()
{
	Risker newuser;
	QString str = ui.username->text();
	QString pass_str = ui.passwd->text();
	std::string string_name = str.toStdString();
	std::string string_passwd = pass_str.toStdString();
	if (string_name == "" || string_passwd == "") {
		QMessageBox::warning(NULL, QStringLiteral("֪ͨ~"), QStringLiteral("���ܲ�����Ŷ"), QMessageBox::Yes, QMessageBox::Yes);
	}
	else if (newuser.risker_register(string_name, string_passwd)) {
		QMessageBox::warning(NULL, QStringLiteral("֪ͨ"), QStringLiteral("ע��ɹ���"), QMessageBox::Yes, QMessageBox::Yes);
	}
	else {
		QMessageBox::warning(NULL, QStringLiteral("֪ͨ"), QStringLiteral("�����Ѿ��������أ���һ����"), QMessageBox::Yes, QMessageBox::Yes);
	}
}
