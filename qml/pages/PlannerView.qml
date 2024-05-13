import QtQuick 2.0
import QtQuick.Layouts 1.1
import Sailfish.Silica 1.0

SilicaListView {
    id: taskList
    model: AppManager.model
    quickScroll: true
    spacing: 10

    delegate: RowLayout {
        height: 100
        width: parent.width
        Rectangle {
            id: rec
            height: 100
            width: parent.width - 100
            radius: 20
            color: model.priority
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    pageStack.push(Qt.resolvedUrl("TaskDescription.qml"), {
                                       "task": model.task,
                                       "date": model.date,
                                       "priority": model.priority,
                                       "time": model.time,
                                       "description": model.description,
                                       "tag_name": model.tag_name,
                                       "tag_color": model.tag_color,
                                       "completed": model.completed,
                                       "id": model.id
                                   })
                }
            }

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
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                AppManager.model.filterByTag(model.tag_name)
                            }
                        }
                    }

                    Label {
                        id: name_label
                        text: model.tag_name
                        color: "white"
                        font.pixelSize: Theme.fontSizeSmall
                        font.family: Theme.fontFamily
                        wrapMode: Label.WordWrap
                    }
                    //                    MouseArea {
                    //                        z: 1
                    //                        anchors.fill: name_label
                    //                        onClicked: {
                    //                            pageStack.push(Qt.resolvedUrl("EditTask.qml"), {
                    //                                               "task": model.task,
                    //                                               "date": Qt.formatDate(
                    //                                                           new Date(model.date),
                    //                                                           "d MMM yyyy"),
                    //                                               "priority": model.priority,
                    //                                               "time": model.time,
                    //                                               "descriptionTask": model.description,
                    //                                               "tag_name": model.tag_name,
                    //                                               "tag_color": model.tag_color,
                    //                                               "completed": model.completed
                    //                                           })
                    //                        }
                    //                    }
                }
            }
            Rectangle {
                height: parent.height
                width: 100
                color: "transparent"
                anchors {
                    verticalCenter: parent.verticalCenter
                    right: parent.right
                }
                IconButton {
                    height: 70
                    id: next
                    anchors.top: parent.top
                    icon.source: "image://theme/icon-cover-next"
                    onClicked: {
                        pageStack.push(Qt.resolvedUrl("EditTask.qml"), {
                                           "task": model.task,
                                           "date": Qt.formatDate(
                                                       new Date(model.date),
                                                       "d MMM yyyy"),
                                           "priority": model.priority,
                                           "time": model.time,
                                           "descriptionTask": model.description,
                                           "tag_name": model.tag_name,
                                           "tag_color": model.tag_color,
                                           "completed": model.completed,
                                           "id": model.id
                                       })
                    }
                }

                Label {
                    text: "изменить"
                    font.pixelSize: 20
                    anchors.top: next.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }
        Rectangle {
            radius: 20
            height: 100
            width: 100
            id: check
            anchors {
                verticalCenter: parent.verticalCenter
                right: parent.right
            }
            color: model.completed ? "green" : "transparent"
            IconButton {
                icon.source: "image://theme/icon-l-check"
                highlighted: model.completed
                onClicked: {
                    AppManager.model.setCompleted(model.id, !model.completed)
                }
            }
        }
    }
}
