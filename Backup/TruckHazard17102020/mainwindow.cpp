#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

// Global Path Constants
const QString configfile = "thazard.conf";

// Left Camera and Ultrasonic Distance
const QString ledLeftPath = "/externalDrive/Documents/Projects/ledLeft.txt";
const QString distLeftPath = "/externalDrive/Documents/Projects/distanceLeft.txt";

// Right Camera and Ultrasonic Distance
const QString ledRightPath = "/externalDrive/Documents/Projects/ledRight.txt";
const QString distRightPath = "/externalDrive/Documents/Projects/distanceRight.txt";

//const QString cameraitem;
//int count = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Declare some default variables
    //QTimer *timer = new QTimer(this);
    //QFile file(path);

    // Trigger populateIPList when checkboxes are changed
    //connect(ui->leftCamON, SIGNAL(stateChanged()), this, SLOT(populateIPList()));
    //connect(ui->rightCamON, SIGNAL(stateChanged()), this, SLOT(populateIPList()));

    // Start timer to show distance at an interval
    //QTimer *timer = new QTimer(this);

    //connect(timer, SIGNAL(timeout()), this, SLOT(displayDistance()));
    //timer->start(1000);

    //connect(timer, SIGNAL(timeout()), this, SLOT(displayDistance()));
    //connect(ui->listCamera, SIGNAL(on_listCamera_itemSelectionChanged()), this, SLOT(changeCamera()));
    //timer->start(10000);

    // Media Player Setup
    player = new QMediaPlayer(this,QMediaPlayer::LowLatency);
    player->setVideoOutput(ui->container);

    // Initialise Defaults
    // Load Configuration File
    loadConfig();
    changeCamera(3);

    // Tab Setup
    ui->tab->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}

// Video Toggle Based on FileWatcher
void MainWindow::displayVideoLeft(){

    QFile file(ledLeftPath);

    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){

        QTextStream stream(&file);

        QString ledCond = stream.readLine();

        if(ledCond == "1"){

            if(changeCamera(1) == 1){

                if(player->state() != 1){

                    player->play();
                }
            }
        }
        else{

            changeCamera(3);
            player->stop();

        }
    }
    file.close();
}

void MainWindow::displayVideoRight(){

    QFile file(ledRightPath);

    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){

        QTextStream stream(&file);

        QString ledCond = stream.readLine();

        if(ledCond == "1"){

            if(changeCamera(2) == 1){

                if(player->state() != 1){

                    player->play();
                }
            }
        }
        else{

            changeCamera(3);
            player->stop();
        }
    }
    file.close();
}


// Saves the configuration file on button click.
void MainWindow::on_saveButton_clicked(){

    saveConfig();
    populateIPList();
}

int MainWindow::changeCamera(int camSelect){

    switch (camSelect) {
        case 1:

            if(leftCamera == "" && ui->leftCamON->checkState() == 2){

                displaymsg("Invalid Camera","Camera activated but not given an address.");

                return -1;
            }else{
                ui->camName->setText("Left Camera");

                const QNetworkRequest requestrtsp(leftCamera);
                player->setMedia(NULL);
                player->setMedia(requestrtsp);

                return 1;
            }
        case 2:

            if (rightCamera == "" && ui->rightCamON->checkState() == 2){

                displaymsg("Invalid Camera","Camera activated but not given an address.");

                return -1;
            }else{

                 const QNetworkRequest requestrtsp(rightCamera);
                 player->setMedia(NULL);
                 player->setMedia(requestrtsp);

                 return 1;
            }
        case 3:

            ui->camName->setText("Camera not triggered");
            player->setMedia(NULL);

            return 1;
        default:

            return -1;
    }
}

// Populates the IP Address List
void MainWindow::on_applyButton_clicked(){

    saveConfig();
    populateIPList();
}

// Saves the configuration file in a "thazard.conf"
void MainWindow::saveConfig(){

    QFile file(configfile);
    QString leftState = "";
    QString rightState = "";

    if(ui->leftCamON->checkState() == 2){
        leftState = "2";
    }

    if(ui->rightCamON->checkState() == 2){
        rightState = "2";
    }
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){

        QTextStream stream(&file);

        stream << "1\\left\\" + ui->leftCamItem->text() << "\n";
        stream << "2\\right\\" + ui->rightCamItem->text() << "\n";
        stream << "3\\leftToggle\\" + leftState << "\n";
        stream << "4\\rightToggle\\" + rightState << "\n";

        file.close();
    }
}

// Loads the configuration file in "thazard.conf"
void MainWindow::loadConfig(){

    // Loading Configuration File
    QFile file(configfile);
    QString configitem;
    QRegExp delim("(\\\\)");

    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){

        QTextStream stream(&file);

        // First line will be the left camera and followed by the second camera
        while(!stream.atEnd()){
            configitem = stream.readLine();
            QStringList tokenConfig = configitem.split(delim);

            if(tokenConfig.size() != 3){

                displaymsg("Invalid Configuration File","Check configuration file for the correct syntax.");
                return;
            }
            if(tokenConfig[2] == ""){

                continue;
            }

            switch (tokenConfig[0].toInt()) {
                case 1:

                    ui->leftCamItem->setText(tokenConfig[2]);
                    break;
                case 2:

                    ui->rightCamItem->setText(tokenConfig[2]);
                    break;
                case 3:
                    if(tokenConfig[2] == "2"){
                        ui->leftCamON->setCheckState(Qt::Checked);
                    }
                    break;
                case 4:
                    if(tokenConfig[2] == "2"){
                        ui->rightCamON->setCheckState(Qt::Checked);
                    }
                    break;
                default:
                    break;
            }
        }
        file.close();
    }
    populateIPList();
}

// Populate the main IP Address List to the current configuration
void MainWindow::populateIPList(){

    if(ui->leftCamON->checkState() == 2){

        QFile ledLeft(ledLeftPath);

        // Set Camera text
        leftCamera = ui->leftCamItem->text();

        // Start watching the trigger file
        QFileSystemWatcher *watcherLeft = new QFileSystemWatcher(this);

        connect(watcherLeft, SIGNAL(fileChanged(const QString &)), this, SLOT(displayVideoLeft()));
        watcherLeft->addPath(ledLeft.fileName());
    }

    if(ui->rightCamON->checkState() == 1){

        QFile ledRight(ledRightPath);

        // Set Camera text
        rightCamera = ui->rightCamItem->text();

        // Start watching the trigger file
        QFileSystemWatcher *watcherRight = new QFileSystemWatcher(this);

        connect(watcherRight, SIGNAL(fileChanged(const QString &)), this, SLOT(displayVideoRight()));
        watcherRight->addPath(ledRight.fileName());
    }
}

void MainWindow::displayDistance()
{
    if(ui->camName->text() == "Left Camera"){
        QFile distanceLeft(distLeftPath);

        if(distanceLeft.open(QIODevice::ReadOnly | QIODevice::Text)){

            QTextStream stream(&distanceLeft);

            ui->distance->setText("Distance: " + stream.readLine());

            distanceLeft.close();
        }
    }else if(ui->camName->text() == "Right Camera"){

        QFile distanceRight(distRightPath);

        if(distanceRight.open(QIODevice::ReadOnly | QIODevice::Text)){

            QTextStream stream(&distanceRight);

            ui->distance->setText("Distance: " + distanceRight.readLine());

            distanceRight.close();
        }
    }else{

        ui->distance->setText("Camera not activated yet");
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
