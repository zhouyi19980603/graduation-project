import QtQuick 2.0
import Felgo 3.0
import QtQuick.Dialogs 1.2

Page {
    id: sendFile
    title: "发送文件"

    property var filepath : undefine
    rightBarItem: IconButtonBarItem{
        icon: IconType.send
        onClicked: {
//            console.log("s_userid"+s_userid)
            message_listModel.add([profilemsg.account,s_userid,"1",filename.text,"1",filepath])
            filename.text = ""
            sendFile.navigationStack.pop();
        }
    }

    Rectangle {
        id: rectangle
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -60
        anchors.horizontalCenter: parent.horizontalCenter
        width: 315
        height: 29
        color: "#ffffff"
        border.color: "black"

        AppText {
            id: filename
            anchors.fill: parent
            anchors.margins: 2
            wrapMode: Text.NoWrap
            font.pixelSize: 12
        }
    }
    IconButton{
        width: 30
        height: 30
        anchors.left: rectangle.right
        anchors.leftMargin: 2
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -60
        icon: IconType.ellipsish
        onClicked: fileDialog.open();
    }

    FileDialog{
        id:fileDialog
        title: "Please choose a file"
        folder: ".."
        //fileDialog.fileUrl文件url，fileDialog.folder当前文件夹的url
//        onAccepted: console.log(fileDialog.fileUrl.toString())
        onAccepted: fileName(fileDialog.fileUrl.toString())
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
