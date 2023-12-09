#include "databasemanager.h"
#include <QDebug>
#include <QVariantMap>
#include <QDateTime>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

DatabaseManager::DatabaseManager(QObject *parent)
    : QObject(parent)
{
}

bool DatabaseManager::openDatabase()
{
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName("dailyplanner.db");

    if (!m_database.open()) {
        qWarning() << "Error: Unable to open database" << m_database.lastError().text();
        return false;
    }

    return true;
}

void DatabaseManager::closeDatabase()
{
    m_database.close();
}

bool DatabaseManager::createTable()
{
    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS reminders ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "task TEXT, "
                   "date DATETIME, "
                   "priority TEXT)")) {
        qWarning() << "Error: Unable to create table" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::addReminder(const QString &task, const QDateTime &date, const QString &priority)
{
    QSqlQuery query;
    query.prepare("INSERT INTO reminders (task, date, priority) VALUES (?, ?, ?)");
    query.addBindValue(task);
    query.addBindValue(date);
    query.addBindValue(priority);

    if (!query.exec()) {
        qWarning() << "Error: Unable to add reminder" << query.lastError().text();
        return false;
    }

    return true;
}

QList<QVariantMap> DatabaseManager::getAllReminders()
{
    QList<QVariantMap> reminders;

    QSqlQuery query("SELECT * FROM reminders");
    while (query.next()) {
        QVariantMap reminder;
        reminder["id"] = query.value("id").toInt();
        reminder["task"] = query.value("task").toString();
        reminder["date"] = query.value("date").toDateTime();
        reminder["priority"] = query.value("priority").toString();
        reminders.append(reminder);
    }

    return reminders;
}
