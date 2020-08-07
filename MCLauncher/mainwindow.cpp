#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstring>
#include <QApplication>
#include <QFileDialog>
#include <QJsonDocument>
#include <QStringList>
#include <QProcess>
#include <QCryptographicHash>
#include <QJsonObject>
#include <QJsonArray>
#include <QList>
#include <QDebug>
#include <QMessageBox>
#include <QUuid>
#include <QDesktopServices>
#include <QDirIterator>
#include <QSettings>
#include "mcdata.h"
#include "windowsinfo.h"
#include "versionjsondata.h"

const QString MainWindow::APP_NAME  = "MCLauncher";
bool initVersion();
QString findNativesFolder(QString strPath);
QProcess *p;
QString id = "";
QLabel *statusBarLabel;
QSettings  *iniFile;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    iniFile = new QSettings(QCoreApplication::applicationDirPath().toLocal8Bit() + "/MCLauncherSetting.ini", QSettings::IniFormat);

    ui->lineEditUserName->setText(iniFile->value("User/UserName").toString());

    long availMemory = WindowsInfo::getAvailMemorySize() / 1024 / 1024;
    long memorySize = WindowsInfo::getMemorySize() / 1024 / 1024;
    ui->lineEditAvailableMemory->setText(QString::number(availMemory));
    ui->lineEditTotalMemory->setText(QString::number(memorySize));
    QString maxMemory = iniFile->value("BasicConfig/MaxMemory").toString();
    if (maxMemory != "") {
        ui->lineEditMaxMemory->setText(maxMemory);
    } else {
        if (memorySize <= 2048) {
            ui->lineEditMaxMemory->setText("512");
        } else if (memorySize > 2048 && memorySize <= 4096) {
            ui->lineEditMaxMemory->setText("1024");
        } else if (memorySize > 4096) {
            ui->lineEditMaxMemory->setText("2048");
        }
    }

    QString javaPath = iniFile->value("Java/JavaPath").toString();
    if (javaPath != "") {
        ui->lineEditJavaPath->setText(javaPath);
    } else {
        QString strReg = "\\HKEY_LOCAL_MACHINE\\SOFTWARE\\JavaSoft\\Java Runtime Environment";
        QSettings* setting = new QSettings(strReg, QSettings::NativeFormat);
        //如果有多个文件夹可以递归
        auto groupsList = setting->childGroups();
        foreach(QString group,groupsList) {
            setting->beginGroup(group);
            QString softWareName=setting->value("JavaHome").toString();
            if(!softWareName.isEmpty()) {
                ui->lineEditJavaPath->setText(softWareName + "\\bin\\java.exe");
            } else {
                ui->lineEditJavaPath->setText("");
                QMessageBox::warning(this, "警告", "未找到java.exe，请手动设置或下载Java！");
            }
            setting->endGroup();
        }
    }

    ui->labelWindowsVersion->setText(WindowsInfo::getWindowsVersion());
    ui->labelCPU->setText(WindowsInfo::getCPU());

    ui->btnStart->setEnabled(false);
    ui->btnStart->setText("未发现游戏！");

    if (initVersion()) {
        ui->listVersion->addItems(MCData::getVersionFolderList());

        if (ui->listVersion->count() > 0) {
            ui->listVersion->item(0)->setSelected(true);
            ui->btnStart->setEnabled(true);
            ui->btnStart->setText("启动");
        }
    }

    statusBarLabel = new QLabel("就绪", this);
    ui->statusbar->addWidget(statusBarLabel);

    //    QString javaDir = setting->value("JavaHome").toString();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool initVersion() {
    QString path = QCoreApplication::applicationDirPath() + "/.minecraft/versions";
    QDir dir(path);
    if (dir.exists()) {
        dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
        dir.setSorting(QDir::Name);
        MCData::setVersionFolderList(dir.entryList());
        return true;
    } else return false;
}

void MainWindow::on_btnStart_clicked()
{
    iniFile->setValue("User/UserName", ui->lineEditUserName->text());
    iniFile->setValue("BasicConfig/MaxMemory", ui->lineEditMaxMemory->text());

    if (ui->lineEditJavaPath->text() == "") {
        QMessageBox::critical(this, "错误", "Java路径不能为空！");
        return;
    } else if (ui->lineEditUserName->text() == "") {
        QMessageBox::critical(this, "错误", "用户名不能为空！");
        return;
    } else if (ui->lineEditMaxMemory->text() == "" || ui->lineEditMaxMemory->text().toInt() <= 0 ||
                ui->lineEditMaxMemory->text().toULongLong() > WindowsInfo::getMemorySize() / 1024 / 1024) {
        QMessageBox::critical(this, "错误", "最大内存设置非法！");
        return;
    }

    //下面开始json解析、替换字符串等逻辑
    VersionJsonData *versionJsonData = new VersionJsonData();

    QString MainJarPath = "";
    bool isOriginal = true;

    QString folderPath = QCoreApplication::applicationDirPath().toUtf8() + "/.minecraft/versions/"+ ui->listVersion->selectedItems().first()->text();
    QString path = folderPath + "/" + ui->listVersion->selectedItems().first()->text()  + ".json";
    QString cpParam;    //cp参数

    path = QDir::fromNativeSeparators(path);

    QStringList list = ui->listVersion->selectedItems().first()->text().split("-");

    statusBarLabel->setText("Json解析开始");
    if(parseVersionJson(path, cpParam, versionJsonData)){

        id = versionJsonData->getId();

        if(versionJsonData->getInheritsFrom() != nullptr) {
            MainJarPath = versionJsonData->getInheritsFrom();
            isOriginal = false;
        } else {
            MainJarPath = versionJsonData->getId();
        }

        if (!isOriginal) {
            cpParam = cpParam + ";";
            parseVersionJson(QCoreApplication::applicationDirPath() + "/.minecraft/versions/"+ MainJarPath
                             + "/" + MainJarPath  + ".json", cpParam, versionJsonData);
        }

        statusBarLabel->setText("Json解析完成");

        cpParam = "\"" + cpParam + ";" + QCoreApplication::applicationDirPath().toUtf8() + "/.minecraft/versions/"
                + MainJarPath + "/" + MainJarPath + ".jar\"";

        QUuid uuid = QUuid::createUuid();   //盗版uuid

        MCData::setUuid(uuid);

        QString uuidString = MCData::getUuid().toString();
        uuidString.replace("{", "");
        uuidString.replace("-", "");
        uuidString.replace("}", "");

        QUuid token = QUuid::createUuid();   //盗版uuid

        QString tokenString = token.toString();
        tokenString.replace("{", "");
        tokenString.replace("-", "");
        tokenString.replace("}", "");

        MCData::setAccessToken(tokenString);

        QString minecraftArguments;
        if (versionJsonData->getMinecraftArguments() != nullptr) {
            minecraftArguments = versionJsonData->getMinecraftArguments();
        } else if (versionJsonData->getArguments().getGame().getList().size() > 0) {
            VersionJsonData::Arguments arguments;
            arguments = versionJsonData->getArguments();
            QList<QVariant> gameList = arguments.getGame().getList();
            minecraftArguments = "";
            for (int i = 0; i < gameList.size(); i++) {
                if (gameList[i].type() == QVariant::String) {
                    minecraftArguments = minecraftArguments + " " + gameList[i].toString();
                }
            }
        } else {
            minecraftArguments = "--username ${auth_player_name} --version ${version_name}"
                                 " --gameDir ${game_directory} --assetsDir ${assets_root}"
                                 " --assetIndex ${assets_index_name} --uuid ${auth_uuid}"
                                 " --accessToken ${auth_access_token} --userType ${user_type}"
                                 " --versionType ${version_type}";
        }
        minecraftArguments.replace("${auth_player_name}", "\"" + ui->lineEditUserName->text() + "\"");
        minecraftArguments.replace("${version_name}", "\"" + APP_NAME + " " + QApplication::applicationVersion() + "\"");
        minecraftArguments.replace("${game_directory}", "\"" + QCoreApplication::applicationDirPath() + "/.minecraft" + "\"");
        minecraftArguments.replace("${assets_root}", "\"" + QCoreApplication::applicationDirPath() + "/.minecraft/assets" + "\"");
        minecraftArguments.replace("${assets_index_name}", versionJsonData->getAssetIndex().getId());
        minecraftArguments.replace("${auth_uuid}", uuidString);
        minecraftArguments.replace("${auth_access_token}", tokenString);
        minecraftArguments.replace("${user_type}", "mojang");
        minecraftArguments.replace("${user_properties}", "{}");
        minecraftArguments.replace("${version_type}", "\"" + APP_NAME + " " + QApplication::applicationVersion() + "\"");

        QString runCommand;
        std::string nativesPath = findNativesFolder(QCoreApplication::applicationDirPath() + "/.minecraft/versions/" + ui->listVersion->selectedItems().first()->text() + "/").toStdString();
        runCommand = "\"" + QDir::fromNativeSeparators(ui->lineEditJavaPath->text()) + "\"";
        runCommand = runCommand + " -Xmx" + ui->lineEditMaxMemory->text().toUtf8() + "m"
                + " -Xmn128m -XX:+UseG1GC -XX:-UseAdaptiveSizePolicy -XX:-OmitStackTraceInFastThrow"
                + " -Dminecraft.launcher.brand=" + "\"" + APP_NAME + "\"" + " -Dminecraft.launcher.version=1" + QApplication::applicationVersion()
                + " -Djava.library.path=" + "\"" + QString::fromStdString(nativesPath).toUtf8() + "\""
                + " -cp " + cpParam
                + " " + versionJsonData->getMainClass()
                + " " + minecraftArguments;
        MCData::setRunCommand(runCommand);

        qDebug() << runCommand;

        statusBarLabel->setText("游戏启动中...");

        p = new QProcess(this);
        p->start("cmd");
        ui->btnStart->setEnabled(false);
        ui->btnStart->setText("启动中...");
        p->waitForStarted();
        runCommand = runCommand + "\n";
        p->write(runCommand.toLocal8Bit().data());
        connect(p , SIGNAL(readyReadStandardOutput()) , this, SLOT(on_readoutput()));
        connect(p , SIGNAL(readyReadStandardError()) , this , SLOT(on_readerror()));
    } else {
        QMessageBox::warning(this, "警告", "版本Json解析失败！");
        statusBarLabel->setText("就绪");
    }
}

void MainWindow::on_readoutput()
{
    QByteArray outPut = p->readAllStandardOutput();
    ui->textEditLog->setText(ui->textEditLog->document()->toPlainText() + QString::fromLocal8Bit(outPut));
    QTextCursor cursor = ui->textEditLog->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textEditLog->setTextCursor(cursor);

    if (outPut.contains("Sound engine started") || outPut.contains("successfully loaded") || outPut.contains("OpenAL initialized")) {
        //        ui->btnStart->setEnabled(true);
        ui->btnStart->setText("\"" + id + "\" 运行中...");
        statusBarLabel->setText("游戏运行中...");

        iniFile->setValue("Java/JavaPath", ui->lineEditJavaPath->text());
    }
    if (outPut.contains("Stopping")) {
        ui->btnStart->setEnabled(true);
        ui->btnStart->setText("启动");
        statusBarLabel->setText("就绪");
    }
}

void MainWindow::on_readerror()
{
    QByteArray outPut = p->readAllStandardError();
    ui->textEditLog->setText(ui->textEditLog->document()->toPlainText() + QString::fromLocal8Bit(outPut));
    QTextCursor cursor = ui->textEditLog->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textEditLog->setTextCursor(cursor);
    ui->btnStart->setEnabled(true);
    ui->btnStart->setText("启动");
    statusBarLabel->setText("就绪");
}

bool MainWindow::parseVersionJson(QString path, QString &cpParam, VersionJsonData *versionJsonData) {
    std::string str = path.toStdString();
    QFile jsonFile(QString::fromStdString(str));
    qDebug() << QString::fromStdString(str);
    if(!jsonFile.open(QIODevice::ReadOnly)) return false;
    QByteArray allData = jsonFile.readAll();
    jsonFile.close();

    QJsonParseError jsonParseError;
    QJsonDocument jsonDoucment = QJsonDocument::fromJson(allData, &jsonParseError);
    if (jsonParseError.error == QJsonParseError::NoError) {
        if (jsonDoucment.isObject())
        {
            //开始解析json对象
            QJsonObject jsonObject0 = jsonDoucment.object();
            if (jsonObject0.contains("id"))
            {
                QJsonValue value = jsonObject0.take("id");
                if (value.isString())
                {
                    versionJsonData->setId(value.toString());
                }
            }
            if (jsonObject0.contains("inheritsFrom"))
            {
                QJsonValue value = jsonObject0.take("inheritsFrom");
                if (value.isString())
                {
                    versionJsonData->setInheritsFrom(value.toString());
                }
            }

            QJsonObject jsonObject;
            if (jsonObject0.contains("patches")) {
                jsonObject = jsonObject0.take("patches").toArray().first().toObject();
            } else {
                jsonObject = jsonDoucment.object();
            }

            if (jsonObject.contains("time"))
            {
                QJsonValue value = jsonObject.take("time");
                if (value.isString())
                {
                    versionJsonData->setTime(value.toVariant().toString());
                }
            }
            if (jsonObject.contains("releaseTime"))
            {
                QJsonValue value = jsonObject.take("releaseTime");
                if (value.isString())
                {
                    versionJsonData->setReleaseTime(value.toString());
                }
            }
            if (jsonObject.contains("type"))
            {
                QJsonValue value = jsonObject.take("type");
                if (value.isString())
                {
                    versionJsonData->setType(value.toString());
                }
            }
            if (jsonObject.contains("minecraftArguments"))
            {
                QJsonValue value = jsonObject.take("minecraftArguments");
                if (value.isString())
                {
                    versionJsonData->setMinecraftArguments(value.toString());
                }
            }
            if (jsonObject.contains("arguments"))
            {
                QJsonValue value = jsonObject.take("arguments");
                QJsonValue game_arrays_value = value.toObject().take("game");
                QList<QVariant> gameList;
                if (game_arrays_value.isArray())//判断他是不是json数组
                {
                    for (int i = 0; i < game_arrays_value.toArray().size(); i++){
                        gameList.push_back(game_arrays_value.toArray().toVariantList()[i]);
                    }
                }
                VersionJsonData::Game game;
                game.setList(gameList);

                QJsonValue jvm_arrays_value = value.toObject().take("game");
                QList<QVariant> jvmList;
                if (jvm_arrays_value.isArray())//判断他是不是json数组
                {
                    for (int i = 0; i < jvm_arrays_value.toArray().size(); i++){
                        jvmList.push_back(jvm_arrays_value.toArray().toVariantList()[i]);
                    }
                }
                VersionJsonData::Jvm jvm;
                jvm.setList(jvmList);

                VersionJsonData::Arguments arguments;
                arguments.setGame(game);
                arguments.setJvm(jvm);
                versionJsonData->setArguments(arguments);
            }
            if (jsonObject.contains("mainClass"))
            {
                QJsonValue value = jsonObject.take("mainClass");
                if (value.isString())
                {
                    versionJsonData->setMainClass(value.toString());
                }
            }
            if (jsonObject.contains("minimumLauncherVersion"))
            {
                QJsonValue value = jsonObject.take("minimumLauncherVersion");
                if (value.isString())
                {
                    versionJsonData->setMinimumLauncherVersion(value.toInt());
                }
            }
            if (jsonObject.contains("assets"))
            {
                QJsonValue value = jsonObject.take("assets");
                if (value.isString())
                {
                    versionJsonData->setAssets(value.toString());
                }
            }

            if (jsonObject.contains("downloads"))
            {
                QJsonObject downloadsObject = jsonObject.take("downloads").toObject();
                QJsonObject clientObject = downloadsObject.take("client").toObject();
                QJsonObject serverObject = downloadsObject.take("server").toObject();
                QJsonValue value = jsonObject.take("downloads");
                VersionJsonDownloadsData versionJsonDownloadsData;
                VersionJsonDownloadsData::Client client;
                client.setUrl(clientObject.take("url").toString());
                client.setSha1(clientObject.take("sha1").toString());
                client.setSize(clientObject.take("size").toString().toLong());
                versionJsonDownloadsData.setClient(client);

                VersionJsonDownloadsData::Client server;
                server.setUrl(clientObject.take("url").toString());
                server.setSha1(clientObject.take("sha1").toString());
                server.setSize(clientObject.take("size").toString().toLong());
                versionJsonDownloadsData.setClient(server);

                versionJsonData->setDownloads(versionJsonDownloadsData);
            }

            if (jsonObject.contains("assetIndex"))
            {
                QJsonObject assetIndexObject = jsonObject.take("assetIndex").toObject();

                VersionJsonAssetIndexData versionJsonAssetIndexData;
                versionJsonAssetIndexData.setTotalSize(assetIndexObject.take("totalSize").toString().toLong());
                versionJsonAssetIndexData.setId(assetIndexObject.take("id").toString());
                versionJsonAssetIndexData.setKnown(assetIndexObject.take("known").toBool());

                versionJsonAssetIndexData.setUrl(assetIndexObject.take("url").toString());
                versionJsonAssetIndexData.setSha1(assetIndexObject.take("sha1").toString());
                versionJsonAssetIndexData.setSize(assetIndexObject.take("size").toString().toLong());
                versionJsonData->setAssetIndex(versionJsonAssetIndexData);
            }

            if (jsonObject.contains("libraries"))
            {
                QJsonValue arrays_value = jsonObject.take("libraries");
                if (arrays_value.isArray())//判断他是不是json数组
                {
                    QJsonArray heeloArray = arrays_value.toArray();
                    QList<VersionJsonLibrariesItemData> libraries;
                    for (int i = 0; i < heeloArray.size(); i++){
                        QJsonValue helloArrayValue = heeloArray.at(i);
                        if (helloArrayValue.isObject()) {
                            VersionJsonLibrariesItemData versionJsonLibrariesItemData;
                            versionJsonLibrariesItemData.setName(helloArrayValue.toObject().take("name").toString());
                            VersionJsonLibrariesItemData::Downloads downloads;
                            VersionJsonLibrariesItemData::Artifact artifact;
                            artifact.setUrl(helloArrayValue.toObject().take("downloads").toObject().take("artifact").toObject().take("url").toString());
                            artifact.setSha1(helloArrayValue.toObject().take("downloads").toObject().take("artifact").toObject().take("sha1").toString());
                            artifact.setSize(helloArrayValue.toObject().take("downloads").toObject().take("artifact").toObject().take("size").toString().toLong());
                            downloads.setArtifact(artifact);
                            versionJsonLibrariesItemData.setDownloads(downloads);

                            QStringList list = versionJsonLibrariesItemData.getName().split(":");
                            list[0].replace(".", "/");
                            QString param = "";
                            for (int j = 0; j < list.size(); j++) {
                                if (j) {
                                    param = param + "/" + list[j];
                                } else {
                                    param = QCoreApplication::applicationDirPath() + "/.minecraft/libraries/" + list[j];
                                }
                            }
                            param = param + "/";
                            for (int j = 1; j < list.size(); j++) {
                                if (j != 1) {
                                    param = param + "-" + list[j];
                                } else {
                                    param = param + list[j];
                                }
                            }
                            param = param + ".jar";
                            if (i) {
                                cpParam = cpParam + ";" + param;
                            } else {
                                cpParam = cpParam + param;
                            }
                            libraries.push_back(versionJsonLibrariesItemData);
                        }
                    }

                    versionJsonData->setLibraries(libraries);

                    return true;
                }
            }
        }
    }
    return false;

}

void MainWindow::on_toolBtnChooseJavaPath_clicked()
{
    //定义文件对话框类
    QFileDialog *fileDialog = new QFileDialog(this);
    //定义文件对话框标题
    fileDialog->setWindowTitle(QStringLiteral("选择Java.exe"));
    //设置默认文件路径
    fileDialog->setDirectory(".");
    //设置文件过滤器
    fileDialog->setNameFilter(tr("java.exe(java.exe)"));
    //设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFiles
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    //设置视图模式
    fileDialog->setViewMode(QFileDialog::Detail);
    //打印所有选择的文件的路径
    QStringList fileNames;
    if (fileDialog->exec()) {
        fileNames = fileDialog->selectedFiles();
        if (fileNames.first() != ""){
            ui->lineEditJavaPath->setText(fileNames.first());
        }
    }
}

QString findFile(const QString &strFilePath, const QString &strNameFilters) {
    if (strFilePath.isEmpty() || strNameFilters.isEmpty()) return "";

    QDir dir;
    QStringList filters;

    filters << strNameFilters;
    dir.setPath(strFilePath);
    dir.setNameFilters(filters);
    QDirIterator iter(dir,QDirIterator::Subdirectories);

    while (iter.hasNext()) {
        iter.next();
        QFileInfo info=iter.fileInfo();
        if (info.isFile()) {
            return info.absoluteFilePath().replace('/', '\\');
        }
    }
    return QString();
}

QString findNativesFolder(QString strPath) {
    if (strPath.isEmpty()) return "";

    QDir dir;
    dir.setPath(strPath);
    QDirIterator iter(dir,QDirIterator::Subdirectories);

    while (iter.hasNext()) {
        iter.next();
        QFileInfo info=iter.fileInfo();
        if (info.isDir() && info.path().split("\\").last().contains("natives")) {
            return info.path();
        }
    }
    return QString();
}
