#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QString>
#include <accountManage.h>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

private:
    enum PAGE_INDEX {
       PAGE_LOGIN = 0,
       PAGE_WELCOME,
       PAGE_QUERY,
    };

    typedef enum PAGE_INDEX pageIndex;

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    void switchPage(pageIndex page);
    void switchLogin();
    void switchWelcome();
    void switchQuery();

private slots:
    void on_btnQuery_clicked();
    void on_btnLogin_clicked();
    void on_btnExit_clicked();

private:
    Ui::Dialog *ui;
    AccountManage *accMag;

    /* 记录当前登陆的账户id */
    QString m_account;

};

#endif // DIALOG_H
