#ifndef UPDATEFORM_H
#define UPDATEFORM_H
#include <QWidget>
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class updateform;
}
QT_END_NAMESPACE

class updateform : public QDialog
{
    Q_OBJECT
public:
    explicit updateform(QWidget *parent = nullptr);
    ~updateform(); // Declaration only

    
private slots:
    void on_pushButton_submit_2_clicked();

    void on_pushButton_submit_clicked();

private:
    Ui::updateform *ui;
};

#endif // UPDATEFORM_H
