#include "dailyplannerapp.h"

using namespace DailyPlanner;
DailyPlannerApp::DailyPlannerApp(QObject *parent) : QObject(parent)
{
    _manager = new DatabaseManager(this);
    _manager->openDatabase();
//    _manager->clearRemindersTable();
    _model = new ReminderModel(_manager, _manager->database(), this);
}

ReminderModel *DailyPlannerApp::model() const
{
    return _model;
}

void DailyPlannerApp::setModel(ReminderModel *newModel)
{
    _model = newModel;
}

DatabaseManager *DailyPlannerApp::manager() const
{
    return _manager;
}

void DailyPlannerApp::setManager(DatabaseManager *newManager)
{
    _manager = newManager;
}
