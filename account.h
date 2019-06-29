#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>

class Account
{
public:
    Account(QString account, QString passwd, double momery = 0.0);

    QString getAccount() const;

    QString getPasswd() const;

    double getMomey() const;

    bool getLocked() const;

    void setMomey(double value);

    void setLocked(bool value);

    void setPasswd(const QString &value);

    int getTryCount() const;
    void setTryCount(int value);

private:
    QString account;
    QString passwd;
    double  momey;
    bool    locked;
    int     tryCount;
};

#endif // ACCOUNT_H
