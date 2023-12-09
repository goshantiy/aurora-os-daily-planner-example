import QtQuick 2.0
import QtQuick.Layouts 1.1
import Sailfish.Silica 1.0

SilicaListView {

    id: taskList
    model: ReminderModel

       delegate: Item {
           width: reminderListView.width
           height: 50

           Rectangle {
               width: parent.width
               height: 50
               color: "lightblue"

               RowLayout {
                   anchors.fill: parent

                   Text {
                       text: model.task
                       Layout.alignment: Qt.AlignLeft
                   }

                   Text {
                       text: model.date.toLocaleString()
                       Layout.alignment: Qt.AlignCenter
                   }

                   Text {
                       text: model.priority
                       Layout.alignment: Qt.AlignRight
                   }
               }
           }
       }
}
