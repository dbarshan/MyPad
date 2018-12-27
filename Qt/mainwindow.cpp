#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "editor.h"

#include <QFileDialog>
#include <QLabel>
#include <QMessageBox>
//#include <QtPrintSupport/QPageSetupDialog>
//#include <QtPrintSupport/QPrinter>

editor e;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(    ui->action_New,         &QAction::triggered,    this,   &MainWindow::newFileAction      );
    connect(    ui->action_Open,        &QAction::triggered,    this,   &MainWindow::openFileAction     );
    connect(    ui->action_Save,        &QAction::triggered,    this,   &MainWindow::saveFileAction     );
    connect(    ui->actionPage_Setup,   &QAction::triggered,    this,   &MainWindow::pageSetupAction    );
    connect(    ui->actionStatus_Bar,   &QAction::triggered,    this,   &MainWindow::statusBarToggle    );
    connect(    ui->actionWord_Wrap,    &QAction::triggered,    this,   &MainWindow::wordWrapToggle     );
    connect(    ui->plainTextEdit,      SIGNAL(textChanged()),  this,   SLOT(textChanged())             );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::performSaveChangesCheck(){
    QMessageBox saveChangesMsgBox;
    saveChangesMsgBox.setWindowTitle("MyPad");
    saveChangesMsgBox.setText("Do you want to save changes?");
    saveChangesMsgBox.setStandardButtons(QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel);
    saveChangesMsgBox.setDefaultButton(QMessageBox::Save);
    saveChangesMsgBox.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    int ret = saveChangesMsgBox.exec();
    switch(ret){

        case QMessageBox::Save:
                                    saveFileAction();
                                    ui->plainTextEdit->document()->setPlainText("");
                                    break;

        case QMessageBox::Discard:
                                    ui->plainTextEdit->document()->setPlainText("");
                                    break;

        case QMessageBox::Cancel:    break;

    }
}

void MainWindow::newFileAction(){

    // New menu is clicked
    // 1. is any file open?
    //     2.  yes -> if open file already saved?
    //              3. yes -> clear editBox content.
    //              4. no  -> ask user to save file. -> save file and do 3.
    //     5.  no -> if editBox content blank?
    //              6. yes -> Do nothing
    //              7. no -> do 4.

    if( e.isFileOpen()){        // if any file open?
        if(e.isFileSaved()){    // file is open. check if file saved?
            ui->plainTextEdit->document()->setPlainText("");    // file is saved. clear editBox.
        }
        else{
            // file not saved. perform save changes
            performSaveChangesCheck();
            ui->plainTextEdit->document()->setPlainText("");    // clear editBox
        }
    }
    else{                   // no file open
        if( !ui->plainTextEdit->toPlainText().isEmpty()){   // edit box content not empty
            performSaveChangesCheck();                      // perform save changes
        }

    }

    e.setFileOpened(false);

}

void MainWindow::openFileAction(){

    // open menu is clicked
    // 1. is any file already opened?
    //      2. yes -> is open file already saved?
    //          3.  yes -> clear editBox content
    //          4.  no -> perform save changes
    //
    //      5. no -> if editBix content blank?
    //          6. yes-> do nothing
    //          7. no-> perform save changes

    if(e.isFileOpen()){
        if(!e.isFileSaved())
            performSaveChangesCheck();
    }
    else{
        if(!ui->plainTextEdit->toPlainText().isEmpty())
            performSaveChangesCheck();
    }

    QString filename = QFileDialog::getOpenFileName(this,tr("Open File"),".",tr("Text Documents (*.txt)"));

    if(filename.isEmpty())
        return;
    QString content;
    e.readTextFile(filename,content);
    ui->plainTextEdit->document()->setPlainText(content);
    e.setOpenFileName(filename);
    e.setFileOpened(true);
    e.setFileSaved(true);
}

void MainWindow::saveFileAction(){

    // save menu triggered
    // if any file open?
    //      yes -> if file saved?
    //          yes -> do nothing
    //          no  -> save file
    //      no ->  if content blank?
    //          yes -> do nothing
    //          no ->  ask for save file name. save file.

    if( e.isFileOpen() && e.isFileSaved())
        return;

    if(!e.isFileOpen() && ui->plainTextEdit->toPlainText().isEmpty())
        return;

    QString filename;
    if(!e.isFileOpen()){
        filename = QFileDialog::getSaveFileName(this,tr("Save File"),".",tr("Text Documents (*.txt)"));
        if ( filename.isEmpty())
            return;
        e.setOpenFileName(filename);
        e.setFileOpened(true);
    }
    else{
        filename = e.getOpenFileName();
    }

    QString content = ui->plainTextEdit->toPlainText();
    e.writeTextFile(filename,content);


    e.setFileSaved(true);

}

void MainWindow::saveAsFileAction(){

}

void MainWindow::pageSetupAction(){
//    QPrinter printer;
//    QPageSetupDialog psd(&printer);
//    if(psd.exec() != QDialog::Accepted)
//        return;
}

void MainWindow::printAction(){

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

    if (e.wordWrap){
        e.wordWrap = false;
        ui->actionWord_Wrap->setChecked(false);
        ui->plainTextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
    }
    else{
        e.wordWrap = true;
        ui->actionWord_Wrap->setChecked(true);
        ui->plainTextEdit->setLineWrapMode((QPlainTextEdit::WidgetWidth));
    }
    statusBarToggle();
}

void MainWindow::textChanged(){
    if(e.isFileSaved())
        e.setFileSaved(false);
}
