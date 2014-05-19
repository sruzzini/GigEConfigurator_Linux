#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
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

    QList<unsigned int> GetConnectedCamerasSerialNumbers();

    unsigned int GetNumberOfConnectedCameras();

private slots:


    void on_setCurrentIPAddressSubnetButton_clicked();

    void on_copyCurrentIPToPersistentIPButton_clicked();

    void on_setPersistentIPAddressSubnetButton_clicked();

    int on_discoverMaxPacketSizeButton_clicked();

    void on_refreshButton_clicked();

    void on_connectedCamerasList_currentRowChanged(int currentRow);

private:
    Ui::MainWindow *ui;
    FlyCapture2::BusManager busManager;
    FlyCapture2::GigECamera gigeCamera;
    QList<unsigned int> connectedCamerasSerialNumbers;

    void ConnectToCamera(unsigned int serialNumber);

    void ClearAllTextFields();

    void InitializeGUITextFieldValuesFromCamera();

    bool IsValidIPAddress(int ip);

    int ReadFromCameraRegister(unsigned int registerIndex);

    void SelectCamera(int index);

    void SetCameraInformationFieldsFromCamera();

    void SetCurrentIPConfigFieldsFromCamera();

    void SetPersistentIPConfigFieldsFromCamera();

    void SetText(QPlainTextEdit * textEdit, QString value);

    void UpdateCameraList();

    int WriteIPToCamera(unsigned int registerIndex, QHostAddress ipAddress);

    int WriteToCameraRegister(unsigned int registerIndex, unsigned int valueToRegister);


};

#endif // MAINWINDOW_H
