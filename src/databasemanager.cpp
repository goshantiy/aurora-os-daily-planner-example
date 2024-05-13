#include "databasemanager.h"
#include <QDebug>
#include <QVariantMap>
#include <QDateTime>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

using namespace DailyPlanner;

// Конструктор
DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent)
{}

// Метод для открытия базы данных
bool DatabaseManager::openDatabase()
{
    // Установка типа базы данных и пути к базе данных
    _database = QSqlDatabase::addDatabase("QSQLITE");
    _database.setDatabaseName("plannerDB.db");

    // Проверка на успешное открытие базы данных
    if (!_database.open()) {
        qWarning() << "Error: Unable to open database" << _database.lastError().text();
        return false;
    }
    qWarning() << _database.databaseName();
    qDebug() << getAllReminders();

    // Создание таблицы, если она не существует
    createTable();

    return true;
}

// Метод для закрытия базы данных
void DatabaseManager::closeDatabase()
{
    _database.close();
}

// Метод для создания таблицы reminders
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
                    "tag_name INTEGER, "
                    "tag_color INTEGER, "
                    "completed INTEGER)")) {
        qWarning() << "Error: Unable to create table" << query.lastError().text();
        return false;
    }

    if (!query.exec("CREATE TABLE IF NOT EXISTS tag ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "tag_name TEXT,"
                    "tag_color TEXT)")) {
        qWarning() << "Error: Unable to create table" << query.lastError().text();
        return false;
    }

    return true;
}

// Метод для добавления напоминания в базу данных
bool DatabaseManager::addReminder(const QString &task,
                                  const QString &description,
                                  const QString &date,
                                  const QTime &time,
                                  const int &priority,
                                  const QString &tag,
                                  const QColor &color)
{
    QDate dateFromStr = QDate::fromString(date, "d MMM yyyy");

    Reminder reminder {
        task, description, dateFromStr, time, static_cast<Priority>(priority), { tag, color }
    };

    // Проверка существует ли тег в базе данных
    QSqlQuery checkTagQuery;
    checkTagQuery.prepare("SELECT id FROM tag WHERE tag_name = ? AND tag_color = ?");
    checkTagQuery.addBindValue(reminder.tag.name);
    checkTagQuery.addBindValue(reminder.tag.color.name());
    if (!checkTagQuery.exec()) {
        qWarning() << "Error: Unable to check tag" << checkTagQuery.lastError().text();
        return false;
    }

    int tagId;
    if (checkTagQuery.next()) {
        // Тег уже существует, получаем его id
        tagId = checkTagQuery.value(0).toInt();
    } else {
        // Тег не существует, добавляем его и получаем его id
        QSqlQuery addTagQuery;
        addTagQuery.prepare("INSERT INTO tag (tag_name, tag_color) VALUES (?, ?)");
        addTagQuery.addBindValue(reminder.tag.name);
        addTagQuery.addBindValue(reminder.tag.color.name());
        if (!addTagQuery.exec()) {
            qWarning() << "Error: Unable to add tag" << addTagQuery.lastError().text();
            return false;
        }
        tagId = addTagQuery.lastInsertId().toInt();
    }

    QSqlQuery query;
    query.prepare("INSERT INTO reminders (taskname, description, date, time, priority, tag_name, "
                  "tag_color, completed) VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(reminder.taskname);
    query.addBindValue(reminder.description);
    query.addBindValue(reminder.date.toString(Qt::ISODate));
    query.addBindValue(reminder.time);
    query.addBindValue(static_cast<int>(reminder.priority));
    query.addBindValue(tagId); // Используем полученный id тега
    query.addBindValue(tagId); // Используем полученный id тега
    query.addBindValue(0); // Изначально напоминание не завершено

    if (!query.exec()) {
        qWarning() << "Error: Unable to add reminder" << query.lastError().text();
        return false;
    }

    return true;
}

// Метод для установки статуса завершенности напоминания по его идентификатору
bool DatabaseManager::setCompleted(int id, bool completed)
{
    QSqlQuery query;
    query.prepare("UPDATE reminders SET completed = ? WHERE id = ?");
    query.addBindValue(completed ? 1 : 0);
    query.addBindValue(id);
    if (!query.exec()) {
        qWarning() << "Error: Unable to set complete reminder" << query.lastError().text();
        return false;
    }

    return true;
}
// Метод для обновления информации о напоминании по его идентификатору
bool DatabaseManager::updateReminder(int id,
                                     const QString &task,
                                     const QString &description,
                                     const QString &date,
                                     const QTime &time,
                                     const int &priority,
                                     const QString &tag,
                                     const QColor &color)
{
    QDate dateFromStr = QDate::fromString(date, "d MMM yyyy");
    Reminder reminder {
        task, description, dateFromStr, time, static_cast<Priority>(priority), { tag, color }
    };
    QSqlQuery query;
    query.prepare("UPDATE reminders SET taskname = ?, description = ?, date = ?, time = ?, "
                  "priority = ?, tag_name = ?, tag_color = ? WHERE id = ?");
    query.addBindValue(reminder.taskname);
    query.addBindValue(reminder.description);
    query.addBindValue(reminder.date.toString(Qt::ISODate));
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
// Метод для очистки таблицы reminders
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
// Метод для получения всех напоминаний из таблицы reminders
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
// Метод для получения объекта базы данных
const QSqlDatabase &DatabaseManager::database() const
{
    return _database;
}
