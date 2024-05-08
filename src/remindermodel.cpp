#include "remindermodel.h"
#include <QSqlQuery>
#include <QDebug>

using namespace DailyPlanner;

// Конструктор класса ReminderModel
ReminderModel::ReminderModel(DatabaseManager *manager, const QSqlDatabase &db, QObject *parent) :
    QSqlTableModel(parent, db), _manager(manager)
{
    // Установка таблицы для модели
    setTable("reminders");
    //     Сортировка по приоритету в порядке убывания при создании модели
    sortByPriority(Qt::DescendingOrder);

    // Фильтрация по приоритету All и текущей дате при создании модели
    filterByPriorityAndDate(Priority::All, QDate::currentDate());
    select();
}

void ReminderModel::filterByTag(const QString &tagName)
{
    _currentFilters.clear();
    _currentFilters.append(QString("tag_name='%1'").arg(tagName));
    //    _currentFilters.append(QString("ORDERED by priority, completed"));
    applyFilters();
}

void ReminderModel::filterByCriteria(Priority priority, const QDate &date, const QString &search)
{
    qDebug() << Q_FUNC_INFO;
    // Очистка текущих фильтров
    _currentFilters.clear();

    // Добавление фильтра по приоритету, если он задан
    if (priority != All) {
        _currentFilters.append(QString("priority='%1'").arg(QString::number(priority)));
    }

    // Добавление фильтра по дате, если она задана
    if (!date.isNull()) {
        _currentFilters.append(QString("date='%1'").arg(date.toString(Qt::ISODate)));
    }

    if (!search.isEmpty()) {
        _currentFilters.append(
         QString("taskname LIKE '%%1%' OR description LIKE '%%1%'").arg(search));
    }
    //    _currentFilters.append(QString("ORDERED by priority, completed"));

    // Применение фильтров
    applyFilters();
}

void ReminderModel::search(const QString &name)
{
    qDebug() << Q_FUNC_INFO;
    // Устанавливаем фильтр для модели
    QString filter =
     QString("taskname LIKE '%%1%' OR description LIKE '%%1%' OR tag LIKE '%%1%'").arg(name);
    setFilter(filter);
    select();
}

// Метод сортировки модели по приоритету
void ReminderModel::sortByPriority(Qt::SortOrder order)
{
    // Получаем индексы столбцов "priority" и "completed"
    int priorityColumn = record().indexOf("priority");
    //       int completedColumn = record().indexOf("completed");

    //       // Устанавливаем сортировку по этим двум столбцам и порядку
    setSort(priorityColumn, order);
    //       setSort(completedColumn, order);
}
// Метод фильтрации модели по приоритету и дате
void ReminderModel::filterByPriorityAndDate(Priority priority, const QDate &date)
{
    qDebug() << Q_FUNC_INFO;
    // Очистка текущих фильтров
    _currentFilters.clear();

    // Добавление фильтра по приоритету, если он задан
    if (priority != All) {
        _currentFilters.append(QString("priority='%1'").arg(QString::number(priority)));
    }

    // Добавление фильтра по дате, если она задана
    if (!date.isNull()) {
        _currentFilters.append(QString("date='%1'").arg(date.toString(Qt::ISODate)));
    }
    //    _currentFilters.append(QString("ORDERED by priority, completed"));

    // Применение фильтров
    applyFilters();
}
// Метод применения текущих фильтров к модели
void ReminderModel::applyFilters()
{
    qDebug() << Q_FUNC_INFO;
    QString filterString;
    // Соединяем все фильтры в одну строку
    if (_currentFilters.count() > 1)
        filterString = _currentFilters.join(" AND ");
    else
        filterString = _currentFilters.first();

    qDebug() << filterString;
    // Установка фильтра
    setFilter(filterString);
    select();
}
// Метод преобразования приоритета в цвет
QColor ReminderModel::mapPriorityToColor(const Priority priority) const
{
    switch (priority) {
    case Lowest:
        return QColor(0, 230, 0, 128); // Green
    case Low:
        return QColor(173, 216, 230, 128); // Light Blue
    case Medium:
        return QColor(230, 230, 0, 128); // Yellow
    case High:
        return QColor(230, 165, 0, 128); // Orange
    case Highest:
        return QColor(230, 0, 0, 128); // Red
    default:
        return QColor(255, 255, 255, 128); // Default to white
    }
}

// Метод фильтрации модели по указанному полю и значению
void ReminderModel::filterByField(const QString &field, const QVariant &value)
{
    qDebug() << Q_FUNC_INFO;
    // Установка фильтрации по заданному полю и значению
    setFilter(QString("%1='%2'").arg(field, value.toString()));

    // Отладочное сообщение с текущим запросом фильтрации
    qDebug() << selectStatement();

    // Выполнение запроса
    select();
}
// Переопределение метода получения данных из модели для обработки пользовательских ролей
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
    case Completed:
        return record.value("completed");
    case Id:
        return record.value("id");
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
    roles[Completed] = "completed";
    roles[Id] = "id";
    return roles;
}
