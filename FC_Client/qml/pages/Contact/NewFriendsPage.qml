import QtQuick 2.0
import Felgo 3.0
import "../../components"


Page {
    id:newFriendsPage
    title: "新朋友"
    property int headPrtraitSize: 54
    AppListView{
        id:listView
        model: fmsg_model
//        model: listmodel
        delegate: delegateMsg
    }

    ListModel{
        id:listmodel
        ListElement{
            heading:"../../../assets/resource/tests/tests001.jpeg"
            name:"张力"
            content:"yes"
        }
        ListElement{
            heading:"../../../assets/resource/tests/tests001.jpeg"
            name:"张其"
            content:"ignore"
        }
        ListElement{
            heading:"../../../assets/resource/tests/tests001.jpeg"
            name:"张宏"
            content:"no"
        }

    }

    property var jsonData: [
        {
            "heading":"../../../assets/resource/tests/tests001.jpeg",
            "name":"张力",
            "content":"yes"
        },{
            "heading":"../../../assets/resource/tests/tests001.jpeg",
            "name":"张力",
            "content":"ignore"
        }
    ]

    JsonListModel{
        id:listModel
        source:newFriendsPage.jsonData
    }

    Component{
        id:delegateMsg
        Rectangle{
            id:rect
            width: parent.width
            height: 70
            AppImage{
                id:headImage
                source: heading
                anchors.left: parent.left
                anchors.leftMargin: 8
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 8
                anchors.topMargin: 8
                width: headPrtraitSize
                fillMode:Image.PreserveAspectFit
            }
            AppText{
                id:nameText
                anchors.left: headImage.right
                anchors.leftMargin: 12
                anchors.top: parent.top
                anchors.topMargin: 10
                height: 30
                text: name
                fontSize: 10
                verticalAlignment: Text.AlignVCenter
            }

            Rectangle{
                id:btn
                height: 30
                width: 100
                anchors.top: parent.top
                anchors.topMargin: 20
                anchors.right: rect.right
                anchors.rightMargin: 16
                visible: content != "ignore"
                AppText{
                    id:btnText
                    anchors.fill: parent
                    text: content=="yes"? "已同意" : "已拒绝"
                }
            }
            Rectangle{
                id:btn2
                anchors.verticalCenter: parent.verticalCenter
                height: 60
                width: 70
                anchors.right: parent.right
                anchors.rightMargin: 16
                visible: content == "ignore"
                Rectangle{
                    id:rect1
                    anchors.top: parent.top
                    anchors.topMargin: 3
                    height: 25
                    width: 60
                    color: "green"
                    AppText{
                        anchors.centerIn: parent
                        id:yes
                        text: qsTr("同意")
                        fontSize: 10
                        verticalAlignment: Text.verticalAlignment
                        horizontalAlignment: Text.horizontalAlignment
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            //同意添加好友
                            buddy.account = account;
                            buddy.nickname = name;
                            buddy.heading = heading;
                            btn.visible = true;
                            btnText.text = "已同意"
                            btn2.visible = false;
                            friends_handle.validation_request("ok");
                        }
                    }
                }

                Rectangle{
                    height: 25
                    width: 60
                    anchors.top:rect1.bottom
                    anchors.topMargin: 4
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 3
                    color: "red"
                    AppText{
                        id:no
                        text: qsTr("拒绝")
                        fontSize: 10
                        anchors.centerIn: parent
                        verticalAlignment: Text.verticalAlignment
                        horizontalAlignment: Text.horizontalAlignment
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            //拒绝添加好友
                            btn.visible = true;
                            btnText.text = "已拒绝"
                            btn2.visible = false;
                            friends_handle.validation_request("no");
                        }
                    }
                }

            }

            Separator{
                anchors.left: headImage.right
                anchors.leftMargin: 12
                anchors.top: parent.bottom
                anchors.topMargin: -1
                orientation: Qt.Horizontal
                color: "#666"
            }
        }
    }
}
