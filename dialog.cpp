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

void Dialog::switchLogin()
{
    this->ui->stackedWidget->setCurrentIndex(this->ui->stackedWidget->indexOf(this->ui->Login));
    this->ui->btnQuery->hide();
    this->ui->btnQukuan->hide();
    this->ui->btnCunkuan->hide();
    this->ui->btnExit->hide();
}

void Dialog::switchNormal()
{
    this->ui->stackedWidget->setCurrentIndex(this->ui->stackedWidget->indexOf(this->ui->Information));
    this->ui->btnQuery->show();
    this->ui->btnQukuan->show();
    this->ui->btnCunkuan->show();
    this->ui->btnExit->show();
}
void Dialog::on_btnQuery_clicked()
{

}

void Dialog::on_btnLogin_clicked()
{
    QString account = "";
    QString passwd  = "";

    account = this->ui->editAccount->text();
    passwd  = this->ui->editPasswd->text();

    if (this->accMag->verifyAccount(account, passwd)) {
        switchNormal();
    }
}

void Dialog::on_btnExit_clicked()
{
    switchLogin();
}
