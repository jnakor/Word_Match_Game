#include "TestmakerWindow.h"

TestmakerWindow::TestmakerWindow(QWidget *parent)
	: QWidget(parent)
{
	user = new Testmaker();
	ui.setupUi(this);
	QObject::connect(ui.input_button, SIGNAL(clicked()), this, SLOT(ClickInputButton()));
	ui.input_button->setShortcut(Qt::Key_Return);//回车帮确认

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
	//单词合法性检测，可以全大写，也可以大写开头，也可以全小写
	//但不可以小写接大写
	if (new_word.length() == 0)return false;
	if (new_word.length() == 1)return isalpha(new_word[0]);
	else {
		for (int i = 0; i < new_word.length() - 1; i++) {
			if (!isalpha(new_word[i + 1]))return false;//非字母情况
			if (islower(new_word[i]) && isupper(new_word[i + 1]))return false;
		}
		return true;
	}
}
void TestmakerWindow::ClickInputButton() {
	std::string new_word = ui.input->text().toStdString();
	if (!islegal(new_word)) {
		//输入不合法
		QMessageBox::warning(NULL, QStringLiteral("通知"), QStringLiteral("这可不是单词呢"), QMessageBox::Yes, QMessageBox::Yes);
		return;
	}
	if (user->make_newword(new_word)) {//是否已经存在交给数据库检查
		user->add_problem_num();
		refresh_info();
		ui.input->setText("");
		QMessageBox::warning(NULL, QStringLiteral("通知"), QStringLiteral("成功"), QMessageBox::Yes, QMessageBox::Yes);
	}
	else {
		QMessageBox::warning(NULL, QStringLiteral("通知"), QStringLiteral("库里已经有了哦，换一个吧"), QMessageBox::Yes, QMessageBox::Yes);
	}
}

void TestmakerWindow::Search_open() {
	SearchWindow * SW = new SearchWindow();
	SW->show();
}

std::string TestmakerWindow::get_name() {
	return user->get_name();
}