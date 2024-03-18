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
            Completed
        };

    public:
        explicit ReminderModel(DatabaseManager *manager,
                               const QSqlDatabase &db,
                               QObject *parent = nullptr);
        Q_INVOKABLE
        void addReminder(const QString &taskname,
                         const QString &description = {},
                         const QString &date = QDate::currentDate().toString(),
                         const QTime &time = QTime::currentTime(),
                         const int &priority = 0,
                         const QString &tag = {},
                         const QColor &color = "gray");
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
        QHash<int, QByteArray> roleNames() const override;
        void sortByPriority(Qt::SortOrder order);
        void sortByField(Qt::SortOrder order, int field);
        void filterByField(const QString &field, const QVariant &value);

        Q_INVOKABLE void filterByPriorityAndDate(Priority priority, const QDate &date);
        void applyFilters();

    private:
        QStringList _currentFilters;
        DatabaseManager *_manager { nullptr };
        QColor mapPriorityToColor(Priority priority) const;
    };
}

#endif // REMINDERMODEL_H
