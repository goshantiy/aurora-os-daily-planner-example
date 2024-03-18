import QtQuick 2.0
import QtQuick.Layouts 1.1
import Sailfish.Silica 1.0

SilicaListView {
    id: taskList
    model: ReminderModel
    quickScroll: true
    spacing: 5

    delegate: Rectangle {
        id: rec
        height: 100
        width: parent.width - 20
        radius: 20
        anchors.horizontalCenter: parent.horizontalCenter
        color: model.priority

        ColumnLayout {
            Label {
                topPadding: 10
                leftPadding: 10
                text: model.task
                color: "white"
                font.family: Theme.fontFamilyHeading
                font.pixelSize: Theme.fontSizeMedium
                font.weight: "Bold"
                wrapMode: Label.WordWrap
            }
            RowLayout {
                Rectangle {
                    Layout.preferredWidth: 10
                    Layout.preferredHeight: 20
                    color: "transparent"
                    radius: 3
                }
                Rectangle {
                    Layout.preferredWidth: 80
                    Layout.preferredHeight: 25
                    color: model.tag_color
                    radius: 3
                }
                Label {
                    text: model.description
                    color: "white"
                    font.pixelSize: Theme.fontSizeSmall
                    font.family: Theme.fontFamily
                    wrapMode: Label.WordWrap
                }
            }
        }
        Rectangle {
            height: 100
            width: 100
            color: "transparent"
            anchors {
                verticalCenter: parent.verticalCenter
                right: check.left
            }
            IconButton {
                height: 60
                id: next
                anchors.top: parent.top
                icon.source: "image://theme/icon-cover-next"
            }

            Label {
                text: "edit"
                anchors.top: next.bottom
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
        IconButton {
            id: check
            anchors {
                verticalCenter: parent.verticalCenter
                right: parent.right
            }
            icon.source: "image://theme/icon-l-check"
            onClicked: {
                model.completed = !model.completed
            }
        }
    }
}
