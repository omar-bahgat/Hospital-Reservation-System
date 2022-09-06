#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    // a vector would have been better as we are using up excess memory that we might not need

    //patient data
    QString patientnames[10] = {"Omar","Rowan","Rana","x","x","x","x","x","x","x"};
    QString passwords[10] = {"aaaaa","bbbbb","ccccc","x","x","x","x","x","x","x"};
    QString age[10] = {"18","17","18","x","x","x","x","x","x","x"};
    int balance[10] = {200,100,50,-1,-1,-1,-1,-1,-1,-1};

    //doctor data
    QString doctornames[3] = {"Ali","Ahmed","Mohamed"};
    int visit_fees[3] = {100,150,200};

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool checkname(QString);
    bool checkpassword(QString, int);
    int checklocation(QString);

private slots:
    void on_Login_button_clicked();

    void on_Register_button_clicked();

    void on_recharge_button_clicked();

    void on_bookAppButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
