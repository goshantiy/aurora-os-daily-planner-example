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
                    objectName: "aboutButton"
                    icon.source: "image://theme/icon-m-about"
                    anchors.verticalCenter: parent.verticalCenter
                    onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
                },
                IconButton {
                    objectName: "add"
                    icon.source: "image://theme/icon-cover-new"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    onClicked: pageStack.push(Qt.resolvedUrl("AddTask.qml"))
                }
            ]
        }
        Button {
            id: button
            text: Qt.formatDate(new Date, "dd MMM yyyy")
            Layout.alignment: Qt.AlignHCenter

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

        PlannerView {
            clip: true
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
