#include <QString>

#ifndef VERSIONJSONLIBRARIESITEMDATA_H
#define VERSIONJSONLIBRARIESITEMDATA_H

class VersionJsonLibrariesItemData
{
public:
    VersionJsonLibrariesItemData();

    class Artifact {
    public:
        Artifact() : url(""), sha1(""), size(0) {

        }
        QString getUrl() {
            return url;
        }

        long getSize() {
            return size;
        }
        QString getSha1() {
            return sha1;
        }
        QString setUrl(QString url) {
            this->url = url;
            return this->url;
        }
        long setSize(long size) {
            this->size = size;
            return this->size;
        }
        QString setSha1(QString sha1) {
            this->sha1 = sha1;
            return this->sha1;
        }
    private:
        QString url;
        QString sha1;
        long size;
    };

    class Downloads {
    public:
        Downloads() : artifact(Artifact()) {

        }
        Artifact getArtifact() {
            return artifact;
        }
        Artifact setArtifact(Artifact artifact){
            this->artifact = artifact;
            return this->artifact;
        }
    private:
        Artifact artifact;
    };

    QString getName();
    QString setName(QString);
    Downloads getDownloads();
    Downloads setDownloads(Downloads);
private:
    QString name;
    Downloads downloads;
};

#endif // VERSIONJSONLIBRARIESITEMDATA_H
