import QtQuick 2.0
import Felgo 3.0
import QtQuick.Layouts 1.1
import "../model"
import "../components"

Page {
    id: chatsView
    title: qsTr("FreeC")
    backgroundColor: "white"
    property int headPrtraitSize: 54

    rightBarItem: IconButtonBarItem{
        icon: IconType.plus

        onClicked: {
            //添加好友
            var component = Qt.createComponent("./Contact/searchPage.qml");
            if(component.status === Component.Ready)
            {
                chatsView.navigationStack.push(component);
            }
        }
    }

    DataModel{
        id:datamodel
    }

    property var jsonData: [
        {
            "heading":"../../assets/resource/tests/tests001.jpeg",
            "name":"张力",
            "content":"在马?"
        },{
            "heading":"../../assets/resource/tests/tests001.jpeg",
            "name":"张力",
            "content":"在马?"
        }
    ]
    JsonListModel{
        id:listModel
        source: chatsView.jsonData

    }
    SortFilterProxyModel{
        id:sortModel
        sourceModel: chat_listModel
    }
    AppListView{
        id: listView
        anchors.topMargin: -93
        model: sortModel
        delegate:delegateCom
    }

    Component{
        id:delegateCom
        Rectangle{
            id:rect
            width: parent.width
            height: 70
            AppImage{
                id:headImage
                source: heading
                //                    source: "../../assets/resource/tests/tests001.jpeg"
                anchors.left: parent.left
                anchors.leftMargin: 8
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 8
                anchors.topMargin: 8
                width: headPrtraitSize
                fillMode:Image.PreserveAspectFit
            }
            AppText{
                id:nameText
                anchors.left: headImage.right
                anchors.leftMargin: 12
                anchors.top: parent.top
                anchors.topMargin: 10
                height: 30
                text: name
                fontSize: 10
                verticalAlignment: Text.AlignVCenter
            }

            AppText{
                id:contentText
                anchors.left: headImage.right
                anchors.leftMargin: 12
                anchors.top: nameText.bottom
                height: 24
                text: content
                fontSize: 8
                verticalAlignment: Text.AlignVCenter
            }

            Separator{
                anchors.left: headImage.right
                anchors.leftMargin: 12
                anchors.top: parent.bottom
                anchors.topMargin: -1
                orientation: Qt.Horizontal
                color: "#666"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    message_listModel.set_currentChatId(account)
                    var component = Qt.createComponent("./Chat/ChatPage.qml");
                    if(component.status === Component.Ready)
                    {
                        chatsView.navigationStack.push(component,{s_username:name,s_userid:account});
                    }
                }
            }
        }
    }


}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:5;anchors_height:54}
}
##^##*/
