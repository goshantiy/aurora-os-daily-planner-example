import QtQuick 2.0
import Sailfish.Silica 1.0
import QtQuick.Layouts 1.1

Page {
    allowedOrientations: Orientation.All
    property string task
    property string date
    property color priority
    property string time
    property string description
    property string tag_name
    property string tag_color
    property string completed
    property int id
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
                    text: "Edit task"
                    onClicked: {
                        ReminderModel.updateReminder(
                                    id, taskName.text, taskDescription.text,
                                    buttondate.text, buttontime.text,
                                    priorityCb.currentIndex, tag.text,
                                    buttoncolor.backgroundColor)
                        pageStack.pop()
                    }
                }
            ]
        }

        Rectangle {
            Layout.alignment: Qt.AlignTop
            Layout.preferredHeight: 110
            Layout.fillWidth: true
            color: "transparent"
            TextField {
                anchors.fill: parent
                id: taskName
                property string placeholderText: task
                Text {
                    text: taskName.placeholderText
                    color: "#aaa"
                    visible: !taskName.text
                }
                text: task
            }
        }
        Rectangle {
            Layout.alignment: Qt.AlignTop
            Layout.preferredHeight: 110
            Layout.fillWidth: true
            color: "transparent"
            TextField {
                anchors.fill: parent
                id: taskDescription
                property string placeholderText: description
                Text {
                    text: taskDescription.placeholderText
                    color: "#aaa"
                    visible: !taskDescription.text
                }
                text: description
            }
        }
        RowLayout {
            Rectangle {
                Layout.alignment: Qt.AlignLeft
                Layout.preferredHeight: 130
                Layout.fillWidth: true
                color: "transparent"
                TextField {
                    anchors.fill: parent
                    id: tag
                    property string placeholderText: tag_name
                    Text {
                        text: tag.placeholderText
                        color: "#aaa"
                        visible: !tag.text
                    }
                    text: tag_name
                }
            }
            Button {
                id: buttoncolor
                text: "Tag color"
                Layout.preferredHeight: 100
                Layout.alignment: Qt.AlignRight
                onClicked: {
                    var dialog = pageStack.push(colorpickerComponent, {})
                    dialog.accepted.connect(function () {
                        backgroundColor = dialog.color
                    })
                }
                backgroundColor: tag_color

                Component {
                    id: colorpickerComponent
                    ColorPickerDialog {}
                }
            }
            Rectangle {
                width: 20
                color: "transparent"
            }
        }
        RowLayout {
            Button {
                id: buttondate
                text: date
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
                text: time
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
            currentIndex: priority
        }
        Rectangle {
            color: "transparent"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
