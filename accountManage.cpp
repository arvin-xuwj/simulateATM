#include "accountManage.h"

AccountManage::AccountManage()
{
    this->users.append(Account("12345", "12345", 100000));
    this->users.append(Account("11111", "12345", 100000));
}

AccountManage::AccountManage(QString fileName)
{
    (void)fileName;
}

bool AccountManage::verifyAccount(QString account, QString passwd)
{
    for (QList<Account>::iterator it = this->users.begin();
         it != this->users.end();
         it++)
    {
        if (it->getAccount() == account &&
                it->getPasswd()  == passwd) {
            return true;
        }
    }

    return false;
}

double AccountManage::getBalance(QString account)
{
    if (getAccount(account) != nullptr) {
        return getAccount(account)->getMomey();
    }

    return 0;
}

void AccountManage::setBalance(QString account, double momey)
{
    if (getAccount(account) != nullptr) {
        return getAccount(account)->setMomey(getAccount(account)->getMomey() + momey);
    }
}

Account* AccountManage::getAccount(QString account)
{
    for (QList<Account>::iterator it = this->users.begin();
         it != this->users.end();
         it++)
    {
        if (it->getAccount() == account) {
            return &*it;
        }
    }

    return nullptr;
}
