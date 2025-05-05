#include "sessionmanager.h"
#include <QSqlQuery>
#include <QSqlError>


SessionManager::SessionManager() : loggedIn(false) {
    // Initialize with an empty Employee object
}

SessionManager& SessionManager::instance() {
    static SessionManager instance;
    return instance;
}

void SessionManager::setCurrentUser(const Employee& employee) {
    currentUser = employee;
    loggedIn = true;
}

const Employee& SessionManager::getCurrentUser() const {
    return currentUser;
}

bool SessionManager::isLoggedIn() const {
    return loggedIn;
}

void SessionManager::clearSession() {
    currentUser = Employee(); // Reset to default Employee
    loggedIn = false;
}

QList<Employee> SessionManager::getAllUsers() {
    QList<Employee> users;
    QSqlQuery query("SELECT ID_EMP, NOM_EMP, PRENOM_EMP, EMAIL, TO_CHAR(NUM), DATEN, ROLE, FACE FROM HOTSTUFF.EMPLOYE");
    if (!query.exec()) {
        qDebug() << "Failed to fetch users:" << query.lastError().text();
        return users;
    }

    while (query.next()) {
        Employee employee(
            query.value(0).toInt(),          // ID_EMP
            query.value(1).toString(),      // NOM_EMP (First Name)
            query.value(2).toString(),      // PRENOM_EMP (Last Name)
            query.value(3).toString(),      // EMAIL
            query.value(4).toString(),      // NUM (Mobile Number)
            query.value(5).toDate(),        // DATEN (Date of Birth)
            query.value(6).toString(),      // ROLE
            "",                             // Password (not fetched)
            query.value(7).toByteArray()    // FACE
            );
        users.append(employee);
    }
    qDebug() << "Fetched" << users.size() << "users";
    return users;
}
