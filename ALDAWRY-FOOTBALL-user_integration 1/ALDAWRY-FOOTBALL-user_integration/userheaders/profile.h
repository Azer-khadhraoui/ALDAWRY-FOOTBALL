#ifndef PROFILE_H
#define PROFILE_H

#include <QDialog>
#include "user.h"

namespace Ui {
class Profile;
}

class Profile : public QDialog {
    Q_OBJECT

public:
    explicit Profile(QWidget *parent = nullptr);
    ~Profile();

private slots:
    void on_closeButton_clicked();

private:
    Ui::Profile *ui;
    void loadUserProfile();
};

#endif // PROFILE_H
