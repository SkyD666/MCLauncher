#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include "versionjsondata.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool parseVersionJson(QString path, QString &cpParam, VersionJsonData *versionJsonData);

private slots:
    void on_btnStart_clicked();

    void on_toolBtnChooseJavaPath_clicked();

    void on_readoutput();

    void on_readerror();
private:
    Ui::MainWindow *ui;

    static const QString APP_NAME;
};
#endif // MAINWINDOW_H
