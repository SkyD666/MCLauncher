#include <QString>
#include <QStringList>
#include <QUuid>

#ifndef MCDATA_H
#define MCDATA_H

class MCData
{
public:
    MCData();

    static QString getRunCommand();
    static QString setRunCommand(QString);
    static QStringList getVersionFolderList();
    static QStringList setVersionFolderList(QStringList);
    static QUuid getUuid();
    static QUuid setUuid(QUuid);
    static QString getAccessToken();
    static QString setAccessToken(QString);
private:
    static QString runCommand;
    static QStringList versionFolderList;
    static QUuid uuid;
    static QString accessToken;
};

#endif // MCDATA_H
