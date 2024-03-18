#include "databasemanager.h"
#include <QDebug>
#include <QVariantMap>
#include <QDateTime>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

using namespace DailyPlanner;
DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent)
{}

bool DatabaseManager::openDatabase()
{
    _database = QSqlDatabase::addDatabase("QSQLITE");
    _database.setDatabaseName("plannerDB.db");

    if (!_database.open()) {
        qWarning() << "Error: Unable to open database" << _database.lastError().text();
        return false;
    }
    qWarning() << _database.databaseName();
    createTable();

    return true;
}

void DatabaseManager::closeDatabase()
{
    _database.close();
}

bool DatabaseManager::createTable()
{
    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS reminders ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "taskname TEXT, "
                    "description TEXT, "
                    "date DATE, "
                    "time TIME, "
                    "priority INTEGER, "
                    "tag_name TEXT, "
                    "tag_color TEXT, "
                    "completed INTEGER)")) {
        qWarning() << "Error: Unable to create table" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::addReminder(const Reminder &reminder)
{
    QSqlQuery query;
    query.prepare("INSERT INTO reminders (taskname, description, date, time, priority, tag_name, "
                  "tag_color, completed) VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(reminder.taskname);
    query.addBindValue(reminder.description);
    query.addBindValue(reminder.date);
    query.addBindValue(reminder.time);
    query.addBindValue(static_cast<int>(reminder.priority));
    query.addBindValue(reminder.tag.name);
    query.addBindValue(reminder.tag.color.name());
    query.addBindValue(0);

    if (!query.exec()) {
        qWarning() << "Error: Unable to add reminder" << query.lastError().text();
        return false;
    }

    return true;
}
bool DatabaseManager::setCompleted(int id, bool completed)
{
    QSqlQuery query;
    query.prepare("UPDATE reminders SET completed = ? WHERE id = ?");
    query.addBindValue(completed);
    query.addBindValue(id);
    if (!query.exec()) {
        qWarning() << "Error: Unable to set complete reminder" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::updateReminder(int id, const Reminder &reminder)
{
    QSqlQuery query;
    query.prepare("UPDATE reminders SET taskname = ?, description = ?, date = ?, time = ?, "
                  "priority = ?, tag_name = ?, tag_color = ? WHERE id = ?");
    query.addBindValue(reminder.taskname);
    query.addBindValue(reminder.description);
    query.addBindValue(reminder.date);
    query.addBindValue(reminder.time);
    query.addBindValue(static_cast<int>(reminder.priority));
    query.addBindValue(reminder.tag.name);
    query.addBindValue(reminder.tag.color.name());
    query.addBindValue(id);

    if (!query.exec()) {
        qWarning() << "Error: Unable to update reminder" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::clearRemindersTable()
{
    QSqlQuery query;

    if (query.exec("DROP TABLE IF EXISTS reminders")) {
        qDebug() << "Successfully dropped the reminders table.";
        return true;
    } else {
        qWarning() << "Error dropping the reminders table:" << query.lastError().text();
        return false;
    }
}

QList<QVariantMap> DatabaseManager::getAllReminders()
{
    QList<QVariantMap> reminders;

    QSqlQuery query("SELECT * FROM reminders");
    while (query.next()) {
        QVariantMap reminder;
        reminder["id"] = query.value("id").toInt();
        reminder["taskname"] = query.value("taskname").toString();
        reminder["description"] = query.value("description").toString();
        reminder["date"] = query.value("date").toDateTime();
        reminder["priority"] = static_cast<Priority>(query.value("priority").toInt());
        QVariantMap tag;
        tag["name"] = query.value("tag_name").toString();
        tag["color"] = QColor(query.value("tag_color").toString());
        reminder["Tag"] = tag;

        reminders.append(reminder);
    }

    return reminders;
}

const QSqlDatabase &DatabaseManager::database() const
{
    return _database;
}
