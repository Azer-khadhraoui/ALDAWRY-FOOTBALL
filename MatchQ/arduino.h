#ifndef ARDUINO_H
#define ARDUINO_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class Arduino
{
public:
    Arduino();
    ~Arduino();
    int connect_arduino();
    int close_arduino();
    void write_to_arduino(const QByteArray &data);
    QByteArray read_from_arduino();
    QSerialPort* getSerial();
    QString getArduino_port_name();
private:
    QSerialPort *serial;
    static const quint16 arduino_vendor_id = 9025;
    static const quint16 arduino_product_id = 67;
    QString arduino_port_name;
    bool arduino_is_available;
    QByteArray data;
};

#endif // ARDUINO_H