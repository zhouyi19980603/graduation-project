import QtQuick 2.14
import Felgo 3.0
import QtQuick.Dialogs 1.1

Page{
    id: settingPage

    property alias nickname: nick.text
    title: "SettingPage"


    Rectangle{
        id:rect1
        border.color: "#ccc"
        width: parent.width
        height: 70
        AppImage {
            id: heading
            anchors.right: image2.left
            width: 66
            height: 54
            anchors.verticalCenter: parent.verticalCenter
            fillMode: Image.PreserveAspectFit
            source: profilemsg.heading
        }

        AppText {
            id: label1
            anchors.left: parent.left
            text: qsTr("头像")
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            font.pointSize: 14
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        AppImage {
            id: image2
            anchors.right: parent.right
            width: 32
            height: 17
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin: 16
            rotation: 180
            fillMode: Image.PreserveAspectFit
            source: "../../../assets/resource/icons/label-icons/return.png"
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
//                imageDialog.open()
                nativeUtils.displayImagePicker(qsTr("Upload image"));
            }
        }
    }

    Connections{
        target: nativeUtils
        onImagePickerFinished:{
            if(accepted){
                var end = path.length;
//                console.log(path.substring(7,end))
                profile_handle.updateHeading(path.substring(7,end))
            }
        }

    }
    FileDialog{
        id:imageDialog
        title: qsTr("Please choose a picture")
        nameFilters: [ "Image files (*.jpg *.png)", "All files (*)" ]
        folder: ".."
        onAccepted: {
            var str = imageDialog.fileUrl.toString()
            console.log("str: " +str)
            var end = str.length;
//            filepath = str.substring(7,end)
            //profile_handle.updateHeading(filepath)
            console.log(str.substring(7,end))
        }
        onRejected: { console.log("Canceled") }
    }
    Rectangle {
        id: rectangle
        y: 70
        width: parent.width
        height: 70
        border.color: "#cccccc"

        AppText {
            id: label2
            anchors.left: parent.left
            text: qsTr("昵称")
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 14
        }

        AppImage {
            id: image3
            anchors.right: parent.right
            width: 32
            height: 17
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin: 16
            rotation: 180
            fillMode: Image.PreserveAspectFit
            source: "../../../assets/resource/icons/label-icons/return.png"
        }

        AppTextInput {
            id: nick
            width: 112
            height: 37
            text: profilemsg.nickname
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: 0
            anchors.right: image3.left
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 14
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                var component = Qt.createComponent("./updateName.qml");
                if(component.status === Component.Ready)
                {
                    personalPage.navigationStack.push(component);
                }
            }
        }
    }

    Rectangle {
        y: 140
        width: parent.width
        height: 70
        border.color: "#cccccc"

        AppText {
            id: label3
            text: qsTr("帐号")
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 14
        }

        AppImage {
            id: image4
            anchors.right: parent.right
            width: 32
            height: 17
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin: 16
            rotation: 180
            fillMode: Image.PreserveAspectFit
            visible: false
            source: "../../../assets/resource/icons/label-icons/return.png"
        }
        AppText {
            id: account
            text: profilemsg.account
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: 0
            anchors.right: image4.left
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 14
        }
    }

    Rectangle {
        y: 210
        width: parent.width
        height: 70
        border.color: "#cccccc"

        AppText {
            id: label4
            text: qsTr("性别")
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 14
        }
        AppImage {
            id: image8
            anchors.right: parent.right
            width: 32
            height: 17
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin: 16
            rotation: 180
            fillMode: Image.PreserveAspectFit
            source: "../../../assets/resource/icons/label-icons/return.png"
        }

        AppTextInput {
            id: sex
            width: 112
            height: 37
            text: profilemsg.gender
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin: 0
            anchors.right: image8.left
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 14
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                var component = Qt.createComponent("./updateSex.qml");
                if(component.status === Component.Ready)
                {
                    personalPage.navigationStack.push(component);

                }
            }
        }
    }

}


/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
