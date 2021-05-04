import QtQuick 2.0
import QtQuick.Controls 2.4

Page {
    id:addPage
    visible: true
    width: 420
    height: 800


    Image {
        id: image
        x: 365
        y: 0
        width: 55
        height: 52
        fillMode: Image.PreserveAspectFit
        source: "asserts/add1.jpg"
        MouseArea{
            anchors.fill: parent
            onClicked: {
//                addPage.destroy() //destory self
                var component = Qt.createComponent("AddUI.qml");
                if(component.status === Component.Ready){
                    component.createObject(addPage);
                    tabBar.visible = false
//                    addPage.destroy() //destory self
                }
            }
        }
    }
}
