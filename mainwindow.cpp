#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for (int i = 0; i < 3; i++){
            ui->comboBox->addItem(doctornames[i]);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


bool MainWindow::checkname(QString name){           // check if name is in database or not
    bool found = false;
    for(int i = 0; i < 10 ;i++){
        if (name == patientnames[i])
            found = true;
    }
    return found;
}

bool MainWindow::checkpassword(QString password, int location){  // check if password is in database or not
    bool found = false;
        if (password == passwords[location])
            found = true;
    return found;
}

int MainWindow::checklocation(QString name){                // check location of name in order to fetch password or balance
    int index = -1;
    for(int i = 0; i < 10; i++ ){
        if(name == patientnames[i])
            index = i;
    }
    return index;
}

void MainWindow::on_Login_button_clicked()
{
    QString name = ui->log_nameslot->text();
    QString password = ui->log_passwordslot->text();
    int location = checklocation(name);
    bool foundName = checkname(name);
    bool foundPass = checkpassword(password,location);
    if(!foundName){
        ui->logStateLabel->setText("Name is not registered");
    }
    else if(!foundPass)
        ui->logStateLabel->setText("Name is correct but password is incorrect");
    else{
        ui->logStateLabel->setText("Signed in successfully");
        ui->BalanceLabel->setText("Balance: ");
        QString temp = QString::number(balance[location]);
        ui->balanceSlotNum->setText(temp);
    }
}

void MainWindow::on_Register_button_clicked()
{
    QString name = ui->reg_nameslot->text();
    QString password = ui->reg_passwordslot->text();
    QString userage = ui->reg_ageslot->text();
    int userbalance = ui->reg_balanceslot->text().toInt();
    bool foundName = checkname(name);
    bool y;
    if(foundName)
        ui->regStateLabel->setText("Name is already registered, choose another one");
    else if(password.length()<5)
        ui->regStateLabel->setText("Password must be at least 5 characters");
    else if (ui->reg_ageslot->text().toInt(&y)==0)
        ui->regStateLabel->setText("Age must be integer not string");
    else if (userage.toInt()<1 || userage.toInt()>100)
        ui->regStateLabel->setText("Age must be between 1 and 100");
    else if (userbalance < 10)
        ui->regStateLabel->setText("Please charge at least 10 pounds");
    else{
        ui->regStateLabel->setText("Registered successfully");
        ui->reg_nameslot->setText("");
        ui->reg_passwordslot->setText("");
        ui->reg_ageslot->setText("");
        ui->reg_balanceslot->setText("");
        for(int i = 0; i < 10; i++){
            if (patientnames[i]=="x")
                patientnames[i] = name;
        }
        for(int i = 0; i < 10; i++){
            if (passwords[i]=="x")
                passwords[i] = password;
        }
        for(int i = 0; i < 10; i++){
            if (age[i]=="x")
                age[i] = userage;
        }
        for(int i = 0; i < 10; i++){
            if (balance[i]==-1)
                balance[i] = userbalance;
        }
    }
}

void MainWindow::on_recharge_button_clicked()
{
    QString name = ui->log_nameslot->text();
    int location = checklocation(name);
    int userBalance = balance[location];
    QString temp = QString::number(userBalance);
    QString valid = ui->logStateLabel->text();
    QString valid1 = "Signed in successfully";
    int x = ui->rechargeslot->text().toInt();
    bool y;
    if(valid!=valid1){
        ui->rechargeslot->setText("Login first to proceed");
    return;
    }
    else{
        ui->BalanceLabel->setText("Balance: ");
        ui->balanceSlotNum->setText(temp);
    }
    if(ui->rechargeslot->text().toInt(&y)==0)
            ui->rechargeslot->setText("Enter number not string");
       else if(x<1)
            ui->rechargeslot->setText("Recharge positive values only");
      else{
           ui->BalanceLabel->setText("Balance: ");
           userBalance+=ui->rechargeslot->text().toInt();
           balance[location] = userBalance;
           QString temp = QString::number(userBalance);
           ui->balanceSlotNum->setText(temp);
           ui->rechargeslot->setText("");
          }
    }

void MainWindow::on_bookAppButton_clicked()
{

    bool x = ui->RB1->isChecked();
    bool y = ui->RB2->isChecked();
    bool z = ui->RB3->isChecked();
    QString name = ui->log_nameslot->text();
    int index = checklocation(name);
    int balancex = ui->balanceSlotNum->text().toInt();
    int fees = ui->feesLabel->text().toInt();
    if (ui->logStateLabel->text() != "Signed in successfully")
        ui->appStatus->setText("Login first");
    else if (balancex < fees)
        ui->appStatus->setText("Recharge your balance first");
    else if (!x && !y && !z)
        ui->appStatus->setText("Select appointment day");
    else{
        balance[index]-=fees;
        ui->BalanceLabel->setText("Balance: ");
        QString temp = QString::number(balance[index]);
        ui->balanceSlotNum->setText(temp);
        ui->appStatus->setText("Appointment Booked");

        ui->Rname->setText(ui->log_nameslot->text());

        if(ui->reg_ageslot->text()=="")
            ui->Rage->setText(age[index]);
        else
             ui->Rage->setText(ui->reg_ageslot->text());
        ui->Rdrname->setText(ui->comboBox->currentText());

        if(x)
        ui->Rappday->setText(ui->RB1->text());
        else if(y)
             ui->Rappday->setText(ui->RB2->text());
        else if(z)
             ui->Rappday->setText(ui->RB3->text());

        ui->Rfees->setText(ui->feesLabel->text());
    }
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    QString temp = QString::number(visit_fees[index]);
    ui->feesLabel->setText(temp);
}

