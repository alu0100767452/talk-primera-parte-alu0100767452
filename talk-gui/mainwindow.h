#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QProcess>

namespace Ui {
class MainWindow;
}

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_exitButton_clicked();

    void on_connectButton_clicked();

    void on_aboutButton_clicked();

    void on_inputTextEdit_returnPressed();

    void processFinished(int exitCode, QProcess::ExitStatus exitStatus);

    void processReadyReadStandardOutput();

    void processError(QProcess::ProcessError error);

    void on_setupButton_clicked();

private:
    Ui::MainWindow *ui;
    bool isConnected_;
    QProcess process_;
};

#endif // MAINWINDOW_H
