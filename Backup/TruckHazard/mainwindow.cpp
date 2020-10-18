#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

// Global Path Constants
const QString configfile = "thazard.conf";

// Left Camera and Ultrasonic Distance
const QString ledLeftPath = "ledLeft.txt";
const QString distLeftPath = "distanceLeft.txt";

// Right Camera and Ultrasonic Distance
const QString ledRightPath = "ledRight.txt";
const QString distRightPath = "distanceRight.txt";

//const QString cameraitem;
//int count = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){

    ui->setupUi(this);

    // Start timer to show distance at an interval
    //QTimer *timer = new QTimer(this);

    //connect(timer, SIGNAL(timeout()), this, SLOT(displayDistance()));
    //timer->start(1000);

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

MainWindow::~MainWindow(){
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

                    // Set Lock to Left Camera so that Right Camera trigger will not overwrite media player
                    authCamera = 1;
                }
            }
        }else if(authCamera == 1){

            // Only stop camera if the same lock is presented
            changeCamera(3);
            player->stop();

            // Remove lock on Camera
            authCamera = 0;

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

                    // Set Lock to Right Camera so that Left Camera trigger will not overwrite media player
                    authCamera = 2;
                }
            }
        }else if(authCamera == 2){

            // Only stop camera if the same lock is presented
            changeCamera(3);
            player->stop();

            // Remove lock on Camera
            authCamera = 0;
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

    if(authCamera != 0){

        return -1;
    }
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

            }
            break;
        case 2:

            if (rightCamera == "" && ui->rightCamON->checkState() == 2){

                displaymsg("Invalid Camera","Camera activated but not given an address.");

                return -1;
            }else{
                ui->camName->setText("Right Camera");
                const QNetworkRequest requestrtsp(rightCamera);
                player->setMedia(NULL);
                player->setMedia(requestrtsp);

            }
            break;
        case 3:

            ui->camName->setText("Camera not triggered");
            player->setMedia(NULL);
            break;
        default:

            return -1;
    }

    return 1;
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

    if(ui->rightCamON->checkState() == 2){

        QFile ledRight(ledRightPath);

        // Set Camera text
        rightCamera = ui->rightCamItem->text();

        // Start watching the trigger file
        QFileSystemWatcher *watcherRight = new QFileSystemWatcher(this);

        connect(watcherRight, SIGNAL(fileChanged(const QString &)), this, SLOT(displayVideoRight()));
        watcherRight->addPath(ledRight.fileName());
    }
}

void MainWindow::displayDistance(){

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
void MainWindow::displaymsg(QString text, QString error){
    QMessageBox msgBox;

    msgBox.setText(text);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDetailedText(error);
    msgBox.exec();
}

// Trigger populateIPList when checkboxes are changed
void MainWindow::on_leftCamON_stateChanged(int arg){

    if(arg == 2){
        populateIPList();
    }
}

void MainWindow::on_rightCamON_stateChanged(int arg){

    if(arg == 2){
        populateIPList();
    }
}

// Testing starting and stopping Camera over ssh (Depreciated)
//void MainWindow::constructScript(int cam, bool start){

//    const QString prefix = "exp raspberry ssh pi@";
//    const QString startCam = "~/.rtsp-stream.sh";
//    const QString stopCam = "killall raspivid";
//    QString command;
//    QProcess *process1 = new QProcess(this);

//    if(cam == 1 && start == 1){

//        command = ui->leftCamItem->text();
//        command = prefix + command.split(":")[1].replace("//","") + startCam;
//        process1->start(command);

//    }else if(cam == 1 && start == 0){

//        command = ui->leftCamItem->text();
//        command = prefix + command.split(":")[1].replace("//","") + stopCam;
//    }
//}
