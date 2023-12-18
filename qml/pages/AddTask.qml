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
            Layout.fillWidth: true
            objectName: "pageHeader"
            extraContent.children: [
                Button {
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Add task"
                    onClicked: ReminderModel.addReminder(
                                   taskName.text, taskDescription.text,
                                   buttondate.text, buttontime.text,
                                   priorityCb.currentIndex, tag.text)
                }
            ]
        }

        Rectangle {
            Layout.alignment: Qt.AlignTop
            Layout.preferredHeight: 100
            Layout.fillWidth: true
            color: "transparent"
            TextField {
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
            color: "transparent"
            TextField {
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
        RowLayout {
            Rectangle {
                Layout.alignment: Qt.AlignLeft
                Layout.preferredHeight: 100
                Layout.fillWidth: true
                color: "transparent"
                TextField {
                    anchors.fill: parent
                    id: tag
                    property string placeholderText: "Tag"
                    Text {
                        text: tag.placeholderText
                        color: "#aaa"
                        visible: !tag.text
                    }
                }
            }
            Button {
                id: buttoncolor
                text: "Color"
                Layout.alignment: Qt.AlignRight
                Layout.fillWidth: true
                onClicked: {
                    var dialog = pageStack.push(colorpickerComponent, {})
                    dialog.accepted.connect(function () {
                        color = dialog.color
                    })
                }

                Component {
                    id: colorpickerComponent
                    ColorPickerDialog {}
                }
            }
        }
        RowLayout {
            Button {
                id: buttondate
                text: "Date"
                Layout.alignment: Qt.AlignLeft
                Layout.fillWidth: true
                onClicked: {
                    var dialog = pageStack.push(datepickerComponent, {
                                                    "date": new Date(buttondate.text)
                                                })
                    dialog.accepted.connect(function () {
                        buttondate.text = dialog.dateText
                    })
                }

                Component {
                    id: datepickerComponent
                    DatePickerDialog {}
                }
            }
            Button {
                id: buttontime
                text: "Time"
                Layout.alignment: Qt.AlignRight
                Layout.fillWidth: true
                onClicked: {
                    var dialog = pageStack.push(timepickerComponent)
                    dialog.accepted.connect(function () {
                        buttontime.text = dialog.timeText
                    })
                }

                Component {
                    id: timepickerComponent
                    TimePickerDialog {}
                }
            }
        }
        ComboBox {
            id: priorityCb
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
    }
}
