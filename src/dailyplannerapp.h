#ifndef DAILYPLANNERAPP_H
#define DAILYPLANNERAPP_H

#include <QObject>
#include "databasemanager.h"
#include "global.h"
#include "remindermodel.h"
namespace DailyPlanner {
    class DailyPlannerApp : public QObject
    {
        Q_OBJECT
    public:
        explicit DailyPlannerApp(QObject *parent = nullptr);

        ReminderModel *model() const;
        void setModel(ReminderModel *newModel);

        DatabaseManager *manager() const;
        void setManager(DatabaseManager *newManager);

    private:
        DatabaseManager *_manager;
        ReminderModel *_model;
    signals:
    };
}
#endif // DAILYPLANNERAPP_H
