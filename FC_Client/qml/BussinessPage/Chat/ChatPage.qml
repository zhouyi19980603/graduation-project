import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Window 2.0
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import QtQuick.LocalStorage 2.0
import "../../Component"

Page {
    id: chatPage

    property var s_username  //聊天对象名
    property var s_userid    //聊天对象ID

    focus: true
    Keys.onBackPressed: {
        event.accepted = true;
        try { stackView.pop(); }  catch(e) { }
    }

    Constant { id: constant }

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
                text: s_username + s_userid
                // Layout.alignment: Qt.AlignRight
                color: "white"
                anchors.verticalCenter: parent.verticalCenter
            }
        }

    }

    bottomBar: BottomBar {
        RowLayout {
            anchors.fill: parent
            spacing: 5

            IconButton {
                width: topBar.height - 2
                height: topBar.height - 2
                activeIconSource: constant.soundActiveIcon
                inactiveIconSource: constant.soundInactiveIcon
            }

            Item {
                Layout.fillWidth: true
                implicitHeight: textInput.implicitHeight
                SampleTextArea {
                    id: textInput
                    width: parent.width
                    implicitHeight: {
                        if(lineCount >= 2) {
                            (topBar.height - 2) * 2
                        } else {
                            (topBar.height- 2) * lineCount
                        }
                    }
                    IconButton {
                        width: topBar.height * 0.9
                        height: topBar.height * 0.9
                        activeIconSource: constant.emoticonActiveIcon
                        inactiveIconSource: constant.emoticonInactiveIcon
                        anchors.bottom: parent.bottom
                        anchors.right: parent.right
                        anchors.rightMargin: 10
                    }

                }
            }

            SampleButton {
                Layout.alignment: Qt.AlignRight
                visible: textInput.text.length ? true: false
                text: qsTr("Send")
                onClicked:  {
                    if(textInput.text != "" ) {
                        //传入用户ID,消息接收端ID,时间,消息内容,消息类型
                        message_listModel.add([profilemsg.account,s_userid,"1",textInput.text,"0"])
                        //message_listModel.currentIndex = message_listModel.count - 1
                        textInput.text = "";
                    }
                }
            }
            IconButton {
                id:toolbutton
                Layout.alignment: Qt.AlignRight
                visible: textInput.text.length ? false: true
                width: topBar.height * 0.9
                height: topBar.height * 0.9
                activeIconSource: constant.toolIcon
                inactiveIconSource: constant.toolIcon
                onClicked: {
                    contextMenu.open()
                }
            }
            //弹出菜单
            Menu {
                id: contextMenu
                MenuItem {
                    icon.source:  constant.groupchatIcon
                    text: qsTr("视频通话")
                }
                MenuItem {
                    icon.source: constant.groupchatIcon
                    text: "文件"
                    onClicked: {
                        var component = Qt.createComponent("SendFile.qml");
                        if(component.status === Component.Ready){
                            var object=component.createObject(chatPage);
                            //可以修改对方的值
                            object.userId = s_userid;
//                            console.log(s_userid)
                        }
                    }

                }
                MenuItem {
                    icon.source: constant.groupchatIcon
                    text: "相册"
                }
            }
            Item { width: 5; height: 5 }
        }
    }

    ListView {
        id: chatListView
        anchors.fill: parent

        model:message_listModel

        spacing: 20

        readonly property int itemSpacing: 10
        readonly property int headPortraitPictureWidth: 60

        readonly property int
        chatContentAreaWidth: chatListView.width - chatListView.headPortraitPictureWidth*2 - 2 *chatListView.itemSpacing

        delegate: chatAreaComponent
    }

    signal data_changed();
    Connections{
        target: message_listModel
        onRecv_mess:{
            chatListView.currentIndex = chatListView.count - 1;
            chat_listModel.add();   //在ChatsView 页面更新消息
            console.log("message_listmodel!")
        }
    }

    Component {
        id: chatAreaComponent
        Row {
            id: chatArea
            spacing: chatListView.itemSpacing
            Image {
                // 头像
                id: headPortraitPic1
                width: chatListView.headPortraitPictureWidth
                height: chatListView.headPortraitPictureWidth
                sourceSize: Qt.size(width, height)
                source: imagePathLeft
                visible:  parseInt(msgOpacity) ? true : false;
            }

            Item {
                id: chatContentAreaLeft
                visible: parseInt(msgOpacity) ? true : false;
                width: chatListView.chatContentAreaWidth
                height:
                {
                    if(chatContentTextLeft.contentHeight)
                    {
                        chatContentTextLeft.contentHeight > 60 ? chatContentTextLeft.contentHeight : 60
                    }else
                    {
                        70
                    }
                }

                Rectangle {
                    id:chatRectangleLeft

                    border.width: 1
                    border.color: "#ccc"
                    anchors.left: parent.left
                    height: parent.height
                    color: "green"
                    width: chatContentTextLeft.contentWidth > 200 ? chatContentTextLeft.contentWidth : 200
                    visible:  parseInt(type)===0 ? true : false
                    Text {
                        id: chatContentTextLeft

                        width: 300
                        anchors.left: parent.left
                        anchors.leftMargin: chatListView.itemSpacing
                        anchors.top: parent.top
                        anchors.topMargin: chatListView.itemSpacing

                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignLeft
                        text:content
                        font.pointSize: constant.normalFontPointSize
                        font.family: "微软雅黑"
                    }
                }

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
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            console.log("open file ")
                            message_listModel.open_file(labelLeft.text)
                        }
                    }
                }
            }

            Image {
                // 头像
                id: empty
                width: chatListView.headPortraitPictureWidth
                height: chatListView.headPortraitPictureWidth
                sourceSize: Qt.size(width, height)
                opacity: message_listModel.msgOpacity ? 1 : 0

            }
            Item {
                id: chatContentAreaRight
                visible: parseInt(msgOpacity) ? false : true;
                width: chatListView.chatContentAreaWidth
                height:
                {
                    if(chatContentTextRight.contentHeight)
                    {
                        chatContentTextRight.contentHeight > 60 ? chatContentTextRight.contentHeight : 60
                    }else
                    {
                        70
                    }
                }

                Rectangle {
                    id:chatRectangleRight

                    border.width: 1
                    border.color: "#ccc"
                    anchors.right: parent.right
                    height: parent.height
                    color: "green"
                    width: chatContentTextRight.contentWidth > 200 ? chatContentTextRight.contentWidth : 200
                    visible: parseInt(type)===0 ? true : false
                    Text {
                        id: chatContentTextRight

                        width: 300
                        anchors.right: parent.right
                        anchors.rightMargin: chatListView.itemSpacing
                        anchors.top: parent.top
                        anchors.topMargin: chatListView.itemSpacing
                        // anchors.centerIn: parent
                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignRight
                        text:content
                        font.pointSize: constant.normalFontPointSize
                        font.family: "微软雅黑"
                    }
                }

                Rectangle{
                    id:chatFileREctangleRight
                    border.width: 1
                    border.color: "#ccc"
                    anchors.right: parent.right
                    height: 70
                    color: "white"
                    width: 250
                    visible: parseInt(type)===1 ? true : false
                    Image {
                        id: image
                        width: 40
                        height: 40
                        anchors.right: parent.right
                        anchors.rightMargin: 10
                        anchors.verticalCenter: parent.verticalCenter
                        source: constant.fileIcon
                        fillMode: Image.PreserveAspectFit
                    }

                    Label {
                        id: label
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
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            console.log("open file ")
                            message_listModel.open_file(labelLeft.text)
                        }
                    }
                }

            }

        Image {
            // 头像
            id: headPortraitPic2
            width: chatListView.headPortraitPictureWidth
            height: chatListView.headPortraitPictureWidth
            sourceSize: Qt.size(width, height)
            source: imagePathRight
            visible: parseInt(msgOpacity) ? false : true;
        }
        }
    }


}



