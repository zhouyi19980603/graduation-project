import QtQuick 2.0
import QtQuick.Controls 2.14
import QtQuick.Window 2.14
import QtQuick.Dialogs 1.2

Window {
    id: sendfile
    visible:true
    x:100
    y:100
    width: 440
    height: 240
    property var userId
    property var filepath

    Label {
        id: label
        x: 45
        y: 46
        width: 169
        height: 18
        text: qsTr("选择文件")
    }

    Rectangle {
        id: rectangle
        x:45
        y:97
        width: 315
        height: 29
        color: "#ffffff"
        border.color: "black"

        Label {
            id: filename
            anchors.fill: parent
            anchors.margins: 2
            wrapMode: Text.NoWrap
            font.pixelSize: 12
        }
    }

    Button {
        id: ok
        x: 159
        y: 175
        text: qsTr("发送")
        onClicked: {
            //传入用户ID,消息接收端ID,时间,消息内容,消息类型
            message_listModel.add([profilemsg.account,userId,"1",filename.text,"1",filepath])
//            chatPage.filename = filename.text
            console.log("profilemsg" + userId)
//            message_listModel.send_file(userId,filepath)
            filename.text="";
            sendfile.destroy()
        }
    }

    Button {
        id: no
        x: 298
        y: 175
        text: qsTr("取消")
        onClicked: {
            sendfile.destroy()
        }
    }

    Image {
        id: image
        x: 375
        y: 97
        width: 37
        height: 29
        source: "../../resource/icons/label-icons/ellipsis.png"
        fillMode: Image.PreserveAspectFit
        MouseArea{
            anchors.fill: parent
            onClicked: fileDialog.open()
        }
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

