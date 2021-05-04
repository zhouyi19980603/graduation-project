import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.0
import "./Component"
import "./BussinessPage"

Page {
    id: mainPage
    title: "Free C"

    Constant { id: constant }

    topBar: TopBar {
        id: topBar
        RowLayout {
            anchors.fill: parent
            Label {
                Layout.leftMargin: 20
                text: title
                color: "white"
            }

            Item { Layout.fillWidth: true }

        }
        // such as menuBar
        Row {

            parent: topBar
            anchors.right: parent.right
            anchors.rightMargin: 10



            IconButton {
                id: iconButton2
                width: topBar.height - 2
                height: topBar.height - 2
                activeIconSource: constant.magnifierActiveIcon
                inactiveIconSource: constant.magnifierInactiveIcon
                onClicked: {

                }
            }

            IconButton {
                id: iconButton1
                width: topBar.height - 2
                height: topBar.height - 2
                activeIconSource: constant.plusActiveIcon
                inactiveIconSource: constant.plusInactiveIcon
                onClicked: {
                    __PushPage(Qt.resolvedUrl("./BussinessPage/Contact/AddUI.qml"), {} ); //压入一个新的界面
                }
            }
        }
    }


    bottomBar: BottomBar {
        id: bottomBar
        property  int iconHeight: topBar.height
        property  int iconWidth: topBar.width
        RowLayout {
            id: iconBar
            spacing: 0
            anchors.fill: parent
            readonly property var iconNames:["聊天","通讯录","发现", "我"]
            function getActiveIconUrl(index) {
                return "./resource/icons/bar-icons/active/"+iconNames[index].toLowerCase()+".png";
            }
            function getInctiveIconUrl(index) {
                return "./resource/icons/bar-icons/inactive/"+iconNames[index].toLowerCase()+".png";
            }

            // Item { Layout.fillWidth: true }

            //Repeater类型用于创建大量类似的项
            Repeater {
                id: repeater
                model:iconBar.iconNames
                Icon {
                    Layout.fillWidth: true
                    iconSize: Qt.size(topBar.height, topBar.height)
                    iconText: iconBar.iconNames[index]
                    activeIconSource: iconBar.getActiveIconUrl(index)
                    inactiveIconSource: iconBar.getInctiveIconUrl(index)
                    activeIconOpacity: (mainListView.currentIndex == index)
                    onClicked: {
                        mainListView.currentIndex = index;
                        mainListView.currentItem.focus = true;
                    }
                }
            }
        }
    }

    ////主界面bottom menu
    MainListView {
        id: mainListView
        focus: mainPage.focus
        anchors.fill: parent
        model: itemsModel
    }


    VisualItemModel {
        id: itemsModel

        ChatsView {
            id: chatsView
            pageStackWindow: mainPage.pageStackWindow
            stackView: mainPage.stackView
            width: mainListView.width
            height: mainListView.height
        }

        ContactsView {
            pageStackWindow: mainPage.pageStackWindow
            stackView: mainPage.stackView
            width: mainListView.width
            height: mainListView.height
        }

        DiscoverPage {
            id: discoverPage
            pageStackWindow: mainPage.pageStackWindow
            stackView: mainPage.stackView
            width: mainListView.width
            height: mainListView.height
        }

        //
        PersonalPage {
            id: personalPage
            pageStackWindow: mainPage.pageStackWindow
            stackView: mainPage.stackView
            width: mainListView.width
            height: mainListView.height
        }
    }
}

