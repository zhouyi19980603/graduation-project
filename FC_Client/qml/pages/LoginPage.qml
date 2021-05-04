import Felgo 3.0
import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.3

Page {
    id: loginPage
//    title: qsTr("Login")
    navigationBarHidden: true
     property var accountValue

    backgroundColor: Qt.rgba(0,0,0, 0.75) // page background is translucent, we can see other items beneath the page
    useSafeArea: false // do not consider safe area insets of screen

    // login form background
    Rectangle {
        id: loginForm
        anchors.centerIn: parent
        color: "white"
        width: content.width + dp(48)
        height: content.height+dp(16)
//        width: content.width + dp(48)
//        height: content.height + dp(16)
        radius: dp(4)
    }

    // login form content
    GridLayout {
        id: content
        anchors.centerIn: loginForm
        columnSpacing: dp(10)
        rowSpacing: dp(10)
        columns: 2

        // headline
        AppText {
            Layout.topMargin: dp(8)
            Layout.bottomMargin: dp(12)
            Layout.columnSpan: 2
            Layout.alignment: Qt.AlignHCenter
            text: "Login"
        }

        // account text and field
        AppText {
            text: qsTr("帐号")
            font.pixelSize: sp(12)
        }

        AppTextField {
            id: txtUsername
            Layout.preferredWidth: dp(140)
            showClearButton: true
            font.pixelSize: sp(14)
            borderColor: Theme.tintColor
            borderWidth: !Theme.isAndroid ? dp(2) : 0
            text: accountValue
        }

        // password text and field
        AppText {
            text: qsTr("密码")
            font.pixelSize: sp(12)
        }

        AppTextField {
            id: txtPassword
            Layout.preferredWidth: dp(140)
            showClearButton: true
            font.pixelSize: sp(14)
            borderColor: Theme.tintColor
            borderWidth: !Theme.isAndroid ? dp(2) : 0
            echoMode: TextInput.Password
        }

        // column for buttons, we use column here to avoid additional spacing between buttons
        Column {
            Layout.fillWidth: true
            Layout.columnSpan: 2
            Layout.topMargin: dp(12)

            // buttons
            AppButton {
                text: qsTr("Login")
                flat: false
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    //登录发送事件在这里

                    profile_handle.login(txtUsername.text,txtPassword.text)

//                    var component = Qt.createComponent("./MainView.qml");
//                    if(component.status === Component.Ready)
//                    {
//                        component.createObject(loginPage);
//                    }
                }
            }

            AppButton {
                text: qsTr("No account yet? Register now")
                flat: true
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    loginPage.forceActiveFocus() // move focus away from text fields

                    // call your logic action to register here
                    console.debug("registering...")
                    var component = Qt.createComponent("./RegisterPage.qml");

                    if(component.status === Component.Ready)
                    {
//                        component.createObject(loginPage);
                        loginPage.navigationStack.push(component)
                    }
                }
            }
        }
    }

    Connections{
        target: status_message
        onStatusChanged:{
            console.log("状态发生改变")
            if(status_message.status === 1)
            {
                messageDialog.open()
                txtPassword.text=""
                console.log("登录失败")
            }
            else if(status_message.status === 0)
            {
                console.log("登录成功! 啊啊啊")
//                __PushPage(Qt.resolvedUrl("./Fc_MainView.qml"), {} );
                var component = Qt.createComponent("./MainView.qml");

                if(component.status === Component.Ready)
                {
                    component.createObject(loginPage);
                }
//                loginPage.navigationStack.popAllExceptFirst();
            }

        }
    }

    MessageDialog{
        id: messageDialog
        title: qsTr("登录失败")
        text: qsTr("帐号或密码错误，请重新登录")
    }
}
