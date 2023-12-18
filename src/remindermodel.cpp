#include "remindermodel.h"
#include <QSqlQuery>
#include <QDebug>
/// TO DO
/// QML INTEGRATION
/// APPLICATION FOR USING THIS COMPONENTS
/// TAGS

using namespace DailyPlanner;

ReminderModel::ReminderModel(DatabaseManager *manager, const QSqlDatabase &db, QObject *parent) :
    QSqlTableModel(parent, db), _manager(manager)
{
    setTable("reminders");
    sortByPriority(Qt::DescendingOrder);
}

void ReminderModel::addReminder(const QString &task,
                                const QString &description,
                                const QString &date,
                                const QTime &time,
                                const int &priority,
                                const QString &tag,
                                const QColor& color)
{
    QDate dateFromStr = QDate::fromString(date, "dd MMM yyyy");
    _manager->addReminder(
     { task, description, dateFromStr, time, static_cast<Priority>(priority), { tag, color } });
    sortByPriority(Qt::DescendingOrder);
}

void ReminderModel::sortByDate(const QString &dateStr)
{
    setFilter(QString("Date='%1'").arg(dateStr));
    select();
}

void ReminderModel::sortByPriority(Qt::SortOrder order)
{
    QSqlQuery query;
    if (order == Qt::AscendingOrder)
        query.prepare("SELECT * FROM reminders ORDER BY priority ASC");
    else
        query.prepare("SELECT * FROM reminders ORDER BY priority DESC");
    if (query.exec()) {
        setQuery(query);
        return;
    }
}

void ReminderModel::filterByPriority(Priority priority)
{
    setFilter(QString("Priority='%1'").arg(QString::number(priority)));
    select();
}
QColor ReminderModel::mapPriorityToColor(const Priority priority) const
{
    switch (priority) {
    case Lowest:
        return QColor(0, 255, 0); // Green
    case Low:
        return QColor(173, 216, 230); // Light Blue
    case Medium:
        return QColor(255, 255, 0); // Yellow
    case High:
        return QColor(255, 165, 0); // Orange
    case Highest:
        return QColor(255, 0, 0); // Red
    default:
        return QColor(255, 255, 255, 255); // Default to white
    }
}

QVariant ReminderModel::data(const QModelIndex &index, int role) const
{
    if (role < Qt::UserRole)
        return QSqlTableModel::data(index, role);

    QSqlRecord record = QSqlTableModel::record(index.row());

    switch (role) {
    case TaskRole:
        return record.value("taskname");
    case DateRole:
        return record.value("date");
    case TimeRole:
        return record.value("time");
    case DescriptionRole:
        return record.value("description");
    case TagRole:
        return record.value("tag_name");
    case TagColor:
        return record.value("tag_color");
    case PriorityRole:
        return mapPriorityToColor(record.value("priority").value<Priority>());
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> ReminderModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TaskRole] = "task";
    roles[DateRole] = "date";
    roles[PriorityRole] = "priority";
    roles[TimeRole] = "time";
    roles[DescriptionRole] = "description";
    roles[TagRole] = "tag_name";
    roles[TagColor] = "tag_color";
    return roles;
}
