#ifndef ML_WINDOW_H
#define ML_WINDOW_H

#include <QDialog>

namespace Ui {
class ML_Window;
}

class ML_Window : public QDialog
{
    Q_OBJECT

public:
    explicit ML_Window(QWidget *parent = nullptr);
    ~ML_Window();

private Q_SLOTS:
    void on_pushButton_clicked();

private:
    Ui::ML_Window *ui;
};

#endif // ML_WINDOW_H
