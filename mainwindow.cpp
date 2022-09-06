#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for (int i = 0; i < 4; i++){
            ui->comboBox->addItem(doctornames[i]);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

// HELPER FUNCTIONS

bool MainWindow::checkname(QString name){         // check if name is in database or not
    bool found = false;
    for(int i = 0; i < patientnames.size() ;i++){
        if (name == patientnames[i])
            found = true;
    }
    return found;
}

bool MainWindow::checkpassword(QString password, int location){  // check if password is in database and corresponds to same location of name
    bool found = false;
        if (password == passwords[location])
            found = true;
    return found;
}

int MainWindow::checklocation(QString name){            // check location of name in order to fetch password or balance
    int index = -1;
    for(int i = 0; i < patientnames.size(); i++ ){
        if(name == patientnames[i])
            index = i;
    }
    return index;
}

// CLICKABLE BUTTONS

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
    else if (name.length()==0)
        ui->regStateLabel->setText("Enter a name first");
    else if(password.length()<5)
        ui->regStateLabel->setText("Password must be at least 5 characters");
    else if (ui->reg_ageslot->text().toInt(&y)==0)
        ui->regStateLabel->setText("Age must be integer not string");
    else if (userage.toInt()<18)
        ui->regStateLabel->setText("You must be at least 18 years old");
    else if (userbalance < 100)
        ui->regStateLabel->setText("Please charge at least $100");
    else{
        ui->regStateLabel->setText("Registered successfully");
        ui->reg_nameslot->setText("");
        ui->reg_passwordslot->setText("");
        ui->reg_ageslot->setText("");
        ui->reg_balanceslot->setText("");

        patientnames.push_back(name);
        passwords.push_back(password);
        age.push_back(userage);
        balance.push_back(userbalance);
    }
}

void MainWindow::on_recharge_button_clicked()
{
    QString name = ui->log_nameslot->text();
    int location = checklocation(name);
    QString valid = ui->logStateLabel->text();
    QString valid1 = "Signed in successfully";
    int x = ui->rechargeslot->text().toInt();
    bool y;

    if(valid!=valid1){
        ui->rechargeslot->setText("Login first to proceed");
    return;
    }
    else{
        int userBalance = balance[location];
        QString temp = QString::number(userBalance);
        ui->BalanceLabel->setText("Balance: ");
        ui->balanceSlotNum->setText(temp);
    }
    if(ui->rechargeslot->text().toInt(&y)==0)
            ui->rechargeslot->setText("Enter number not string");
       else if(x<1)
            ui->rechargeslot->setText("Recharge positive values only");
      else{
           int userBalance = balance[location];
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

