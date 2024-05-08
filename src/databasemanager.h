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

        QList<QVariantMap> getAllReminders();

        const QSqlDatabase &database() const;

        bool clearRemindersTable();
        Q_INVOKABLE bool updateReminder(int id,
                                        const QString &task,
                                        const QString &description,
                                        const QString &date,
                                        const QTime &time,
                                        const int &priority,
                                        const QString &tag,
                                        const QColor &color);
        Q_INVOKABLE bool addReminder(const QString &task,
                                     const QString &description,
                                     const QString &date,
                                     const QTime &time,
                                     const int &priority,
                                     const QString &tag,
                                     const QColor &color);
        Q_INVOKABLE
        bool setCompleted(int id, bool completed);

    private:
        QSqlDatabase _database;
    };
}

#endif // DATABASEMANAGER_H
