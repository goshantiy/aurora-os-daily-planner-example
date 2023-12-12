import QtQuick 2.0
import Sailfish.Silica 1.0
import QtQuick.Layouts 1.1

Page {
    allowedOrientations: Orientation.All

    ColumnLayout {
        anchors.fill: parent
        spacing: 10
        PageHeader {
            Layout.alignment: Qt.AlignTop
            objectName: "pageHeader"
            title: qsTr("Add task")
        }

        Rectangle {
            Layout.alignment: Qt.AlignTop
            Layout.preferredHeight: 100
            Layout.fillWidth: true
            TextEdit {
                anchors.fill: parent
                id: taskName
                property string placeholderText: "Task name"
                Text {
                    text: taskName.placeholderText
                    color: "#aaa"
                    visible: !taskName.text
                }
            }
        }
        Rectangle {
            Layout.alignment: Qt.AlignTop
            Layout.preferredHeight: 100
            Layout.fillWidth: true
            TextEdit {
                anchors.fill: parent
                id: taskDescription
                property string placeholderText: "Task description"
                Text {
                    text: taskDescription.placeholderText
                    color: "#aaa"
                    visible: !taskDescription.text
                }
            }
        }
        ComboBox {
            label: "Priority"
            Layout.alignment: Qt.AlignTop
            menu: ContextMenu {
                MenuItem {
                    text: "Lowest"
                }
                MenuItem {
                    text: "Low"
                }
                MenuItem {
                    text: "Medium"
                }
                MenuItem {
                    text: "High"
                }
                MenuItem {
                    text: "Highest"
                }
            }
        }
        Rectangle {
            color: "transparent"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        IconButton {
            Layout.alignment: Qt.AlignHCenter
            icon.source: "image://theme/icon-l-add"
        }
    }
}
