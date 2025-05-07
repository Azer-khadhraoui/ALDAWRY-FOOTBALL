#include "../matchheaders/arduino.h"
#include <QDebug>
#include <QThread>

Arduino::Arduino(DeviceType type) : serial(new QSerialPort), deviceType(type), arduino_is_available(false) {
    data.clear();
    vendor_id = 9025;
    product_id = 67; // Same for both Unos, differentiate by port
}

Arduino::~Arduino() {
    close_arduino();
    delete serial;
}

int Arduino::connect_arduino() {
    if (deviceType != WeatherArduino) {
        qDebug() << "connect_arduino called for non-weather Arduino";
        return -1;
    }
    arduino_is_available = false;
    int retries = 3;
    qDebug() << "Available ports for Weather Arduino:";
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        qDebug() << "Port:" << info.portName() << "Vendor:" << info.vendorIdentifier() << "Product:" << info.productIdentifier();
    }
    while (retries > 0) {
        foreach(const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()) {
            bool isWeatherArduinoPort = serial_port_info.portName().contains("COM7"); // Adjust to your weather Arduino port
            if (isWeatherArduinoPort) {
                arduino_is_available = true;
                arduino_port_name = serial_port_info.portName();
                qDebug() << "Weather Arduino found on port:" << arduino_port_name;
                break;
            }
        }

        if (!arduino_is_available) {
            qDebug() << "Weather Arduino not found, retries left:" << retries;
            retries--;
            QThread::msleep(1000);
            continue;
        }

        serial->setPortName(arduino_port_name);
        if (serial->open(QIODevice::ReadWrite)) {
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);
            serial->clear();
            QThread::msleep(2000);
            qDebug() << "Connected to Weather Arduino on port:" << arduino_port_name;
            return 0;
        } else {
            qDebug() << "Failed to open port:" << arduino_port_name << serial->errorString();
            retries--;
            QThread::msleep(1000);
        }
    }
    qDebug() << "Failed to connect to Weather Arduino after retries";
    return -1;
}

int Arduino::connect_goal_arduino() {
    if (deviceType != GoalArduino) {
        qDebug() << "connect_goal_arduino called for non-goal Arduino";
        return -1;
    }
    arduino_is_available = false;
    int retries = 3;
    qDebug() << "Available ports for Goal Arduino:";
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        qDebug() << "Port:" << info.portName() << "Vendor:" << info.vendorIdentifier() << "Product:" << info.productIdentifier();
    }
    while (retries > 0) {
        foreach(const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()) {
            bool isGoalArduinoPort = serial_port_info.portName().contains("COM8"); // Your goal Arduino port
            if (isGoalArduinoPort) {
                arduino_is_available = true;
                arduino_port_name = serial_port_info.portName();
                qDebug() << "Goal Arduino found on port:" << arduino_port_name;
                break;
            }
        }

        if (!arduino_is_available) {
            qDebug() << "Goal Arduino not found, retries left:" << retries;
            retries--;
            QThread::msleep(1000);
            continue;
        }

        serial->setPortName(arduino_port_name);
        if (serial->open(QIODevice::ReadWrite)) {
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);
            serial->clear();
            QThread::msleep(2000);
            qDebug() << "Connected to Goal Arduino on port:" << arduino_port_name;
            return 0;
        } else {
            qDebug() << "Failed to open port:" << arduino_port_name << serial->errorString();
            retries--;
            QThread::msleep(1000);
        }
    }
    qDebug() << "Failed to connect to Goal Arduino after retries";
    return -1;
}

int Arduino::close_arduino() {
    if (serial->isOpen()) {
        serial->flush();
        serial->clear();
        serial->close();
        QThread::msleep(1000);
        qDebug() << "Disconnected from" << (deviceType == WeatherArduino ? "Weather" : "Goal") << "Arduino on port:" << arduino_port_name;
        return 0;
    }
    qDebug() << "Port is already closed:" << arduino_port_name;
    return -1;
}

QByteArray Arduino::read_from_arduino() {
    if (deviceType != WeatherArduino) {
        qDebug() << "read_from_arduino called for non-weather Arduino";
        return QByteArray();
    }
    if (!serial->isOpen()) {
        qDebug() << "Port is closed, cannot read from Weather Arduino:" << arduino_port_name;
        return QByteArray();
    }

    serial->clear();
    QByteArray data;
    if (serial->waitForReadyRead(1000)) {
        data = serial->readAll();
        while (serial->waitForReadyRead(50)) {
            data += serial->readAll();
        }
        qDebug() << "Read from Weather Arduino:" << data;
    } else {
        qDebug() << "No data available from Weather Arduino after 1000ms";
    }
    return data;
}

QByteArray Arduino::read_from_goal_arduino() {
    if (deviceType != GoalArduino) {
        qDebug() << "read_from_goal_arduino called for non-goal Arduino";
        return QByteArray();
    }
    if (!serial->isOpen()) {
        qDebug() << "Port is closed, cannot read from Goal Arduino:" << arduino_port_name;
        return QByteArray();
    }

    serial->clear();
    QByteArray data;
    if (serial->waitForReadyRead(500)) {
        data = serial->readAll();
        while (serial->waitForReadyRead(50)) {
            data += serial->readAll();
        }
        qDebug() << "Read from Goal Arduino:" << data;
    } else {
        qDebug() << "No data available from Goal Arduino after 500ms";
    }
    return data;
}

void Arduino::write_to_arduino(const QByteArray &data) {
    if (serial->isOpen()) {
        serial->write(data);
        serial->waitForBytesWritten(100);
        qDebug() << "Data written to" << (deviceType == WeatherArduino ? "Weather" : "Goal") << "Arduino:" << data;
    } else {
        qDebug() << "Port is closed, cannot write to" << (deviceType == WeatherArduino ? "Weather" : "Goal") << "Arduino:" << arduino_port_name;
    }
}

QSerialPort* Arduino::getSerial() {
    return serial;
}

QString Arduino::getArduino_port_name() {
    return arduino_port_name;
}
