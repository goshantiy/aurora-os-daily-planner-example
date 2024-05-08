#include <auroraapp.h>
#include <QtQuick>
#include <QDebug>
#include "dailyplannerapp.h"

int main(int argc, char *argv[])
{
    QScopedPointer<QGuiApplication> application(Aurora::Application::application(argc, argv));
    application->setOrganizationName(QStringLiteral("ru.auroraos"));
    application->setApplicationName(QStringLiteral("dailyplanner"));

    QScopedPointer<QQuickView> view(Aurora::Application::createView());
    view->setSource(Aurora::Application::pathTo(QStringLiteral("qml/dailyplanner.qml")));

    const auto dailyplanner = new DailyPlanner::DailyPlannerApp;

    view->rootContext()->setContextProperty("AppManager", QVariant::fromValue(dailyplanner));
    view->show();

    return application->exec();
}
