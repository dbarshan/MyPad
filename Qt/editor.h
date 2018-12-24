#ifndef EDITOR_H
#define EDITOR_H
#include <QString>

class editor
{
public:
    editor();
    bool readTextFile(const QString &, QString &);
    bool writeTextFile(const QString &, QString &);
};

#endif // EDITOR_H
