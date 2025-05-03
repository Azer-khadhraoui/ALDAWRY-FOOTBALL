#include "../userheaders/User.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QRegularExpression> // Add this line to fix the QRegularExpression error
#include <QCryptographicHash> // Ensure this is included for hashing

Employee::Employee(int id, QString firstName, QString lastName, QString email, QString mobileNumber, QDate dob, QString role, QString password, QByteArray face)
    : id(id), firstName(firstName), lastName(lastName), email(email), mobileNumber(mobileNumber), dateOfBirth(dob), role(role), password(password), face(face) {}


bool Employee::addEmployee()
{
    /* ---------- 1. VALIDATION ---------- */
    if (firstName.isEmpty() || lastName.isEmpty() || email.isEmpty() ||
        mobileNumber.isEmpty() || role.isEmpty()) {
        qDebug() << "Validation failed: Required fields must be non-empty.";
        return false;
    }

    if (firstName.length() > 100 || lastName.length() > 100 || email.length() > 100 ||
        role.length() > 100) {
        qDebug() << "Validation failed: Input exceeds 100 chars for firstName, lastName, email, or role.";
        return false;
    }

    // Allow password to be empty, but if provided, check its length
    if (!password.isEmpty() && password.length() > 110) {
        qDebug() << "Validation failed: Password exceeds 110 chars.";
        return false;
    }

    if (mobileNumber.length() > 10) {
        qDebug() << "Validation failed: Mobile number > 10 digits.";
        return false;
    }
    if (!validatePhoneNumber(mobileNumber)) {
        qDebug() << "Validation failed: Invalid phone.";
        return false;
    }
    if (!validateAge(dateOfBirth)) {
        qDebug() << "Validation failed: < 18 years old.";
        return false;
    }

    bool ok;
    qlonglong mobileNum = mobileNumber.toLongLong(&ok);
    if (!ok) {
        qDebug() << "Validation failed: Mobile not numeric.";
        return false;
    }

    if (face.size() > 5 * 1024 * 1024) {
        qDebug() << "Validation failed: Photo > 5 MB.";
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
             << "Password:" << (password.isEmpty() ? "[empty]" : "[set]")
             << "Face size:" << face.size();

    /* ---------- 3. BUILD THE TEXT FOR “STRING” PART ---------- */
    QString passwordValue = password.isEmpty() ? "NULL" : QString("'%1'").arg(password.replace("'", "''"));
    QString queryStr = QString(R"(
        INSERT INTO EMPLOYE
        (ID_EMP, NOM_EMP, PRENOM_EMP, EMAIL, MDP,
         NUM, DATEN, ROLE, FACE)
        VALUES
        (%1, '%2', '%3', '%4', %5,
         %6, TO_DATE('%7','YYYY-MM-DD'), '%8', :face)
    )")
                           .arg(id)
                           .arg(firstName.replace("'", "''"))
                           .arg(lastName.replace("'", "''"))
                           .arg(email.replace("'", "''"))
                           .arg(passwordValue)
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

    query.bindValue(":face", face, QSql::In | QSql::Binary);

    if (!query.exec()) {
        QSqlError err = query.lastError();
        qDebug() << "SQL execution failed:" << err.text()
                 << "Native error code:" << err.nativeErrorCode();
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
    QDate currentDate(2025, 5, 1); // Fixed date for consistency
    int years = currentDate.year() - dob.year();
    if (dob.month() > currentDate.month() || (dob.month() == currentDate.month() && dob.day() > currentDate.day())) {
        years--;
    }
    return years >= 18;
}
#include <QCryptographicHash> // Ensure this is included for hashing

bool Employee::authenticate(const QString& email, const QString& password) {
    static bool isProcessing = false;
    if (isProcessing) {
        qDebug() << "Authentication: Already processing for email:" << email << ", skipping.";
        return false;
    }
    isProcessing = true;

    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Authentication failed: Database connection not open for email:" << email;
        isProcessing = false;
        return false;
    }

    QSqlQuery query;
    query.prepare("SELECT MDP FROM HOTSTUFF.EMPLOYE WHERE UPPER(EMAIL) = UPPER(:email)");
    query.bindValue(":email", email);

    if (!query.exec()) {
        qDebug() << "Authentication query failed for email:" << email << "Error:" << query.lastError().text();
        qDebug() << "Database error:" << db.lastError().text();
        isProcessing = false;
        return false;
    }

    bool result = false;
    if (query.next()) {
        QString storedPassword = query.value(0).toString();
        qDebug() << "Stored password for email:" << email << "is" << (storedPassword.isEmpty() ? "empty" : "[non-empty]");

        if (storedPassword.isEmpty() || storedPassword.toUpper() == "NULL") {
            qDebug() << "Authentication failed: No password set for email:" << email;
        } else {
            QStringList hashSalt = storedPassword.split(":");
            if (hashSalt.size() == 2) {
                QString storedHash = hashSalt[0];
                QString salt = hashSalt[1];
                QString saltedPassword = password + salt;
                QString computedHash = QString(QCryptographicHash::hash(saltedPassword.toUtf8(), QCryptographicHash::Sha256).toHex());
                result = (computedHash == storedHash);
            } else {
                result = (storedPassword == password);
            }
        }
    } else {
        qDebug() << "Authentication failed: No employee found with email:" << email;
    }

    // Ensure the query is fully consumed and finalized
    while (query.next()) {} // Consume any remaining rows
    query.finish(); // Explicitly finalize the query
    isProcessing = false;
    return result;
}
int Employee::getAge() const {
    QDate dob = getDateOfBirth();
    QDate today = QDate::currentDate();

    if (!dob.isValid() || dob > today) {
        return -1; // Invalid DOB
    }

    int age = today.year() - dob.year();
    if (dob > today.addYears(-age)) {
        age--; // Adjust for birthday not yet occurred
    }
    return age;
}

QList<Employee> Employee::getAllEmployees() {
    QList<Employee> employees;
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database connection not open when fetching employees";
        if (!db.open()) {
            qDebug() << "Failed to reopen database:" << db.lastError().text();
            return employees;
        }
    }

    if (!db.transaction()) {
        qDebug() << "Failed to start transaction:" << db.lastError().text();
        return employees;
    }

    QSqlQuery query;
    query.prepare("SELECT ID_EMP, NOM_EMP, PRENOM_EMP, EMAIL, DATEN, NUM, ROLE, FACE FROM EMPLOYE");

    if (!query.exec()) {
        qDebug() << "Failed to fetch employees:" << query.lastError().text();
        qDebug() << "Database error:" << db.lastError().text();
        db.rollback();
        return employees;
    }

    while (query.next()) {
        QVariant rawDate = query.value(4); // DATEN
        QDate dob;
        if (rawDate.isValid()) {
            QString dateStr = rawDate.toString();
            // Parse format "YYYY-MM-DDThh:mm:ss.sss"
            dob = QDate::fromString(dateStr.left(10), "yyyy-MM-dd");
        }
        if (!dob.isValid()) {
            qDebug() << "Failed to parse DATEN for ID" << query.value(0).toInt() << ":" << rawDate.toString();
            dob = QDate(1990, 1, 1); // Fallback date
        }
        qDebug() << "ID" << query.value(0).toInt() << "DOB:" << dob.toString("yyyy-MM-dd");

        Employee employee(
            query.value(0).toInt(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toString(),
            query.value(5).toString(),
            dob,
            query.value(6).toString(),
            "",
            query.value(7).toByteArray()
            );
        employees.append(employee);
    }

    if (!db.commit()) {
        qDebug() << "Failed to commit transaction:" << db.lastError().text();
        db.rollback();
    }

    query.finish();
    qDebug() << "Fetched" << employees.size() << "employees directly from Employee table";
    return employees;
}

