#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QPoint>
#include <QMenu>
#include <QString>
#include <unistd.h>
#include "addconfig.h"
#include <QJsonObject>
#include <QJsonParseError>
#include <QDebug>
#include <dirent.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QStandardItemModel *model;
    QMenu *menu;
    QModelIndex menu_click_index;



    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void show_target_table();
    void insert_target_table(QJsonObject jObj, char* file_path);
    void create_data_module();


signals:

public slots:
    void slot_getshell();
    void slot_file_manage();
    void slot_delete();
    void slotCustomContextMenuRequested(const QPoint &pos);
    void slot_add_config();
    void slot_refresh_table();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
