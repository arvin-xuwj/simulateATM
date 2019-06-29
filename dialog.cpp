#include "dialog.h"
#include "ui_dialog.h"
#include <QArrayData>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QMessageBox>

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
    case PAGE_SAVE:
        switchSave();
        break;
    case PAGE_QUKUAN:
        switchQukuan();
        break;
    case PAGE_CHANGEPASSWD:
        switchChangePasswd();
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
    this->ui->btnChangePasswd->hide();
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
    this->ui->btnChangePasswd->show();
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

void Dialog::switchSave()
{
    /*
        显示账户存款信息;
     */
    this->ui->stackedWidget->setCurrentIndex(this->ui->stackedWidget->indexOf(this->ui->saveMomery));
    this->ui->btnQuery->show();
    this->ui->btnQukuan->show();
    this->ui->btnCunkuan->show();
    this->ui->btnExit->show();
    this->ui->labLoginErr->hide();
}

void Dialog::switchQukuan()
{
    /*
        显示账户取款信息;
     */
    this->ui->stackedWidget->setCurrentIndex(this->ui->stackedWidget->indexOf(this->ui->qukuanPage));
    this->ui->btnQuery->show();
    this->ui->btnQukuan->show();
    this->ui->btnCunkuan->show();
    this->ui->btnExit->show();
    this->ui->labLoginErr->hide();
}

void Dialog::switchChangePasswd()
{
    /*
        修改密码信息;
     */
    this->ui->stackedWidget->setCurrentIndex(this->ui->stackedWidget->indexOf(this->ui->pageChangePasswd));
    this->ui->lineEditOldPasswd->setText("");
    this->ui->lineEditNewPasswd->setText("");
    this->ui->lineEditNewPasswd2->setText("");
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
        if (this->accMag->getLocked(account)) {
            this->ui->labLoginErr->setText("account locked");
        } else {
            this->ui->labLoginErr->setText("account or passwd error");
        }

        this->ui->labLoginErr->show();
    }
}

void Dialog::on_btnExit_clicked()
{
    switchPage(PAGE_LOGIN);
}

void Dialog::on_btnCunkuan_clicked()
{
    switchPage(PAGE_SAVE);
}

void Dialog::on_btnSave_clicked()
{
    QString sz_memey = this->ui->LineEditSaveMomey->text();
    /*
        此处未检查输入的内容是否未全数字;
     */

    double memey = sz_memey.toDouble();

    this->accMag->setBalance(this->m_account, memey);

    QMessageBox::information(this, "提示信息", sz_memey.sprintf("金额: %0.2f, 操作已完成", memey), QMessageBox::Yes, QMessageBox::Yes);

    this->ui->LineEditSaveMomey->setText("");
}

void Dialog::on_btnQuKuanSure_clicked()
{
    QString sz_memey = this->ui->LineEditQukuanMomey->text();
    /*
        此处未检查输入的内容是否未全数字;
     */

    double memey = sz_memey.toDouble();

    this->accMag->setBalance(this->m_account, memey * -1);

    QMessageBox::information(this, "提示信息", sz_memey.sprintf("金额: %0.2f, 操作已完成", memey), QMessageBox::Yes, QMessageBox::Yes);

    this->ui->LineEditQukuanMomey->setText("");
}

void Dialog::on_btnQukuan_clicked()
{
    switchPage(PAGE_QUKUAN);
}

void Dialog::on_btnChangePasswd_clicked()
{
    switchPage(PAGE_CHANGEPASSWD);
}

void Dialog::on_btnSurePasswd_clicked()
{
    QString oldPasswd = this->ui->lineEditOldPasswd->text();
    QString newPasswd = this->ui->lineEditNewPasswd->text();
    QString new2Passwd = this->ui->lineEditNewPasswd2->text();

    if (oldPasswd.isEmpty() || newPasswd.isEmpty() || new2Passwd.isEmpty()) {
        QMessageBox::information(this, "提示信息", "密码输入不能为空", QMessageBox::Yes, QMessageBox::Yes);
        switchChangePasswd();
        return;
    }

    if (this->accMag->verifyAccount(this->m_account, oldPasswd)) {
        if (newPasswd == new2Passwd) {
            this->accMag->changePasswd(this->m_account, newPasswd);
            QMessageBox::information(this, "提示信息", "密码已修改, 请重新登陆", QMessageBox::Yes, QMessageBox::Yes);
            switchPage(PAGE_LOGIN);
            return;
        }
    }

    QMessageBox::information(this, "提示信息", "密码输入错误", QMessageBox::Yes, QMessageBox::Yes);
    switchChangePasswd();
}
