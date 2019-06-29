#include "accountManage.h"
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QFile>

AccountManage::AccountManage()
{
    this->tryMax = 3;
    this->users.append(Account("12345", "12345", 100000));
    this->users.append(Account("11111", "12345", 100000));
}

AccountManage::AccountManage(QString fileName)
{
    this->tryMax = 3;

    this->m_file = new QFile(fileName);

    if (this->m_file == nullptr || !this->m_file->open(QIODevice::ReadWrite)) {
        if (this->m_file != nullptr) {
            delete (this->m_file);
            this->m_file = nullptr;
        }

        return;
    }

    QByteArray ba = this->m_file->readAll();

    QJsonParseError e;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(ba, &e);
    if(e.error != QJsonParseError::NoError || jsonDoc.isNull())
    {
        return;
    }

    if (jsonDoc.isObject()) {
        QJsonObject obj = jsonDoc.object();

        if (obj.contains("tryCount")) {
            QJsonValue val = obj.value("tryCount");
            this->tryMax = val.toInt(3);
        }

        if (obj.contains("accounts")) {
            QJsonArray val = obj.value("accounts").toArray();

            for (QJsonArray::iterator it = val.begin();
                 it != val.end(); it++) {
                QJsonObject acc = it.a->at(it.i).toObject();

                this->users.append(Account(acc.value("account").toString(),
                                           acc.value("passwd").toString(),
                                           acc.value("memey").toDouble()));
            }
        }
    }
}

AccountManage::~AccountManage()
{
    if (this->m_file->isWritable() && this->users.size()) {
        QJsonObject root;
        QJsonObject obj;
        QJsonValue  val;
        QJsonArray  accounts;

        val = this->tryMax;
        root.insert("tryCount", val);

        for (QList<Account>::iterator it = this->users.begin();
             it != this->users.end();
             it++)
        {
            QJsonValue  account;
            QJsonValue  passwd;
            QJsonValue  memey;
            QJsonObject obj;

            account = it->getAccount();
            passwd  = it->getPasswd();
            memey   = it->getMomey();

            obj.insert("account", account);
            obj.insert("passwd", passwd);
            obj.insert("memey", memey);

            accounts.append(obj);
        }

        root.insert("accounts", accounts);


        QJsonDocument doc(root);
        QByteArray ba = doc.toJson(QJsonDocument::Indented);

        this->m_file->resize(0);
        this->m_file->write(ba);
        this->m_file->close();
    }
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
