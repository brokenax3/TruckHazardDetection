#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

QString path = "/home/pi/led.txt";
QString configfile = "thazard.conf";
QString cameraitem;
int trigcount = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Declare some default variables
    QTimer *timer = new QTimer(this);

    QFile file(path);
    //QFileSystemWatcher *watcher = new QFileSystemWatcher(this);
    //watcher->addPath(file.fileName());
    //connect(watcher, SIGNAL(fileChanged(const QString &)), this, SLOT(displayVideo()));


    connect(timer, SIGNAL(timeout()), this, SLOT(displayVideo()));
    //connect(ui->listCamera, SIGNAL(on_listCamera_itemSelectionChanged()), this, SLOT(changeCamera()));
    timer->start(1000);

    // Media Player Setup
    player = new QMediaPlayer;
    player->setVideoOutput(ui->container);
    // Load Configuration File
    loadConfig();

    // Tab Setup
    ui->tab->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}

// Creates a "New Item" in the Setting List and makes each item editable
void MainWindow::on_addButton_clicked()
{
    QListWidgetItem * item = new QListWidgetItem("New Item");

    item->setFlags(item->flags() | Qt::ItemIsEditable);
    ui->settingWidget->addItem(item);
}

// Delete selected items
void MainWindow::on_deleteButton_clicked()
{
    QList<QListWidgetItem*> items = ui->settingWidget->selectedItems();

    foreach(QListWidgetItem * item, items)
    {
        delete ui->settingWidget->takeItem(ui->settingWidget->row(item));
    }
}

// Timer video Toggle
void MainWindow::displayVideo()
{
    if(cameraitem == ""){
        return;
    }

    if(trigcount >= 1){
        QFile file(path);

        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream stream(&file);
            QString ledCond = stream.readLine();
            qDebug() << ledCond;

            if(ledCond == "1")
            {
                if(player->state() != 1)
                {
                    changeCamera();
                    player->play();
                }
            }
            else if(ledCond == "0")
            {
                player->stop();
            }
            else
            {
                return;
            }
        }
        trigcount = 0;
    }else{
        trigcount++;
    }
}

// Saves the configuration file on button click.
void MainWindow::on_saveButton_clicked()
{
    saveConfig();
}

// Changes camera streams on selection
void MainWindow::on_listCamera_itemSelectionChanged()
{
    QListWidgetItem * item = ui->listCamera->currentItem();
    cameraitem = item->text();

}

void MainWindow::changeCamera()
{
    if(cameraitem == "")
    {
        displaymsg("Invalid Camera","Camera not selected or not added.");
        return;
    }
    // Split String with regex. Delimiter is "\"
    QRegExp delim("(\\\\)");
    QStringList token = cameraitem.split(delim);

    if(token.size() != 2)
    {
        displaymsg("Wrong Identifier","The camera identifier might not be delimited properly. Check Again.");
        ui->camName->setText("Camera : Invalid Name ");
    }
    else
    {
        const QNetworkRequest requestrtsp(QUrl(token.at(1)));

        ui->camName->setText("Camera : " + token.at(0));
        player->setMedia(requestrtsp);
    }
}
// Populates the IP Address List
void MainWindow::on_applyButton_clicked()
{
    populateIPList();
    saveConfig();
}

// Saves the configuration file in a "thazard.conf"
void MainWindow::saveConfig()
{
    QFile file(configfile);

    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&file);

        for(int i = 0; i < ui->settingWidget->count(); i++)
        {
            QListWidgetItem * item = ui->settingWidget->item(i);

            stream << item->text() << "\n";
        }
        file.close();
    }
}

// Loads the configuration file in "thazard.conf"
void MainWindow::loadConfig()
{
    // Loading Configuration File
    QFile file(configfile);

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);

        while(!stream.atEnd())
        {
            QListWidgetItem * item = new QListWidgetItem(stream.readLine());

            item->setFlags(item->flags() | Qt::ItemIsEditable);
            ui->settingWidget->addItem(item);
        }
        file.close();
    }

    populateIPList();
}

// Populate the main IP Address List to the current configuration
void MainWindow::populateIPList()
{
    ui->listCamera->clear();

    for(int i = 0; i < ui->settingWidget->count(); i++)
    {
        QListWidgetItem * item = ui->settingWidget->item(i);

        ui->listCamera->addItem(item->text());
    }
    saveConfig();
}

void MainWindow::displayDistance()
{
    QFile file("/home/pi/Desktop/distance.txt");

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);

        while(!stream.atEnd())
        {
            ui->distance->setText(stream.readAll());
        }
        file.close();
    }
}
// Yet to implement... on some functions
void MainWindow::displaymsg(QString text, QString error)
{
    QMessageBox msgBox;

    msgBox.setText(text);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDetailedText(error);
    msgBox.exec();
}
