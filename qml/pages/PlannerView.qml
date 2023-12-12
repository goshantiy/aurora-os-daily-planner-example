import QtQuick 2.0
import QtQuick.Layouts 1.1
import Sailfish.Silica 1.0

SilicaListView {
    id: taskLis
    model: ReminderModel
    quickScroll: true
    spacing: 5

    delegate: Rectangle {
        id: rec
        height: 100
        width: parent.width - 20
        anchors.horizontalCenter: parent.horizontalCenter
        color: {
            switch (model.priority) {
            case 0:
                color = Qt.rgba(176 / 255, 68 / 255, 68 / 255, 0.9)
                break
            case 1:
                color = Qt.rgba(33 / 255, 33 / 255, 49 / 255, 0.9)
                break
            case 2:
                color = Qt.rgba(176 / 255, 127 / 255, 0, 0.9)
                break
            case 3:
                color = Qt.rgba(176 / 255, 68 / 255, 68 / 255, 0.5)
            }
        }
        ColumnLayout {
            Label {
                topPadding: 10
                leftPadding: 10
                text: model.task
                color: "white"
                font.pointSize: ((rec.height / 5) + (rec.width / 10)) / 5
                font.weight: "DemiBold"
                font.family: "OpenSans"
                wrapMode: Label.WordWrap
            }
            RowLayout {
                Text {
                    text: model.date.toLocaleString()
                    color: "white"
                    font.pixelSize: 24
                    font.family: "OpenSans"
                }
            }
        }
    }
}
