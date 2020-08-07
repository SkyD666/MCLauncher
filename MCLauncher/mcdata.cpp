#include "mcdata.h"

MCData::MCData()
{

}

QString MCData::runCommand = "";
QStringList MCData::versionFolderList = QStringList();
QUuid MCData::uuid = QUuid::createUuid();
QString MCData::accessToken = "";

QUuid MCData::getUuid() {
    return uuid;
}

QUuid MCData::setUuid(QUuid uuid) {
    MCData::uuid = uuid;
    return MCData::uuid;
}

QString MCData::getAccessToken() {
    return accessToken;
}

QString MCData::setAccessToken(QString accessToken) {
    MCData::accessToken = accessToken;
    return MCData::accessToken;
}

QString MCData::getRunCommand() {
    return runCommand;
}

QString MCData::setRunCommand(QString runCommand) {
    MCData::runCommand = runCommand;
    return MCData::runCommand;
}

QStringList MCData::getVersionFolderList() {
    return versionFolderList;
}

QStringList MCData::setVersionFolderList(QStringList versionFolderList) {
     MCData::versionFolderList = versionFolderList;
     return MCData::versionFolderList;
}

