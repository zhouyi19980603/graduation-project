import QtQuick 2.0
import QtQuick.Controls 2.14
import QtQuick.Window 2.12
import QtQuick.Layouts 1.11
//import Message_Handle 1.0

Page{
    id: element
    width: 420
    height: 800
    //屏蔽父对象的鼠标事件
    signal addfriends(string msg);

    MouseArea{
        id: mouseArea
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent
    }
    Image {
        id: image
        x: 0
        y: 8
        width: 32
        height: 32
        fillMode: Image.PreserveAspectFit
        source: "asserts/return.jpg"
        MouseArea{
            anchors.fill: parent
            onClicked: {
                console.log("mouseArea")
//                addui.destroy(); //destroy to this ui
                var component = Qt.createComponent("AddUI.qml");
                if(component.status === Component.Ready){
                    var object=component.createObject(element);
                }
            }
        }
    }


    //repeater留下来当扩展
//    Repeater {
//       model:buddys

       Rectangle{
           id:rect
           width: 420
           height: 120
           anchors.top: image.bottom
           Rectangle {
               id: fileicon
               width: 80
               height: 80
               radius: 50
               color:"yellow"
               anchors{
                   left: parent.left
                   leftMargin: 20
                   verticalCenter: parent.verticalCenter
               }

               //使其位于margin
           }
           Column{
               anchors{
                   left: fileicon.right
                   leftMargin: 20
                   top: parent.top
                   topMargin:20
               }
               spacing: 10

               Label{
                   id:account
                   text: qsTr("@12345")
               }
               Label{
                   id:nick
                   text: qsTr("Gftae")
                   color: "grey"
               }
           }
       }

//    }
    Button{
        id:addFriendButton
        text: "添加好友"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        width: parent.width
        onClicked: {
            console.log("add Friends")
//            element.addfriends("hello C++")
            message_handle.add_friends("@12345")
            //请求添加为好友的信息

        }
    }
    function showF(msg)
    {
        console.log("进来了")
        console.log(msg)
        account.text = "zhouyi"
        console.log("this is msg",account.text)
    }

}

