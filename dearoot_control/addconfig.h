#ifndef ADDCONFIG_H
#define ADDCONFIG_H

#include <QWidget>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QMessageBox>
#include <QDir>

namespace Ui {
class AddConfig;
}

class AddConfig : public QWidget
{
    Q_OBJECT

public:
    explicit AddConfig(QWidget *parent = 0);
    ~AddConfig();

public slots:
    void slot_write_config();

private:
    Ui::AddConfig *ui;
};

#endif // ADDCONFIG_H
