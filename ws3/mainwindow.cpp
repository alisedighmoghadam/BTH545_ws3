#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_6->setVisible(false);
    connect(ui->checkBox_ham, &QCheckBox::toggled, this, &MainWindow::check_Box_checked);
    connect(ui->checkBox_pepper, &QCheckBox::toggled, this, &MainWindow::check_Box_checked);
    connect(ui->checkBox_mushroom, &QCheckBox::toggled, this, &MainWindow::check_Box_checked);
    connect(ui->checkBox_artichokes, &QCheckBox::toggled, this, &MainWindow::check_Box_checked);
    connect(ui->checkBox_cheese, &QCheckBox::toggled, this, &MainWindow::check_Box_checked);
    connect(ui->checkBox_pineapple, &QCheckBox::toggled, this, &MainWindow::check_Box_checked);
    connect(ui->checkBox_greenPepper, &QCheckBox::toggled, this, &MainWindow::check_Box_checked);
    connect(ui->checkBox_onion, &QCheckBox::toggled, this, &MainWindow::check_Box_checked);
    connect(ui->checkBox_olive, &QCheckBox::toggled, this, &MainWindow::check_Box_checked);
    ui->postalCodeLineEdit->setPlaceholderText("A1A1A1");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_large_radioButton_clicked()
{
    if(ui->checkBox_cheese->isChecked()){
        ui->checkBox_cheese->setChecked(false);
    }
    ui->checkBox_cheese->setEnabled(false);
    QFont font=ui->checkBox_cheese->font();
    font.setStrikeOut(true);
    ui->checkBox_cheese->setFont(font);
}


void MainWindow::on_medium_radioButton_clicked()
{
    ui->checkBox_cheese->setEnabled(true);
    QFont font=ui->checkBox_cheese->font();
    font.setStrikeOut(false);
    ui->checkBox_cheese->setFont(font);
}


void MainWindow::on_small_radioButton_clicked()
{
    ui->checkBox_cheese->setEnabled(true);
    QFont font=ui->checkBox_cheese->font();
    font.setStrikeOut(false);
    ui->checkBox_cheese->setFont(font);
}

void MainWindow::check_Box_checked(bool value){
    static int totalChecked = 0; // static! the value is remembered for next invocation
    totalChecked += value ? 1 : -1;
    Q_ASSERT(totalChecked >= 0);
    int maxChecked = 3; // any number you like
    if (value && totalChecked > maxChecked)
    {
        qobject_cast<QCheckBox*>(sender())->setChecked(false);
    }
}

void MainWindow::on_pushButton_reset_clicked()
{
    ui->small_radioButton->setChecked(true);
    MainWindow::on_small_radioButton_clicked();
    ui->checkBox_cheese->setChecked(false);
    ui->checkBox_greenPepper->setChecked(false);
    ui->checkBox_artichokes->setChecked(false);
    ui->checkBox_ham->setChecked(false);
    ui->checkBox_mushroom->setChecked(false);
    ui->checkBox_olive->setChecked(false);
    ui->checkBox_onion->setChecked(false);
    ui->checkBox_pepper->setChecked(false);
    ui->checkBox_pineapple->setChecked(false);
}


void MainWindow::on_pushButton_cancel_clicked()
{
    QApplication::quit();
}


void MainWindow::on_pushButton_order_clicked()
{
    if(!ui->firstNameLineEdit->text().isEmpty()&&!ui->lastNameLineEdit->text().isEmpty()&&!ui->streetLineEdit->text().isEmpty()&&!ui->postalCodeLineEdit->text().isEmpty()&&!ui->cityLineEdit->text().isEmpty()){
        if(ui->postalCodeLineEdit->text().length()==6){
            ui->label_6->setVisible(false);
         ui->firstNameLineEdit->setStyleSheet("border: 0px ;");
         ui->lastNameLineEdit->setStyleSheet("border: 0px ;");
         ui->streetLineEdit->setStyleSheet("border: 0px ;");
          ui->postalCodeLineEdit->setStyleSheet("border: 0px ;");
         ui->cityLineEdit->setStyleSheet("border: 0px ;");
    // Create a QString to store the summary
    QString summary = "\t\t\t\t\t\t\t\nOrder Summary:\n";

    // Iterate through all checkboxes and radio buttons
    QList<QCheckBox*> checkboxes = this->findChildren<QCheckBox*>();
    QList<QRadioButton*> radioButtons = this->findChildren<QRadioButton*>();

    for (QRadioButton* radioButton : radioButtons) {
        if (radioButton->isChecked()){
            summary += "Your pizza size: \n\t" + radioButton->text() + "\n";
        }

    }
    summary+="Your pizza toppings:\n";
    for (QCheckBox* checkbox : checkboxes) {
        summary += (checkbox->isChecked() ? "\t"+checkbox->text()+"\n" : "");
    }



    // Create and configure a QMessageBox for confirmation with the summary
    QMessageBox messageBox;
    messageBox.setWindowTitle("Order Confirmation");
    messageBox.setText(summary);
    messageBox.setIcon(QMessageBox::Question);


    // Add "Confirm" and "Reject" buttons
    QPushButton *rejectButton = messageBox.addButton("Reject", QMessageBox::NoRole);
    QPushButton *confirmButton = messageBox.addButton("Confirm", QMessageBox::YesRole);


    // Show the QMessageBox as a popup
    messageBox.exec();

    // Check which button was clicked
    if (messageBox.clickedButton() == confirmButton) {
        // User confirmed, close the application
        QApplication::quit();
    }
        }else{
    ui->postalCodeLineEdit->setStyleSheet("border: 1px solid red;");
    ui->label_6->setVisible(true);
        }
    }else{
    ui->label_6->setVisible(true);
    if (ui->firstNameLineEdit->text().isEmpty()) {
        // First Name is not empty
        ui->firstNameLineEdit->setStyleSheet("border: 1px solid red;");
    }

    if (ui->lastNameLineEdit->text().isEmpty()) {
        // Last Name is not empty
        ui->lastNameLineEdit->setStyleSheet("border: 1px solid red;");
    }

    if (ui->streetLineEdit->text().isEmpty()) {
        // Street is not empty
        ui->streetLineEdit->setStyleSheet("border: 1px solid red;");
    }

    if (ui->postalCodeLineEdit->text().isEmpty()) {
        // Postal Code is not empty
        ui->postalCodeLineEdit->setStyleSheet("border: 1px solid red;");
    }

    if (ui->cityLineEdit->text().isEmpty()) {
        // City is not empty
        ui->cityLineEdit->setStyleSheet("border: 1px solid red;");
    }
    }
}


void MainWindow::on_firstNameLineEdit_textEdited(const QString &arg1)
{
    validateText(arg1,"[^A-Za-z ]");
}

void MainWindow::on_lastNameLineEdit_textEdited(const QString &arg1)
{
    validateText(arg1,"[^A-Za-z ]");
}


void MainWindow::validateText(const QString &arg,const QString &regex){
    std::cout << "Input: " << arg.toStdString() << std::endl;
    std::cout << "Regex: " << regex.toStdString() << std::endl;

    QRegularExpression removePattern(regex);

    // Remove characters that match the remove pattern from the input
    QString validInput = arg;
    validInput.remove(removePattern);

    // Update the input field with the cleaned input
    QLineEdit *firstNameLineEdit = qobject_cast<QLineEdit*>(sender()); // Get the sender (the QLineEdit widget)
    if (firstNameLineEdit)
    {
        firstNameLineEdit->setText(validInput);

        // Optionally, set the cursor position to the end of the input
        firstNameLineEdit->setCursorPosition(validInput.length());
    }
}




void MainWindow::on_streetLineEdit_textEdited(const QString &arg1)
{
    validateText(arg1,"[^A-Za-z0-9'\.\-\s\, ]");
}






void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{
    validateText(arg1,"[^A-Za-z0-9\. ]");
}



void MainWindow::on_cityLineEdit_textEdited(const QString &arg1)
{
    validateText(arg1,"[^A-Za-z ]");
}



void MainWindow::on_postalCodeLineEdit_textEdited(const QString &arg1)
{

    validatePostalCode(arg1);
}

void MainWindow::validatePostalCode(const QString &arg){
    QString validInput;

    for (int i = 0; i < arg.length()&&i<6; ++i)
        {
            QChar ch = arg[i];

            if (i % 2 == 0)
            {
                // Even position (0-based index), check if it's a digit
                if (ch.isLetter())
                {
                    validInput.append(ch);
                }
                // Optionally, you can provide feedback for invalid even positions.
            }
            else
            {
                // Odd position, check if it's an alphabetic character
                if (ch.isDigit())
                {
                    validInput.append(ch);
                }
                // Optionally, you can provide feedback for invalid odd positions.
            }
        }



    // Update the input field with the cleaned input
    ui->postalCodeLineEdit->setText(validInput);

    // Optionally, set the cursor position to the end of the input
    ui->postalCodeLineEdit->setCursorPosition(validInput.length());
}
