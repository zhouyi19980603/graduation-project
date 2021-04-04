import QtQuick 2.0
import QtQuick.Window 2.2
import "./UI.js" as UI

QtObject {
    id: constant
// "#71d01d":"#ccc"
    // 微信 深灰 #22292c
    // 微信绿 #71d01d
    // 普通灰 #ccc


    readonly property string fontFamily: "微软雅黑"

    readonly property int smallFontPointSize : UI.smallFontPointSize          // 主页面下的icon的文本例如chat等
    readonly property int middleFontPointSize : UI.middleFontPointSize
    readonly property int normalFontPointSize : UI.normalFontPointSize        // 文本编辑框，按钮中的字体大小
    readonly property int bigFontPointSize : UI.bigFontPointSize              // 软件标题

    readonly property url testPic: Qt.resolvedUrl( "../resource/tests/tests001.jpeg")
    readonly property url qipaoRight: Qt.resolvedUrl( "../resource/background/active/chat-bubble.png")
    readonly property url qipaoLeft: Qt.resolvedUrl( "../resource/background/active/chat-bubble1.png")

    readonly property alias icons: __icons
    readonly property url iconsPath: "../resource/icons/"

    readonly property url femaleSampleIcon: icons.sampleIcon("female")                      // 女性
    readonly property url maleSampleIcon: icons.sampleIcon("male")                          // 男性

    readonly property url soundActiveIcon: icons.activeIcon("sound")
    readonly property url soundInactiveIcon: icons.inactiveIcon("sound")
    readonly property url emoticonActiveIcon: icons.activeIcon("emoticon")
    readonly property url emoticonInactiveIcon: icons.inactiveIcon("emoticon")
    readonly property url backActiveIcon: icons.activeIcon("back")
    readonly property url backInactiveIcon: icons.inactiveIcon("back")
    readonly property url magnifierActiveIcon: icons.activeIcon("magnifier")
    readonly property url magnifierInactiveIcon: icons.inactiveIcon("magnifier")
    readonly property url plusActiveIcon: icons.activeIcon("plus")
    readonly property url plusInactiveIcon: icons.inactiveIcon("plus")

    readonly property url momentsLabelIcon: icons.labelIcon("moments")                      // 朋友圈
    readonly property url momentsLikeIcon: icons.labelIcon("like-1") //点赞的图标
    readonly property url momentsCommentsIcon: icons.labelIcon("comments-1")
    readonly property url scanQRCodeLabelIcon: icons.labelIcon("scan-qr-code")              // 二维码
    readonly property url shakeLabelIcon: icons.labelIcon("shake")                          // 摇一摇
    readonly property url peopleNearbyLabelIcon: icons.labelIcon("people-nearby")           // 附近的人
    readonly property url driftBottleLabelIcon: icons.labelIcon("drift-bottle")             // 漂流瓶
    readonly property url gamesLabelIcon: icons.labelIcon("games")                          // 游戏中心
    readonly property url favoritesLabelIcon: icons.labelIcon("favorites")                  // 收藏
    readonly property url myPostsLabelIcon: icons.labelIcon("my-posts")                     // 相册
    readonly property url settingsLabelIcon: icons.labelIcon("settings")                    // 设置
    readonly property url walletLabelIcon: icons.labelIcon("wallet")                        // 钱包
    readonly property url groupchatIcon: icons.labelIcon("groupchat")                       // 群聊
    readonly property url newfriendsIcon: icons.labelIcon("new-fri")                        // 新的朋友
    readonly property url friendlistright: icons.labelIcon("right")                         // 分组箭头
    readonly property url toolIcon: icons.labelIcon("ellipsis")                             // 工具栏
    readonly property url fileIcon: icons.labelIcon("fileIcon")                             // 文件
    readonly property url returnIcon: icons.labelIcon("return")                             // 返回

    readonly property url addchatIcon: icons.chatIcon("add")

    readonly property url shareExcelIcon: icons.share("share-excel")
    readonly property url shareFileIcon: icons.share("share-file")
    readonly property url shareMusicIcon: icons.share("share-music")
    readonly property url sharePdfIcon: icons.share("share-pdf")
    readonly property url sharePictureIcon: icons.share("share-picture")
    readonly property url sharePositionIcon: icons.share("share-position")
    readonly property url shareSoundIcon: icons.share("share-sound")
    readonly property url shareTextIcon: icons.share("share-text")
    readonly property url shareUrlIcon: icons.share("share-url")
    readonly property url shareVideoIcon: icons.share("share-video")
    readonly property url shareWordIcon: icons.share("share-word")
    readonly property url shareZipIcon: icons.share("share-zip")


    property var _icons: QtObject {
        id: __icons
        function share(name) {
            return Qt.resolvedUrl(iconsPath + "label-icons/" + name + ".png");
        }

        function labelIcon(name) {
            return Qt.resolvedUrl(iconsPath + "label-icons/" + name + ".png");
        }

        function activeIcon(name) {
            return Qt.resolvedUrl(iconsPath + "bar-icons/active/" + name +".png")
        }

        function inactiveIcon(name) {
            return Qt.resolvedUrl(iconsPath + "bar-icons/inactive/" + name +".png")
        }

        function chatIcon(name){
            return Qt.resolvedUrl(iconsPath + "bar-icons/" + name +".png")
        }

        function sampleIcon(name) {
            return Qt.resolvedUrl(iconsPath + "icons/" + name +".png")
        }
    }


}
