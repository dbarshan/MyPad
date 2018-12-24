#include "editor.h"
#include <QFile>
#include <QString>
#include <QIODevice>
#include <QTextStream>

editor::editor()
{

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
