#ifndef TARGET_TABLE_H
#define TARGET_TABLE_H

#include <QObject>

class target_table : public QObject
{
    Q_OBJECT
public:
    explicit target_table(QObject *parent = 0);
    //void* show_target_table();
signals:

public slots:
};

#endif // TARGET_TABLE_H
