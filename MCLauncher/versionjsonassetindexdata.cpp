#include "versionjsonassetindexdata.h"

VersionJsonAssetIndexData::VersionJsonAssetIndexData()
{

}

long VersionJsonAssetIndexData::getTotalSize() {
    return VersionJsonAssetIndexData::totalSize;
}
long VersionJsonAssetIndexData::setTotalSize(long totalSize) {
    VersionJsonAssetIndexData::totalSize = totalSize;
    return VersionJsonAssetIndexData::totalSize;
}
bool VersionJsonAssetIndexData::getKnown() {
    return VersionJsonAssetIndexData::known;
}
bool VersionJsonAssetIndexData::setKnown(bool known) {
    VersionJsonAssetIndexData::known = known;
    return VersionJsonAssetIndexData::known;
}
QString VersionJsonAssetIndexData::getId() {
    return VersionJsonAssetIndexData::id;
}
QString VersionJsonAssetIndexData::setId(QString id) {
    VersionJsonAssetIndexData::id = id;
    return VersionJsonAssetIndexData::id;
}
QString VersionJsonAssetIndexData::getUrl() {
    return VersionJsonAssetIndexData::url;
}
QString VersionJsonAssetIndexData::setUrl(QString url) {
    VersionJsonAssetIndexData::url = url;
    return VersionJsonAssetIndexData::url;
}
QString VersionJsonAssetIndexData::getSha1() {
    return VersionJsonAssetIndexData::sha1;
}
QString VersionJsonAssetIndexData::setSha1(QString sha1) {
    VersionJsonAssetIndexData::sha1 = sha1;
    return VersionJsonAssetIndexData::sha1;
}
long VersionJsonAssetIndexData::getSize() {
    return VersionJsonAssetIndexData::size;
}
long VersionJsonAssetIndexData::setSize(long size) {
    VersionJsonAssetIndexData::size = size;
    return VersionJsonAssetIndexData::size;
}
