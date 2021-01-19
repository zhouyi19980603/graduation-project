import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Window 2.2
import "./"

ApplicationWindow{
    id: window
    visible: true
    width: 360
    height: 820
    color: "lightblue"
    title: qsTr("main ui")

    Rectangle {
        id: rectangle
        x: 24
        y: 69
        width: 313
        height: 136
        color: "#fce94f"

        Text {
            id: element
            x: 128
            y: 61
            text: qsTr("profile")
            font.pixelSize: 12
        }
    }

    Rectangle {
        id: rectangle1
        x: 15
        y: 211
        width: 331
        height: 39
        color: "#ffffff"

        Text {
            id: element1
            x: 116
            y: 12
            width: 36
            height: 19
            text: qsTr("Search")
            font.pixelSize: 12
        }
    }

    Rectangle {
        id: rectangle3
        x: 11
        y: 265
        width: 339
        height: 46
        color: "#ffffff"

        Button{
            x:15
            y:3
            width: 80;

            Text {
                id: element2
                x: 28
                y: 12
                text: qsTr("消息")
                font.pixelSize: 12
            }
        }
        Button{
            x:125
            y:3
            width: 80;

            Text {
                id: element3
                x: 20
                y: 19
                text: qsTr("好友")
                font.pixelSize: 12
            }
        }

        Button{
            x:238
            y:3
            width: 80;

            Text {
                id: element4
                x: 20
                y: 11
                text: qsTr("群组")
                font.pixelSize: 12
            }
        }
    }

    Rectangle {
        id: rectangle2
        x: 11
        y: 317
        width: 339
        height: 435
        color: "#ffffff"

        Text {
            id: element5
            x: 122
            y: 27
            width: 173
            height: 16
            text: qsTr("三个LISTVIEW")
            font.pixelSize: 12
        }
    }
}
