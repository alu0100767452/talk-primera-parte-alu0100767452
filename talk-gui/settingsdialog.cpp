#include <QtGlobal>
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>

#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    QSettings settings;
    ui->talkPathEdit->setText(settings.value("talkPath", "").toString());
    ui->serverModeCheckBox->setChecked(settings.value("serverMode", false).toBool());
    ui->serverAddressEdit ->setText(settings.value("serverAddress", "127.0.0.1").toString());
    ui->portBox->setValue(settings.value("port", 3000).toInt());

    QByteArray username = qgetenv("USER");
    if(!username.isNull())
        ui->usuarioLineEdit->setText( settings.value("username", username).toString() );
    else
        ui->usuarioLineEdit->setText( settings.value("username", "").toString() );


}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::done(int r)
{
    if(r == QDialog::Accepted){
        if(ui->talkPathEdit->text().isEmpty()){
            QMessageBox::critical(this,"Talk GUI",
                                  "Se necesita una ruta al comando talk.");
            return;
        }
        else if(!ui->serverModeCheckBox->isChecked() &&
                ui->serverAddressEdit->text().isEmpty()){
            QMessageBox::critical(this,"Talk GUI",
                                  "Se necesita la dirección del servidor.");
            return;
        }
        else{
            QSettings settings;
            settings.setValue("talkPath", ui->talkPathEdit->text());
            settings.setValue("serverMode", ui->serverModeCheckBox->isChecked());
            settings.setValue("serverAddress", ui->serverAddressEdit->text());
            settings.setValue("port", ui->portBox->value());
            if(ui->usuarioLineEdit->text().isEmpty())
                settings.remove("username");
            else
                settings.setValue("username", ui->usuarioLineEdit->text());
        }

        QDialog::done(r);
        return;
    }
    else QDialog::done(r);
}

void SettingsDialog::on_browseButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if(!fileName.isNull())
        ui->talkPathEdit->setText(fileName);
}

void SettingsDialog::serverModeCheckBox(bool checked)
{
    ui->serverAddressEdit->setDisabled(checked);
    ui->serverAddressLabel->setDisabled(checked);
}
