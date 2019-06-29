#ifndef ACCOUNTMANAGE_H
#define ACCOUNTMANAGE_H

#include <QString>
#include <QList>
#include <QFile>
#include "account.h"

class AccountManage
{
public:
    AccountManage();
    AccountManage(QString fileName);
    ~AccountManage();

    bool verifyAccount(QString account, QString passwd);
    double getBalance(QString account);
    bool   getLocked(QString account);
    void   setBalance(QString account, double momey);
    void   changePasswd(QString account, QString newpasswd);

private:
    Account* getAccount(QString account);

private:
    QList<Account> users;
    QFile           *m_file;
    int             tryMax;
};

#endif // ACCOUNTMANAGE_H
