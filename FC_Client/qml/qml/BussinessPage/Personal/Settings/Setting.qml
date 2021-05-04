import QtQuick 2.14
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.4
import QtQuick.Layouts 1.11
import QtQuick.Dialogs 1.1
import "../../../Component"
Page{
    id: settingPage
    width: 360
    height: 720

    property alias heading: heading.source
    property alias nickname: nick.text
    property alias sex: sex.text
    property var filepath

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
                text: personalPage.title
                color: "white"
                anchors.verticalCenter: parent.verticalCenter
                font.family: "微软雅黑"
                font.pointSize: constant.middleFontPointSize
            }
        }
    }
    Rectangle{
        id:rect1
        x: 0
        y: 6
        border.color: "#ccc"
        width: parent.width
        height: 70
        Image {
            id: heading
            anchors.right: image2.left
            anchors.centerIn: parent
            width: 66
            height: 54
            anchors.horizontalCenterOffset: 118
            fillMode: Image.PreserveAspectFit
            source: profilemsg.heading
        }

        Label {
            id: label1
            anchors.left: parent.left
            anchors.centerIn: parent
            width: 48
            height: 37
            text: qsTr("头像")
            anchors.horizontalCenterOffset: -148
            font.pointSize: 14
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Image {
            id: image2
            anchors.right: parent.right
            anchors.centerIn: parent
            anchors.horizontalCenterOffset: 166
            width: 32
            height: 17
            rotation: 180
            fillMode: Image.PreserveAspectFit
            source: "../../../../asserts/return.jpg"
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                imageDialog.open()
            }
        }
    }

    FileDialog{
        id:imageDialog
        title: qsTr("Please choose a picture")
        nameFilters: [ "Image files (*.jpg *.png)", "All files (*)" ]
        folder: ".."
//        onAccepted: { heading.source = imageDialog.fileUrl }
        onAccepted: {
            var str = imageDialog.fileUrl.toString()
            var end = str.length;
            filepath = str.substring(7,end)
            profile_handle.updateHeading(filepath)
        }
        onRejected: { console.log("Canceled") }
    }
    Rectangle {
        x: 0
        y: 74
        width: parent.width
        height: 70
        border.color: "#cccccc"

        Label {
            id: label2
            width: 48
            height: 37
            anchors.left: parent.left
            anchors.centerIn: parent
            anchors.horizontalCenterOffset: -148
            text: qsTr("昵称")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 14
        }

        Image {
            id: image3
            anchors.right: parent.right
            anchors.centerIn: parent
            anchors.horizontalCenterOffset: 166
            width: 32
            height: 17
            rotation: 180
            fillMode: Image.PreserveAspectFit
            source: "../../../../asserts/return.jpg"
        }

        TextInput {
            id: nick
            width: 112
            height: 37
            text: profilemsg.nickname
            anchors.verticalCenterOffset: 0
            anchors.horizontalCenterOffset: 93
            anchors.right: image3.left
            anchors.centerIn: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 14
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                __PushPage(Qt.resolvedUrl("./UpdateName.qml"), {} ); //压入一个新的界面
            }
        }
    }

    Rectangle {
        x: 0
        y: 144
        width: parent.width
        height: 70
        border.color: "#cccccc"

        Label {
            id: label3
            width: 48
            height: 37
            text: qsTr("帐号")
            anchors.left: parent.left
            anchors.centerIn: parent
            anchors.horizontalCenterOffset: -148
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 14
        }

        Label {
            id: account
            width: 112
            height: 37
            text: profilemsg.account
            anchors.verticalCenterOffset: 0
            anchors.horizontalCenterOffset: 114
            anchors.rightMargin: -114
            anchors.right: parent.right
            anchors.centerIn: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 14
        }
    }

    Rectangle {
        x: 0
        y: 214
        width: parent.width
        height: 70
        border.color: "#cccccc"

        Label {
            id: label4
            width: 48
            height: 37
            text: qsTr("性别")
            anchors.left: parent.left
            anchors.centerIn: parent
            anchors.horizontalCenterOffset: -148
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 14
        }
        Image {
            id: image8
            anchors.right: parent.right
            anchors.centerIn: parent
            anchors.horizontalCenterOffset: 166
            width: 32
            height: 17
            rotation: 180
            fillMode: Image.PreserveAspectFit
            source: "../../../../asserts/return.jpg"
        }

        TextInput {
            id: sex
            width: 112
            height: 37
            text: profilemsg.gender
            anchors.horizontalCenterOffset: 97
            anchors.rightMargin: -97
            anchors.right: image8.left
            anchors.centerIn: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 14
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                __PushPage(Qt.resolvedUrl("./UpdateSex.qml"), {} ); //压入一个新的界面
            }
        }
    }
}

