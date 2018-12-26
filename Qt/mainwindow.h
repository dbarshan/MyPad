#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void newFileAction();
    void openFileAction();
    void saveFileAction();
    void saveAsFileAction();
    void pageSetupAction();
    void printAction();
    void statusBarToggle();
    void wordWrapToggle();
    void performSaveChangesCheck();
    void textChanged();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
