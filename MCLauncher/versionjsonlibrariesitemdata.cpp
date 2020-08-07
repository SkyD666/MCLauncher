#include "versionjsonlibrariesitemdata.h"

VersionJsonLibrariesItemData::VersionJsonLibrariesItemData() : name(""), downloads(Downloads())
{
}

QString VersionJsonLibrariesItemData::getName(){
    return name;
}

QString VersionJsonLibrariesItemData::setName(QString name) {
    VersionJsonLibrariesItemData::name = name;
    return name;
}
VersionJsonLibrariesItemData::Downloads VersionJsonLibrariesItemData::getDownloads() {
    return downloads;
}
VersionJsonLibrariesItemData::Downloads VersionJsonLibrariesItemData::setDownloads(Downloads downloads) {
    VersionJsonLibrariesItemData::downloads = downloads;
    return downloads;
}
