#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    void switchLogin();
    void switchNormal();

private slots:
    void on_btnQuery_clicked();
    void on_btnLogin_clicked();

    void on_btnExit_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
