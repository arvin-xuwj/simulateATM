#include "accountManage.h"

AccountManage::AccountManage()
{
    this->tryMax = 3;
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
        if (it->getAccount() == account) {
            if (it->getLocked() == true) {
                return false;
            }

            if (it->getPasswd()  == passwd) {
                it->setTryCount(0);
                return true;
            } else {
                it->setTryCount(it->getTryCount() + 1);
                if (it->getTryCount() == this->tryMax) {
                    it->setLocked(true);
                }
                return false;
            }
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

bool AccountManage::getLocked(QString account)
{
    if (getAccount(account) != nullptr) {
        return getAccount(account)->getLocked();
    }

    return false;
}

void AccountManage::setBalance(QString account, double momey)
{
    if (getAccount(account) != nullptr) {
        return getAccount(account)->setMomey(getAccount(account)->getMomey() + momey);
    }
}

void AccountManage::changePasswd(QString account, QString newpasswd)
{
    if (getAccount(account) != nullptr) {
        return getAccount(account)->setPasswd(newpasswd);
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
