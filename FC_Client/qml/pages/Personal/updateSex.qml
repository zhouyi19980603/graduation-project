import QtQuick 2.0
import QtQuick.Controls 2.0
import Felgo 3.0


Page {
    id: updateSex
    title: "设置性别"
    rightBarItem: IconButtonBarItem{
        id:editorSex
        icon: IconType.check
        onClicked: {
            profile_handle.updateGender(combobox.currentText);
            try{updateSex.navigationStack.pop();}catch(e){}
            //可以进行操作
        }
    }

    ComboBox {
        id:combobox
        width: parent.width
        font.pointSize: 20
        model: ["female","male"]
        background: Rectangle {
                    implicitWidth: 100
                    implicitHeight: 70
                    border.color: "white"
        }
    }


}
