#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QLabel>
#include <QNetworkRequest>
#include <QListWidget>
#include <QFile>
#include <QMessageBox>
//#include <QSettings>
#include <QTimer>
#include <QFileSystemWatcher>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_addButton_clicked();
    void on_deleteButton_clicked();
    void on_toggleButton_clicked();
    void on_saveButton_clicked();
    void on_listCamera_itemSelectionChanged();
    void on_applyButton_clicked();
    void loadConfig();
    void saveConfig();
    void populateIPList();
    void displaymsg(QString text, QString error);
    void displayDistance();

private:

    Ui::MainWindow *ui;
    QPushButton *m_button;
    QMediaPlayer *player;
    QNetworkRequest streamurl;
    QFileSystemWatcher ledsig;
};

#endif // MAINWINDOW_H
