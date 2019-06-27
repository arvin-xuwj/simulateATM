#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    this->resize(800, 600);

    switchLogin();
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

    if (account == passwd) {
        switchNormal();
    }
}

void Dialog::on_btnExit_clicked()
{
    switchLogin();
}
