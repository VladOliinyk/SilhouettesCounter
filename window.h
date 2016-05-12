#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>

namespace Ui {
class window;
}

class window : public QMainWindow
{
    Q_OBJECT

public:
    explicit window(QWidget *parent = 0);
    ~window();

private slots:
    void on_openFileButton_clicked();

    void on_showButton_clicked();

    void on_fixImageButton_clicked();

    void on_findSilhButton_clicked();

    void on_showRadioButton_toggled(bool checked);

private:
    Ui::window *ui;
};

#endif // WINDOW_H
