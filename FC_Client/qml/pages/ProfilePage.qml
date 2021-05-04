import QtQuick 2.0
import Felgo 3.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import "../model"
import "../components"

Page {
    id: profilePage
    backgroundColor: "#ebebeb"

    Constant{ id: constant}


    property var heading: undefined
    property var nickname: undefined
    property var account: undefined
    property var teamname: undefined

    Column{
        id: contentColumn
        width: parent.width
        anchors{
            top: parent.top
        }
        Rectangle{
            id:headrect
            width: parent.width
            height: dp(70)
            color: "white"
            Row{
                id:head
                spacing: dp(15)
                height: parent.height
                RoundedImage{
                    id: image
                    width: dp(45)
                    height: width
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: profilePage.left
                    anchors.leftMargin: dp(10)
                    source: heading
                    radius: height/2
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
                        text: nickname
                    }
                    AppText{
                        font.pixelSize: sp(12)
                        text: account
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
            id: markitem
            width: profilePage.width
            color: "white"
            height: 70
            anchors.top:headrect.bottom
            AppText{
                id:makename
                text: qsTr("设置备注")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.left: parent.left
                anchors.leftMargin: 20
                anchors.verticalCenter: parent.verticalCenter

            }

            AppImage {
                id: image3
                anchors.right: parent.right
                width: 32
                height: 17
                anchors.verticalCenter: parent.verticalCenter
                anchors.rightMargin: 16
                rotation: 180
                fillMode: Image.PreserveAspectFit
                source: "../../assets/resource/icons/label-icons/return.png"
            }

            Separator{
                width: parent.width+100
                color: "#DDDDDD"
                orientation: Qt.Horizontal
                anchors.horizontalCenter: parent.horizontalCenter
            }

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    //进入设置备注界面
                    var component = Qt.createComponent("./Contact/updateRemark.qml");
                    if(component.status === Component.Ready)
                    {
                        profilePage.navigationStack.push(component);
                    }
                }
            }
        }

        Rectangle {
            id: settingbutton
            anchors.top:markitem.bottom
            anchors.topMargin: dp(5)
            color: "white"
            width: parent.width
            height: 140
            Column{
                width: profilePage.width
                height: parent.height
                Rectangle{
                    //删除好友的按钮
                    id:deletef
                    width: parent.width
                    height: 70
                    IconButton{
                        icon: IconType.remove
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: delText.left
                        anchors.rightMargin: -16
                    }
                    AppText{
                        id:delText
                        anchors.centerIn: parent
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        text: qsTr("删除")
                        color: "blue"
                    }

                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            //删除好友
                            friends_handle.delete_friend(teamname,account)
                        }
                    }
                }
                Separator{
                    width: parent.width
                    height: 1
                    color: "#DDDDDD"
                    orientation: Qt.Horizontal
                }
                Rectangle{
                    id:sendmsg
                    width: parent.width
                    height: 70
                    IconButton{
                        icon: IconType.comment
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: sendtext.left
                        anchors.rightMargin: -16
                    }
                    AppText{
                        id:sendtext
                        anchors.centerIn: parent
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        text: qsTr("发消息")
                        color: "blue"
                    }

                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            message_listModel.set_currentChatId(account);
                            //发送消息，跳转到另一个界面
                            var component = Qt.createComponent("./Chat/ChatPage.qml");
                            if(component.status === Component.Ready)
                            {
                                profilePage.navigationStack.push(component,{s_username:nickname,s_userid:account});
                            }
                        }

                    }
                }
            }


        }



    }
}


/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
