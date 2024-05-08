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
    public:
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



        Q_INVOKABLE void filterByPriorityAndDate(Priority priority, const QDate &date);

        Q_INVOKABLE void filterByTag(const QString &tagName);

        Q_INVOKABLE void search(const QString &name);

        Q_INVOKABLE void
        filterByCriteria(Priority priority, const QDate &date, const QString &search);

    private:
        void applyFilters();
        QStringList _currentFilters;
        DatabaseManager *_manager { nullptr };
        QColor mapPriorityToColor(Priority priority) const;
    };
}

#endif // REMINDERMODEL_H
