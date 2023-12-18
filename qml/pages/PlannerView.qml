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

        //        objectName: "infoLabel"
        //        wrapMode: Text.Wrap
        //        horizontalAlignment: Text.AlignHCenter
        //        color: palette.secondaryHighlightColor
        //        font {
        //            pixelSize: Theme.fontSizeExtraLarge
        //            family: Theme.fontFamilyHeading
        //        }
        //        anchors {
        //            left: parent.left; right: parent.right
        //            margins: Theme.horizontalPageMargin
        //        }
        //    }
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
                    //                    Text {
                    //                        text: model.tag_name
                    //                        font.pointSize: 15
                    //                    }
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
    }
}
