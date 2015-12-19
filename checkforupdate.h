#ifndef CHECKFORUPDATE_H
#define CHECKFORUPDATE_H

#include <QObject>

class CheckForUpdate : public QObject
{
    Q_OBJECT
public:
    void updateCheck();
    void downloadUpdate();
    void doUpdate();

    explicit CheckForUpdate(QObject *parent = 0);

signals:
    void broadcastMessage(QString message);

public slots:
};

#endif // CHECKFORUPDATE_H
