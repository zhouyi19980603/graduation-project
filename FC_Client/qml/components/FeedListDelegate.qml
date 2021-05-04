import Felgo 3.0
import QtQuick 2.8


AppPaper {
  id: feedListDelegate

  property int modelIndex: 0
  property var modelItem: null
  property alias name: appB

  signal commentClicked()
  signal postClicked()
  signal likeClicked(Id:string)
  signal refreshLike(string action)


//  Component.onCompleted:refreshLike(appB)
  width: parent.width
  height: column.height + footer.height + footer.anchors.topMargin

  elevated: mouseArea.pressed
  background.color: Theme.backgroundColor
  shadowColor: "#40000000"

  Column {
    id: column
    width: parent.width
    spacing: dp(10)

    Row {
      id: header

      width: parent.width
      height: dp(60)

      leftPadding: dp(Theme.contentPadding)
      spacing: Theme.contentPadding

      RoundedImage {
        id: avatarImage
        anchors.verticalCenter: parent.verticalCenter

        width: dp(40)
        height: width

        source: modelItem.heading
        radius: height / 2
      }

      Column {
        anchors.verticalCenter: parent.verticalCenter

        spacing: dp(2)

        AppText {
          id: authorText
          font.bold: true
          font.pixelSize: sp(12)
          text: modelItem.nickname
        }

        Row {
          height: dp(20)
          spacing: dp(4)

          AppText {
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: sp(10)
            text: modelItem.time
          }
        }
      }
    }

    AppText { //content
      id:conText
      anchors.horizontalCenter: parent.horizontalCenter
      width: parent.width - 2 * dp(Theme.contentPadding)

      font.bold: modelItem.type === "Workout"
      text: modelItem.content_text
//       text: modelItem.con_text
      wrapMode: Text.Wrap
      anchors.bottom:conImage
      anchors.bottomMargin: 8
    }

    AppImage{
        id:conImage
        anchors.left: parent.left
        anchors.leftMargin: 16
        anchors.right: parent.right
        anchors.rightMargin: 16
        anchors.bottom: footer.top
        anchors.bottomMargin: 16
        fillMode: Image.PreserveAspectFit
        source: visible ? modelItem.content_image : ""
        visible: modelItem.content_image !== undefined && modelItem.content_image !== ""
    }

    AppText {
        id:commentsNumberText
        width: parent.width

        color: Theme.secondaryTextColor
        font.pixelSize: sp(12)
        horizontalAlignment: Text.AlignRight
        rightPadding: dp(Theme.contentPadding)

        visible: (Number(modelItem.comNum) >0)
        text: modelItem.comNum + " comment" + (modelItem.comNum>1 ? "s" : "")
    }

  }

  //点赞和评论的部分
  Rectangle {
    id: footer


    anchors {
      top: column.bottom
      topMargin: 16
//      topMargin: modelItem.comments.length > 0 || (modelItem.type == "Post" && modelItem.image == "") ? column.spacing : 0
    }

    width: parent.width
    height: dp(45)

    color: Theme.secondaryBackgroundColor

    AppButton {
      id:appB
      anchors {
        horizontalCenter: parent.horizontalCenter
        horizontalCenterOffset: - parent.width / 4
      }

      minimumWidth: parent.width / 2
      height: parent.height

      flat: true
      icon: modelItem.is_like? IconType.thumbsup : IconType.thumbsoup
      textColor: Theme.secondaryTextColor
      verticalMargin: 0

      onClicked: {
          moments_control.like(modelItem.is_like,modelItem.dyId);
          appB.icon = modelItem.is_like? IconType.thumbsup : IconType.thumbsoup

//          console.log("点击响应时间点赞")
//          feedListDelegate.likeClicked(name);
//          console.log("modelItem.is_like: "+modelItem.is_like)
      }
    }
//    AppImage{
//        id:image
//        anchors {
//            horizontalCenter: parent.horizontalCenter
//            horizontalCenterOffset: - parent.width / 4
//        }
//        width: parent.width / 2
//        height: parent.height
//        source: modelItem.is_like ? "../../assets/resource/icons/icons/male.png": "../../assets/resource/icons/icons//female.png"
//        MouseArea{
//            anchors.fill: parent
//            onClicked: {
//                moments_control.like(modelItem.dyId);
//                image.source=modelItem.is_like ? "../../assets/resource/icons/icons/male.png": "../../assets/resource/icons/icons//female.png"
//            }
//        }
//    }

    AppButton {
      anchors {
        horizontalCenter: parent.horizontalCenter
        horizontalCenterOffset: parent.width / 4
      }

      minimumWidth: parent.width / 2
      height: parent.height

      flat: true
      icon: IconType.commento
      textColor: Theme.secondaryTextColor
      verticalMargin: 0

      onClicked: {
        feedListDelegate.commentClicked()
      }
    }

    Rectangle {
      anchors {
        horizontalCenter: parent.horizontalCenter
        verticalCenter: parent.verticalCenter
      }

      width: 1
      height: parent.height / 2
      color: Theme.listItem.dividerColor
    }

    Rectangle {
      id: topFooterDivider

      width: parent.width
      height: 1
      visible: false

      color: Theme.listItem.dividerColor
    }

    Rectangle {
      id: bottomFooterDivider

      anchors.top: parent.bottom

      width: parent.width
      height: 1
      visible: false

      color: Theme.listItem.dividerColor
    }
  }

  RippleMouseArea {
    id: mouseArea
    width: column.width * 3

    anchors {
      top: parent.top
      bottom: footer.top
    }

    circularBackground: false
    hoverEffectRadius: 0
    radius: 0
    pressedDuration: 300

    onClicked: {
      console.log("有作用没")
      feedListDelegate.postClicked()
    }
  }


//  Connections {
//    target: dataModel

//    onUserDataChanged: {
//      if (modelItem.author !== "currentUser") {
//        return
//      }

//      avatarImage.source = dataModel.imageForUser(modelItem.author)
//      authorText.text = dataModel.nickForUser(modelItem.author)
//    }
//  }

//  Component.onCompleted: {
//    // condition to not load loader content if there is no image for regular post
//    if (modelItem.type === "Post") {
//      if (modelItem.image == "" || modelItem.image === undefined) {
//        return
//      }
//    }

//    contentLoader.active = true
//  }
}
