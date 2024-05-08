import QtQuick 2.0
import Sailfish.Silica 1.0
import QtQuick.Layouts 1.1

Page {
    allowedOrientations: Orientation.All
    property string task
    property string date
    property color priorityColor
    property string time
    property string description
    property string tag_name
    property color tag_color
    property string completed
    property int id
    ColumnLayout {
        anchors.fill: parent
        spacing: 10
        PageHeader {
            Layout.alignment: Qt.AlignTop
            Layout.fillWidth: true
            title: "Детали"
        }

        Label {
            Layout.alignment: Qt.AlignTop
            Layout.fillWidth: true
            text: "Задача: " + task
            wrapMode: Text.Wrap
        }
        Rectangle {
            height: 1
            width: parent.width
            color: "white"
        }
        Label {
            Layout.alignment: Qt.AlignTop
            Layout.fillWidth: true
            text: "Описание: " + description
            wrapMode: Text.Wrap
        }
        Rectangle {
            height: 1
            width: parent.width
            color: "white"
        }
        Label {
            Layout.alignment: Qt.AlignTop
            Layout.fillWidth: true
            text: "Tag: " + tag_name
            color: tag_color
        }
        Rectangle {
            height: 1
            width: parent.width
            color: "white"
        }
        Label {
            Layout.alignment: Qt.AlignTop
            Layout.fillWidth: true
            text: "Дата: " + date
        }
        Rectangle {
            height: 1
            width: parent.width
            color: "white"
        }
        Label {
            Layout.alignment: Qt.AlignTop
            Layout.fillWidth: true
            text: "Время: " + time
        }
        Rectangle {
            height: 1
            width: parent.width
            color: "white"
        }
        Label {
            Layout.alignment: Qt.AlignTop
            Layout.fillWidth: true
            text: completed ? "Завершено: да" : "Завершено: нет"
        }
    }
}
