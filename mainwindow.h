#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    //patients' data

    vector<QString> patientnames;
    vector<QString> passwords;
    vector<QString> age;
    vector<int> balance;

    //doctors' data

    QString doctornames[4] = {"John","Sarah","Mohamed","Jennifer"};
    int visit_fees[4] = {200,450,300,250};

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
