#include "User.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QRegularExpression> // Add this line to fix the QRegularExpression error

Employee::Employee(int id, QString firstName, QString lastName, QString email, QString mobileNumber, QDate dob, QString role, QString password)
    : id(id), firstName(firstName), lastName(lastName), email(email), mobileNumber(mobileNumber), dateOfBirth(dob), role(role), password(password) {}



bool Employee::addEmployee() {
    // Validate for NOT NULL constraints
    if (firstName.isEmpty() || lastName.isEmpty() || email.isEmpty() ||
        password.isEmpty() || mobileNumber.isEmpty() || role.isEmpty()) {
        qDebug() << "Validation failed: All fields must be non-empty (NOT NULL constraint).";
        return false;
    }

    // Validate data lengths to match database constraints (VARCHAR2(100))
    if (firstName.length() > 100 || lastName.length() > 100 || email.length() > 100 ||
        role.length() > 100 || password.length() > 100) {
        qDebug() << "Validation failed: Input length exceeds 100 characters.";
        return false;
    }
    if (mobileNumber.length() > 10) {
        qDebug() << "Validation failed: Mobile number exceeds 10 digits.";
        return false;
    }

    // Add phone number validation
    if (!validatePhoneNumber(mobileNumber)) {
        qDebug() << "Validation failed: Mobile number must contain only numbers and be at least 8 digits.";
        return false;
    }

    // Add age validation
    if (!validateAge(dateOfBirth)) {
        qDebug() << "Validation failed: Employee must be at least 18 years old.";
        return false;
    }

    // Convert mobileNumber to a number since NUM is a NUMBER type
    bool ok;
    qlonglong mobileNum = mobileNumber.toLongLong(&ok);
    if (!ok) {
        qDebug() << "Validation failed: Mobile number must be numeric. Input:" << mobileNumber;
        return false;
    }

    // Log the data being inserted for debugging
    qDebug() << "Attempting to insert employee with data:"
             << "First Name:" << firstName
             << "Last Name:" << lastName
             << "Email:" << email
             << "Password:" << password
             << "Mobile Number:" << mobileNum
             << "Date of Birth:" << dateOfBirth.toString("yyyy-MM-dd")
             << "Role:" << role;

    // Construct the query dynamically
    QString queryStr = QString("INSERT INTO EMPLOYE (ID_EMP, NOM_EMP, PRENOM_EMP, EMAIL, MDP, NUM, DATEN, ROLE) "
                               "VALUES (%1, '%2', '%3', '%4', '%5', %6, TO_DATE('%7', 'YYYY-MM-DD'), '%8')")
                           .arg(id) // Add the ID here
                           .arg(firstName.replace("'", "''"))
                           .arg(lastName.replace("'", "''"))
                           .arg(email.replace("'", "''"))
                           .arg(password.replace("'", "''"))
                           .arg(mobileNum)
                           .arg(dateOfBirth.toString("yyyy-MM-dd"))
                           .arg(role.replace("'", "''"));

    qDebug() << "Constructed query:" << queryStr;

    QSqlQuery query;
    if (!query.exec(queryStr)) {
        QSqlError error = query.lastError();
        qDebug() << "SQL Execution failed:" << error.text();
        qDebug() << "Database Error:" << QSqlDatabase::database().lastError().text();
        qDebug() << "Native Error Code:" << error.nativeErrorCode();
        return false;
    }

    qDebug() << "Employee added successfully.";
    return true;
}
bool Employee::deleteEmployee(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM HOTSTUFF.EMPLOYE WHERE ID_EMP = :id");
    query.bindValue(":id", id);
    bool success = query.exec();
    if (!success) {
        QSqlError error = query.lastError();
        qDebug() << "SQL Error:" << error.text();
    }
    return success;
}

bool Employee::updateEmployee() {
    // Log the data being updated for debugging
    qDebug() << "Attempting to update employee with data:"
             << "ID:" << id
             << "First Name:" << firstName
             << "Last Name:" << lastName
             << "Email:" << email
             << "Password:" << (password.isEmpty() ? "[unchanged]" : "[new password]")
             << "Mobile Number:" << mobileNumber
             << "Date of Birth:" << dateOfBirth.toString("yyyy-MM-dd")
             << "Role:" << role;

    // Construct the query dynamically
    QString queryStr;

    if (password.isEmpty()) {
        // Don't update the password
        queryStr = QString("UPDATE HOTSTUFF.EMPLOYE SET "
                           "NOM_EMP = '%1', "
                           "PRENOM_EMP = '%2', "
                           "EMAIL = '%3', "
                           "NUM = %4, "
                           "DATEN = TO_DATE('%5', 'YYYY-MM-DD'), "
                           "ROLE = '%6' "
                           "WHERE ID_EMP = %7")
                       .arg(firstName.replace("'", "''")) // Escape single quotes
                       .arg(lastName.replace("'", "''"))
                       .arg(email.replace("'", "''"))
                       .arg(mobileNumber)
                       .arg(dateOfBirth.toString("yyyy-MM-dd"))
                       .arg(role.replace("'", "''"))
                       .arg(id);
    } else {
        // Update including password
        queryStr = QString("UPDATE HOTSTUFF.EMPLOYE SET "
                           "NOM_EMP = '%1', "
                           "PRENOM_EMP = '%2', "
                           "EMAIL = '%3', "
                           "MDP = '%4', "
                           "NUM = %5, "
                           "DATEN = TO_DATE('%6', 'YYYY-MM-DD'), "
                           "ROLE = '%7' "
                           "WHERE ID_EMP = %8")
                       .arg(firstName.replace("'", "''")) // Escape single quotes
                       .arg(lastName.replace("'", "''"))
                       .arg(email.replace("'", "''"))
                       .arg(password.replace("'", "''"))
                       .arg(mobileNumber)
                       .arg(dateOfBirth.toString("yyyy-MM-dd"))
                       .arg(role.replace("'", "''"))
                       .arg(id);
    }

    // Add phone number validation
    if (!validatePhoneNumber(mobileNumber)) {
        qDebug() << "Validation failed: Mobile number must contain only numbers and be at least 8 digits.";
        return false;
    }

    // Add age validation
    if (!validateAge(dateOfBirth)) {
        qDebug() << "Validation failed: Employee must be at least 18 years old.";
        return false;
    }

    qDebug() << "Constructed query:" << queryStr;

    QSqlQuery query;
    if (!query.exec(queryStr)) {
        QSqlError error = query.lastError();
        qDebug() << "SQL Execution failed:" << error.text();
        qDebug() << "Database Error:" << QSqlDatabase::database().lastError().text();
        qDebug() << "Native Error Code:" << error.nativeErrorCode();
        return false;
    }

    if (query.numRowsAffected() <= 0) {
        qDebug() << "Update affected 0 rows. Employee ID might not exist.";
        return false;
    }

    qDebug() << "Employee updated successfully. Rows affected:" << query.numRowsAffected();
    return true;
}

QSqlQueryModel* Employee::displayEmployees() {
    QSqlQueryModel* model = new QSqlQueryModel();
    // Cast NUM to a string using TO_CHAR to avoid scientific notation
    model->setQuery("SELECT ID_EMP, NOM_EMP, PRENOM_EMP, EMAIL, TO_CHAR(NUM), DATEN, ROLE FROM HOTSTUFF.EMPLOYE");
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "First Name");
    model->setHeaderData(2, Qt::Horizontal, "Last Name");
    model->setHeaderData(3, Qt::Horizontal, "Email");
    model->setHeaderData(4, Qt::Horizontal, "Mobile Number");
    model->setHeaderData(5, Qt::Horizontal, "Date of Birth");
    model->setHeaderData(6, Qt::Horizontal, "Role");
    return model;
}

Employee* Employee::getById(int id) {
    QSqlQuery query;
    query.prepare("SELECT ID_EMP, NOM_EMP, PRENOM_EMP, EMAIL, TO_CHAR(NUM), DATEN, ROLE FROM HOTSTUFF.EMPLOYE WHERE ID_EMP = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        Employee* employee = new Employee();
        employee->setId(query.value(0).toInt());
        employee->setFirstName(query.value(1).toString());
        employee->setLastName(query.value(2).toString());
        employee->setEmail(query.value(3).toString());
        employee->setMobileNumber(query.value(4).toString()); // Now a string
        employee->setDateOfBirth(query.value(5).toDate());
        employee->setRole(query.value(6).toString());
        return employee;
    }
    return nullptr;
}

QSqlQueryModel* Employee::search(const QString& field, const QString& term) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QString column;

    QString fieldLower = field.toLower().trimmed();
    if (fieldLower == "id") column = "ID_EMP";
    else if (fieldLower == "first name") column = "NOM_EMP";
    else if (fieldLower == "last name") column = "PRENOM_EMP";
    else if (fieldLower == "email") column = "EMAIL";
    else if (fieldLower == "mobile number") column = "NUM";
    else if (fieldLower == "date of birth") column = "DATEN";
    else if (fieldLower == "role") column = "ROLE";
    else {
        delete model;
        return displayEmployees();
    }

    QSqlQuery query;
    QString queryStr;

    if (column == "ID_EMP" || column == "NUM") {
        queryStr = QString("SELECT ID_EMP, NOM_EMP, PRENOM_EMP, EMAIL, TO_CHAR(NUM), DATEN, ROLE "
                           "FROM HOTSTUFF.EMPLOYE WHERE %1 = :value").arg(column);
        query.prepare(queryStr);
        query.bindValue(":value", term.toLongLong());
    } else if (column == "DATEN") {
        QDate date = QDate::fromString(term, "yyyy-MM-dd");
        if (!date.isValid()) {
            date = QDate::fromString(term, "yyyy");
            if (!date.isValid()) {
                delete model;
                return displayEmployees();
            }
            queryStr = QString("SELECT ID_EMP, NOM_EMP, PRENOM_EMP, EMAIL, TO_CHAR(NUM), DATEN, ROLE "
                               "FROM HOTSTUFF.EMPLOYE WHERE EXTRACT(YEAR FROM DATEN) = :year");
            query.prepare(queryStr);
            query.bindValue(":year", term.toInt());
        } else {
            queryStr = QString("SELECT ID_EMP, NOM_EMP, PRENOM_EMP, EMAIL, TO_CHAR(NUM), DATEN, ROLE "
                               "FROM HOTSTUFF.EMPLOYE WHERE DATEN = TO_DATE(:date, 'YYYY-MM-DD')");
            query.prepare(queryStr);
            query.bindValue(":date", date.toString("yyyy-MM-dd"));
        }
    } else {
        queryStr = QString("SELECT ID_EMP, NOM_EMP, PRENOM_EMP, EMAIL, TO_CHAR(NUM), DATEN, ROLE "
                           "FROM HOTSTUFF.EMPLOYE WHERE UPPER(%1) LIKE UPPER(:term)").arg(column);
        query.prepare(queryStr);
        query.bindValue(":term", "%" + term + "%");
    }

    if (query.exec()) {
        model->setQuery(query);
        model->setHeaderData(0, Qt::Horizontal, "ID");
        model->setHeaderData(1, Qt::Horizontal, "First Name");
        model->setHeaderData(2, Qt::Horizontal, "Last Name");
        model->setHeaderData(3, Qt::Horizontal, "Email");
        model->setHeaderData(4, Qt::Horizontal, "Mobile Number");
        model->setHeaderData(5, Qt::Horizontal, "Date of Birth");
        model->setHeaderData(6, Qt::Horizontal, "Role");
    } else {
        qDebug() << "Search query failed:" << query.lastError().text();
        delete model;
        return displayEmployees();
    }
    return model;
}
// Helper function to validate phone number (only numbers, at least 8 digits)
bool Employee::validatePhoneNumber(const QString& mobileNumber) {
    QRegularExpression re("^[0-9]{8,}$"); // At least 8 digits, only numbers
    return re.match(mobileNumber).hasMatch();
}

// Helper function to validate age (at least 18 years old)
bool Employee::validateAge(const QDate& dob) {
    QDate currentDate(2025, 3, 12); // Current date as per your setup
    // Alternatively, use QDate::currentDate() for dynamic date
    int age = dob.daysTo(currentDate) / 365; // Approximate age in years
    return age >= 18;
}


bool Employee::authenticate(const QString& email, const QString& password) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM HOTSTUFF.EMPLOYE WHERE EMAIL = :email AND MDP = :password");
    query.bindValue(":email", email);
    query.bindValue(":password", password);

    if (!query.exec()) {
        qDebug() << "Authentication query failed:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        int count = query.value(0).toInt();
        return count > 0; // Return true if a matching employee is found
    }

    return false; // No matching employee found
}
