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
            title: "Добавить"
            extraContent.children: [
                Button {
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Добавить"
                    onClicked: {
                        AppManager.manager.addReminder(
                                    taskName.text, taskDescription.text,
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
                property string placeholderText: "Имя"
                Text {
                    text: taskName.placeholderText
                    color: "#aaa"
                    visible: !taskName.text
                }
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
                property string placeholderText: "Описание"
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
                Layout.preferredHeight: 130
                Layout.fillWidth: true
                color: "transparent"
                TextField {
                    anchors.fill: parent
                    id: tag
                    property string placeholderText: "Тэг"
                    Text {
                        text: tag.placeholderText
                        color: "#aaa"
                        visible: !tag.text
                    }
                }
            }
            Button {
                id: buttoncolor
                text: "Цвет тэга"
                Layout.preferredHeight: 100
                Layout.alignment: Qt.AlignRight
                onClicked: {
                    var dialog = pageStack.push(colorpickerComponent, {})
                    dialog.accepted.connect(function () {
                        backgroundColor = dialog.color
                    })
                }

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
                text: "Дата"
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
                text: "Время"
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
            label: "Приоритет"
            Layout.alignment: Qt.AlignTop
            menu: ContextMenu {
                MenuItem {
                    text: "Самый низкий"
                }
                MenuItem {
                    text: "Низкий"
                }
                MenuItem {
                    text: "Средний"
                }
                MenuItem {
                    text: "Высокий"
                }
                MenuItem {
                    text: "Самый высокий"
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
