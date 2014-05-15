#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QIdentityProxyModel>
#include <QtNetwork/QHostAddress>
#include <QPlainTextEdit>
#include <FlyCapture2.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:


    void on_autoForceCurrentIPButton_clicked();

    void on_setCurrentIPAddressSubnetButton_clicked();

    void on_copyCurrentIPToPersistentIPButton_clicked();

    void on_setPersistentIPAddressSubnetButton_clicked();

    int on_discoverMaxPacketSizeButton_clicked();

    void on_testCameraConnectionButton_clicked();

private:
    Ui::MainWindow *ui;
    FlyCapture2::GigECamera gigeCamera;

    void ConnectToCamera();

    void InitializeGUITextFieldValuesFromCamera();

    bool IsValidIPAddress(QString ipMostSignificant, QString ipSecond, QString ipThird, QString ipLeastSignificant);

    int ReadFromCameraRegister(unsigned int registerIndex);

    void SetCameraInformationFieldsFromCamera();

    void SetCurrentIPConfigFieldsFromCamera();

    void SetPersistentIPConfigFieldsFromCamera();

    void SetText(QPlainTextEdit * textEdit, QString value);

    int WriteIPToCamera(unsigned int registerIndex, QString ipMostSignificant, QString ipSecond, QString ipThird, QString ipLeastSignificant);

    int WriteToCameraRegister(unsigned int registerIndex, unsigned int valueToRegister);


};

#endif // MAINWINDOW_H
