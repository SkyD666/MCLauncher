#include <QString>
#include <QList>
#include <QVariant>
#include "versionjsonlibrariesitemdata.h"
#include "versionjsonassetindexdata.h"
#include "versionjsondownloadsdata.h"

#ifndef VERSIONJSONDATA_H
#define VERSIONJSONDATA_H

class VersionJsonData
{
public:
    VersionJsonData();

    class Game{
    public:
        QList<QVariant> getList() {
            return list;
        }

        QList<QVariant> setList(QList<QVariant> list) {
            this->list = list;
            return this->list;
        }
    private:
        QList<QVariant> list;
    };

    class Jvm{
    public:
        QList<QVariant> getList() {
            return list;
        }

        QList<QVariant> setList(QList<QVariant> list) {
            this->list = list;
            return this->list;
        }
    private:
        QList<QVariant> list;
    };

    class Arguments{
    public:
        Game getGame() {
            return game;
        }

        Game setGame(Game game) {
            this->game = game;
            return this->game;
        }

        Jvm getJvm() {
            return jvm;
        }

        Jvm setJvm(Jvm jvm) {
            this->jvm = jvm;
            return this->jvm;
        }
    private:
        Game game;
        Jvm jvm;
    };

    QString getId();
    QString setId(QString);
    QString getInheritsFrom();
    QString setInheritsFrom(QString);
    QString getTime();
    QString setTime(QString);
    QString getReleaseTime();
    QString setReleaseTime(QString);
    QString getType();
    QString setType(QString);
    QString getMinecraftArguments();
    QString setMinecraftArguments(QString);
    QList<VersionJsonLibrariesItemData> getLibraries();
    QList<VersionJsonLibrariesItemData> setLibraries(QList<VersionJsonLibrariesItemData>);
    QString getMainClass();
    QString setMainClass(QString);
    int getMinimumLauncherVersion();
    int setMinimumLauncherVersion(int);
    QString getAssets();
    QString setAssets(QString);
    VersionJsonDownloadsData getDownloads();
    VersionJsonDownloadsData setDownloads(VersionJsonDownloadsData downloads);
    VersionJsonAssetIndexData getAssetIndex();
    VersionJsonAssetIndexData setAssetIndex(VersionJsonAssetIndexData);
    Arguments getArguments();
    Arguments setArguments(Arguments);
private:
    QString id;
    QString inheritsFrom;
    QString time;
    QString releaseTime;
    QString type;
    QString minecraftArguments;
    QList<VersionJsonLibrariesItemData> libraries;
    QString mainClass;
    int minimumLauncherVersion;
    QString assets;
    VersionJsonDownloadsData downloads;
    VersionJsonAssetIndexData assetIndex;
    Arguments arguments;
};

#endif // VERSIONJSONDATA_H
