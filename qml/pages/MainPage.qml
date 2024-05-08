import QtQuick 2.0
import Sailfish.Silica 1.0
import QtQuick.Layouts 1.1

Page {
    objectName: "mainPage"
    allowedOrientations: Orientation.All
    ColumnLayout {
        anchors.fill: parent
        PageHeader {
            Layout.alignment: Qt.AlignTop
            objectName: "pageHeader"
            title: qsTr("Ежедневник")
            extraContent.children: [
                Button {
                    anchors.verticalCenter: parent.verticalCenter
                    width: 225
                    height: 80
                    onClicked: {
                        pageStack.push(Qt.resolvedUrl("AddTask.qml"))
                    }

                    icon.source: "image://theme/icon-cover-new"
                    text: qsTr("Добавить")
                    Layout.alignment: Qt.AlignHCenter
                }
            ]
        }
        RowLayout {
            height: 100
            TextField {
                id: taskNameField
                Layout.fillWidth: true
                placeholderText: qsTr("Введите фильтр")
            }
            IconButton {
                icon.source: "image://theme/icon-m-certificates"
                Layout.alignment: Qt.AlignRight
                onClicked: {
                    AppManager.model.filterByCriteria(
                                sortByPriorityCombo.currentIndex,
                                new Date(button.text), taskNameField.text)
                }
            }
        }
        RowLayout {
            ComboBox {
                Layout.alignment: Qt.AlignLeft
                width: 400
                label: "Приоритет"
                id: sortByPriorityCombo
                currentIndex: 5 // Устанавливаем "All" как значение по умолчанию
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
                    MenuItem {
                        text: "Все"
                    }
                }
            }
            Button {
                id: button
                Layout.alignment: Qt.AlignRight
                width: 200
                text: Qt.formatDate(new Date, "d MMM yyyy")
                onClicked: {
                    var dialog = pageStack.push(pickerComponent, {
                                                    "date": new Date(button.text)
                                                })
                    dialog.accepted.connect(function () {
                        button.text = dialog.dateText
                        AppManager.model.filterByPriorityAndDate(
                                    sortByPriorityCombo.currentIndex,
                                    new Date(button.text))
                    })
                }

                Component {
                    id: pickerComponent
                    DatePickerDialog {}
                }
            }
        }

        PlannerView {
            clip: true
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
