#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdlib.h>

const unsigned int VERSION_ADDRESS = 0;
const unsigned int DEVICE_MODE_ADDRESS = 4;
const unsigned int DEVICE_MAC_ADDRESS = 8;
const unsigned int SUPPORTED_IP_CONFIG_ADDRESS = 16;
const unsigned int CUURENT_IP_CONFIG_ADDRESS = 20;
const unsigned int CURRENT_IP_ADDRESS = 36;
const unsigned int CURRENT_GATEWAY_MASK_ADDRESS = 68;
const unsigned int CURRENT_SUBNET_MASK_ADDRESS = 52;
const unsigned int MANUFACTURER_ADDRESS = 72;
const unsigned int MODEL_ADDRESS = 104;
const unsigned int DEVICE_VERSION_ADDRESS = 136;
const unsigned int MANUFACTURER_INFO_ADDRESS = 168;
const unsigned int SERIAL_NUMBER_ADDRESS = 216;
const unsigned int FIRST_URL_ADDRESS = 512;
const unsigned int SECOND_URL_ADDRESS = 1024;
const unsigned int NUM_NETWORK_INTERFACES_ADDRESS = 1536;
const unsigned int PERSISTENT_IP_ADDRESS = 1612;
const unsigned int PERSISTENT_GATEWAY_MASK_ADDRESS = 1644;
const unsigned int PERSISTENT_SUBNET_MASK_ADDRESS = 1628;
const unsigned int LINK_SPEED_ADDRESS = 1648;
const unsigned int NUM_MESSAGE_CHANNELS_ADDRESS = 2304;
const unsigned int NUM_STREAM_CHANNELS_ADDRESS = 2308;
const unsigned int STREAM_CHANNELS_CAP_ADDRESS = 2348;
const unsigned int GVCP_CAP_ADDRESS = 2356;
const unsigned int HEARTBEAT_TIMEOUT_ADDRESS = 2360;
const unsigned int TIMESTAMP_TICKFREQ_H_ADDRESS = 2364;
const unsigned int TIMESTAMP_TICKFREQ_L_ADDRESS = 2368;
const unsigned int TIMESTAMP_CONTROL_ADDRESS = 2372;
const unsigned int TIMESTAMP_VALUE_H_ADDRESS = 2376;
const unsigned int TIMESTAMP_VALUE_L_ADDRESS = 2380;
const unsigned int GVCP_CONFIG_ADDRESS = 2388;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    UpdateCameraList();
}

MainWindow::~MainWindow()
{
    delete ui;
}



//Sets Current IP Configuration to user entered inputs
void MainWindow::on_setCurrentIPAddressSubnetButton_clicked()
{
    QHostAddress ipAddress = QHostAddress();
    QHostAddress subnetAddress = QHostAddress();
    QString ip = QString("%1.%2.%3.%4").arg(ui->currentIP3Text->toPlainText())
                                        .arg(ui->currentIP2Text->toPlainText())
                                        .arg(ui->currentIP1Text->toPlainText())
                                        .arg(ui->currentIP0Text->toPlainText());
    QString subnet = QString("%1.%2.%3.%4").arg(ui->currentSubnet3Text->toPlainText())
                                            .arg(ui->currentSubnet2Text->toPlainText())
                                            .arg(ui->currentSubnet1Text->toPlainText())
                                            .arg(ui->currentSubnet0Text->toPlainText());
    if (ipAddress.setAddress(ip)) //check IP Address
    {
        if (subnetAddress.setAddress(subnet)) //check subnet mask
        {
            if (gigeCamera.IsConnected())
            {
                if (WriteIPToCamera(CURRENT_IP_ADDRESS, ipAddress) == 0) //write the ip address
                {
                    WriteIPToCamera(CURRENT_SUBNET_MASK_ADDRESS, subnetAddress); //write the subnet
                }
            }
        }
    }
}

//Copies Current IP Configuration to Persistent IP Configuration (GUI and in Camera)
void MainWindow::on_copyCurrentIPToPersistentIPButton_clicked()
{
    QHostAddress ipAddress = QHostAddress();
    QHostAddress subnetAddress = QHostAddress();
    QHostAddress gatewayAddress = QHostAddress();
    QString ip = QString("%1.%2.%3.%4").arg(ui->currentIP3Text->toPlainText())
                                        .arg(ui->currentIP2Text->toPlainText())
                                        .arg(ui->currentIP1Text->toPlainText())
                                        .arg(ui->currentIP0Text->toPlainText());
    QString subnet = QString("%1.%2.%3.%4").arg(ui->currentSubnet3Text->toPlainText())
                                            .arg(ui->currentSubnet2Text->toPlainText())
                                            .arg(ui->currentSubnet1Text->toPlainText())
                                            .arg(ui->currentSubnet0Text->toPlainText());
    QString gateway = QString("%1.%2.%3.%4").arg(ui->currentGateway3Text->toPlainText())
                                             .arg(ui->currentGateway2Text->toPlainText())
                                             .arg(ui->currentGateway1Text->toPlainText())
                                             .arg(ui->currentGateway0Text->toPlainText());
    if (ipAddress.setAddress(ip)) //check IP Address
    {
        if (subnetAddress.setAddress(subnet)) //check subnet mask
        {
            if (gatewayAddress.setAddress(gateway)) //check default gateway
            {
                if (gigeCamera.IsConnected())
                {
                    if (WriteIPToCamera(PERSISTENT_IP_ADDRESS, ipAddress) == 0) //write the ip address
                    {
                        SetText(ui->persistentIP3Text, ui->currentIP3Text->toPlainText());
                        SetText(ui->persistentIP2Text, ui->currentIP2Text->toPlainText());
                        SetText(ui->persistentIP1Text, ui->currentIP1Text->toPlainText());
                        SetText(ui->persistentIP0Text, ui->currentIP0Text->toPlainText());
                        if (WriteIPToCamera(PERSISTENT_SUBNET_MASK_ADDRESS, subnetAddress) == 0) //write the subnet
                        {
                            SetText(ui->persistentSubnet3Text, ui->currentSubnet3Text->toPlainText());
                            SetText(ui->persistentSubnet2Text, ui->currentSubnet2Text->toPlainText());
                            SetText(ui->persistentSubnet1Text, ui->currentSubnet1Text->toPlainText());
                            SetText(ui->persistentSubnet0Text, ui->currentSubnet0Text->toPlainText());
                            if (WriteIPToCamera(PERSISTENT_GATEWAY_MASK_ADDRESS, gatewayAddress) == 0) //write the gateway
                            {
                                SetText(ui->persistentGateway3Text, ui->currentGateway3Text->toPlainText());
                                SetText(ui->persistentGateway2Text, ui->currentGateway2Text->toPlainText());
                                SetText(ui->persistentGateway1Text, ui->currentGateway1Text->toPlainText());
                                SetText(ui->persistentGateway0Text, ui->currentGateway0Text->toPlainText());
                            }
                        }
                    }
                }
            }
        }
    }
}

//Sets Persistent IP Configuration to user entered inputs
void MainWindow::on_setPersistentIPAddressSubnetButton_clicked()
{
    QHostAddress ipAddress = QHostAddress();
    QHostAddress subnetAddress = QHostAddress();
    QString ip = QString("%1.%2.%3.%4").arg(ui->persistentIP3Text->toPlainText())
                                        .arg(ui->persistentIP2Text->toPlainText())
                                        .arg(ui->persistentIP1Text->toPlainText())
                                        .arg(ui->persistentIP0Text->toPlainText());
    QString subnet = QString("%1.%2.%3.%4").arg(ui->persistentSubnet3Text->toPlainText())
                                            .arg(ui->persistentSubnet2Text->toPlainText())
                                            .arg(ui->persistentSubnet1Text->toPlainText())
                                            .arg(ui->persistentSubnet0Text->toPlainText());
    if (ipAddress.setAddress(ip)) //check IP Address
    {
        if (subnetAddress.setAddress(subnet)) //check subnet mask
        {
            if (gigeCamera.IsConnected())
            {
                if (WriteIPToCamera(PERSISTENT_IP_ADDRESS, ipAddress) == 0) //write the ip address
                {
                    WriteIPToCamera(PERSISTENT_SUBNET_MASK_ADDRESS, subnetAddress); //write the subnet
                }
            }
        }
    }
}

//Returns -1 if couldn't find max packet size, else returns 0 or positive integer
int MainWindow::on_discoverMaxPacketSizeButton_clicked()
{
    int returnPacket = -1;
    unsigned int packetSize;
    if (gigeCamera.IsConnected())
    {
        FlyCapture2::Error error = gigeCamera.DiscoverGigEPacketSize(&packetSize);
        if (error.GetType() != FlyCapture2::PGRERROR_OK)
        {
            char error[512];
            sprintf( error, "There was an error discovering the max packet size.");
        }
        else
        {
            returnPacket = packetSize;
        }
    }
    return returnPacket;
}

//Handles the Refresh button being clicked
void MainWindow::on_refreshButton_clicked()
{
    UpdateCameraList();
}

//Handles when different camera is selected
void MainWindow::on_connectedCamerasList_currentRowChanged(int currentRow)
{
    if (currentRow >= 0)
    {
        SelectCamera(currentRow);
    }
    else
    {
        ClearAllTextFields();
    }
}




//Tries 20 times to connect to the camera
void MainWindow::ConnectToCamera(unsigned int serialNumber)
{
    int connectionAttempts = 0;
    FlyCapture2::PGRGuid camGUID;
    FlyCapture2::Error error = busManager.GetCameraFromSerialNumber(serialNumber, &camGUID); //get GUID of camera with specified serial number
    if (error.GetType() == FlyCapture2::PGRERROR_OK) //successful GUID retrieval
    {
        do //iterate loop until camera is connected or attempted 20 times
        {
            gigeCamera.Connect(&camGUID);
            connectionAttempts++;
        } while(!gigeCamera.IsConnected() && connectionAttempts < 20);

    }
}

//Clears all text fields in the gui
void MainWindow::ClearAllTextFields()
{
    SetText(ui->serialNumberText, QString(""));
    SetText(ui->modelText, QString(""));
    SetText(ui->vendorText, QString(""));
    SetText(ui->sensorText, QString(""));
    SetText(ui->resolutionText, QString(""));
    SetText(ui->firmwareText, QString(""));
    SetText(ui->gigEVersionText, QString(""));
    SetText(ui->userDefinedNameText, QString(""));
    SetText(ui->xmlURL1Text, QString(""));
    SetText(ui->xmlURL2Text, QString(""));
    SetText(ui->macAddressText, QString(""));
    SetText(ui->currentIP0Text, QString(""));
    SetText(ui->currentIP1Text, QString(""));
    SetText(ui->currentIP2Text, QString(""));
    SetText(ui->currentIP3Text, QString(""));
    SetText(ui->currentGateway0Text, QString(""));
    SetText(ui->currentGateway1Text, QString(""));
    SetText(ui->currentGateway2Text, QString(""));
    SetText(ui->currentGateway3Text, QString(""));
    SetText(ui->currentSubnet0Text, QString(""));
    SetText(ui->currentSubnet1Text, QString(""));
    SetText(ui->currentSubnet2Text, QString(""));
    SetText(ui->currentSubnet3Text, QString(""));
    SetText(ui->persistentIP0Text, QString(""));
    SetText(ui->persistentIP1Text, QString(""));
    SetText(ui->persistentIP2Text, QString(""));
    SetText(ui->persistentIP3Text, QString(""));
    SetText(ui->persistentGateway0Text, QString(""));
    SetText(ui->persistentGateway1Text, QString(""));
    SetText(ui->persistentGateway2Text, QString(""));
    SetText(ui->persistentGateway3Text, QString(""));
    SetText(ui->persistentSubnet0Text, QString(""));
    SetText(ui->persistentSubnet1Text, QString(""));
    SetText(ui->persistentSubnet2Text, QString(""));
    SetText(ui->persistentSubnet3Text, QString(""));
}

//Returns the serial numbers of all connected cameras
QList<unsigned int> MainWindow::GetConnectedCamerasSerialNumbers()
{
    unsigned int currSerialNumber, numCamerasConnected, i;
    FlyCapture2::Error error;
    QList<unsigned int> serialNumbers = QList<unsigned int>(); //initiallize empty list of serial numbers
    numCamerasConnected = GetNumberOfConnectedCameras(); //get number of connected cams
    for (i = 0; i < numCamerasConnected; i++) //iterate throught each connected camera
    {
        error = busManager.GetCameraSerialNumberFromIndex(i, &currSerialNumber); //get serial number of cam
        if (error.GetType() != FlyCapture2::PGRERROR_OK) //unsuccessful
        {
            break;
        }
        serialNumbers.append(currSerialNumber); //add serial number found to list
    }
    return serialNumbers;
}

//Returns the number of connected cameras
unsigned int MainWindow::GetNumberOfConnectedCameras()
{
    unsigned int numCamerasConnected;
    FlyCapture2::Error error = busManager.GetNumOfCameras(&numCamerasConnected);
    if (error.GetType() != FlyCapture2::PGRERROR_OK)
    {
        numCamerasConnected = 0;
    }
    return numCamerasConnected;
}

//Initializes all Text Field Values from what is in the Camera Registers
void MainWindow::InitializeGUITextFieldValuesFromCamera()
{
    SetCameraInformationFieldsFromCamera();
    SetCurrentIPConfigFieldsFromCamera();
    SetPersistentIPConfigFieldsFromCamera();
}

//Returns -1 on unsuccessful read, 0 or positive number on successful read
int MainWindow::ReadFromCameraRegister(unsigned int registerIndex)
{
    int readValue = -1;     // -1 = unsuccessful read
                            //  0 or positive # = successful read
    unsigned int unsignedRead;
    if (gigeCamera.IsConnected()) //make sure the camera is connect before writing
    {
        FlyCapture2::Error error = gigeCamera.ReadGVCPRegister(registerIndex, &unsignedRead);
        //Error error = gigeCamera.ReadRegister(registerIndex, &readValue);
        //   We may need to use ReadRegister() instead of ReadGVCPRegister().  Still looking for documentation
        //   to see what the difference is.
        if ( error.GetType() != FlyCapture2::PGRERROR_OK ) //If read was unsuccessful
        {
            qDebug() << QString("There was an error reading GVCP register %1.").arg(registerIndex);
            readValue = -1;
        }
        else
        {
            readValue = unsignedRead;
        }
    }
    return readValue;
}

//Connects to Camera selected in the "Connected Cameras" lists and updates all text fields accordingly
void MainWindow::SelectCamera(int index)
{
    ConnectToCamera(connectedCamerasSerialNumbers.at(index));
    InitializeGUITextFieldValuesFromCamera();
}

//Sets all uneditable text fields in "Camera Information"
void MainWindow::SetCameraInformationFieldsFromCamera()
{
    if (gigeCamera.IsConnected())
    {
        FlyCapture2::CameraInfo camInfo;
        FlyCapture2::Error error = gigeCamera.GetCameraInfo(&camInfo);
        if (error.GetType() == FlyCapture2::PGRERROR_OK) //successful at getting camera info
        {
            //set Serial Number text field
            SetText(ui->serialNumberText, QString("%1").arg(camInfo.serialNumber));

            //set model text field
            SetText(ui->modelText, QString(camInfo.modelName));

            //set vendor text field
            SetText(ui->vendorText, QString(camInfo.vendorName));

            //set sensor text field
            SetText(ui->sensorText, QString(camInfo.sensorInfo));

            //set sensor resolution text field
            SetText(ui->resolutionText, QString(camInfo.sensorResolution));

            //set firmware text field
            SetText(ui->firmwareText, QString("%1; %2").arg(camInfo.firmwareVersion).arg(camInfo.firmwareBuildTime));

            //set GigE Version text field
            SetText(ui->gigEVersionText, QString("%1.%2").arg(camInfo.gigEMajorVersion).arg(camInfo.gigEMinorVersion));

            //set User Defined Name text field
            SetText(ui->userDefinedNameText, QString(camInfo.userDefinedName));

            //set XML URL1 text field
            SetText(ui->xmlURL1Text, QString(camInfo.xmlURL1));

            //set XML URL2 text field
            SetText(ui->xmlURL2Text, QString(camInfo.xmlURL2));
        }
    }
}

//Sets all text fields in "Current IP Configuration"
void MainWindow::SetCurrentIPConfigFieldsFromCamera()
{
    int readVal;
    if (gigeCamera.IsConnected())
    {
        FlyCapture2::CameraInfo camInfo;
        FlyCapture2::Error error = gigeCamera.GetCameraInfo(&camInfo);
        QHostAddress ipAddress;
        QStringList ipSegments;
        if (error.GetType() == FlyCapture2::PGRERROR_OK) //successful at getting camera info
        {
            //set Current IP Address
            readVal = ReadFromCameraRegister(CURRENT_IP_ADDRESS);
            ipAddress = QHostAddress((quint32) readVal);
            ipSegments = ipAddress.toString().split('.');
            SetText(ui->currentIP3Text, ipSegments.at(0));
            SetText(ui->currentIP2Text, ipSegments.at(1));
            SetText(ui->currentIP1Text, ipSegments.at(2));
            SetText(ui->currentIP0Text, ipSegments.at(3));

            //set Current Subnet
            readVal = ReadFromCameraRegister(CURRENT_SUBNET_MASK_ADDRESS);
            ipAddress = QHostAddress((quint32) readVal);
            ipSegments = ipAddress.toString().split('.');
            SetText(ui->currentSubnet3Text, ipSegments.at(0));
            SetText(ui->currentSubnet2Text, ipSegments.at(1));
            SetText(ui->currentSubnet1Text, ipSegments.at(2));
            SetText(ui->currentSubnet0Text, ipSegments.at(3));

            //set Current GateWay
            readVal = ReadFromCameraRegister(CURRENT_GATEWAY_MASK_ADDRESS);
            ipAddress = QHostAddress((quint32) readVal);
            ipSegments = ipAddress.toString().split('.');
            SetText(ui->currentGateway3Text, ipSegments.at(0));
            SetText(ui->currentGateway2Text, ipSegments.at(1));
            SetText(ui->currentGateway1Text, ipSegments.at(2));
            SetText(ui->currentGateway0Text, ipSegments.at(3));
        }
    }
}

//Sets all text fields in "Persistent IP Configuration"
void MainWindow::SetPersistentIPConfigFieldsFromCamera()
{
    int readVal;
    if (gigeCamera.IsConnected())
    {
        FlyCapture2::CameraInfo camInfo;
        FlyCapture2::Error error = gigeCamera.GetCameraInfo(&camInfo);
        QHostAddress ipAddress;
        QStringList ipSegments;
        if (error.GetType() == FlyCapture2::PGRERROR_OK) //successful at getting camera info
        {
            //set Current IP Address
            readVal = ReadFromCameraRegister(PERSISTENT_IP_ADDRESS);
            ipAddress = QHostAddress((quint32) readVal);
            ipSegments = ipAddress.toString().split('.');
            SetText(ui->persistentIP3Text, ipSegments.at(0));
            SetText(ui->persistentIP2Text, ipSegments.at(1));
            SetText(ui->persistentIP1Text, ipSegments.at(2));
            SetText(ui->persistentIP0Text, ipSegments.at(3));

            //set Current Subnet
            readVal = ReadFromCameraRegister(PERSISTENT_SUBNET_MASK_ADDRESS);
            ipAddress = QHostAddress((quint32) readVal);
            ipSegments = ipAddress.toString().split('.');
            SetText(ui->persistentSubnet3Text, ipSegments.at(0));
            SetText(ui->persistentSubnet2Text, ipSegments.at(1));
            SetText(ui->persistentSubnet1Text, ipSegments.at(2));
            SetText(ui->persistentSubnet0Text, ipSegments.at(3));

            //set Current GateWay
            readVal = ReadFromCameraRegister(PERSISTENT_GATEWAY_MASK_ADDRESS);
            ipAddress = QHostAddress((quint32) readVal);
            ipSegments = ipAddress.toString().split('.');
            SetText(ui->persistentGateway3Text, ipSegments.at(0));
            SetText(ui->persistentGateway2Text, ipSegments.at(1));
            SetText(ui->persistentGateway1Text, ipSegments.at(2));
            SetText(ui->persistentGateway0Text, ipSegments.at(3));
        }
    }
}

//Sets the specified QPlainTextEdit to the specified QString
void MainWindow::SetText(QPlainTextEdit * textEdit, QString value)
{
    textEdit->clear();
    textEdit->appendPlainText(value);
}

//Checks to see what cameras are connected to the computer and updates the GUI accordingly
void MainWindow::UpdateCameraList()
{
    int i, existingItems;
    connectedCamerasSerialNumbers = GetConnectedCamerasSerialNumbers(); //get serial numbers of all connected cameras
    if (connectedCamerasSerialNumbers.length() > 0) //if there are connected cameras
    {
        existingItems = ui->connectedCamerasList->count();
        for (i = 0; i < existingItems; i++) //remove all cameras from the list (if any exist)
        {
            ui->connectedCamerasList->takeItem(ui->connectedCamerasList->count() - 1);
        }
        for (i = 0; i < connectedCamerasSerialNumbers.length(); i++) //add all cameras to the list
        {
            ui->connectedCamerasList->addItem(QString("%1").arg(connectedCamerasSerialNumbers.at(i)));
        }
        ui->connectedCamerasList->item(0)->setSelected(true);
        on_connectedCamerasList_currentRowChanged(0);
    }
    else
    {
        gigeCamera.Disconnect();
        existingItems = ui->connectedCamerasList->count();
        for (i = 0; i < existingItems; i++) //remove all cameras from the list (if any exist)
        {
            ui->connectedCamerasList->removeItemWidget(ui->connectedCamerasList->item(ui->connectedCamerasList->count() - 1));
        }
        ClearAllTextFields();
    }
}

//Returns "0" if successful write, "-1" if unsuccessful Write
int MainWindow::WriteIPToCamera(unsigned int registerIndex, QHostAddress ipAddress)
{
    int writeSuccess = -1;
    unsigned int ip = ipAddress.toIPv4Address();
    if (WriteToCameraRegister(registerIndex, ip) == 0)
    {
        writeSuccess = 0;
    }
    return writeSuccess;
}

//Returns "0" if successful write, "-1" if unsuccessful Write, "-2" if no camera connected (and no write)
int MainWindow::WriteToCameraRegister(unsigned int registerIndex, unsigned int valueToRegister)
{
    int writeStatus = -2;   // -2 = camera not connected
                            // -1 = camera connected, but unsuccessful write
                            //  0 = successful write
    if (gigeCamera.IsConnected()) //make sure the camera is connect before writing
    {
        FlyCapture2::Error error = gigeCamera.WriteGVCPRegister(registerIndex, valueToRegister, false); //write to camera
        //Error error = gigeCamera.WriteRegister(registerIndex, valueToRegister, false);
        //   We may need to use WriteRegister() instead of WriteGVCPRegister().  Still looking for documentation
        //   to see what the difference is.
        if ( error.GetType() != FlyCapture2::PGRERROR_OK ) //If the write was unsuccessful
        {
            qDebug() << QString("There was an error writing GVCP register %1 with the value %2.").arg(registerIndex).arg(valueToRegister);
            writeStatus = -1; //unsuccessful Write
        }
        else
        {
            writeStatus = 0; //successful Write
        }
    }
    return writeStatus;
}


























