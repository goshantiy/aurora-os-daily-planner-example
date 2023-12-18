#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include "global.h"

namespace DailyPlanner {
    class DatabaseManager : public QObject
    {
        Q_OBJECT
    public:
        explicit DatabaseManager(QObject *parent = nullptr);
        bool openDatabase();
        void closeDatabase();

        bool createTable();
        bool addReminder(const Reminder &reminder);
        QList<QVariantMap> getAllReminders();

        const QSqlDatabase &database() const;

        bool clearRemindersTable();
    private:
        QSqlDatabase _database;
    };
}

#endif // DATABASEMANAGER_H
