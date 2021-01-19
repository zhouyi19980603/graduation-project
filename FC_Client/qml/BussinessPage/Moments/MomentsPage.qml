import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.1
import "../../Component"

Page {
    id:cicle
    width: 360
    height: 720
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
    Component{
        id:head_part
        Rectangle{
            id:part
            width: cicle.width
            height: cicle.height/3+70
            Rectangle{
                id:firstpart
                width: cicle.width
                height: cicle.height/3
                Image {
                    id: image
                    anchors.fill: parent
                    source: "back.jpg"
                    fillMode: Image.PreserveAspectCrop
                }
                Label {
                    id: label
                    width: 50
                    height: 27
                    color: "#ffffff"
                    anchors.right: parent.right
                    anchors.rightMargin: 100
                    font.pixelSize: 20
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 15
                    text: qsTr("Girgle")
                }
                Image {
                    id: heading
                    source: "logo.jpg"
                    width: 70
                    height: 70
                    anchors.right: parent.right
                    anchors.rightMargin: 12
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: -15
                    MouseArea{
                        anchors.fill: parent
                        onClicked: moments_control.publish_dynamic()
                    }
                }
            }
        }

    }


        ListView{
            header: head_part
            width: parent.width
            height: parent.height
            model: moments_model
            delegate: cicleDelegate
            snapMode: ListView.NoSnap
        }

    /*ListModel{
        id:cicleModel
        ListElement{
            heading:"@13456.jpg"
            nickname:"张礼"
            content_text:"夜阑卧听风吹雨。"
            content_image:"one.jpg"
        }
        ListElement{
            heading:"@23456.jpg"
            nickname:"陈婧"
            content_text:"不喜欢雨天!!"
            content_image:"two.jpg"
        }
        ListElement{
            heading:"@23456.jpg"
            nickname:"陈婧"
            content_text:"不喜欢雨天!!"
            content_image:"two.jpg"
        }
    }*/

    Component{
        id:cicleDelegate
        Rectangle{
            anchors.topMargin: 40
            width: parent.width
            height: model_heading.height+nick.height+content.height+tail.height

            Image {
                id: model_heading
                source: heading
                width: 50
                height: 50
                anchors.left: parent.left
                anchors.leftMargin: 10
            }

            Label {
                id: nick
                color: "#3288de"
                anchors.left: model_heading.right
                anchors.leftMargin: 7
                font.pixelSize: 20
                text: nickname
            }

            Rectangle{
                id:content
                width: parent.width-model_heading.width-17
                anchors.left: model_heading.right
                anchors.leftMargin: 7
                anchors.top: nick.bottom
                anchors.topMargin: 3
                height: element_text.height+element_image.height

                Text {
                    id: element_text
                    width: parent.width-100
                    text: content_text
                    font.pixelSize: 20
                    wrapMode: Text.WordWrap
                }
                Image {
                    id: element_image
                    anchors.top: element_text.bottom
                    width: 250
                    height: 220
                    fillMode: Image.PreserveAspectCrop
                    source: content_image
                }
            }
            Rectangle{
                id: tail
                anchors.top: content.bottom
                anchors.topMargin: 15
                height: 30
                anchors.left: model_heading.right
                anchors.leftMargin: 7
                width: content.width

                Label{
                    id:time
                    text: qsTr("1分钟前")

                }
                Image {
                    id: point
                    source: "point.png"
                    anchors.right: parent.right
                    anchors.rightMargin: 9
                    width: 25
                    height: 20
                    fillMode: Image.PreserveAspectCrop
                }
            }
            Rectangle{
                anchors.top: tail.bottom
                anchors.topMargin: 10
                color: "#cdc7c7"
                width: parent.width
                height: 1
            }
        }


    }
}
