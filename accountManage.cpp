#include "accountManage.h"

AccountManage::AccountManage()
{
    this->users.append(Account("12345", "12345", 100000));
    this->users.append(Account("11111", "12345", 100000));
}

AccountManage::AccountManage(QString fileName)
{

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
