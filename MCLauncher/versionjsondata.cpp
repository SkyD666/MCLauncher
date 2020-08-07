#include "versionjsondata.h"

VersionJsonData::VersionJsonData()
{
    this->minecraftArguments = nullptr;
    this->inheritsFrom = nullptr;
}

VersionJsonData::Arguments VersionJsonData::getArguments() {
    return this->arguments;
}
VersionJsonData::Arguments VersionJsonData::setArguments(Arguments arguments) {
    this->arguments = arguments;
    return this->arguments;
}
QString VersionJsonData::getId() {
    return id;
}
QString VersionJsonData::setId(QString id) {
    this->id = id;
    return id;
}
QString VersionJsonData::getInheritsFrom() {
    return inheritsFrom;
}
QString VersionJsonData::setInheritsFrom(QString inheritsFrom) {
    this->inheritsFrom = inheritsFrom;
    return inheritsFrom;
}
QString VersionJsonData::getTime() {
    return time;
}
QString VersionJsonData::setTime(QString time) {
    this->time = time;
    return time;
}
QString VersionJsonData::getReleaseTime() {
    return releaseTime;
}
QString VersionJsonData::setReleaseTime(QString releaseTime) {
    this->releaseTime = releaseTime;
    return releaseTime;
}
QString VersionJsonData::getType() {
    return type;
}
QString VersionJsonData::setType(QString type) {
    this->type = type;
    return type;
}
QString VersionJsonData::getMinecraftArguments() {
    return minecraftArguments;
}
QString VersionJsonData::setMinecraftArguments(QString minecraftArguments) {
    this->minecraftArguments = minecraftArguments;
    return minecraftArguments;
}
QList<VersionJsonLibrariesItemData> VersionJsonData::getLibraries() {
    return libraries;
}
QList<VersionJsonLibrariesItemData> VersionJsonData::setLibraries(QList<VersionJsonLibrariesItemData> libraries) {
    this->libraries = libraries;
    return libraries;
}
QString VersionJsonData::getMainClass() {
    return mainClass;
}
QString VersionJsonData::setMainClass(QString mainClass) {
    this->mainClass = mainClass;
    return mainClass;
}
int VersionJsonData::getMinimumLauncherVersion() {
    return minimumLauncherVersion;
}
int VersionJsonData::setMinimumLauncherVersion(int minimumLauncherVersion) {
    this->minimumLauncherVersion = minimumLauncherVersion;
    return minimumLauncherVersion;
}
QString VersionJsonData::getAssets() {
    return assets;
}
QString VersionJsonData::setAssets(QString assets) {
    this->assets = assets;
    return assets;
}
VersionJsonDownloadsData VersionJsonData::getDownloads() {
    return downloads;
}
VersionJsonDownloadsData VersionJsonData::setDownloads(VersionJsonDownloadsData downloads) {
    this->downloads = downloads;
    return downloads;
}
VersionJsonAssetIndexData VersionJsonData::getAssetIndex() {
    return assetIndex;
}
VersionJsonAssetIndexData VersionJsonData::setAssetIndex(VersionJsonAssetIndexData assetIndex) {
    this->assetIndex = assetIndex;
    return assetIndex;
}
