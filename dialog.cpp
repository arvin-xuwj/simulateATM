#include "dialog.h"
#include "ui_dialog.h"
#include <QArrayData>
#include <QJsonParseError>
#include <QJsonDocument>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    this->accMag = new AccountManage();

    this->resize(800, 600);

    switchLogin();


    //QByteArray *byte = new QByteArray(  "{\"accounts\": [{ 		\"account\": \"1234567890\", 		\"passwd\": \"12345\", 		\"balance\": 10000 	}] }");


}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::switchPage(pageIndex page)
{
    switch (page) {
    case PAGE_LOGIN:
        switchLogin();
        break;
    case PAGE_WELCOME:
        switchWelcome();
        break;
    case PAGE_QUERY:
        switchQuery();
        break;
    default:
        switchWelcome();
    }
}

void Dialog::switchLogin()
{
    /*
        显示登陆页面, 隐藏其余控件
     */
    this->ui->stackedWidget->setCurrentIndex(this->ui->stackedWidget->indexOf(this->ui->Login));
    this->ui->btnQuery->hide();
    this->ui->btnQukuan->hide();
    this->ui->btnCunkuan->hide();
    this->ui->btnExit->hide();
    this->ui->lab_account->hide();
    this->ui->lab_account_display->hide();
    this->ui->labLoginErr->hide();

    /* 恢复部分label显示信息 */
    this->m_account = "n/a";
    this->ui->lab_account->setText(this->m_account);
}

void Dialog::switchWelcome()
{
    /*
        默认显示欢迎页面;
     */
    this->ui->stackedWidget->setCurrentIndex(this->ui->stackedWidget->indexOf(this->ui->Welcome));
    this->ui->btnQuery->show();
    this->ui->btnQukuan->show();
    this->ui->btnCunkuan->show();
    this->ui->btnExit->show();
    this->ui->labLoginErr->hide();

    this->ui->lab_account->show();
    this->ui->lab_account_display->show();

    /* 填充部分label显示信息 */
    this->ui->lab_account->setText(this->m_account);
}

void Dialog::switchQuery()
{
    /*
        显示账户余额信息;
     */
    this->ui->stackedWidget->setCurrentIndex(this->ui->stackedWidget->indexOf(this->ui->displayQuery));
    this->ui->btnQuery->show();
    this->ui->btnQukuan->show();
    this->ui->btnCunkuan->show();
    this->ui->btnExit->show();
    this->ui->labLoginErr->hide();
}

void Dialog::on_btnQuery_clicked()
{
    QString balance;
    balance = balance.sprintf("%0.2f", this->accMag->getBalance(this->m_account));
    this->ui->lineEditMemoy->setText(balance);
    switchPage(PAGE_QUERY);
}

void Dialog::on_btnLogin_clicked()
{
    QString account = "";
    QString passwd  = "";

    account = this->ui->editAccount->text();
    passwd  = this->ui->editPasswd->text();

    if (this->accMag->verifyAccount(account, passwd)) {
        /* 记录当前登陆的账户ID */
        this->m_account = account;

        switchPage(PAGE_WELCOME);
    } else {
        this->ui->labLoginErr->show();
    }
}

void Dialog::on_btnExit_clicked()
{
    switchPage(PAGE_LOGIN);
}
