#include "User.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Employee::Employee() : id(0) {}

Employee::Employee(int id, QString firstName, QString lastName, QString email, QString mobileNumber, QDate dob, QString role, QString password) {
    this->id = id;
    this->firstName = firstName;
    this->lastName = lastName;
    this->email = email;
    this->mobileNumber = mobileNumber;
    this->dateOfBirth = dob;
    this->role = role;
    this->password = password;
}

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
    QString queryStr = QString("INSERT INTO HOTSTUFF.EMPLOYE (NOM_EMP, PRENOM_EMP, EMAIL, MDP, NUM, DATEN, ROLE) "
                               "VALUES ('%1', '%2', '%3', '%4', %5, TO_DATE('%6', 'YYYY-MM-DD'), '%7')")
                           .arg(firstName.replace("'", "''")) // Escape single quotes
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
    model->setQuery("SELECT ID_EMP, NOM_EMP, PRENOM_EMP, EMAIL, NUM, DATEN, ROLE FROM HOTSTUFF.EMPLOYE");
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
    query.prepare("SELECT ID_EMP, NOM_EMP, PRENOM_EMP, EMAIL, NUM, DATEN, ROLE FROM HOTSTUFF.EMPLOYE WHERE ID_EMP = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        Employee* employee = new Employee();
        employee->setId(query.value(0).toInt());
        employee->setFirstName(query.value(1).toString());
        employee->setLastName(query.value(2).toString());
        employee->setEmail(query.value(3).toString());
        employee->setMobileNumber(query.value(4).toString());
        employee->setDateOfBirth(query.value(5).toDate());
        employee->setRole(query.value(6).toString());

        return employee;
    }

    return nullptr; // Return null if employee with given ID not found
}


QSqlQueryModel* Employee::search(const QString& field, const QString& term) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QString column;

    // Map field to database column (case-insensitive)
    QString fieldLower = field.toLower().trimmed();
    if (fieldLower == "id") column = "ID_EMP";
    else if (fieldLower == "first name") column = "NOM_EMP";
    else if (fieldLower == "last name") column = "PRENOM_EMP";
    else if (fieldLower == "email") column = "EMAIL";
    else if (fieldLower == "mobile number") column = "NUM";
    else if (fieldLower == "date of birth") column = "DATEN";
    else if (fieldLower == "role") column = "ROLE";
    else {
        qDebug() << "Invalid search field:" << field;
        delete model;
        return displayEmployees(); // Fallback to full list
    }

    // Prepare the query
    QSqlQuery query;
    QString queryStr;

    if (column == "ID_EMP" || column == "NUM") {
        // Numeric fields: Use exact match
        bool ok;
        qlonglong number = term.toLongLong(&ok);
        if (!ok) {
            qDebug() << "Invalid numeric input for" << column << ":" << term;
            delete model;
            return displayEmployees();
        }
        queryStr = QString("SELECT ID_EMP, NOM_EMP, PRENOM_EMP, EMAIL, NUM, DATEN, ROLE "
                           "FROM HOTSTUFF.EMPLOYE WHERE %1 = :value").arg(column);
        query.prepare(queryStr);
        query.bindValue(":value", number);
    } else if (column == "DATEN") {
        // Date field: Try parsing date
        QDate date = QDate::fromString(term, "yyyy-MM-dd");
        if (!date.isValid()) {
            date = QDate::fromString(term, "yyyy"); // Try year-only fallback
            if (!date.isValid()) {
                qDebug() << "Invalid date format:" << term;
                delete model;
                return displayEmployees();
            }
            queryStr = QString("SELECT ID_EMP, NOM_EMP, PRENOM_EMP, EMAIL, NUM, DATEN, ROLE "
                               "FROM HOTSTUFF.EMPLOYE WHERE EXTRACT(YEAR FROM DATEN) = :year");
            query.prepare(queryStr);
            query.bindValue(":year", term.toInt());
        } else {
            queryStr = QString("SELECT ID_EMP, NOM_EMP, PRENOM_EMP, EMAIL, NUM, DATEN, ROLE "
                               "FROM HOTSTUFF.EMPLOYE WHERE DATEN = TO_DATE(:date, 'YYYY-MM-DD')");
            query.prepare(queryStr);
            query.bindValue(":date", date.toString("yyyy-MM-dd"));
        }
    } else {
        // Text fields: Use LIKE for partial matching (case-insensitive)
        queryStr = QString("SELECT ID_EMP, NOM_EMP, PRENOM_EMP, EMAIL, NUM, DATEN, ROLE "
                           "FROM HOTSTUFF.EMPLOYE WHERE UPPER(%1) LIKE UPPER(:term)").arg(column);
        query.prepare(queryStr);
        query.bindValue(":term", "%" + term + "%");
    }

    // Execute and set the model
    if (query.exec()) {
        model->setQuery(query);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("First Name"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Last Name"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Mobile Number"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date of Birth"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("Role"));
    } else {
        qDebug() << "Search query failed:" << query.lastError().text();
        delete model;
        return displayEmployees();
    }

    return model;
}
