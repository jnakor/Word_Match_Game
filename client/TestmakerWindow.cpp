#include "TestmakerWindow.h"

TestmakerWindow::TestmakerWindow(QWidget *parent)
	: QWidget(parent)
{
	user = new Testmaker();
	ui.setupUi(this);
	QObject::connect(ui.input_button, SIGNAL(clicked()), this, SLOT(ClickInputButton()));
	ui.input_button->setShortcut(Qt::Key_Return);//�س���ȷ��

	QObject::connect(ui.search_button, SIGNAL(clicked()), this, SLOT(Search_open()));
}

TestmakerWindow::~TestmakerWindow()
{
	printf("del test win\n");
	delete user;
}

bool TestmakerWindow::user_login(std::string user_name) {
	if (user->testmaker_login(user_name));
	else {
		std::cout << "TestWindow::user_login:failed" << std::endl;
		return false;
	}
	refresh_info();
	return true;
}

void TestmakerWindow::refresh_info() {
	ui.name->setText(QString::fromStdString(user->get_name()));
	ui.level->setText(QString::fromStdString(std::to_string(user->get_level())));
	ui.problemnum->setText(QString::fromStdString(std::to_string(user->get_num())));
}

bool TestmakerWindow::islegal(std::string new_word) {
	//���ʺϷ��Լ�⣬����ȫ��д��Ҳ���Դ�д��ͷ��Ҳ����ȫСд
	//��������Сд�Ӵ�д
	if (new_word.length() == 0)return false;
	if (new_word.length() == 1)return isalpha(new_word[0]);
	else {
		for (int i = 0; i < new_word.length() - 1; i++) {
			if (!isalpha(new_word[i + 1]))return false;//����ĸ���
			if (islower(new_word[i]) && isupper(new_word[i + 1]))return false;
		}
		return true;
	}
}
void TestmakerWindow::ClickInputButton() {
	std::string new_word = ui.input->text().toStdString();
	if (!islegal(new_word)) {
		//���벻�Ϸ�
		QMessageBox::warning(NULL, QStringLiteral("֪ͨ"), QStringLiteral("��ɲ��ǵ�����"), QMessageBox::Yes, QMessageBox::Yes);
		return;
	}
	if (user->make_newword(new_word)) {//�Ƿ��Ѿ����ڽ������ݿ���
		user->add_problem_num();
		refresh_info();
		ui.input->setText("");
		QMessageBox::warning(NULL, QStringLiteral("֪ͨ"), QStringLiteral("�ɹ�"), QMessageBox::Yes, QMessageBox::Yes);
	}
	else {
		QMessageBox::warning(NULL, QStringLiteral("֪ͨ"), QStringLiteral("�����Ѿ�����Ŷ����һ����"), QMessageBox::Yes, QMessageBox::Yes);
	}
}

void TestmakerWindow::Search_open() {
	SearchWindow * SW = new SearchWindow();
	SW->show();
}

std::string TestmakerWindow::get_name() {
	return user->get_name();
}