#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QtSql/QSqlDatabase>

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseManager(QObject *parent = nullptr);

    bool openDatabase();
    void closeDatabase();

    bool createTable();
    bool addReminder(const QString &task, const QDateTime &date, const QString &priority);
    QList<QVariantMap> getAllReminders();

private:
    QSqlDatabase m_database;
};

#endif // DATABASEMANAGER_H
