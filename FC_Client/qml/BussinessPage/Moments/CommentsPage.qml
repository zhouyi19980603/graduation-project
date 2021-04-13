import QtQuick 2.0
import QtQuick.Controls 2.14
import QtQuick.Window 2.14

/**************************************************************

  @brief....:评论界面，分为两块，下面是可以自己发送的评论，上面为评论内容的显示
  @author...: zhouyi
  @date.....:2021-04-12

  ************************************************************/
Window {
    id : comments_page
    width: 500
    height: 400
    visible: true

    Rectangle{
        id:header
        width: parent.width
        height: 40

        Label {
            id: label
            width: 181
            text: qsTr("评论消息")
            anchors.left: parent.left
            anchors.leftMargin: 150
            font.bold: true
            font.pointSize: 20
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        Image {
            id: image1
            width: 49
            anchors.top: parent.top
            anchors.topMargin: 8
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 8
            anchors.left: parent.left
            anchors.leftMargin: 8
            source: "../../resource/icons/label-icons/return.png"
            fillMode: Image.PreserveAspectFit

            MouseArea{
                id: return_image
                anchors.fill: parent
                onClicked: {
                    //返回朋友圈界面,销毁当前的window
                    comments_page.destroy();
                }
            }
        }

    }
    //    Rectangle {
    //        id: rectangle
    //        height: 40
    //        //        color: "#ffffff"
    //        color: "#f5f5f5"
    //        anchors.top: parent.top
    //        anchors.topMargin: 25
    //        anchors.right: parent.right
    //        anchors.rightMargin: 30
    //        anchors.left: parent.left
    //        anchors.leftMargin: 30

    //        Label {
    //            id: label1
    //            height: 30
    //            text: name
    //            anchors.top: parent.top
    //            anchors.topMargin: 5
    //            anchors.left: parent.left
    //            anchors.leftMargin: 15
    //            verticalAlignment: Text.AlignVCenter
    //            horizontalAlignment: Text.AlignHCenter
    //        }

    //        Text {
    //            id: element
    //            text: content
    //            height: 30
    //            anchors.top: parent.top
    //            anchors.topMargin: 5
    //            verticalAlignment: Text.AlignVCenter
    //            horizontalAlignment: Text.AlignHCenter
    //            font.pixelSize: 12
    //            anchors.left: label1.right
    //            anchors.leftMargin: 8
    //        }
    //    }
    ListView{
        width: parent.width
        anchors.top: header.bottom
        anchors.topMargin: 15
        height: parent.height - rectangle1.height-header.height-20
        model: comments_model
//        model: comments
        delegate: delegates
        //        highlight: Rectangle{color: "lightsteelblue";radius: 5}
        //        focus: true
    }


    Rectangle {
        id: rectangle1
        height: 49
        color: "#ffffff"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 20

        Image {
            id: image
            width: 32
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 8
            anchors.top: parent.top
            anchors.topMargin: 8
            anchors.left: parent.left
            anchors.leftMargin: 10
            source: "logo.jpg"
            fillMode: Image.PreserveAspectFit
        }




        Rectangle {
            id: rectangle2
            width: 200
            height: 200
            color: "#ffffff"
            anchors.fill: element1
            border.color: "black"
        }

        TextField {
            id: element1
            width: 336
            height: 33
            placeholderText: qsTr("写下你的评论")
            anchors.top: parent.top
            anchors.topMargin: 8
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            anchors.left: image.right
            anchors.leftMargin: 15
            font.pixelSize: 12
            clip: true
        }

        Button {
            id: button
            height: 32
            text: qsTr("发布")
            anchors.top: parent.top
            anchors.topMargin: 8
            anchors.left: element1.right
            anchors.leftMargin: 5
            anchors.right: parent.right
            anchors.rightMargin: 0
        }

    }

    ListModel {
        id: comments
        ListElement{
            name: "张李"
            content: "还不错嘛"
        }
        ListElement{
            name: "陈婧回复张礼"
            content: "有眼光"
        }
        ListElement{
            name: "Zerob回复陈婧"
            content: "你真的是弟弟"
        }
        ListElement{
            name: "张李"
            content: "还不错嘛"
        }
        ListElement{
            name: "陈婧回复张礼"
            content: "有眼光"
        }
        ListElement{
            name: "Zerob回复陈婧"
            content: "你真的是弟弟"
        }
        ListElement{
            name: "张李"
            content: "还不错嘛"
        }
        ListElement{
            name: "陈婧回复张礼"
            content: "有眼光"
        }
        ListElement{
            name: "Zerob回复陈婧"
            content: "你真的是弟弟"
        }
        ListElement{
            name: "张李"
            content: "还不错嘛"
        }
        ListElement{
            name: "陈婧回复张礼"
            content: "有眼光"
        }
        ListElement{
            name: "Zerob回复陈婧"
            content: "你真的是弟弟"
        }
    }

    Component{
        id:delegates
        Rectangle {
            id: rectangle
            height: 40
            color: "#f5f5f5"
            anchors.right: parent.right
            anchors.rightMargin: 30
            anchors.left: parent.left
            anchors.leftMargin: 30

            Label {
                id: label1
                height: 30
                text: name+" :"
                anchors.top: parent.top
                anchors.topMargin: 5
                anchors.left: parent.left
                anchors.leftMargin: 15
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            Text {
                id: element
                text: content
                height: 30
                anchors.top: parent.top
                anchors.topMargin: 5
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 12
                anchors.left: label1.right
                anchors.leftMargin: 8
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    console.log("点击单项,可以获得到单项的id" + index)
//                    console.log(index)
                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:2;anchors_y:11}D{i:1;anchors_width:411;anchors_x:51;anchors_y:41}D{i:3;anchors_x:34;anchors_y:8}
D{i:5;anchors_width:458;anchors_x:22}D{i:6;anchors_height:32;anchors_x:18;anchors_y:8}
D{i:8;anchors_x:71}D{i:9;anchors_width:72;anchors_x:399}
}
##^##*/
