import QtQuick 2.6
import Sailfish.Silica 1.0
Page {
    PageHeader {
        objectName: "pageHeader"
        title: qsTr("Daily planner")
    }
    objectName: "planner"
    allowedOrientations: Orientation.All
    DatePicker{
        id: calendar
    }
SilicaListView  {
      id: taskList
      anchors.fill: parent
      quickScroll: true

      model: ListModel {
          ListElement { fruit: "jackfruit" }
          ListElement { fruit: "orange" }
          ListElement { fruit: "lemon" }
          ListElement { fruit: "lychee" }
          ListElement { fruit: "apricots" }

      }
      delegate: Rectangle {
                  radius: 20
                  width: ListView.view.width
                  height: Theme.itemSizeSmall
                  color: "lightblue"
                  Label { text: fruit }
              }
      }
}
