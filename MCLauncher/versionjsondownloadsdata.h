#include <QString>

#ifndef VERSIONJSONDOWNLOADSDATA_H
#define VERSIONJSONDOWNLOADSDATA_H


class VersionJsonDownloadsData
{
public:
    VersionJsonDownloadsData();

    class Client {
    public:
        QString getUrl() {
            return url;
        }

        QString setUrl(QString url) {
            this->url = url;
            return url;
        }

        QString getSha1() {
            return sha1;
        }

        QString setSha1(QString sha1) {
            this->sha1 = sha1;
            return sha1;
        }

        long getSize() {
            return size;
        }

        long setSize(long size) {
            this->size = size;
            return size;
        }
    private:
        QString url;
        QString sha1;
        long size;
    };

    class Server {
    public:
        QString getUrl() {
            return url;
        }

        QString setUrl(QString url) {
            this->url = url;
            return url;
        }

        QString getSha1() {
            return sha1;
        }

        QString setSha1(QString sha1) {
            this->sha1 = sha1;
            return sha1;
        }

        long getSize() {
            return size;
        }

        long setSize(long size) {
            this->size = size;
            return size;
        }
    private:
        QString url;
        QString sha1;
        long size;
    };

    Client getClient() {
        return client;
    }

    Client setClient(Client client) {
        this->client = client;
        return this->client;
    }

    Server getServer() {
        return server;
    }

    Server setServer(Server server) {
        this->server = server;
        return this->server;
    }
private:
    Client client;
    Server server;
};

#endif // VERSIONJSONDOWNLOADSDATA_H
