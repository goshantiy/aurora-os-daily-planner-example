#include "remindermodel.h"

ReminderModel::ReminderModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void ReminderModel::addReminder(const QString &task, Priority priority, const QDateTime &date)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_reminders.append({task, date, priority});
    endInsertRows();
}

int ReminderModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_reminders.size();
}

QVariant ReminderModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const Reminder &reminder = m_reminders.at(index.row());

    switch (role) {
    case TaskRole:
        return reminder.task;
    case DateRole:
        return reminder.date;
    case PriorityRole:
        return reminder.priority;
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
    return roles;
}
