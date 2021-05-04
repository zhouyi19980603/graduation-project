import QtQuick 2.0
import Felgo 3.0
import "../../components"

Page {
    id: searchMsg

    onPopped: buddy.clear();
    Column{
        id: contentColumn
        width: parent.width
        anchors{
            top: parent.top
        }
        visible: buddy.account!=""
        Rectangle{
            id:headrect
            width: parent.width
            height: dp(70)
            color: "white"
            Row{
                id:head
                spacing: dp(15)
                height: parent.height
                Image{
                    id: image
                    width: dp(45)
                    height: width
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: searchMsg.left
                    anchors.leftMargin: dp(10)
                    source: buddy.heading
                }
                Column{
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: dp(5)
                    AppText{
                        leftPadding: 0
                        font{
                            bold: true
                            pixelSize: dp(16)
                        }
                        text: buddy.nickname
                    }
                    AppText{
                        id:acc
                        font.pixelSize: sp(12)
                        text: "帐号:"+ buddy.account
                    }
                }
            }
        }


        Separator{
            anchors.top: headrect.bottom
            color: "black"
            orientation: Qt.Horizontal
            anchors.horizontalCenter: parent.horizontalCenter

        }
        Rectangle{
            id:addFriendRect
            anchors.top: headrect.bottom
            anchors.topMargin: 16
            width: parent.width
            height: 70
            AppText{
                id:addFriendButton
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.fill: parent
                color: "blue"
                text: qsTr("添加好友")
            }

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    friends_handle.add_friends(buddy.account)
                }
            }
        }

//        Rectangle{
//            id:sendMsgRect
//            anchors.top: addFriendRect.bottom
//            anchors.topMargin: 16
//            width: parent.width
//            height: 70
//            AppText{
//                id:sendMsgButton
//                verticalAlignment: Text.AlignVCenter
//                horizontalAlignment: Text.AlignHCenter
//                anchors.fill: parent
//                color: "blue"
//            }

////            MouseArea{
////                anchors.fill: parent
////                onClicked: {
////                    //进入好友的个人信息界面
////                }
////            }

//        }

    }
    AppText{
        anchors.centerIn: parent
        text: qsTr("该用户不存在")
        visible: buddy.account==""
    }
}
