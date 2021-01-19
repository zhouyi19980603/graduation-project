import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Window 2.0
import QtQuick.Layouts 1.1
import "../../Component"

Page {
    id: chatsView
    title: "GroupList"
    color: "white"
    property int headPrtraitSize: 90
    property string s_username : "Family"
    property string s_userid  :"@56789"

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
                }

                Separator {
                    color: "black"

                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    Label{ text: "   群   聊";color: "white"}
                }

                //! [0] fix the bug
                // 在本页面压入一个页面之后再弹出
                // x 的值会变成 18

                // 需要将其设置回 0
                onXChanged: {
                    if(x != 0 ) {
                        x = 0
                    }
                }
                //! [0] fix the bug
            }
        }
    }
    ListView {
        id: listView
        width: chatsView.width
        height: chatsView.height

        model: chatItemsModel

        add: Transition {
            NumberAnimation { property: "opacity"; from: 0; to: 1.0; duration: 400 }
            NumberAnimation { property: "scale"; from: 0; to: 1.0; duration: 400 }
        }
        move: Transition {
            NumberAnimation { properties: "x,y"; duration: 800; easing.type: Easing.OutBack }
        }
        displaced: Transition {
            NumberAnimation { properties: "x,y"; duration: 400; easing.type: Easing.OutBounce }
        }

        //scrollbar移动效果
        states: [
            State {
                name: "ShowBar"
                when: listView.movingVertically
                PropertyChanges { target: verticalScrollBar; opacity: 0}
            },
            State {
                name: "HideBar"
                when: !listView.movingVertically
                PropertyChanges { target: verticalScrollBar; opacity: 1}
            }
        ]

        transitions: [
            Transition {
                from: "ShowBar"
                to: "HideBar"
                NumberAnimation { properties: "opacity"; duration: 400 }
            },
            Transition {
                from: "HideBar"
                to: "ShowBar"
                NumberAnimation { properties: "opacity"; duration: 400 }
            }
        ]


        ScrollBar {
            id: verticalScrollBar
            width: 10 * Screen.devicePixelRatio
            height: listView.height - width
            anchors.right: listView.right
            orientation: Qt.Vertical
            position: listView.visibleArea.yPosition
            pageSize: listView.visibleArea.heightRatio
        }


        delegate: Rectangle {
            id: chatItem
            // chatItem
            width: chatsView.width
            height: headPrtraitSize
            color: "transparent"
            border.width: 1
            border.color: "#ccc"
            state: "UnSelected"
            states: [
                State {
                    name: "Selected"
                    PropertyChanges { target:chatItem; color: "#ccc" }
                },
                State {
                    name: "UnSelected"
                    PropertyChanges { target:chatItem; color: "transparent" }
                }
            ]

            transitions: [
                Transition {
                    from: "Selected"
                    to: "UnSelected"
                    NumberAnimation { properties: "color"; duration: 400 }
                },
                Transition {
                    from: "UnSelected"
                    to: "Selected"
                    NumberAnimation { properties: "color"; duration: 400 }
                }
            ]

            RowLayout {
                anchors.fill: parent
                anchors.margins: spacing
                Image {
                    width: headPrtraitSize
                    height: headPrtraitSize
                    anchors.verticalCenter: parent.verticalCenter
                    sourceSize.width: headPrtraitSize - 2
                    sourceSize.height: headPrtraitSize - 2
                    source: "../../resource/tests/tests001.jpeg"
                    fillMode: Image.PreserveAspectFit
                    //clip: true
                }
                ColumnLayout {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    RowLayout {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Label { Layout.fillWidth: true; text: name }

                    }
                    RowLayout {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Label { Layout.fillWidth: true; text: chatId }

                    }
                }
            }

            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                onPressAndHold: {
                    chatItem.state = "Selected";
                    chatItemMenu.aboutToHide.connect(function(){
                        chatItemMenu.aboutToHide.disconnect(arguments.callee);
                        chatItem.state = "UnSelected";
                    });
                    chatItemMenu.aboutToShow.connect(function(){
                        chatItemMenu.aboutToShow.disconnect(arguments.callee);
                        chatItem.state = "Selected";
                    });
                    chatItemMenu.chatItemIndex = index;
                    chatItemMenu.popup();
                }
                onClicked: {
                     message_listModel.set_currentChatId(s_userid);
                    __LoadChatPage(chatId, name);
                }
            }
        }

        Menu {
            id: chatItemMenu
            property int chatItemIndex: 0
            MenuItem {
                text: qsTr("Delete conversation")
                onTriggered: {
                    listView.model.remove(chatItemMenu.chatItemIndex);
                }
            }
            MenuItem {
                text: qsTr("Sticky on top")
                onTriggered: {
                    listView.model.move(chatItemMenu.chatItemIndex, 0, 1);
                }
            }
            MenuItem {
                text: qsTr("Clear")
                onTriggered: {
                    listView.model.clear();
                }
            }
        }

        ListModel {
            id: chatItemsModel

            /*
                  联系人名字
                  聊天记录
                  时间
                  是否
                 */
            Component.onCompleted: {

                chatItemsModel
                .append(
                     {
                         "name":"Family ",
                         "chatId":"@56789",
                     });
            }
        }
    }


    function __LoadChatPage(s_userid, s_username){

        __PushPage(Qt.resolvedUrl("../Chat/ChatPage.qml"),
                   {s_userid:s_userid,s_username: s_username } );


    }

}

