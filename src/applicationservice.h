#ifndef APPLICATIONSERVICE_H
#define APPLICATIONSERVICE_H

#include <QtDBus/QDBusAbstractAdaptor>

class ApplicationService : public QDBusAbstractAdaptor
{
    Q_OBJECT

    Q_CLASSINFO("D-Bus Interface", DBUS_INTERFACE)

public:
    explicit ApplicationService(QObject *parent = nullptr);
    ~ApplicationService() override;

    static bool isRegistered();

    static QString notifyDBusService();
    static QString notifyDBusPath();
    static QString notifyDBusIface();
    static QString notifyDBusMethod();

    static int updateApplicationArgs(const QStringList &arguments);

signals:
    void guiRequested();

public slots:
    void handleApplicationArgs(const QStringList &arguments);
    void handleApplicationWakeUp();
};


#endif // APPLICATIONSERVICE_H
