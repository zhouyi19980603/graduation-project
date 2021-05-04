import QtQuick 2.0
import Felgo 3.0

Page {

    title: "设置备注名"
    backgroundColor: "#ebebeb"
    rightBarItem: IconButtonBarItem{
        icon: IconType.save
        onClicked: {
            //点击完成后会自动退出这个界面
            //首先判断值进行更改没，如果没有改则不会进行click事件
        }
    }
    Column{
        width: parent.width
        AppText{
            id:nameText
            text: qsTr("备注名")
            fontSize: 10
        }

        Rectangle{
            anchors.top: nameText.bottom
            anchors.topMargin: 8
            width: parent.width
            color: "white"
            height: 70
            AppTextInput{
                id:texts
                text: qsTr("周意")
                width: parent.width
                height: parent.height
                anchors.left: parent.left
                anchors.leftMargin: 16
                font.pointSize: 16
                verticalAlignment: Text.AlignVCenter
            }
        }
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
