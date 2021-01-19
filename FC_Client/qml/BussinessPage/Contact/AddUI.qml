import QtQuick 2.2
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.4
import QtQuick.Layouts 1.11
import "../../Component"
Page{
    id: addui
    visible: true
    width: 360
    height: 720
    //屏蔽父对象的鼠标事件
    MouseArea{
        anchors.fill: parent
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
                text: qsTr("添加好友")
                color: "white"
                anchors.verticalCenter: parent.verticalCenter
                font.family: "微软雅黑"
                font.pointSize: constant.middleFontPointSize
            }
        }
    }
    Row{
        x: 8
        y: 64
        spacing: 8
        Rectangle{
            width: 280
            height: 45
            border.color: "green"

            Row {
                id: row
                anchors.fill: parent
                spacing: 2

                Image {
                    id: findImage
                    width: 30
                    height: parent.height
                    fillMode: Image.PreserveAspectFit
                    source: "../../../asserts/find.jpg"
                }

                TextInput {
                    id: textInputSearch
                    width: 250
                    height: parent.height
                    verticalAlignment: Text.AlignVCenter
                    selectionColor: "#02020a"
                    font.pixelSize: 14

                }

            }
        }

        Rectangle {
            id: rectangle
            width: 40
            height: parent.height
            color: "#ffffff"
//            anchors.leftMargin: 10
            Text {
                id: buttonText
                anchors.fill: parent
                text: textInputSearch.text.length ? qsTr("搜索") : qsTr("取消")
                font.pointSize: 14
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                MouseArea{
                    id:findClick
                    anchors.fill: parent
                    onClicked: {
                        friends_handle.search_friends(textInputSearch.text)
//                        message_handle.search_friends(textInputSearch.text)
                        __PushPage(Qt.resolvedUrl("./FriendsMessage.qml"), {} ); //压入一个新的界面
                    }
                }
            }
        }
    }

    function changeTextSearch(msg)
    {
        console.log(msg)
        textInputSearch.text=msg
    }

}
