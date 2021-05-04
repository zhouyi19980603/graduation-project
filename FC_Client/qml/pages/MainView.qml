import QtQuick 2.0
import Felgo 3.0
import "../model"
import "../logic"

Page {

    title: "MainWindow"



    // business logic
    Logic {
        id: logic
    }
    Constant{
        id:constant
    }
    // model
    DataModel {
        id: dataModel
    }

    // helper functions for view
    ViewHelper {
        id: viewHelper
    }
    // view
    Navigation {
        id: navigation

        //        navigationMode: navigationModeTabs

        // first tab
        NavigationItem {
            title: qsTr("FreeC")
            icon: IconType.comment

            NavigationStack {
                id: chatView
                initialPage: ChatsView { }
            }
        }

        // second tab
        NavigationItem {
            title: qsTr("通讯录") // use qsTr for strings you want to translate
            icon: IconType.book

            NavigationStack {
                id: contactsPage
                initialPage: ContactsView{}
            }
        }

        NavigationItem {
            title: qsTr("发现") // use qsTr for strings you want to translate
            icon: IconType.file

            NavigationStack {
                id:discoverPage
                initialPage: DiscoverPage{}
            }
        }

        NavigationItem {
            title: qsTr("我") // use qsTr for strings you want to translate
            icon: IconType.home

            NavigationStack {
                id: personPage
                initialPage: PersonalPage{}
            }
        }
    }
}
