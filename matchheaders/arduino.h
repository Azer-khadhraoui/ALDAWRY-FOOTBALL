#ifndef ARDUINO_H
#define ARDUINO_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class Arduino
{
public:
    enum DeviceType {
        WeatherArduino,
        GoalArduino
    };

    Arduino(DeviceType type);
    ~Arduino();
    int connect_arduino(); // For weather Arduino
    int connect_goal_arduino(); // For goal Arduino
    int close_arduino();
    void write_to_arduino(const QByteArray &data);
    QByteArray read_from_arduino(); // For weather Arduino
    QByteArray read_from_goal_arduino(); // For goal Arduino
    QSerialPort* getSerial();
    QString getArduino_port_name();
private:
    QSerialPort *serial;
    DeviceType deviceType;
    quint16 vendor_id;
    quint16 product_id;
    QString arduino_port_name;
    bool arduino_is_available;
    QByteArray data;
};

#endif // ARDUINO_H