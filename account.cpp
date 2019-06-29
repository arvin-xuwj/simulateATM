#include "account.h"

Account::Account(QString account, QString passwd, double momey)
{
    this->account = account;
    this->passwd  = passwd;
    this->momey   = momey;
    this->locked  = false;
}

QString Account::getAccount() const
{
    return account;
}

QString Account::getPasswd() const
{
    return passwd;
}

double Account::getMomey() const
{
    return momey;
}

bool Account::getLocked() const
{
    return locked;
}

void Account::setMomey(double value)
{
    momey = value;
}

void Account::setLocked(bool value)
{
    locked = value;
}

void Account::setPasswd(const QString &value)
{
    passwd = value;
}

int Account::getTryCount() const
{
    return tryCount;
}

void Account::setTryCount(int value)
{
    tryCount = value;
}
