#include <QMessageBox>
#include <QSettings>

#include "aboutdialog.h"
#include "settingsdialog.h"


#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow),
    isConnected_(false),
    process_(this)
{
    ui->setupUi(this);

    connect(&process_, SIGNAL(finished(int,QProcess::ExitStatus)),
            SLOT(processFinished(int,QProcess::ExitStatus)));
    connect(&process_, SIGNAL(readyReadStandardOutput()),
            SLOT(processReadyReadStandardOutput()));
    connect(&process_, SIGNAL(error(QProcess::ProcessError)),
            SLOT(processError(QProcess::ProcessError)));

}

MainWindow::~MainWindow()
{
    process_.disconnect();
    delete ui;
}

void MainWindow::on_exitButton_clicked()
{
    qApp->quit();
}

void MainWindow::on_connectButton_clicked()
{
    if(isConnected_){
        process_.terminate();
    }
    else{
        QSettings settings;
        QString talkPath = settings.value("talkPath").toString();
        bool serverMode = settings.value("serverMode", false).toBool();
        QString serverAddress = settings.value("serverAddress", "127.0.0.1").toString();
        QString port = settings.value("port", 3000).toString();
        QString username = settings.value("username", "").toString();

        QStringList arguments;
        arguments.append("-p" + port);
        if(serverMode)
            arguments.append("-s");
        else
            arguments.append("-c" + serverAddress);

        if(!username.isEmpty())
            arguments.append("-u" + username);


        process_.start(talkPath, arguments);
        //process_.start("/home/aledelgado/Qt_Projects/talk-primera-parte-alu0100767452/TALK/Talk1/talk -p 8000 -c 127.0.0.2 -u ale");
        ui->connectButton->setText("Desconectar");
        isConnected_ = true;
    }
}

void MainWindow::on_aboutButton_clicked()
{
    AboutDialog dialog;
    dialog.exec();
}

void MainWindow::on_inputTextEdit_returnPressed()
{
    QString line = ui->inputTextEdit->text();
    ui->outputTextEdit->appendPlainText(line);
    line += '\n';
    process_.write(line.toLocal8Bit());
    ui->inputTextEdit->clear();
}

void MainWindow::processFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    ui->connectButton->setText("Conectar");
    isConnected_ = false;
}

void MainWindow::processReadyReadStandardOutput()
{
    while(process_.canReadLine()){
        QString line = process_.readLine();
        line.truncate(line.length() - 1);
        ui->outputTextEdit->appendPlainText(line);
    }
}

void MainWindow::processError(QProcess::ProcessError error)
{
    QMessageBox::critical(this, "Talk GUI",
                          "Error con talk.\n" + process_.errorString());
}

void MainWindow::on_setupButton_clicked()
{
    SettingsDialog dialog;
    dialog.exec();
}
