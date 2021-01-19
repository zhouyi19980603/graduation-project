import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Window 2.0
import QtQuick.Layouts 1.1
import "../Component"

Page {
    id: personalPage
    title: qsTr("Personal")
    color: "#ebebeb"

    Constant {  id: constant  }

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

                        Image {
                            height: 110
                            width: 110
                            sourceSize: Qt.size(width, height)
                            source: profilemsg.heading
                        }

                        ColumnLayout {
                            Layout.fillHeight: true
                            Label {
                                text: profilemsg.nickname
                                font.family: "微软雅黑"
                                font.pointSize: constant.normalFontPointSize
                            }
                            Label {
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
                                __PushPage(Qt.resolvedUrl("./Personal/Settings/Setting.qml"), {} ); //压入一个新的界面
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
                            Layout.fillWidth: true; Layout.leftMargin: 10; Layout.rightMargin: 10
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
                    labelText:  qsTr("设置")
                    fontPointSize: constant.middleFontPointSize + 1.0
                    onClicked: {
//                        __PushPage(Qt.resolvedUrl("./Personal/SettingsPage.qml"), {} ); //压入一个新的界面
                    }
                }
            }
        }
    }
}

