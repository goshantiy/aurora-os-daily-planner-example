#ifndef PRIORITYCOMPLETEDPROXY_H
#define PRIORITYCOMPLETEDPROXY_H
#include <QSortFilterProxyModel>
#include "remindermodel.h"
namespace DailyPlanner {
    class PriorityCompletedSortProxyModel : public QSortFilterProxyModel
    {
    public:
        PriorityCompletedSortProxyModel(QObject *parent = nullptr);

    protected:
        // Переопределение метода для сортировки по двум столбцам
        bool lessThan(const QModelIndex &left, const QModelIndex &right) const override
        {
            // Сравниваем приоритеты
            int leftPriority = sourceModel()->data(left).toInt();
            int rightPriority = sourceModel()->data(right).toInt();

            if (leftPriority != rightPriority)
                return leftPriority < rightPriority;

            // Если приоритеты равны, сравниваем статус выполнения
            QModelIndex leftCompletedIndex = sourceModel()->index(left.row(), 8, left.parent());
            QModelIndex rightCompletedIndex = sourceModel()->index(right.row(), 8, right.parent());

            bool leftCompleted = sourceModel()->data(leftCompletedIndex).toBool();
            bool rightCompleted = sourceModel()->data(rightCompletedIndex).toBool();

            return leftCompleted < rightCompleted;
        }
    };

    inline PriorityCompletedSortProxyModel::PriorityCompletedSortProxyModel(QObject *parent) :
        QSortFilterProxyModel(parent)
    {}

}

#endif // PRIORITYCOMPLETEDPROXY_H
