#include "editor.h"
#include <QFile>
#include <QString>
#include <QIODevice>
#include <QTextStream>

editor::editor()
{
    wordWrap = false;
    fileOpened = false;
    fileSaved = false;
}


bool editor::readTextFile(const QString &filename, QString &content){
    content = "";
    QFile inputFile(filename);
    if(inputFile.open(QIODevice::ReadOnly)){
        QTextStream in(&inputFile);
        while(!in.atEnd()){
            QString line = in.readLine();
            content += line + "\n";
        }
    }
    return true;
}

bool editor::writeTextFile(const QString &filename, QString &content){
    QFile outputFile(filename);
    if(outputFile.open(QIODevice::WriteOnly)){
        QTextStream out(&outputFile);
        out << content;
    }
   return true;
}

bool editor::isFileOpen(){
    return fileOpened;
}

bool editor::isFileSaved(){
    return fileSaved;
}

void editor::setFileOpened(bool s){
    fileOpened = s;
}

void editor::setFileSaved(bool s){
    fileSaved = s;
}

void editor::setOpenFileName(QString fname){
    openFilename = fname;
}

QString editor::getOpenFileName(){
    return openFilename;
}
