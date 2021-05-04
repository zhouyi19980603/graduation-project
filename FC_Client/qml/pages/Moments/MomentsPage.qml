import QtQuick 2.0
import Felgo 3.0
import "../../components"
import "../../model"

Page {
    id:momentsPage
    Constant{
        id:constant
    }

    rightBarItem: IconButtonBarItem{
        icon: IconType.plus
        onClicked: {
            //点击后进行处理
            addpostModal.open();
        }

    }

    AddPostModal{
        id:addpostModal
    }

    Component{
        id:head_part
        Rectangle{
            id:part
            width: momentsPage.width
            height: momentsPage.height/3+70
            Rectangle{
                id:firstpart
                width: momentsPage.width
                height: momentsPage.height/3
                AppImage {
                    id: image
                    anchors.fill: parent
                    source: "../../qml/BussinessPage/Moments/back.jpg"
                    fillMode: Image.PreserveAspectCrop
                }
                AppText {
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
                AppImage {
                    id: heading
                    source: profilemsg.heading
                    width: 70
                    height: 70
                    anchors.right: parent.right
                    anchors.rightMargin: 12
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: -15
                    MouseArea{
                        anchors.fill: parent
                        onClicked: console.log(dataSource)
                    }
                }
            }
        }

    }

    property var dataSource: ""


    JsonListModel{
        id:jsonModel
        source: dataSource
    }
    SortFilterProxyModel {
        id:sortModel
        //        sourceModel: jsonModel
        sourceModel: moments_model
        sorters: StringSorter { roleName: "time"
            sortOrder:Qt.DescendingOrder 	 }
    }

    Connections{
      target: moments_control
      onComments:{
      console.log("收到信号这是数据 "+data)
      }
    }
//    Connections{
//      target: moments_control
//      onComments_data:{
//      console.log("收到信号这是数据 "+data)
//      }
//      onComments:{
//        console.log("收到信号onComments")
//      }
//    }
//    Connections{
//      target: comments_model
//      onComment_mess:console.log("收到信号onComments")
//    }

    AppListView{
        id:listView
        header: head_part
        anchors.fill: parent
        spacing: dp(15)

        width: parent.width
        height: parent.height
//                    model: moments_model
        model: sortModel
        //            delegate: cicleDelegate
        delegate: FeedListDelegate {
            modelIndex: index
            modelItem: model

            onCommentClicked: {

                //在这里请求评论和点赞事件
                //                  moments_control.request_dynamic_data(dyId)
                var component = Qt.createComponent("./PostPage.qml");
                if(component.status === Component.Ready)
                {
                    momentsPage.navigationStack.push(component,{"modelIndex": modelIndex, "modelItem": modelItem, "state": "addingComment"});
                }
            }

            onPostClicked: {
                //                  console.log("有事件接收"+"dyid:"+dyId)
                console.log("有事件接收"+ "dyId"+model.dyId)

                //在这里请求评论和点赞事件
                moments_control.request_post_comments_data(dyId);
                var component = Qt.createComponent("./PostPage.qml");
                if(component.status === Component.Ready)
                {
                    momentsPage.navigationStack.push(component,{"modelIndex": modelIndex, "modelItem": modelItem});
                }
            }
            onLikeClicked: {
                                console.log("有点赞事件接收"+ "dyId"+modelItem.dyId)
                moments_control.like(modelItem.dyId);
//                name.icon = modelItem.is_like? IconType.thumbsup : IconType.thumbsoup
//                sortModel.get(modelIndex).is_like = true;
            }

        }
        snapMode: ListView.NoSnap
    }


    Component{
        id:cicleDelegate
        Rectangle{
            anchors.topMargin: 40
            width: parent.width
            height: model_heading.height+nick.height+content.height+tail.height

            AppImage {
                id: model_heading
                source: heading
                width: 50
                height: 50
                anchors.left: parent.left
                anchors.leftMargin: 10
            }

            AppText {
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

                AppText {
                    id: element_text
                    width: parent.width-100
                    text: content_text
                    font.pixelSize: 20
                    wrapMode: Text.WordWrap
                }
                AppImage {
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

                AppText{
                    id:tiem
                    text: time

                }
                AppImage {
                    id: like
                    source:is_like ? constant.momentsLikeIconed : constant.momentsLikeIcon;
                    anchors.right: parent.right
                    anchors.rightMargin: parent.width/3
                    width: 20
                    height: 20
                    fillMode: Image.PreserveAspectCrop
                    MouseArea{
                        anchors.fill: parent
                        onClicked:{
                            is_like = true;
                            if(like.source == constant.momentsLikeIcon)
                                moments_control.like(dyId);
                            like.source = constant.momentsLikeIconed;//以及点赞
                            //likeModule.text =  profilemsg.nickname
                            //console.log(profilemsg.nickname)//显示自己的昵称就可
                        }
                        //                        onClicked: console.log("发送点赞信号")
                    }
                }
                AppImage {
                    id: comments
                    source:constant.momentsCommentsIcon
                    anchors.right: parent.right
                    anchors.rightMargin: parent.width/5
                    width: 20
                    height: 20
                    fillMode: Image.PreserveAspectCrop
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            //发送消息给服务端请求信息来填充界面
                            //弹出新的评论界面
                            var component = Qt.createComponent("CommentsPage.qml");
                            if(component.status === Component.Ready){
                                var object=component.createObject(cicle);
                                //可以修改对方的值
                                object.postId = dyId;
                            }
                            moments_control.request_post_comments_data(dyId);
                        }
                    }
                }
            }
            AppTextEdit{
                id:likeModule
                anchors.top: tail.bottom
                anchors.topMargin: 6
                anchors.left: model_heading.right
                anchors.leftMargin: 7
                text:like_text
                visible: likeModule.text!=""
            }
            //            横线
            Rectangle{
                id:split
                anchors.top: likeModule.visible? likeModule : tail.bottom
                anchors.topMargin: 10
                color: "#cdc7c7"
                width: parent.width
                height: 1
            }

        }


    }//component的结尾
}
