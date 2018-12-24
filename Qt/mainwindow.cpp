#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "editor.h"

#include <QFileDialog>
#include <QLabel>


editor e;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->action_Open, &QAction::triggered, this, &MainWindow::openFileAction);
    connect(ui->actionStatus_Bar,&QAction::triggered, this,&MainWindow::statusBarToggle);
    connect(ui->actionWord_Wrap,&QAction::triggered, this,&MainWindow::wordWrapToggle);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveFileAction(){
    QString filename = QFileDialog::getSaveFileName(this,tr("Save File"));

    if ( filename.isEmpty())
        return;
    QString content = ui->plainTextEdit->toPlainText();
    e.writeTextFile(filename,content);
}

void MainWindow::openFileAction(){

    QString filename = QFileDialog::getOpenFileName(this,tr("Open File"),".",tr("Text Documents (*.txt)"));

    if(filename.isEmpty())
        return;
    QString content;
    e.readTextFile(filename,content);
    ui->plainTextEdit->document()->setPlainText(content);
}

void MainWindow::statusBarToggle(){
    if ( ui->statusBar->isVisible()){
        ui->statusBar->hide();
        ui->actionStatus_Bar->setChecked(false);
    }
    else{
        ui->statusBar->show();
        ui->actionStatus_Bar->setChecked(true);
    }
}

void MainWindow::wordWrapToggle(){

    if ( ui->actionWord_Wrap->isChecked()){
        ui->statusBar->showMessage("Hello");
        ui->actionWord_Wrap->setChecked(false);
    }
    else{
        ui->statusBar->showMessage("Hi");
        ui->actionWord_Wrap->setChecked(true);
    }
}
