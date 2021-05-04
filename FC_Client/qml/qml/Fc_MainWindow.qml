import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Window 2.0
import "./Component"

PageStackWindow {
    id: mainWindow
    title: qsTr("Free C")
    width: 360
    height: 720


    initialPage: FC_Login {
        id: mainView
        focus: mainWindow.focus

        stackView: mainWindow.stackView
        pageStackWindow: mainWindow
        width: stackView.width
        height: stackView.height



        Keys.onBackPressed: {
            event.accepted = true;
            // console.log("back")
            Qt.quit();
        }
    }


}
