import QtQuick 2.0
import Felgo 3.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import "../model"
import "../components"

Page {
    id: personalPage
//    title: "Person Page"
    backgroundColor: "#ebebeb"

    Constant{ id: constant}


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

                Rectangle {
                    Layout.fillWidth: true
                    height: rowLayout1.height + 10

                    RowLayout {
                        id: rowLayout1
                        width: parent.width
                        anchors.verticalCenter: parent.verticalCenter
                        spacing: 10

                        Item {  width: parent.spacing;  height: parent.height }

                        AppImage {
                            height: 110
                            width: 110
                            sourceSize: Qt.size(width, height)
                            source: profilemsg.heading
                        }

                        ColumnLayout {
                            Layout.fillHeight: true
                            AppText {
                                text: profilemsg.nickname
                                font.family: "微软雅黑"
                                font.pointSize: constant.normalFontPointSize
                            }
                            AppText {
                                text: profilemsg.account
                                font.pointSize: constant.normalFontPointSize
                                font.family: "微软雅黑"
                                color: "#888"
                            }
                        }

                        Item { Layout.fillWidth: true }
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                var component = Qt.createComponent("./Personal/setting.qml");
                                if(component.status === Component.Ready)
                                {
                                    personalPage.navigationStack.push(component);
                                }
                            }
                        }
                    }
                }

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
                            iconSource: constant.myPostsLabelIcon
                            labelText:  qsTr("相册")
                            fontPointSize: constant.middleFontPointSize + 1.0
                        }

                        Separator {
                            Layout.fillWidth: true;
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
                            iconSource: constant.favoritesLabelIcon
                            labelText:  qsTr("收藏")
                            fontPointSize: constant.middleFontPointSize + 1.0
                        }
                    }
                }

                IconLabel {
                    Layout.fillWidth: true
                    height: 70
                    iconWidth: 40
                    iconHeight: 40
                    iconSource: constant.walletLabelIcon
                    labelText:  qsTr("钱包")
                    fontPointSize: constant.middleFontPointSize + 1.0
                }

                IconLabel {
                    Layout.fillWidth: true
                    height: 70
                    iconWidth: 40
                    iconHeight: 40
                    iconSource: constant.settingsLabelIcon
                    labelText:  qsTr("退出系统")
                    fontPointSize: constant.middleFontPointSize + 1.0
                    onClicked: {
                        Qt.quit();
                    }
                }
            }
        }
    }
}
