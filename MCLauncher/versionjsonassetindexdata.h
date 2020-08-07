#include <QString>

#ifndef VERSIONJSONASSETINDEXDATA_H
#define VERSIONJSONASSETINDEXDATA_H


class VersionJsonAssetIndexData
{
public:
    VersionJsonAssetIndexData();

    long getTotalSize();
    long setTotalSize(long);
    bool getKnown();
    bool setKnown(bool);
    QString getId();
    QString setId(QString);
    QString getUrl();
    QString setUrl(QString);
    QString getSha1();
    QString setSha1(QString);
    long getSize();
    long setSize(long);
private:
    long totalSize;
    bool known;
    QString id;
    QString url;
    QString sha1;
    long size;
};

#endif // VERSIONJSONASSETINDEXDATA_H
