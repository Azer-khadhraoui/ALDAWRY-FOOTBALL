#include "arduino.h"
#include <QDebug>
#include <QThread>

Arduino::Arduino() : serial(new QSerialPort), arduino_is_available(false) {
    data.clear();
}

Arduino::~Arduino() {
    close_arduino();
    delete serial;
}

int Arduino::connect_arduino() {
    arduino_is_available = false;
    int retries = 3;
    while (retries > 0) {
        foreach(const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()) {
            if (serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()) {
                if (serial_port_info.vendorIdentifier() == arduino_vendor_id &&
                    serial_port_info.productIdentifier() == arduino_product_id) {
                    arduino_is_available = true;
                    arduino_port_name = serial_port_info.portName();
                    qDebug() << "Arduino found on port:" << arduino_port_name;
                    break;
                }
            }
        }

        if (!arduino_is_available) {
            qDebug() << "No Arduino found, retries left:" << retries;
            retries--;
            QThread::msleep(1000); // Delay for port release
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
            QThread::msleep(2000); // Wait for Arduino to stabilize
            qDebug() << "Connected to Arduino on port:" << arduino_port_name;
            return 0;
        } else {
            qDebug() << "Failed to open port:" << arduino_port_name << serial->errorString();
            retries--;
            QThread::msleep(1000); // Delay for port release
        }
    }
    qDebug() << "Failed to connect to Arduino after retries";
    return -1;
}

int Arduino::close_arduino() {
    if (serial->isOpen()) {
        serial->flush(); // Ensure all data is sent/received
        serial->clear();
        serial->close();
        QThread::msleep(1000); // Delay to ensure port is released
        qDebug() << "Disconnected from Arduino on port:" << arduino_port_name;
        return 0;
    }
    qDebug() << "Port is already closed:" << arduino_port_name;
    return -1;
}

QByteArray Arduino::read_from_arduino() {
    if (!serial->isOpen()) {
        qDebug() << "Port is closed, cannot read from Arduino:" << arduino_port_name;
        return QByteArray();
    }

    serial->clear();  // Clear buffer to avoid stale data
    QByteArray data;
    if (serial->waitForReadyRead(1000)) {  // Extended timeout to 1000ms
        data = serial->readAll();
        while (serial->waitForReadyRead(50)) {  // Accumulate additional data
            data += serial->readAll();
        }
        qDebug() << "Read from Arduino:" << data;
    } else {
        qDebug() << "No data available from Arduino after 1000ms";
    }
    return data;
}

void Arduino::write_to_arduino(const QByteArray &data) {
    if (serial->isOpen()) {
        serial->write(data);
        serial->waitForBytesWritten(100);
        qDebug() << "Data written to Arduino:" << data;
    } else {
        qDebug() << "Port is closed, cannot write to Arduino:" << arduino_port_name;
    }
}

QSerialPort* Arduino::getSerial() {
    return serial;
}

QString Arduino::getArduino_port_name() {
    return arduino_port_name;
}