import Felgo 3.0
import QtQuick 2.0
import "pages"
import "pages/Contact"

App {

    onInitTheme:{
        Theme.colors.statusBarStyle = Theme.colors.statusBarStyleWhite


    }

    NavigationStack{
        initialPage: LoginPage{}
    }
}
//}
