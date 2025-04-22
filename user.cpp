#include "User.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QRegularExpression> // Add this line to fix the QRegularExpression error

Employee::Employee(int id, QString firstName, QString lastName, QString email, QString mobileNumber, QDate dob, QString role, QString password, QByteArray face)
    : id(id), firstName(firstName), lastName(lastName), email(email), mobileNumber(mobileNumber), dateOfBirth(dob), role(role), password(password), face(face) {}


bool Employee::addEmployee()
{
    /* ---------- 1. VALIDATION (unchanged) ---------- */
    if (firstName.isEmpty() || lastName.isEmpty() || email.isEmpty() ||
        password.isEmpty() || mobileNumber.isEmpty() || role.isEmpty()) {
        qDebug() << "Validation failed: All fields must be non‑empty.";
        return false;
    }

    if (firstName.length() > 100 || lastName.length() > 100 || email.length() > 100 ||
        role.length() > 100 || password.length() > 100) {
        qDebug() << "Validation failed: Input exceeds 100 chars.";
        return false;
    }
    if (mobileNumber.length() > 10) {
        qDebug() << "Validation failed: Mobile number > 10 digits.";
        return false;
    }
    if (!validatePhoneNumber(mobileNumber)) {
        qDebug() << "Validation failed: Invalid phone.";
        return false;
    }
    if (!validateAge(dateOfBirth)) {
        qDebug() << "Validation failed: < 18 years old.";
        return false;
    }

    bool ok;
    qlonglong mobileNum = mobileNumber.toLongLong(&ok);
    if (!ok) {
        qDebug() << "Validation failed: Mobile not numeric.";
        return false;
    }

    if (face.size() > 5 * 1024 * 1024) {
        qDebug() << "Validation failed: Photo > 5 MB.";
        return false;
    }

    /* ---------- 2. LOG DATA ---------- */
    qDebug() << "Attempting INSERT:"
             << "ID:" << id
             << "First:" << firstName
             << "Last:"  << lastName
             << "Email:" << email
             << "Mobile:" << mobileNum
             << "DOB:" << dateOfBirth.toString("yyyy-MM-dd")
             << "Role:" << role
             << "Face size:" << face.size();

    /* ---------- 3. BUILD THE TEXT FOR “STRING” PART ---------- */
    // Everything except the BLOB is still baked into the string.
    QString queryStr = QString(R"(
        INSERT INTO EMPLOYE
        (ID_EMP, NOM_EMP, PRENOM_EMP, EMAIL, MDP,
         NUM, DATEN, ROLE, FACE)
        VALUES
        (%1, '%2', '%3', '%4', '%5',
         %6, TO_DATE('%7','YYYY-MM-DD'), '%8', :face)
    )")
                           .arg(id)
                           .arg(firstName.replace("'", "''"))
                           .arg(lastName.replace("'", "''"))
                           .arg(email.replace("'", "''"))
                           .arg(password.replace("'", "''"))
                           .arg(mobileNum)
                           .arg(dateOfBirth.toString("yyyy-MM-dd"))
                           .arg(role.replace("'", "''"));

    qDebug() << "Constructed query:" << queryStr.trimmed();

    /* ---------- 4. EXECUTE WITH A SINGLE BLOB BIND ---------- */
    QSqlQuery query;
    if (!query.prepare(queryStr)) {
        qDebug() << "Prepare failed:" << query.lastError().text();
        return false;
    }

    // bind the QByteArray; if empty Oracle stores NULL
    query.bindValue(":face", face, QSql::In | QSql::Binary);

    if (!query.exec()) {
        QSqlError err = query.lastError();
        qDebug() << "SQL exec failed:" << err.text()
                 << "Native:" << err.nativeErrorCode();
        return false;
    }

    qDebug() << "Employee added successfully; rows:" << query.numRowsAffected();
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
             << "Role:" << role
             << "Face:" << (face.isEmpty() ? "No photo" : "Photo provided");

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

    // Use a prepared statement to handle the BLOB
    QSqlQuery query;
    if (password.isEmpty()) {
        // Don't update the password
        query.prepare("UPDATE HOTSTUFF.EMPLOYE SET "
                      "NOM_EMP = :firstName, "
                      "PRENOM_EMP = :lastName, "
                      "EMAIL = :email, "
                      "NUM = :mobileNum, "
                      "DATEN = TO_DATE(:dob, 'YYYY-MM-DD'), "
                      "ROLE = :role, "
                      "FACE = :face "
                      "WHERE ID_EMP = :id");
    } else {
        // Update including password
        query.prepare("UPDATE HOTSTUFF.EMPLOYE SET "
                      "NOM_EMP = :firstName, "
                      "PRENOM_EMP = :lastName, "
                      "EMAIL = :email, "
                      "MDP = :password, "
                      "NUM = :mobileNum, "
                      "DATEN = TO_DATE(:dob, 'YYYY-MM-DD'), "
                      "ROLE = :role, "
                      "FACE = :face "
                      "WHERE ID_EMP = :id");
        query.bindValue(":password", password);
    }

    query.bindValue(":id", id);
    query.bindValue(":firstName", firstName);
    query.bindValue(":lastName", lastName);
    query.bindValue(":email", email);
    query.bindValue(":mobileNum", mobileNumber);
    query.bindValue(":dob", dateOfBirth.toString("yyyy-MM-dd"));
    query.bindValue(":role", role);
    query.bindValue(":face", face); // Bind the BLOB data

    if (!query.exec()) {
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
    query.prepare("SELECT ID_EMP, NOM_EMP, PRENOM_EMP, EMAIL, TO_CHAR(NUM), DATEN, ROLE, FACE "
                  "FROM HOTSTUFF.EMPLOYE WHERE ID_EMP = :id");
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
        employee->setFace(query.value(7).toByteArray()); // Fetch the BLOB
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
