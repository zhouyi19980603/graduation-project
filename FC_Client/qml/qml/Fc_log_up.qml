import QtQuick 2.0
import QtQuick.Controls 2.0
ApplicationWindow{
    id: window
    visible: true
    width: 640
    height: 480
    color: "lightblue"
    title: qsTr("Logup Dialog")

    TextInput{
        id: textinput
        x: 134
        y: 189
        width: 142
        height: 26
       // inputMethodHints: "enter your account"
        text: qsTr("")
        font.pixelSize: 12
        focus: true
        validator: IntValidator{top:99999999;bottom: 11111111}
    }
    Label {
        id: label
        x: 134
        y: 156
        width: 135
        height: 21
        text: qsTr("enter your count:")
    }
    Button {
        id: button
        x: 382
        y: 283
        text: qsTr("log_up")
        onClicked: {
            if(textinput.text.length!=0){
               profile.set_account(textinput.text)
               console.log(profile.account+"login up");
               mainWindow.visible = true;
               window.visible = false;
            }
        }
    }
    Fc_MainWindow{
        id: mainWindow
        visible: false
    }

}
