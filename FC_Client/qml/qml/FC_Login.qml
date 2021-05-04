import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.0
import QtQuick.Dialogs 1.3
import "./Component"
import "./BussinessPage"

Page {
    id: mainPage
    title: "Free C"
    color: "white"

    Constant { id: constant }
    property var accountValue

    Rectangle {
      id: loginForm
      anchors.centerIn: parent
      color: "white"
      width: content.width + 48
      height: content.height + 16
      radius: 4
    }

    // registerform content
    GridLayout {
      id: content
      anchors.centerIn: loginForm
      columnSpacing: 20
      rowSpacing: 10
      columns: 2

      // headline
      Text {
        Layout.topMargin: 8
        Layout.bottomMargin: 12
        Layout.columnSpan: 2
        Layout.alignment: Qt.AlignHCenter
        text: "Login"
      }

      // email text and field
      Text {
        text: qsTr("帐号")
        font.pixelSize: 12
      }

      TextField {
        id: txtUsername
        Layout.preferredWidth: 200
        font.pixelSize: 14
        text: accountValue
      }

      // password text and field
      Text {
        text: qsTr("密码")
        font.pixelSize: 12
      }

      TextField {
        id: txtPassword
        Layout.preferredWidth: 200
        font.pixelSize: 14
        echoMode: TextInput.Password //field
      }
      Loader{
        id:loader
      }

      // column for buttons, we use column here to avoid additional spacing between buttons
      Column {
        Layout.fillWidth: true
        Layout.columnSpan: 2
        Layout.topMargin: 12

        // buttons
        Button {
          text: qsTr("Login")
          flat: false
          anchors.horizontalCenter: parent.horizontalCenter
          onClicked: {
//              profile_handle.login(txtUsername.text,txtPassword.text)
              __PushPage(Qt.resolvedUrl("./Fc_MainView.qml"), {} ); //压入一个新的界面
          }
        }

        Button {
          text: qsTr("No account yet? Register now")
          flat: true
          anchors.horizontalCenter: parent.horizontalCenter
          onClicked: {
              __PushPage(Qt.resolvedUrl("./FC_Register.qml"), {} );
          }
        }
      }
    }

//    //在这里看状态,如果是登录成功则跳转到Fc_MainView，若为登录失败，则弹出一个对话框

    Connections{
        target: status_message
        onStatusChanged:{
            console.log("状态发生改变")
//            if(status_message.status === 1)
//            {
//                messageDialog.open()
//                txtPassword.text=""
//                console.log("登录失败")
//            }
//            else if(status_message.status === 0)
//            {
//                console.log("登录成功! 啊啊啊")
//                __PushPage(Qt.resolvedUrl("./Fc_MainView.qml"), {} );
//            }

        }
    }
    MessageDialog {
        id: messageDialog
        title: "登录失败"
        text: "帐号或密码错误，请重新登录"
    }
}
