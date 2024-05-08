#ifndef DAILYPLANNERAPP_H
#define DAILYPLANNERAPP_H

#include <QObject>

#include "databasemanager.h"
#include "global.h"
#include "remindermodel.h"
#include "prioritycompletedproxy.h"

namespace DailyPlanner {
    class DailyPlannerApp : public QObject
    {
        Q_OBJECT
    public:
        Q_PROPERTY(DatabaseManager *manager READ manager WRITE setManager NOTIFY managerChanged)
        Q_PROPERTY(ReminderModel *model READ model WRITE setModel NOTIFY modelChanged)
        Q_PROPERTY(
         PriorityCompletedSortProxyModel *proxy READ proxy WRITE setProxy NOTIFY proxyChanged)

        explicit DailyPlannerApp(QObject *parent = nullptr);
        PriorityCompletedSortProxyModel *proxy() const;

        DatabaseManager *manager() const;
        void setManager(DatabaseManager *newManager);

        ReminderModel *model() const;
        void setModel(ReminderModel *newModel);

        void setProxy(PriorityCompletedSortProxyModel *newProxy);

    signals:
        void managerChanged();
        void modelChanged();
        void proxyChanged();

    private:
        PriorityCompletedSortProxyModel *_proxy;
        DatabaseManager *_manager;
        ReminderModel *_model;
    };
}
#endif // DAILYPLANNERAPP_H
