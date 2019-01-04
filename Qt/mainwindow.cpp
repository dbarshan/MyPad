#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "editor.h"

#include <QFileDialog>
#include <QLabel>
#include <QMessageBox>
#include <QFont>
#include <QFontDialog>

#include <QPageSetupDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QIcon>

editor e;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //----------------------- connect slots for File Menu actions ----------------------------------------
    connect(    ui->action_New,         &QAction::triggered,    this,   &MainWindow::newFileAction      );
    connect(    ui->action_Open,        &QAction::triggered,    this,   &MainWindow::openFileAction     );
    connect(    ui->action_Save,        &QAction::triggered,    this,   &MainWindow::saveFileAction     );
    connect(    ui->actionSave_As,      &QAction::triggered,    this,   &MainWindow::saveAsFileAction   );

    connect(    ui->actionPage_Setup,   &QAction::triggered,    this,   &MainWindow::pageSetupAction    );
    connect(    ui->actionPrint,        &QAction::triggered,    this,   &MainWindow::printAction        );

    connect(    ui->actionExit,         &QAction::triggered,    this,   &MainWindow::exitAction         );

    //----------------------- connect slots for Edit Menu actions ----------------------------------------
    connect(    ui->actionUndo,         &QAction::triggered,    this,   &MainWindow::undoAction         );

    connect(    ui->actionCut,          &QAction::triggered,    this,   &MainWindow::cutAction          );
    connect(    ui->actionCopy,         &QAction::triggered,    this,   &MainWindow::copyAction         );
    connect(    ui->actionPaste,        &QAction::triggered,    this,   &MainWindow::pasteAction        );
    connect(    ui->actionDelete,       &QAction::triggered,    this,   &MainWindow::deleteAction       );

    connect(    ui->actionFind,         &QAction::triggered,    this,   &MainWindow::findAction         );
    connect(    ui->actionFind_Next,    &QAction::triggered,    this,   &MainWindow::findNextAction     );
    connect(    ui->actionReplace,      &QAction::triggered,    this,   &MainWindow::replaceAction      );
    connect(    ui->actionGo_To,        &QAction::triggered,    this,   &MainWindow::gotoAction         );

    connect(    ui->actionSelect_All,   &QAction::triggered,    this,   &MainWindow::selectAllAction    );
    connect(    ui->actionTime_Date,    &QAction::triggered,    this,   &MainWindow::timeDateAction     );

    //----------------------- connect slots for Format Menu actions ----------------------------------------
    connect(    ui->actionWord_Wrap,    &QAction::triggered,    this,   &MainWindow::wordWrapToggleAction );
    connect(    ui->actionFont,         &QAction::triggered,    this,   &MainWindow::fontSelectAction   );

    //----------------------- connect slots for View Menu actions ----------------------------------------
    connect(    ui->actionStatus_Bar,   &QAction::triggered,    this,   &MainWindow::statusBarToggleAction);

    //----------------------- connect slots for Help Menu actions ----------------------------------------
    connect(    ui->actionView_Help,    &QAction::triggered,    this,   &MainWindow::viewHelpAction     );
    connect(    ui->actionAbout_MyPad,  &QAction::triggered,    this,   &MainWindow::aboutAction        );

    //-------------------------other slots ---------------------------------------------------------------
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
    //      no ->  ask for save file name. save file.


    if( e.isFileOpen() && e.isFileSaved())
        return;

    QString filename;

    if(e.isFileOpen() && !e.isFileSaved()){
        filename = e.getOpenFileName();
    }

    if(!e.isFileOpen()){
        QString filename;
        filename = QFileDialog::getSaveFileName(this,tr("Save File"),".",tr("Text Documents (*.txt)"));
        if ( filename.isEmpty())
            return;
        e.setOpenFileName(filename);
        e.setFileOpened(true);
    }

    QString content = ui->plainTextEdit->toPlainText();
    e.writeTextFile(filename,content);
    e.setFileSaved(true);
}

void MainWindow::saveAsFileAction(){
    // SaveAs menu triggered
    // ask for save file name. save file.
    // close old file without saving.
    // open new file


    QString filename = QFileDialog::getSaveFileName(this,tr("Save File"),".",tr("Text Documents (*.txt)"));
    if ( filename.isEmpty())
        return;
    QString content = ui->plainTextEdit->toPlainText();
    e.writeTextFile(filename,content);

    e.readTextFile(filename,content);
    ui->plainTextEdit->document()->setPlainText(content);
    e.setOpenFileName(filename);
    e.setFileOpened(true);
    e.setFileSaved(true);

}

void MainWindow::pageSetupAction(){
    QPageSetupDialog psd(&printer);
    if(psd.exec() != QDialog::Accepted)
        return;
}

void MainWindow::printAction(){

    QPrintDialog dialog(&printer, this);
    dialog.setWindowTitle(tr("Print Document"));
    if (ui->plainTextEdit->textCursor().hasSelection()){
        dialog.addEnabledOption(QAbstractPrintDialog::PrintSelection);
    }
    if (dialog.exec() != QDialog::Accepted) {
               return;
    }


    //QPrinter printer(QPrinter::HighResolution);
    //printer.setOutputFileName("print.ps");
    //QPainter painter;
    //painter.begin(&printer);

    //for (int page = 0; page < numberOfPages; ++page) {
    //    // Use the painter to draw on the page.
    //    if (page != lastPage)
    //        printer.newPage();
    //}

    //painter.end();
}

void MainWindow::exitAction(){
    this->close();
}

void MainWindow::undoAction(){
    ui->plainTextEdit->undo();
}

void MainWindow::cutAction(){
    ui->plainTextEdit->cut();
}

void MainWindow::copyAction(){
    ui->plainTextEdit->copy();
}

void MainWindow::pasteAction(){
    ui->plainTextEdit->paste();
}

void MainWindow::deleteAction(){
    ui->plainTextEdit->textCursor().removeSelectedText();
}

void MainWindow::findAction(){

}

void MainWindow::findNextAction(){

}

void MainWindow::replaceAction(){

}

void MainWindow::gotoAction(){

}

void MainWindow::selectAllAction(){

}

void MainWindow::timeDateAction(){

}

void MainWindow::fontSelectAction(){
    bool ok;
    QFont font = ui->plainTextEdit->font();
    font =  QFontDialog::getFont(&ok,font,this,"Font");
    if(ok){
        ui->plainTextEdit->setFont(font);
    }
    else{

    }
}

void MainWindow::statusBarToggleAction(){
    if ( ui->statusBar->isVisible()){
        ui->statusBar->hide();
        ui->actionStatus_Bar->setChecked(false);
    }
    else{
        ui->statusBar->show();
        ui->actionStatus_Bar->setChecked(true);
    }
}

void MainWindow::wordWrapToggleAction(){

    if (e.wordWrap){
        e.wordWrap = false;
        ui->actionWord_Wrap->setChecked(false);
        ui->plainTextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
        ui->actionStatus_Bar->setEnabled(true);
    }
    else{
        e.wordWrap = true;
        ui->actionWord_Wrap->setChecked(true);
        ui->plainTextEdit->setLineWrapMode((QPlainTextEdit::WidgetWidth));
        ui->actionStatus_Bar->setEnabled(false);
    }
    statusBarToggleAction();
}

void MainWindow::viewHelpAction(){

}

void MainWindow::aboutAction(){

    QMessageBox msgBox;
    QIcon icon;

    msgBox.setWindowTitle("About MyPad");
    msgBox.setWindowIcon(icon);

    msgBox.setIconPixmap(QPixmap("C:\\users\\bdas\\Desktop\\myPad4.ico"));
    msgBox.setText("MyPad is a simple Text editor.\n\n\nVersion: 1.0.0");
    msgBox.exec();

    QMessageBox messageBox;



}


void MainWindow::textChanged(){
    if(e.isFileSaved())
        e.setFileSaved(false);
}
