import Felgo 3.0
import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.3

Page {
    id: registerPage
    title: qsTr("Register")

    backgroundColor: Qt.rgba(0,0,0, 0.75) // page background is translucent, we can see other items beneath the page
    useSafeArea: false // do not consider safe area insets of screen
    // login form background
    Rectangle {
        id: registerForm
        anchors.centerIn: parent
        color: "white"
        width: content.width + dp(48)
        height: content.height+dp(16)
        radius: dp(4)
    }

    // login form content
    GridLayout {
        id: content
        anchors.centerIn: registerForm
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
            text: qsTr("昵称")
            font.pixelSize: sp(12)
        }

        AppTextField {
            id: txtUsername
            Layout.preferredWidth: dp(140)
            showClearButton: true
            font.pixelSize: sp(14)
            borderColor: Theme.tintColor
            borderWidth: !Theme.isAndroid ? dp(2) : 0
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
                text: qsTr("Register")
                flat: false
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    profile_handle.registers(txtUsername.text,txtPassword.text)
                }
            }

        }
    }


    Connections{
        target: status_message
        onStatusChanged:{
            console.log("状态发生改变")
            if(status_message.status === 2)
            {
                messageDialog.open()
                txtUsername.text=""
                txtPassword.text=""
            }
        }
    }

    MessageDialog {
        id: messageDialog
        title: "注册成功"
        text: "你的帐号为:"+status_message.acc
        standardButtons: StandardButton.Yes
        onYes: {
            try {
                registerPage.navigationStack.pop();
                loginPage.accountValue = status_message.acc;
            }  catch(e) { } }
    }
}
