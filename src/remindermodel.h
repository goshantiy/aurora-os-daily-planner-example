#ifndef REMINDERMODEL_H
#define REMINDERMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <QDateTime>

class ReminderModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum ReminderRoles {
        TaskRole = Qt::UserRole + 1,
        DateRole,
        PriorityRole,
    };

    explicit ReminderModel(QObject *parent = nullptr);

    void addReminder(const QString &task, const QDateTime &date = QDateTime::currentDateTime(), const QString &priority = "test");

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    struct Reminder {
        QString task;
        QDateTime date;
        QString priority;
        // Add more properties as needed
    };

    QList<Reminder> m_reminders;
};

#endif // REMINDERMODEL_H
