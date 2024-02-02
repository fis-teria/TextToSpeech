#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void stack_text(const QString &str);
    //void BOOST_PYTHON_HELLOWORLD();
    //void BOOST_PYTHON_VOICE_INFERENCE(QString &str);

private Q_SLOTS:
    void on_GoTTS_clicked();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_back_start_clicked();

    void on_lineEdit_returnPressed();


    void on_credit_pressed();

    void on_pushButton_2_pressed();

    void on_stackedWidget_currentChanged(int arg1);

    void on_GoML_clicked();

    void on_pushButton_3_clicked();

    void on_GoData_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
