import QtQuick 2.0
import Felgo 3.0
import "../../components"

Page {
    id: page

    title: "更改名字"
    rightBarItem: IconButtonBarItem{
        id:editorName
        icon: IconType.check
        //        title: qsTr("保存")

        onClicked: {
            //可以进行操作
            profile_handle.updateNick(newname.text)
            page.navigationStack.pop();
        }
    }

    //    Row{
    //        spacing: 40
    AppTextInput {
        id: newname
        width: 480
        height: 40
//        text: "#settingPage.nickname#"
        text: settingPage.nickname
        anchors.left: parent.left
        anchors.leftMargin: 24
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 14

    }

    Separator{
        color: "black"
        orientation: Qt.Horizontal
        anchors.top: newname.bottom
        anchors.left: parent.left
        anchors.leftMargin: 24
    }
    AppText {
        id: textInput1
        width: 480
        height: 25
        text: qsTr("换个名字，小伙伴更容易找到你哟")
        anchors.left: parent.left
        anchors.leftMargin: 24
        anchors.top: newname.bottom
        anchors.topMargin: 8
        font.pixelSize: 12
    }
    //    }


}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
