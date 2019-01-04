#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPrinter>

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
    void exitAction();
    void undoAction();
    void cutAction();
    void copyAction();
    void pasteAction();
    void deleteAction();
    void findAction();
    void findNextAction();
    void replaceAction();
    void gotoAction();
    void selectAllAction();
    void timeDateAction();
    void wordWrapToggleAction();
    void fontSelectAction();
    void statusBarToggleAction();
    void viewHelpAction();
    void aboutAction();
    void textChanged();

private:
    void performSaveChangesCheck();




private:
    Ui::MainWindow *ui;
    QPrinter printer;
};

#endif // MAINWINDOW_H
