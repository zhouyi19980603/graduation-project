import QtQuick 2.0
import QtQuick.Controls 2.14
import QtQuick.Window 2.12
import QtQuick.Layouts 1.11
import "../../Component"
//import Message_Handle 1.0

Page{
    id: element
    width: 360
    height: 720
    //屏蔽父对象的鼠标事件

    MouseArea{
        id: mouseArea
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent
    }
    Rectangle{
        id:one
        height: 32
        width: parent.width
        Image {
            id: image
            x: 0
            y: 8
            width: 32
            height: parent.height
            fillMode: Image.PreserveAspectFit
            source: "../../../asserts/return.jpg"
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    try { stackView.pop(); }  catch(e) { }
                }
            }
        }
    }



    //repeater留下来当扩展
//    Repeater {
//       model:buddys

    Rectangle {
        anchors.top: one.bottom
        width: parent.width
        height: rowLayout1.height + 10

        Text {
            id: name
            visible: acc.text ? false : true
            text: qsTr("该用户不存在")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.fill: parent
            color: "#888"
        }
        RowLayout {
            id: rowLayout1
            width: parent.width
            anchors.verticalCenter: parent.verticalCenter
            spacing: 10

            Item {  width: parent.spacing;  height: parent.height }

            Image {
                height: 110
                width: 110
                sourceSize: Qt.size(width, height)
                source: buddy.heading
            }

            ColumnLayout {
                Layout.fillHeight: true
                Label {
                    text: buddy.nickname
                    font.family: "微软雅黑"
                    font.pointSize: constant.normalFontPointSize
                }
                Label {
                    id:acc
                    text: buddy.account
                    font.pointSize: constant.normalFontPointSize
                    font.family: "微软雅黑"
                    color: "#888"
                }
            }

            Item { Layout.fillWidth: true }
        }
    }
    Separator {
        color: "black"
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
    }
    Button{
        id:addFriendButton
        x: 0
        y: 190
        text: "添加好友"
        visible: acc.text && buddy.visShow== false? true : false
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 490
        width: parent.width
        onClicked: {
            console.log("add Friends")
            friends_handle.add_friends(acc.text)
            //请求添加为好友的信息
        }
    }
    Button{
        id:sendButton
        x: 0
        y: 190
        text: "发送消息"
        visible: buddy.visShow
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 490
        width: parent.width
        onClicked: {
            message_listModel.set_currentChatId(buddy.account);

            __PushPage(Qt.resolvedUrl("../Chat/ChatPage.qml"),
                       {s_userid:buddy.account,s_username:buddy.nickname});
        }
    }

}

