import QtQuick 2.14
import Felgo 3.0
import "../../components"
import "../../model"
import QtQuick.Dialogs 1.2

Page{
    id:chatPage

    property var s_username: undefine
    property var s_userid: undefine

    title: s_username
    Constant{id: constant}

    SortFilterProxyModel{
        id:sortModel
        sourceModel: message_listModel
    }
    AppListView{
        id:chatListView
//        model: message_listModel
        model: sortModel
        spacing: 20
        height: parent.height-message.height-16
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
//            chat_listModel.add();   //在ChatsView 页面更新消息
//            console.log("message_listmodel!")
        }
    }

    Component {
        id: chatAreaComponent
        Row {
            id: chatArea
            spacing: chatListView.itemSpacing
            AppImage {
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
                    AppText {
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
                        fontSize: 12
                        color: "white"
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
                    AppImage {
                        id: imageLeft
                        width: 40
                        height: 40
                        anchors.right: parent.right
                        anchors.rightMargin: 10
                        anchors.verticalCenter: parent.verticalCenter
                        source: constant.fileIcon
                        fillMode: Image.PreserveAspectFit
                    }

                    AppText {
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
                        fontSize: 8
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

            AppImage {
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
                    AppText {
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
                        fontSize: 12
                        color: "white"
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
                    AppImage {
                        id: image
                        width: 40
                        height: 40
                        anchors.right: parent.right
                        anchors.rightMargin: 10
                        anchors.verticalCenter: parent.verticalCenter
                        source: constant.fileIcon
                        fillMode: Image.PreserveAspectFit
                    }

                    AppText {
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
                        fontSize: 8
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

        AppImage {
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

    AppPaper{
        id:message
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: parent.width
        height: content.height+ (tool.visible ? tool.height : 16)
        IconButton{
            id:plus
            width: 40
            height: 40
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 4
            icon: IconType.plus
            color: Theme.tintColor
            onClicked: {
                //显示其他信息
                tool.visible = !tool.visible
            }
        }
        AppTextField{
            id:content
            anchors.top: parent.top
            anchors.left: parent.left
            borderColor: "black"
            anchors.right:plus.left
            anchors.margins: 8
            placeholderText: "这是输入内容"
            showClearButton: true
            onAccepted: {
                //传入用户ID,消息接收端ID,时间,消息内容,消息类型
                message_listModel.add([profilemsg.account,s_userid,"1",content.text,"0"])
                content.text = "";
            }
        }
        Rectangle{
            id:sep
            width: parent.width
            height: 1
            anchors.top:content.bottom
            anchors.topMargin: 8
            color: "#ABABAB"
        }
        Rectangle{
            id:tool
            height: 120
            visible: false
            anchors.top: sep.bottom
            anchors.topMargin: 8
            Row{
                IconButton{
                    icon: IconType.pictureo
                }
                IconButton{
                    icon: IconType.file
                    onClicked: {
                        var component = Qt.createComponent("./SendFile.qml");
                        if(component.status === Component.Ready)
                        {
                            chatPage.navigationStack.push(component);
                        }
                    }
                }
            }

        }
    }

    FileDialog{
        id:fileDialog
        title: "Please choose a file"
        folder: ".."
        //fileDialog.fileUrl文件url，fileDialog.folder当前文件夹的url
        onAccepted: console.log(fileDialog.fileUrl.toString())
//        onAccepted: fileName(fileDialog.fileUrl.toString())
    }

    function fileName(str)
    {
        var start = str.lastIndexOf('/')+1;// 从这个下标开始
        var end = str.length;
        filename.text = str.substring(start,end)

        filepath = str.substring(7,end)
        console.log(" str.substring(7,end): "+str.substring(7,end)) //这里是绝对路径
        console.log("userId: "+ userId)
    }

}
