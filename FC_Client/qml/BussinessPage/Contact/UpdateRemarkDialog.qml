import QtQuick 2.0
import QtQuick.Controls 2.14
import QtQuick.Window 2.14
/**************************************************************

  @brief....:修改备注界面
  @author...: zhouyi
  @date.....:2020-05-30

  ************************************************************/
Window {
    id:updatedialog
    x: 100
    y:100
    visible:true
    width: 440
    height: 240
    property var teamId
    property var itemId

    Label {
        id: label
        x: 45
        y: 46
        width: 169
        height: 18
        text: qsTr("请输入好友备注：")
    }

    Rectangle {
        id: rectangle
        x:45
        y:97
        width: 315
        height: 29
        color: "#ffffff"
        border.color: "black"

        TextEdit {
            id: textEdit
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
        text: qsTr("确定")
        onClicked: {
//            console.log(textEdit.text)
//            console.log("name:  "+ name)
            //传送当前的好友id，也就是好友标识，新备注信息
            updatedialog.destroy()
            friends_handle.update_remark(teamId,itemId,textEdit.text)
//            message_handle.update_remark(teamId,itemId,textEdit.text)
//            contactsView.listModel = teamModel.teams
        }
    }

    Button {
        id: no
        x: 298
        y: 175
        text: qsTr("取消")
        onClicked: {
            updatedialog.destroy()
        }
    }


}

