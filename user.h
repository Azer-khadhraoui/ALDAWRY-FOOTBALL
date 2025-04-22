#ifndef USER_H
#define USER_H

#include <QString>
#include <QDate>
#include <QSqlQueryModel>
#include <QByteArray> // Add for BLOB data

class Employee {
public:
    Employee() : id(-1), dateOfBirth(QDate()) {} // Default constructor
    Employee(int id, QString firstName, QString lastName, QString email, QString mobileNumber, QDate dob, QString role, QString password, QByteArray face = QByteArray());

    // Getters
    int getId() const { return id; }
    QString getFirstName() const { return firstName; }
    QString getLastName() const { return lastName; }
    QString getEmail() const { return email; }
    QString getMobileNumber() const { return mobileNumber; }
    QDate getDateOfBirth() const { return dateOfBirth; }
    QString getRole() const { return role; }
    QString getPassword() const { return password; }
    QByteArray getFace() const { return face; } // Getter for photo

    // Setters
    void setId(int newId) { id = newId; }
    void setFirstName(const QString &newFirstName) { firstName = newFirstName; }
    void setLastName(const QString &newLastName) { lastName = newLastName; }
    void setEmail(const QString &newEmail) { email = newEmail; }
    void setMobileNumber(const QString &newMobileNumber) { mobileNumber = newMobileNumber; }
    void setDateOfBirth(const QDate &newDob) { dateOfBirth = newDob; }
    void setRole(const QString &newRole) { role = newRole; }
    void setPassword(const QString &newPassword) { password = newPassword; }
    void setFace(const QByteArray &newFace) { face = newFace; } // Setter for photo

    Employee* getById(int id);
    static QSqlQueryModel* search(const QString& field, const QString& term);

    // CRUD Operations
    bool addEmployee();
    bool deleteEmployee(int id);
    bool updateEmployee();
    static QSqlQueryModel* displayEmployees();

    bool authenticate(const QString& email, const QString& password);

private:
    int id;               // Maps to ID_EMP
    QString firstName;    // Maps to NOM_EMP
    QString lastName;     // Maps to PRENOM_EMP
    QString email;        // Maps to EMAIL_EMP
    QString mobileNumber; // Maps to NUM
    QDate dateOfBirth;    // Maps to DATEN
    QString role;         // Maps to ROLE
    QString password;     // Maps to MDP
    QByteArray face;      // Maps to FACE (BLOB)

    // Validation helper functions
    bool validatePhoneNumber(const QString& mobileNumber);
    bool validateAge(const QDate& dob);
};

#endif // USER_H
