#include "sessionmanager.h"

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
