import QtQuick 2.0
import Felgo 3.0

Page {
    id: searchPage
  rightBarItem: NavigationBarItem{
    Row{
        property real backButtonWidth: dp(Theme.navigationTabBar.height)
        height: dp(Theme.navigationBar.height)
        width: searchPage.width - backButtonWidth
        anchors.right: parent.right

        SearchBar{
            id:searchBar
            placeHolderText: "输入帐号"
            inputBackgroundColor: Theme.backgroundColor
            barBackgroundColor: "transparent"
            showClearButton: false
            anchors.verticalCenter: parent.verticalCenter
            width: textField.displayText != "" ? parent.width - searchButton.width - dp(Theme.contentPadding) : parent.width
            Behavior on  width { NumberAnimation{ duration: 150; easing.type: Easing.InOutQuad}}

            textField.onDisplayTextChanged: {
                //当值改变时进行处理
            }
        }

        AppButton{
            id: searchButton
            flat: true
            text: "搜索"
            width: 40
            anchors.verticalCenter: parent.verticalCenter
            horizontalMargin: 0
            textColor: Theme.textColor
            textColorPressed: Qt.darker(Theme.textColor,1.2)
            textSize: sp(14)
            opacity: searchBar.textField.displayText != ""
            Behavior on opacity {NumberAnimation{duration: 150}}
            onClicked: {
                friends_handle.search_friends(searchBar.text)
                searchBar.text=""

//                var component = Qt.createComponent("./exam.qml");
//                if(component.status === Component.Ready)
//                {
//                    searchPage.navigationStack.push(component);
////                    searchPage.navigationStack.push(component,{nickname:buddy.nickname,account:buddy.account,heading:buddy.heading});
//                }
//                console.log(buddy.account+" : "+buddy.nickname)

                if(buddy.visShow)
                {
                    //进入好友界面
                    var component = Qt.createComponent("../ProfilePage.qml");
                    if(component.status === Component.Ready)
                    {
                        searchPage.navigationStack.push(component,{nickname:buddy.nickname,account:buddy.account,heading:buddy.heading});
                    }
                }else
                {
//                        进去查找的好友界面
                    var component = Qt.createComponent("./searchMsgPage.qml");
                    if(component.status === Component.Ready)
                    {
                        searchPage.navigationStack.push(component);
                    }
                }

//                if(buddy.account!="")
//                {
//                    console.log("friends_handle.search_friends(searchBar.text)")
//                    if(buddy.visShow)
//                    {
//                        //进入好友界面
//                        var component = Qt.createComponent("../ProfilePage.qml");
//                        if(component.status === Component.Ready)
//                        {
//                            searchPage.navigationStack.push(component,{nickname:buddy.nickname,account:buddy.account,heading:buddy.heading});
//                        }
//                    }else
//                    {
////                        进去查找的好友界面
//                        var component = Qt.createComponent("./searchMsgPage.qml");
//                        if(component.status === Component.Ready)
//                        {
//                            searchPage.navigationStack.push(component);
//                        }
//                    }
//                }
//                else
//                {
//                    errormsg.visible = true
//                }
                //在这里判断该用户是否存在来进行选择
            }
        }
    }

  }

  AppText{
    id: errormsg
    visible: false
    anchors.centerIn: parent
    text: qsTr("该用户不存在")
  }

}
