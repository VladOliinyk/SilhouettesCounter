#include "window.h"
#include "ui_window.h"

#include "logic.h"

int delayMS = 10;

template <typename T>
void delay(T ui)
{
    if (getShow()) {
        delayMS = ui->delayBox->value();
        QTime dieTime= QTime::currentTime().addMSecs(delayMS);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, delayMS/10);
    }
}

window::window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::window)
{
    ui->setupUi(this);
    ui->label->setText("");

    ui->showButton->setEnabled(false);
    ui->fixImageButton->setEnabled(false);
    ui->findSilhButton->setEnabled(false);
}

window::~window()
{
    delete ui;
}

void window::on_openFileButton_clicked()
{
    //getting file name & path
    QString userFilename = QFileDialog::getOpenFileName(
                this,
                tr("Open file..."),
                "./",
                "All supported files... (*.jpg; *.gif; *.bmp)"
                );

    //saving user image
    QImage tempImage(userFilename);

    if (userFilename.size() != 0) {
        saveImage(tempImage);

        ui->titleLabel->setText("Image downloaded.");

        //enabling buttons
        ui->showButton->setEnabled(true);
        ui->fixImageButton->setEnabled(true);
    } else {
        ui->titleLabel->setText("Please choose the file!");

        //enabling buttons
        ui->showButton->setEnabled(false);
        ui->fixImageButton->setEnabled(false);
    }
}

void window::on_showButton_clicked()
{
    showImage(ui, getImage());
}

void window::on_fixImageButton_clicked()
{
    saveImage(fixImage(ui, getImage()));
}

void window::on_findSilhButton_clicked()
{
    findSilhouettes(ui, getImage());
}

void window::on_showRadioButton_toggled(bool checked)
{
    if (checked) {
        setShow(true);
    } else {
        setShow(false);
    }
}
