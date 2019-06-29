#ifndef ACCOUNTMANAGE_H
#define ACCOUNTMANAGE_H

#include <QString>
#include <QList>
#include "account.h"

class AccountManage
{
public:
    AccountManage();
    AccountManage(QString fileName);

    bool verifyAccount(QString account, QString passwd);
    double getBalance(QString account);
    void   setBalance(QString account, double momey);
    void   changePasswd(QString account, QString newpasswd);

private:
    Account* getAccount(QString account);

private:
    QList<Account> users;
};

#endif // ACCOUNTMANAGE_H
