import QtQuick 2.0
import QtQuick.Controls 2.0
import "./qml/Component"
ApplicationWindow{
    id: window
    visible: true
    width: 640
    height: 480
    color: "lightblue"
    title: qsTr("Logup Dialog")

//    TextInput{
//        id: textinput
//        x: 134
//        y: 189
//        width: 142
//        height: 26
//       // inputMethodHints: "enter your account"
//        text: qsTr("")
//        font.pixelSize: 12
//        focus: true
//        validator: IntValidator{top:999999;bottom: 111111}
//    }
//    Label {
//        id: label
//        x: 134
//        y: 156
//        width: 135
//        height: 21
//        text: qsTr("enter your count:")
//    }
//    Button {
//        id: button
//        x: 382
//        y: 283
//        text: qsTr("log_up")
//        onClicked: {
//            if(textinput.text.length!=0){
//                console.log(textinput.text+"log ups");
//                profile.set_account(textinput.text)
//                console.log(profile.account);
//                chat_dialog.visible = true;
//                window.visible = false;
//            }
//        }
//    }
//    Fc_chat_dialog{
//        id: chat_dialog
//        visible: false
//    }

    Constant { id: constant }
    Rectangle{
        id:chatFileREctangleLeft
        border.width: 1
        border.color: "#ccc"
        anchors.left: parent.left
        height: 70
        color: "white"
        width: 250
        visible: parseInt(type)===1 ? true : false
        Image {
            id: imageLeft
            width: 40
            height: 40
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            source: constant.fileIcon
            fillMode: Image.PreserveAspectFit
        }

        Label {
            id: labelLeft
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            width: 133
            height: 45
            text: content
            wrapMode: Text.WordWrap
            verticalAlignment: Text.AlignTop
            horizontalAlignment: Text.AlignLeft
        }

    }
}
