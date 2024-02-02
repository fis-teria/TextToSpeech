#include "ml_window.h"
#include "ui_ml_window.h"

ML_Window::ML_Window(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ML_Window)
{
    ui->setupUi(this);
}

ML_Window::~ML_Window()
{
    delete ui;
}

void ML_Window::on_pushButton_clicked()
{
    this->close();
}

