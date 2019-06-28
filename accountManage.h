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

private:
    Account* getAccount(QString account);

private:
    QList<Account> users;
};

#endif // ACCOUNTMANAGE_H
