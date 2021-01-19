import QtQuick 2.0
//import CppModel 1.0
Item {
//    FC_Message_ListModel{
//        id:message_listModel
//    }
    Component{
        id:message_listDelegate
        Item {
            Rectangle{
                id:writerrect
                anchors.bottom: headimgrect.top
                anchors.left: headimgrect.left
                width: headimgrect.width
                height: width/2
                color: "red"
            }
            Rectangle{
                id:headimgrect
                width: 25
                height: width
                radius: width/2
                color: "blue"
            }
            Rectangle{
                id:contentimg
                anchors.left: headimgrect.right
                anchors.verticalCenter: headimgrect.Center
                height: headimgrect.height
                width: height*2
                color: "pink"
            }
        }
    }
    ListView{
        id:message_listView
        x:0
        y:0
        width: parent.width
        height: 200
        model: message_listModel
        delegate: message_listDelegate
    }



    //    ListModel {
    //        id: listModel
    //        ListElement {
    //            name: "I"
    //            content: "hi"
    //        }
    //        ListElement {
    //            name: "I"
    //            content: "how are you"
    //        }
    //        ListElement {
    //            name: "NotI"
    //            content: "I'm fine"
    //        }
    //        ListElement {
    //            name: "NotI"
    //            content: "And you?"
    //        }
    //        ListElement {
    //            name: "I"
    //            content: "too."
    //        }
    //    }
    //    Component {
    //        id: listDelegate
    //        Item {
    //            width: listView.width
    //            height: 40
    //            Row {
    //                Text {
    //                    id: rowtext
    //                    text: content
    //                }
    //                anchors.right: name === "I" ? parent.right : parent.left - rowtext.width
    //            }
    //        }
    //    }
    //    ListView {
    //        id: listView
    //        x: 80
    //        y: 58
    //        width: 448
    //        height: 203
    //        clip: true
    //        model: listModel
    //        delegate: listDelegate
    //    }




//    Component{
//        id:testDelegate
//        Rectangle {
//            radius: 4
//            color: "blue"
//            height: 20
//            width: 50
//            MouseArea{
//                anchors.fill: parent
//                onClicked: {
//                    testView.model.add(["a","b","c","d"])
//                }
//            }

//            Row{
//                Text {text: time}
//                Text {text: writer}
//                Text {text: headimg}
//                Text {text: content}
////                Text {text: testView.model.time}
////                Text {text: testView.model.writer}
////                Text {text: testView.model.headimg}
////                Text {text: testView.model.content}
//            }
//        }
//    }
//    ListView{
//        width: 100
//        height: 100
//        x:0
//        y:0
//        id:testView
//        model: FC_Message_ListModel{}
//        delegate: testDelegate
//    }
}
