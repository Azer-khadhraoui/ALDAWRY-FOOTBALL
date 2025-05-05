#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H
#include "user.h"

class SessionManager
{
public:
    static SessionManager& instance();

    // Set the current user after login
    void setCurrentUser(const Employee& employee);

    // Get the current user
    const Employee& getCurrentUser() const;

    // Check if a user is logged in
    bool isLoggedIn() const;

    // Clear the session (e.g., on logout)
    void clearSession();

    QList<Employee> getAllUsers(); // New method

private:
    SessionManager();
    SessionManager(const SessionManager&) = delete;
    SessionManager& operator=(const SessionManager&) = delete;

    // Current user data
    Employee currentUser;
    bool loggedIn;
};

#endif // SESSIONMANAGER_H
