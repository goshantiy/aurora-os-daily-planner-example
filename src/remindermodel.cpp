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

    qDebug() << _manager->getAllReminders();

    //     Сортировка по приоритету в порядке убывания при создании модели
    sortByPriority(Qt::DescendingOrder);

    // Фильтрация по приоритету All и текущей дате при создании модели
    filterByPriorityAndDate(Priority::All, QDate::currentDate());
    select();
}

// Метод добавления напоминания в базу данных
void ReminderModel::addReminder(const QString &task,
                                const QString &description,
                                const QString &date,
                                const QTime &time,
                                const int &priority,
                                const QString &tag,
                                const QColor &color)
{
    // Преобразование строки с датой в QDate
    QDate dateFromStr = QDate::fromString(date, "dd MMM yyyy");

    // Добавление напоминания через менеджер базы данных
    _manager->addReminder(
     { task, description, dateFromStr, time, static_cast<Priority>(priority), { tag, color } });
    //     Пересортировка модели по приоритету после добавления напоминания
    sortByPriority(Qt::DescendingOrder);
    //    applyFilters();
}

// Метод изменения напоминания в базе данных
void ReminderModel::updateReminder(int id,
                                   const QString &task,
                                   const QString &description,
                                   const QString &date,
                                   const QTime &time,
                                   const int &priority,
                                   const QString &tag,
                                   const QColor &color)
{
    // Преобразование строки с датой в QDate
    QDate dateFromStr = QDate::fromString(date, "dd MMM yyyy");

    // Добавление напоминания через менеджер базы данных
    _manager->updateReminder(
     id, { task, description, dateFromStr, time, static_cast<Priority>(priority), { tag, color } });
    select();
}

void ReminderModel::setCompleted(int id, bool completed)
{
    _manager->setCompleted(id, completed);
    select();
}

// Метод сортировки модели по приоритету
void ReminderModel::sortByPriority(Qt::SortOrder order)
{
    // Получаем индекс столбца "priority"
    int priorityColumn = record().indexOf("priority");

    // Устанавливаем сортировку по этому столбцу и порядку
    setSort(priorityColumn, order);
}
// Метод фильтрации модели по приоритету и дате
void ReminderModel::filterByPriorityAndDate(Priority priority, const QDate &date)
{
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

    // Применение фильтров
    applyFilters();
}
// Метод применения текущих фильтров к модели
void ReminderModel::applyFilters()
{
    // Соединяем все фильтры в одну строку
    QString filterString = _currentFilters.join(" AND ");

    // Установка фильтра
    setFilter(filterString);
    select();
}
// Метод преобразования приоритета в цвет
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

// Метод сортировки модели по указанному полю и порядку
void ReminderModel::sortByField(Qt::SortOrder order, int field)
{
    // Установка сортировки по заданному полю и порядку
    setSort(field, order);

    // Отладочное сообщение с текущим запросом сортировки
    qDebug() << selectStatement();

    // Выполнение запроса
    select();
}

// Метод фильтрации модели по указанному полю и значению
void ReminderModel::filterByField(const QString &field, const QVariant &value)
{
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
