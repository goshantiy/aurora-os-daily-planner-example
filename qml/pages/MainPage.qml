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
            title: qsTr("Daily Planner")
            extraContent.children: [
                IconButton {
                    objectName: "add"
                    icon.source: "image://theme/icon-cover-new"
                    anchors.verticalCenter: parent.verticalCenter
                    onClicked: pageStack.push(Qt.resolvedUrl("AddTask.qml"))
                }
            ]
        }
        RowLayout {
            ComboBox {
                Layout.alignment: Qt.AlignLeft
                width: 400
                label: "Priority"
                id: sortByPriorityCombo
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
                    MenuItem {
                        text: "All"
                    }
                }
                //                currentIndex: 5
            }
            Button {
                id: button
                Layout.alignment: Qt.AlignRight
                width: 200
                text: Qt.formatDate(new Date, "dd MMM yyyy")
                onClicked: {
                    var dialog = pageStack.push(pickerComponent, {
                                                    "date": new Date(button.text)
                                                })
                    dialog.accepted.connect(function () {
                        button.text = dialog.dateText
                    })
                }

                Component {
                    id: pickerComponent
                    DatePickerDialog {}
                }
            }
        }
        Button {
            text: "Apply Filter"
            Layout.alignment: Qt.AlignHCenter
            onClicked: {
                ReminderModel.filterByPriorityAndDate(
                            sortByPriorityCombo.currentIndex,
                            new Date(button.text))
            }
        }

        PlannerView {
            clip: true
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
