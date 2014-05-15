#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdlib.h>

const unsigned int VERSION_ADDRESS = 0;
const unsigned int DEVICE_MODE_ADDRESS = 4;
const unsigned int DEVICE_MAC_ADDRESS = 8;
const unsigned int SUPPORTED_IP_CONFIG_ADDRESS = 16;
const unsigned int CUURENT_IP_CONFIG_ADDRESS = 20;
const unsigned int CURRENT_IP_ADDRESS = 36;
const unsigned int CURRENT_GATEWAY_MASK = 68;
const unsigned int CURRENT_SUBNET_MASK = 52;
const unsigned int MANUFACTURER_ADDRESS = 72;
const unsigned int MODEL_ADDRESS = 104;
const unsigned int DEVICE_VERSION_ADDRESS = 136;
const unsigned int MANUFACTURER_INFO_ADDRESS = 168;
const unsigned int SERIAL_NUMBER_ADDRESS = 216;
const unsigned int FIRST_URL_ADDRESS = 512;
const unsigned int SECOND_URL_ADDRESS = 1024;
const unsigned int NUM_NETWORK_INTERFACES_ADDRESS = 1536;
const unsigned int PERSISTENT_IP_ADDRESS = 1612;
const unsigned int PERSISTENT_GATEWAY_MASK = 1644;
const unsigned int PERSISTENT_SUBNET_MASK = 1628;
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
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_autoForceCurrentIPButton_clicked()
{
    /* The Gig# Configurator can automatically force an IP address refresh.  This
     * detects the IP address fo the Network Interface card and automatically sets
     * the camera's IP address relative to the card.
     *
     * The FlyCap2 demo program can be used to test your camera settings and verify
     * operation.  From the camera selection window, you can also automatically
     * force an IP address refresh.
     */
}

//Sets Current IP Configuration to user entered inputs
void MainWindow::on_setCurrentIPAddressSubnetButton_clicked()
{
    QString ip0 = ui->currentIP0Text->toPlainText(); //least significant
    QString ip1 = ui->currentIP1Text->toPlainText();
    QString ip2 = ui->currentIP2Text->toPlainText();
    QString ip3 = ui->currentIP3Text->toPlainText(); //most significant
    QString subnet0 = ui->currentSubnet0Text->toPlainText(); //least significant
    QString subnet1 = ui->currentSubnet1Text->toPlainText();
    QString subnet2 = ui->currentSubnet2Text->toPlainText();
    QString subnet3 = ui->currentSubnet3Text->toPlainText(); //most significant
    if (IsValidIPAddress(ip3, ip2, ip1, ip0)) //check IP Address
    {
        if (IsValidIPAddress(subnet3, subnet2, subnet1, subnet0)) //check subnet mask
        {
            ConnectToCamera();
            if (gigeCamera.IsConnected())
            {
                if (WriteIPToCamera(CURRENT_IP_ADDRESS, ip3, ip2, ip1, ip0) == 0) //write the ip address
                {
                    WriteIPToCamera(CURRENT_SUBNET_MASK, subnet3, subnet2, subnet1, subnet0); //write the subnet
                }
            }
        }
    }
}

//Copies Current IP Configuration to Persistent IP Configuration (GUI and in Camera)
void MainWindow::on_copyCurrentIPToPersistentIPButton_clicked()
{
    QString ip0 = ui->currentIP0Text->toPlainText(); //least significant
    QString ip1 = ui->currentIP1Text->toPlainText();
    QString ip2 = ui->currentIP2Text->toPlainText();
    QString ip3 = ui->currentIP3Text->toPlainText(); //most significant
    QString subnet0 = ui->currentSubnet0Text->toPlainText(); //least significant
    QString subnet1 = ui->currentSubnet1Text->toPlainText();
    QString subnet2 = ui->currentSubnet2Text->toPlainText();
    QString subnet3 = ui->currentSubnet3Text->toPlainText(); //most significant
    QString gateway0 = ui->currentGateway0Text->toPlainText(); //least significant
    QString gateway1 = ui->currentGateway1Text->toPlainText();
    QString gateway2 = ui->currentGateway2Text->toPlainText();
    QString gateway3 = ui->currentGateway3Text->toPlainText(); //most significant
    if (IsValidIPAddress(ip3, ip2, ip1, ip0)) //check IP Address
    {
        if (IsValidIPAddress(subnet3, subnet2, subnet1, subnet0)) //check subnet mask
        {
            if (IsValidIPAddress(gateway3, gateway2, gateway1, gateway0)) //check default gateway
            {
                ConnectToCamera();
                if (gigeCamera.IsConnected())
                {
                    if (WriteIPToCamera(PERSISTENT_IP_ADDRESS, ip3, ip2, ip1, ip0) == 0) //write IP address
                    {
                        if (WriteIPToCamera(PERSISTENT_SUBNET_MASK, subnet3, subnet2, subnet1, subnet0) == 0) //write Subnet Mask
                        {
                            if (WriteIPToCamera(PERSISTENT_GATEWAY_MASK, gateway3, gateway2, gateway1, gateway0) == 0) //write Default Gateway
                            {
                                //Change values on the gui
                                SetText(ui->persistentIP0Text, ip0);
                                SetText(ui->persistentIP1Text, ip1);
                                SetText(ui->persistentIP2Text, ip2);
                                SetText(ui->persistentIP3Text, ip3);
                                SetText(ui->persistentSubnet0Text, subnet0);
                                SetText(ui->persistentSubnet1Text, subnet1);
                                SetText(ui->persistentSubnet2Text, subnet2);
                                SetText(ui->persistentSubnet3Text, subnet3);
                                SetText(ui->persistentGateway0Text, gateway0);
                                SetText(ui->persistentGateway1Text, gateway1);
                                SetText(ui->persistentGateway2Text, gateway2);
                                SetText(ui->persistentGateway3Text, gateway3);
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
    QString ip0 = ui->persistentIP0Text->toPlainText(); //least significant
    QString ip1 = ui->persistentIP1Text->toPlainText();
    QString ip2 = ui->persistentIP2Text->toPlainText();
    QString ip3 = ui->persistentIP3Text->toPlainText(); //most significant
    QString subnet0 = ui->persistentSubnet0Text->toPlainText(); //least significant
    QString subnet1 = ui->persistentSubnet1Text->toPlainText();
    QString subnet2 = ui->persistentSubnet2Text->toPlainText();
    QString subnet3 = ui->persistentSubnet3Text->toPlainText(); //most significant
    if (IsValidIPAddress(ip3, ip2, ip1, ip0)) //check IP Address
    {
        if (IsValidIPAddress(subnet3, subnet2, subnet1, subnet0)) //check subnet mask
        {
            ConnectToCamera();
            if (gigeCamera.IsConnected())
            {
                if (WriteIPToCamera(PERSISTENT_IP_ADDRESS, ip3, ip2, ip1, ip0) == 0) //write the ip address
                {
                    WriteIPToCamera(PERSISTENT_SUBNET_MASK, subnet3, subnet2, subnet1, subnet0); //write the subnet
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
    ConnectToCamera();
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

void MainWindow::on_testCameraConnectionButton_clicked()
{

}




//Tries 20 times to connect to the camera
void MainWindow::ConnectToCamera()
{
    int connectionAttempts = 0;
    //attempt to connect a maximum of 20 times
    while (!gigeCamera.IsConnected() && connectionAttempts < 20)
    {
        gigeCamera.Connect();
        connectionAttempts++;
    }
}

//Initializes all Text Field Values from what is in the Camera Registers
void MainWindow::InitializeGUITextFieldValuesFromCamera()
{
    SetCameraInformationFieldsFromCamera();
    SetCurrentIPConfigFieldsFromCamera();
    SetPersistentIPConfigFieldsFromCamera();
}

//Checks to see if a particular ip address is valid
//  ipMostSignificant refers to "198" in IP Address "198.166.0.2"
//  ipSecond refers to "166" in IP Address "198.166.0.2"
//  ipThird refers to "0" in IP Address "198.166.0.2"
//  ipLeastSignificant refers to "2" in IP Address "198.166.0.2"
bool MainWindow::IsValidIPAddress(QString ipMostSignificant, QString ipSecond, QString ipThird, QString ipLeastSignificant)
{
    QString ipString = ipMostSignificant;
    //Form QString representation of IP Address
    QHostAddress ipAddress = QHostAddress();
    ipString.append('.');
    ipString.append(ipSecond);
    ipString.append('.');
    ipString.append(ipThird);
    ipString.append('.');
    ipString.append(ipLeastSignificant);

    bool success = ipAddress.setAddress(ipString);
    return success;
}

//Returns -1 on unsuccessful read, 0 or positive number on successful read
int MainWindow::ReadFromCameraRegister(unsigned int registerIndex)
{
    int readValue = -1;     // -1 = unsuccessful read
                            //  0 or positive # = successful read
    unsigned int unsignedRead;
    ConnectToCamera();
    if (gigeCamera.IsConnected()) //make sure the camera is connect before writing
    {
        FlyCapture2::Error error = gigeCamera.ReadGVCPRegister(registerIndex, &unsignedRead);
        //Error error = gigeCamera.ReadRegister(registerIndex, &readValue);
        //   We may need to use ReadRegister() instead of ReadGVCPRegister().  Still looking for documentation
        //   to see what the difference is.
        if ( error.GetType() != FlyCapture2::PGRERROR_OK ) //If read was unsuccessful
        {
            char error[512];
            sprintf( error, "There was an error reading GVCP register %X.", registerIndex);
            readValue = -1;
        }
        else
        {
            readValue = unsignedRead;
        }
    }
    return readValue;
}

//Sets all uneditable text fields in "Camera Information"
void MainWindow::SetCameraInformationFieldsFromCamera()
{
    QString firmwareString, gigEString;
    ConnectToCamera();
    if (gigeCamera.IsConnected())
    {
        FlyCapture2::CameraInfo camInfo;
        FlyCapture2::Error error = gigeCamera.GetCameraInfo(&camInfo);
        if (error.GetType() == FlyCapture2::PGRERROR_OK) //successful at getting camera info
        {
            //set Serial Number text field
            SetText(ui->serialNumberText, QString((char *) camInfo.serialNumber));

            //set model text field
            SetText(ui->modelText, QString(camInfo.modelName));

            //set vendor text field
            SetText(ui->vendorText, QString(camInfo.vendorName));

            //set sensor text field
            SetText(ui->sensorText, QString(camInfo.sensorInfo));

            //set sensor resolution text field
            SetText(ui->resolutionText, QString(camInfo.sensorResolution));

            //set firmware text field
            firmwareString = QString(camInfo.firmwareVersion);
            firmwareString.append("; ");
            firmwareString.append(QString(camInfo.firmwareBuildTime));
            SetText(ui->firmwareText, firmwareString);

            //set GigE Version text field
            gigEString = QString((char*) camInfo.gigEMajorVersion);
            gigEString.append(".");
            gigEString.append(QString((char*) camInfo.gigEMinorVersion));
            SetText(ui->gigEVersionText, gigEString);

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
    ConnectToCamera();
    if (gigeCamera.IsConnected())
    {
        FlyCapture2::CameraInfo camInfo;
        FlyCapture2::Error error = gigeCamera.GetCameraInfo(&camInfo);
        if (error.GetType() == FlyCapture2::PGRERROR_OK) //successful at getting camera info
        {
            //set Current IP Address
            readVal = ReadFromCameraRegister(CURRENT_IP_ADDRESS);
            SetText(ui->currentIP3Text, QString((char*) ((readVal >= 0) ? readVal : '\0')));
            readVal = ReadFromCameraRegister(CURRENT_IP_ADDRESS + 4);
            SetText(ui->currentIP2Text, QString((char*) ((readVal >= 0) ? readVal : '\0')));
            readVal = ReadFromCameraRegister(CURRENT_IP_ADDRESS + 8);
            SetText(ui->currentIP1Text, QString((char*) ((readVal >= 0) ? readVal : '\0')));
            readVal = ReadFromCameraRegister(CURRENT_IP_ADDRESS + 12);
            SetText(ui->currentIP0Text, QString((char*) ((readVal >= 0) ? readVal : '\0')));

            //set Current Subnet
            readVal = ReadFromCameraRegister(CURRENT_SUBNET_MASK);
            SetText(ui->currentSubnet3Text, QString((char*) ((readVal >= 0) ? readVal : '\0')));
            readVal = ReadFromCameraRegister(CURRENT_SUBNET_MASK + 4);
            SetText(ui->currentSubnet2Text, QString((char*) ((readVal >= 0) ? readVal : '\0')));
            readVal = ReadFromCameraRegister(CURRENT_SUBNET_MASK + 8);
            SetText(ui->currentSubnet1Text, QString((char*) ((readVal >= 0) ? readVal : '\0')));
            readVal = ReadFromCameraRegister(CURRENT_SUBNET_MASK + 12);
            SetText(ui->currentSubnet0Text, QString((char*) ((readVal >= 0) ? readVal : '\0')));

            //set Current GateWay
            readVal = ReadFromCameraRegister(CURRENT_GATEWAY_MASK);
            SetText(ui->currentGateway3Text, QString((char*) ((readVal >= 0) ? readVal : '\0')));
            readVal = ReadFromCameraRegister(CURRENT_GATEWAY_MASK + 4);
            SetText(ui->currentGateway2Text, QString((char*) ((readVal >= 0) ? readVal : '\0')));
            readVal = ReadFromCameraRegister(CURRENT_GATEWAY_MASK + 8);
            SetText(ui->currentGateway1Text, QString((char*) ((readVal >= 0) ? readVal : '\0')));
            readVal = ReadFromCameraRegister(CURRENT_GATEWAY_MASK + 12);
            SetText(ui->currentGateway0Text, QString((char*) ((readVal >= 0) ? readVal : '\0')));
        }
    }
}

//Sets all text fields in "Persistent IP Configuration"
void MainWindow::SetPersistentIPConfigFieldsFromCamera()
{
    int readVal;
    ConnectToCamera();
    if (gigeCamera.IsConnected())
    {
        FlyCapture2::CameraInfo camInfo;
        FlyCapture2::Error error = gigeCamera.GetCameraInfo(&camInfo);
        if (error.GetType() == FlyCapture2::PGRERROR_OK) //successful at getting camera info
        {
            //set Current IP Address
            readVal = ReadFromCameraRegister(PERSISTENT_IP_ADDRESS);
            SetText(ui->persistentIP3Text, QString((char*) ((readVal >= 0) ? readVal : '\0')));
            readVal = ReadFromCameraRegister(PERSISTENT_IP_ADDRESS + 4);
            SetText(ui->persistentIP2Text, QString((char*) ((readVal >= 0) ? readVal : '\0')));
            readVal = ReadFromCameraRegister(PERSISTENT_IP_ADDRESS + 8);
            SetText(ui->persistentIP1Text, QString((char*) ((readVal >= 0) ? readVal : '\0')));
            readVal = ReadFromCameraRegister(PERSISTENT_IP_ADDRESS + 12);
            SetText(ui->persistentIP0Text, QString((char*) ((readVal >= 0) ? readVal : '\0')));

            //set Current Subnet
            readVal = ReadFromCameraRegister(PERSISTENT_SUBNET_MASK);
            SetText(ui->persistentSubnet3Text, QString((char*) ((readVal >= 0) ? readVal : '\0')));
            readVal = ReadFromCameraRegister(PERSISTENT_SUBNET_MASK + 4);
            SetText(ui->persistentSubnet2Text, QString((char*) ((readVal >= 0) ? readVal : '\0')));
            readVal = ReadFromCameraRegister(PERSISTENT_SUBNET_MASK + 8);
            SetText(ui->persistentSubnet1Text, QString((char*) ((readVal >= 0) ? readVal : '\0')));
            readVal = ReadFromCameraRegister(PERSISTENT_SUBNET_MASK + 12);
            SetText(ui->persistentSubnet0Text, QString((char*) ((readVal >= 0) ? readVal : '\0')));

            //set Current GateWay
            readVal = ReadFromCameraRegister(PERSISTENT_GATEWAY_MASK);
            SetText(ui->persistentGateway3Text, QString((char*) ((readVal >= 0) ? readVal : '\0')));
            readVal = ReadFromCameraRegister(PERSISTENT_GATEWAY_MASK + 4);
            SetText(ui->persistentGateway2Text, QString((char*) ((readVal >= 0) ? readVal : '\0')));
            readVal = ReadFromCameraRegister(PERSISTENT_GATEWAY_MASK + 8);
            SetText(ui->persistentGateway1Text, QString((char*) ((readVal >= 0) ? readVal : '\0')));
            readVal = ReadFromCameraRegister(PERSISTENT_GATEWAY_MASK + 12);
            SetText(ui->persistentGateway0Text, QString((char*) ((readVal >= 0) ? readVal : '\0')));
        }
    }
}

//Sets the specified QPlainTextEdit to the specified QString
void MainWindow::SetText(QPlainTextEdit * textEdit, QString value)
{
    textEdit->clear();
    textEdit->appendPlainText(value);
}

//Returns "0" if successful write, "-1" if unsuccessful Write
int MainWindow::WriteIPToCamera(unsigned int registerIndex, QString ipMostSignificant, QString ipSecond, QString ipThird, QString ipLeastSignificant)
{
    bool good = true;
    int writeSuccess = -1;
    unsigned int ipOne, ipTwo, ipThree, ipFour;
    ipOne = ipMostSignificant.toUInt(&good, 10); //gets first segment of IP address
    if (good)
    {
        ipTwo = ipSecond.toUInt(&good, 10); //gets second segment of IP address
        if (good)
        {
            ipThree = ipThird.toUInt(&good, 10); //gets third segment of IP address
            if (good)
            {
                ipFour = ipLeastSignificant.toUInt(&good, 10); //gets fourth segment of IP address
                if (good)
                {
                    if (WriteToCameraRegister(registerIndex, ipOne) == 0)
                    {
                        if (WriteToCameraRegister((registerIndex + 4), ipTwo) == 0)
                        {
                            if (WriteToCameraRegister((registerIndex + 8), ipThree) == 0)
                            {
                                if (WriteToCameraRegister((registerIndex + 12), ipFour) == 0)
                                {
                                    writeSuccess = 0;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return writeSuccess;
}

//Returns "0" if successful write, "-1" if unsuccessful Write, "-2" if no camera connected (and no write)
int MainWindow::WriteToCameraRegister(unsigned int registerIndex, unsigned int valueToRegister)
{
    int writeStatus = -2;   // -2 = camera not connected
                            // -1 = camera connected, but unsuccessful write
                            //  0 = successful write
    ConnectToCamera();
    if (gigeCamera.IsConnected()) //make sure the camera is connect before writing
    {
        FlyCapture2::Error error = gigeCamera.WriteGVCPRegister(registerIndex, valueToRegister, false); //write to camera
        //Error error = gigeCamera.WriteRegister(registerIndex, valueToRegister, false);
        //   We may need to use WriteRegister() instead of WriteGVCPRegister().  Still looking for documentation
        //   to see what the difference is.
        if ( error.GetType() != FlyCapture2::PGRERROR_OK ) //If the write was unsuccessful
        {
            char error[512];
            sprintf( error, "There was an error writing GVCP register %X with the value %X.", registerIndex, valueToRegister );
            writeStatus = -1; //unsuccessful Write
        }
        else
        {
            writeStatus = 0; //successful Write
        }
    }
    return writeStatus;
}

























