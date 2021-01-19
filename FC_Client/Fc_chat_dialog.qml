import QtQuick 2.12
import QtQuick.Controls 2.12
//import CppModel 1.0
ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    color: "lightblue"
    title: qsTr("Chat Dialog")
    Button {
        id: button
        x: 468
        y: 296
        text: qsTr("send")
        MouseArea {
            id: mouseArea
            anchors.fill: parent
            onClicked: {
                if (textEdit.text.length){
                    message_listModel.add([profile.account,"1","1",textEdit.text])
//                    message_listView.positionViewAtEnd()

                    message_listView.currentIndex = message_listView.count - 1
                    textEdit.clear()
                    console.log("send!")
                }
            }
        }
    }

    Connections{
        target: message_listModel
        onRecv_mess:{
//             message_listView.positionViewAtEnd()
//            message_listView.atYEnd
//            message_listView.forceLayout()
message_listView.currentIndex = message_listView.count - 1
        }
    }

    Button {
        id: button1
        x: 468
        y: 354
        text: qsTr("close")
        MouseArea {
            id: mouseArea1
            anchors.fill: parent
            onClicked: window.close()
        }
    }
    TextEdit {
        id: textEdit
        x: 62
        y: 326
        width: 311
        height: 106
        text: "123"
        font.pixelSize: 12
    }


    Component{
        id:message_listDelegate
        Rectangle {
            color: "green"
            radius: 5
            width: message_listView.width
            height: 50
            Rectangle{
                id:writerrect
                width: 25
                height: width/2
                color: "red"
                Text {
                    anchors.centerIn: parent
                    width: parent.width
                    clip: true
                    id: writertext
                    text: writer
                }
            }
            Rectangle{
                id:headimgrect
                anchors.left: writerrect.left
                anchors.top: writerrect.bottom
                width: writerrect.width
                height: width
                radius: width/2
                color: "blue"
            }
            Rectangle{
                id:contentimg
                anchors.left: headimgrect.right
                anchors.verticalCenter: headimgrect.verticalCenter
                height: headimgrect.height
                width: height*2
                color: "pink"
                Text {
                    text: content
                }
            }
        }
    }
    ListView{
        id:message_listView
        x:0
        y:0
        width: parent.width
        height: 200
        model: message_listModel
        delegate: message_listDelegate
    }
}
