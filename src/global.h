#ifndef GLOBAL_H
#define GLOBAL_H
#include <QString>
#include <QDateTime>
#include <QColor>
#include <QObject>

enum Priority
{
    Lowest,
    Low,
    Medium,
    High,
    Highest
};
Q_DECLARE_METATYPE(Priority)
struct Tag
{
    QString name;
    QColor color { "gray" };
};
Q_DECLARE_METATYPE(Tag)
struct Reminder
{
    QString taskname;
    QString description;
    QDate date;
    QTime time;
    Priority priority;
    Tag tag;
};
Q_DECLARE_METATYPE(Reminder)

#endif // GLOBAL_H
