import Felgo 3.0
import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import "../components"
import "../model"


Page {
    id: discoverPage
    title: qsTr("发现")
    backgroundColor: "#ebebeb"

    property var dataSource: ""
    rightBarItem: IconButtonBarItem{
        icon: IconType.plus

        onClicked: {
            //添加好友
            var component = Qt.createComponent("./Contact/searchPage.qml");
            if(component.status === Component.Ready)
            {
                discoverPage.navigationStack.push(component);
            }
        }
    }
    Constant {  id: constant  }

//    DataModel{
//        id:dataModel
//    }

    Connections{
      target: moments_control
      onComments_data:{
      console.log("收到信号这是数据 "+data)
      }
      onComments:{
        console.log("收到信号onComments")
      }
    }
    Connections{
      target: moments_model
      onUpdate_mess:{
//          listView.currentIndex = 0
//        console.log("是发送了信号")
//          console.log(listView.count)
      }
      onReplay_dy:{
          dataSource = JSON.parse(str)
//          console.log("是发送了信号")
//          console.log("值是多少str:"+str)
          var component = Qt.createComponent("./Moments/MomentsPage.qml");
          if(component.status === Component.Ready)
          {
              discoverPage.navigationStack.push(component,{"dataSource":dataSource});
          }
      }
    }

    ScrollView {
        id: page
        anchors.fill: parent

        horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff

        Item {
            id: content

            width: page.width
            height: Math.max(page.viewport.height, column.implicitHeight + 2 * column.spacing)

            ColumnLayout {
                id: column
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                spacing: 20

                Item {  width: parent.spacing;  height: parent.height }

                IconLabel {
                    Layout.fillWidth: true
                    height: 70
                    iconWidth: 40
                    iconHeight: 40
                    iconSource: constant.momentsLabelIcon
                    labelText:  qsTr("朋友圈")
                    fontPointSize: constant.middleFontPointSize + 1.0

                    Image {
                        id: momentsCurrentActiveFriend
                        anchors.right: parent.right
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.rightMargin: column.spacing
                        width: 60
                        height: 60
                        sourceSize: Qt.size(width, height)
                        source: constant.testPic
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            //填充jsonModel的信息
                            moments_control.request_dynamic_data();
//                            dataSource = JSON.parse();
                            var component = Qt.createComponent("./Moments/MomentsPage.qml");
                            if(component.status === Component.Ready)
                            {
                                discoverPage.navigationStack.push(component,{"dataSource":dataSource});
                            }

                            //在这里请求数据
//                            moments_control.request_dynamic_data();
//                            __PushPage(Qt.resolvedUrl("./Moments/MomentsPage.qml"), {} ); //压入一个新的界面
                        }
                    }

                } // First Group

                Rectangle {
                    id: colmnLayout2Parent
                    Layout.fillWidth: true
                    height: columnLayout2.height
                    color: "white"
                    ColumnLayout {
                        id: columnLayout2
                        width: parent.width
                        spacing: 0
                        IconLabel {
                            Layout.fillWidth: true
                            height: 70
                            iconWidth: 40
                            iconHeight: 40
                            iconSource: constant.scanQRCodeLabelIcon
                            labelText:  qsTr("二维码")
                            fontPointSize: constant.middleFontPointSize + 1.0
                        }

                        Separator {
                            Layout.fillWidth: true;
                            Layout.alignment: Qt.AlignLeft
//                            Layout.alignment: Qt.AlignRight
                            Layout.leftMargin: 10;
                            Layout.rightMargin: 10
                            color: "#666";
                            orientation: Qt.Horizontal ;
                            anchors.horizontalCenter: parent.horizontalCenter
                        }

                        IconLabel {
                            Layout.fillWidth: true
                            height: 70
                            iconWidth: 40
                            iconHeight: 40
                            iconSource: constant.shakeLabelIcon
                            labelText:  qsTr("摇一摇")
                            fontPointSize: constant.middleFontPointSize + 1.0
                        }
                    }
                } // Second Group


                Rectangle {
                    Layout.fillWidth: true
                    height: columnLayout3.height
                    color: "white"
                    ColumnLayout {
                        id: columnLayout3
                        width: parent.width
                        spacing: 0
                        IconLabel {
                            Layout.fillWidth: true
                            height: 70
                            iconWidth: 40
                            iconHeight: 40
                            iconSource: constant.peopleNearbyLabelIcon
                            labelText:  qsTr("附近的人")
                            fontPointSize: constant.middleFontPointSize + 1.0
                        }

                        Separator {
                            Layout.fillWidth: true;
                            Layout.alignment: Qt.AlignLeft
//                            Layout.alignment: Qt.AlignRight
                            Layout.leftMargin: 10;
                            Layout.rightMargin: 10
                            color: "#666"; orientation: Qt.Horizontal ;
                            anchors.horizontalCenter: parent.horizontalCenter
                        }

                        IconLabel {
                            Layout.fillWidth: true
                            height: 70
                            iconWidth: 40
                            iconHeight: 40
                            iconSource: constant.driftBottleLabelIcon
                            labelText:  qsTr("漂流瓶")
                            fontPointSize: constant.middleFontPointSize + 1.0
                        }
                    }
                } // Thrid Group

                IconLabel {
                    Layout.fillWidth: true
                    height: 70
                    iconWidth: 40
                    iconHeight: 40
                    iconSource: constant.gamesLabelIcon
                    labelText:  qsTr("游戏")
                    fontPointSize: constant.middleFontPointSize + 1.0
                } // First Group
            } // Main ColumnLayout
        } // content
    } // ScrollView
}

