#ifndef REMINDERMODEL_H
#define REMINDERMODEL_H

#include <QSqlTableModel>
#include <QSqlRecord>
#include <QObject>
#include <QDateTime>
#include "databasemanager.h"
#include "global.h"

namespace DailyPlanner {
    class ReminderModel : public QSqlTableModel
    {
        Q_OBJECT

        enum ReminderRoles
        {
            TaskRole = Qt::UserRole + 1,
            DateRole,
            TimeRole,
            DescriptionRole,
            PriorityRole,
            TagRole,
            TagColor,
            Completed,
            Id
        };

    public:
        explicit ReminderModel(DatabaseManager *manager,
                               const QSqlDatabase &db,
                               QObject *parent = nullptr);

        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
        QHash<int, QByteArray> roleNames() const override;
        void sortByPriority(Qt::SortOrder order);
        void sortByField(Qt::SortOrder order, int field);
        void filterByField(const QString &field, const QVariant &value);

        Q_INVOKABLE
        void addReminder(const QString &taskname,
                         const QString &description = {},
                         const QString &date = QDate::currentDate().toString(),
                         const QTime &time = QTime::currentTime(),
                         const int &priority = 0,
                         const QString &tag = {},
                         const QColor &color = "gray");

        Q_INVOKABLE void filterByPriorityAndDate(Priority priority, const QDate &date);

        Q_INVOKABLE void updateReminder(int id,
                                        const QString &task,
                                        const QString &description,
                                        const QString &date,
                                        const QTime &time,
                                        const int &priority,
                                        const QString &tag,
                                        const QColor &color);
        Q_INVOKABLE void setCompleted(int id, bool completed);

        Q_INVOKABLE void filterByTag(const QString& tagName);

    private:
        void applyFilters();
        QStringList _currentFilters;
        DatabaseManager *_manager { nullptr };
        QColor mapPriorityToColor(Priority priority) const;
    };
}

#endif // REMINDERMODEL_H
