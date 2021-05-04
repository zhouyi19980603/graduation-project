import QtQuick 2.0
import QtQuick.Controls 2.14
import QtQuick.Window 2.12
import QtQuick.Layouts 1.11
import "../../Component"

Page {
    id:newfriendspage
    width: 360
    height: 720
    Constant{
        id:constant
    }
    topBar: TopBar {
        id: topBar
        //! aviod looping binding
        Item { anchors.fill: parent }
        RowLayout {
            anchors.fill: parent
            spacing: 10

            Item { width:  topBar.height - 2; height: width }

            IconButton {
                height: topBar.height - 2
                width: topBar.height - 2
                anchors.verticalCenter: parent.verticalCenter
                activeIconSource: constant.backActiveIcon
                inactiveIconSource: constant.backInactiveIcon
                onClicked: {
                    try { stackView.pop(); }  catch(e) { }
                    // console.log(x, y)
                }

                //! [0] fix the bug
                // 在本页面压入一个页面之后再弹出
                // x 的值会变成 180
                // 需要将其设置回 0
                onXChanged: {
                    if(x != 0 ) {
                        x = 0
                    }
                }
                //! [0] fix the bug

                Separator {
                    color: "black"
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }
        // such as menuBar

        Row {
            parent: topBar
            anchors.left: parent.left
            anchors.leftMargin: (topBar.height - 2) * 1.5
            anchors.fill: parent
            Label {
                text: qsTr("新的朋友")
                color: "white"
                anchors.verticalCenter: parent.verticalCenter
                font.family: "微软雅黑"
                font.pointSize: constant.middleFontPointSize
            }
        }
    }
    Rectangle{
        anchors.top: topBar.bottom
        height: 80
        width: parent.width
        Image {
            id:image
            width: 60
            height: 60
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            source: buddy.heading
        }
        ColumnLayout{
            id:col
            height:60
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: image.right
            anchors.leftMargin: 10
            Label{
                text: buddy.nickname
                height: 40
                font.pointSize: 15
            }
            Label{
                id:message
                text: qsTr("请求添加你为朋友") //这里存的其实是备注信息
                height: 20
                color: "#8c808b"
                font.pointSize: 11
            }
        }
        Column{
            id:result
            width: 60
            height: 60
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 10
            Button{
                id:ok
                width: 60
                height: 25
                anchors.top: parent.top
                anchors.topMargin: 5
                anchors.left: parent.left
                text: qsTr("接受")
                onClicked: {
                    result.visible=false;
                    show.visible = true;
                    message.visible=false;
                    show.text="已接受";
                    buddy.value="0";
                    friends_handle.validation_request("ok");
                }
            }
            Button{
                id:error
                anchors.top: ok.bottom
                anchors.topMargin: 5
                width:60
                height: 25
                text: qsTr("拒绝")
                onClicked: {
                    result.visible=false;
                    show.visible = true;
                    message.visible=false;
                    show.text="已拒绝";
                    buddy.value="0";
                    friends_handle.validation_request("no");
                }
            }
        }
        Button{
            id:show
            width: 60
            height: 30
            visible: false;
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 10
        }
    }

    Connections{
        target: message_handle
        onAddFriendSignal:console.log("收到了C++端发送的信号")
    }
}
