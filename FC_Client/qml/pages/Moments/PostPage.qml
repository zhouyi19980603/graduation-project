import Felgo 3.0
import QtQuick 2.0
import "../../components"


Page {
    id: root

    property alias modelIndex: feedItem.modelIndex
    property alias modelItem: feedItem.modelItem

    onPopped: {
        name.icon = modelItem.is_like? IconType.thumbsup : IconType.thumbsoup
    }

    property var type: Number(1)
    title: qsTr("Post")

    states: [
        State {
            name: "addingComment"
            PropertyChanges {
                target: addCommentPaper
                anchors.leftMargin: 0
                opacity: 1
            }
        }
    ]

    transitions: [
        Transition {
            from: ""
            to: "addingComment"
            NumberAnimation {
                property: "anchors.leftMargin"
                duration: 250
            }
        },
        Transition {
            from: "addingComment"
            to: ""
            NumberAnimation {
                property: "opacity"
                duration: 250
            }
        }
    ]

    Flickable {
        id: flickable

        anchors {
            top: parent.top
            bottom: addCommentPaper.top
            left: parent.left
            right: parent.right
        }

        contentHeight: column.height
        interactive: flickable.contentHeight > flickable.height

        Column {
            id: column

            width: parent.width
            spacing: dp(2)

            FeedListDelegate {
                id: feedItem

                state: "postPage"

                onCommentClicked: {
                    if(root.state == "")
                        addCommentPaper.open();
                    else
                    {
                        root.state="";
                        commentTextField.placeholderText="Add a comment"
                    }
                    console.log("modelItem.dyId"+modelItem.dyId)
                }
                onLikeClicked: {
                    moments_control.like(modelItem.is_like,modelItem.dyId);
                    name.icon = modelItem.is_like? IconType.thumbsup : IconType.thumbsoup
                }
            }

            SortFilterProxyModel{
                id:sortModel
                sourceModel: comments_model
            }

            AppListView {
                id: commentsList
                width: parent.width
                height: count > 0 ? contentHeight : dp(80)

                clip: count > 0
                backgroundColor: Theme.backgroundColor
                emptyText.font.pixelSize: dp(14)
                emptyText.color: Theme.secondaryTextColor
                emptyText.text: qsTr("No Comments Yet")
                interactive: false
                model: sortModel
                delegate: SimpleRow {
                    text: name + " : "
                    detailText: content
                    showDisclosure: false
                    onSelected: {
                        if(user_id != profilemsg.account)
                        {
                            addCommentPaper.open();
                            commentTextField.placeholderText = "回复"+user_id
                            type = Number(2)
                        }

                    }
                }

                RippleMouseArea {
                    anchors.centerIn: parent
                    width: parent.width * 2
                    height: parent.height + 2 * column.spacing
                    visible: commentsList.count == 0

                    circularBackground: false
                    hoverEffectRadius: 0
                    radius: 0
                    pressedDuration: 300

                    onClicked: {
                        addCommentPaper.open()
                    }
                }
            }

            Rectangle {
                width: parent.width
                height: dp(1)
                visible: commentsList.count == 0

                color: Theme.secondaryTextColor
            }
        }
    }

    AppPaper {
        id: addCommentPaper

        anchors {
            bottom: parent.bottom
            left: parent.left
            leftMargin: width
        }

        anchors.onLeftMarginChanged: {
            if (anchors.leftMargin < width && opacity > 0) {
                commentTextField.forceActiveFocus()
            }
        }

        width: parent.width
        height: dp(50)
        opacity: 0

        shadow.visible: opacity > 0


        IconButton {
            id: commitCommentButton
            width: height
            height: parent.height

            anchors.right: parent.right

            icon: IconType.check
            enabled: addCommentPaper.visible && commentTextField.displayText.length > 0

            color: Theme.tintColor
            disabledColor: Theme.placeholderTextColor

            onClicked: {
                addCommentPaper.close()
            }
        }

        AppTextField {
            id: commentTextField

            anchors {
                verticalCenter: parent.verticalCenter
                left: parent.left
                right: commitCommentButton.left
                margins: dp(Theme.contentPadding)
            }

            cursorColor: "transparent"
            placeholderText: qsTr("Add a comment")

            onAccepted: {
                if(displayText.length >0 ){
                    addCommentPaper.close();
                }

            }
        }

        function open() {
            root.state = "addingComment"
            commentTextField.focus = true
        }

        function close() {
            Qt.inputMethod.hide()
            root.state = ""
            if(type == Number(1)){
                console.log("function close(): "+type)
                moments_control.send_comment(["1",modelItem.dyId,commentTextField.text])
            }else
            {
                console.log(commentsList.model.get(commentsList.currentIndex).content)
                var puser_ids = commentsList.model.get(commentsList.currentIndex).user_id
                var parent_ids = commentsList.model.get(commentsList.currentIndex).id
                moments_control.send_comment(["2",modelItem.dyId,commentTextField.text,puser_ids,parent_ids])
                //        console.log("function close(): "+type)
            }

            //      dataModel.addComment(modelIndex, commentTextField.displayText)
            //      root.modelItem.comments = dataModel.get(modelIndex).comments
            commentTextField.clear()
            type = Number(1)
        }
    }
}
