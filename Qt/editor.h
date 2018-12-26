#ifndef EDITOR_H
#define EDITOR_H
#include <QString>

class editor
{
private:
    bool fileOpened;
    bool fileSaved;
    QString openFilename;
public:
    editor();
    bool wordWrap;
    bool readTextFile(const QString &, QString &);
    bool writeTextFile(const QString &, QString &);
    bool isFileOpen();
    bool isFileSaved();
    void setFileOpened(bool);
    void setFileSaved(bool);
    QString getOpenFileName();
    void setOpenFileName(QString);
};

#endif // EDITOR_H
