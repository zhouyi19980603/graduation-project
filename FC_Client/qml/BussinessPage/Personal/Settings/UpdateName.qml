import QtQuick 2.14
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.4
import QtQuick.Layouts 1.11
import "../../../Component"

/**************************************************************

  @brief....:这是修改用户昵称时的界面
  @author...: zhouyi
  @date.....:2020-06-08

  ************************************************************/

Page{
    id: updatename
    width: 360
    height: 720
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
                text: qsTr("更改昵称")
                color: "white"
                anchors.verticalCenter: parent.verticalCenter
                font.family: "微软雅黑"
                font.pointSize: constant.middleFontPointSize
            }
            Button {
                id: save
                anchors.right: parent.right
                anchors.rightMargin: 5
                anchors.verticalCenter: parent.verticalCenter
                width: 59
                height: 32
                text: qsTr("保存")
                font.pointSize: 14
                onClicked:{
                    profile_handle.updateNick(newname.text)
                    try { stackView.pop(); }  catch(e) { }
                }
            }
        }
    }

    TextInput {
        id: newname
        x: 15
        y: 49
        width: parent.width
        height: 40
        text: settingPage.nickname
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 14

    }

    Label {
        id: textInput1
        x: 15
        y: 102
        width: parent.width
        height: 25
        text: qsTr("换个名字，小伙伴更容易找到你哟")
        font.pixelSize: 12
    }


}
