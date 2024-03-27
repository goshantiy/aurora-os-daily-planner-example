#include <QtGui/QGuiApplication>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusConnectionInterface>

#include "applicationservice.h"

const QString dbusServiceStr = QStringLiteral(DBUS_SERVICE);
const QString dbusPathStr = QStringLiteral(DBUS_PATH);
const QString dbusIfaceStr = QStringLiteral(DBUS_INTERFACE);
const QString dbusMethodStr = QStringLiteral("handleApplicationArgs");
const QString dbusMethodAppWakeUp = QStringLiteral("handleApplicationWakeUp");

ApplicationService::ApplicationService(QObject *parent) : QDBusAbstractAdaptor(parent)
{
    setAutoRelaySignals(true);

    QDBusConnection dbus = QDBusConnection::sessionBus();
    dbus.registerObject(dbusPathStr, this, QDBusConnection::ExportAllSlots);
    if (!isRegistered()) {
        bool success = dbus.registerService(dbusServiceStr);
        if (!success)
            qApp->quit();
    }
}

ApplicationService::~ApplicationService()
{
    QDBusConnection dbus = QDBusConnection::sessionBus();
    dbus.unregisterObject(dbusPathStr);
    dbus.unregisterService(dbusServiceStr);
}

bool ApplicationService::isRegistered()
{
    return QDBusConnection::sessionBus().interface()->isServiceRegistered(dbusServiceStr);
}

QString ApplicationService::notifyDBusService()
{
    return dbusServiceStr;
}

QString ApplicationService::notifyDBusPath()
{
    return dbusPathStr;
}

QString ApplicationService::notifyDBusIface()
{
    return dbusIfaceStr;
}

QString ApplicationService::notifyDBusMethod()
{
    return dbusMethodAppWakeUp;
}

int ApplicationService::updateApplicationArgs(const QStringList &arguments)
{
    QDBusMessage message = QDBusMessage::createMethodCall(dbusServiceStr, dbusPathStr, dbusIfaceStr,
                                                          dbusMethodStr);
    message.setArguments(QList<QVariant>() << arguments);
    QDBusMessage reply = QDBusConnection::sessionBus().call(message);

    return 0;
}

void ApplicationService::handleApplicationArgs(const QStringList &arguments)
{
    if (arguments.indexOf(QStringLiteral("/no-gui")) != -1)
        return;

    emit guiRequested();
}

void ApplicationService::handleApplicationWakeUp()
{
    emit guiRequested();
}
