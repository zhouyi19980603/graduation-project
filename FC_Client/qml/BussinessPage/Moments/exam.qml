import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.1


Rectangle{
    Rectangle {
        id: rectangle
        x: 165
        y: 114
        color: "#f3f2f2"
        TextEdit{
            anchors.fill: parent
            text: qsTr("Hello World Mrs Zhou")
            selectionColor: "#891414"
        }
    }

}
