#include "dailyplannerapp.h"

using namespace DailyPlanner;
DailyPlannerApp::DailyPlannerApp(QObject *parent) : QObject(parent)
{
    _manager = new DatabaseManager(this);
    _manager->openDatabase();
    _proxy = new PriorityCompletedSortProxyModel(this);
    _model = new ReminderModel(_manager, _manager->database(), this);
}

PriorityCompletedSortProxyModel *DailyPlannerApp::proxy() const
{
    return _proxy;
}

DatabaseManager *DailyPlannerApp::manager() const
{
    return _manager;
}

void DailyPlannerApp::setManager(DatabaseManager *newManager)
{
    if (_manager == newManager)
        return;
    _manager = newManager;
    emit managerChanged();
}

ReminderModel *DailyPlannerApp::model() const
{
    return _model;
}

void DailyPlannerApp::setModel(ReminderModel *newModel)
{
    if (_model == newModel)
        return;
    _model = newModel;
    emit modelChanged();
}

void DailyPlannerApp::setProxy(PriorityCompletedSortProxyModel *newProxy)
{
    if (_proxy == newProxy)
        return;
    _proxy = newProxy;
    emit proxyChanged();
}
