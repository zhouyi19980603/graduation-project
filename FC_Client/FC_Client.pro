# allows to add DEPLOYMENTFOLDERS and links to the Felgo library and QtCreator auto-completion
CONFIG += felgo
CONFIG += console c++17 thread

include(json/json.pri)

#INCLUDEPATH += /usr/local/boost/include
LIBS +=/usr/lib/libboost_thread.a
LIBS += /usr/lib/libz.a
#LIBS += /usr/local/boost/lib/libboost_thread.a

#INCLUDEPATH += /run/media/root/linux_data/C++/boost.asio/arm-boost/usr/include
#LIBS += /run/media/root/linux_data/C++/boost.asio/arm-boost/usr/lib/libboost_thread.a


# uncomment this line to add the Live Client Module and use live reloading with your custom C++ code
# for the remaining steps to build a custom Live Code Reload app see here: https://felgo.com/custom-code-reload-app/
#CONFIG += felgo-live

# Project identifier and version
# More information: https://felgo.com/doc/felgo-publishing/#project-configuration
PRODUCT_IDENTIFIER = com.yourcompany.wizardEVAP.FCClient
PRODUCT_VERSION_NAME = 1.0.0
PRODUCT_VERSION_CODE = 1

# Optionally set a license key that is used instead of the license key from
# main.qml file (App::licenseKey for your app or GameWindow::licenseKey for your game)
# Only used for local builds and Felgo Cloud Builds (https://felgo.com/cloud-builds)
# Not used if using Felgo Live
PRODUCT_LICENSE_KEY = ""

qmlFolder.source = qml
DEPLOYMENTFOLDERS += qmlFolder # comment for publishing

assetsFolder.source = assets
DEPLOYMENTFOLDERS += assetsFolder

# Add more folders to ship with the application here

# RESOURCES += resources.qrc # uncomment for publishing

# NOTE: for PUBLISHING, perform the following steps:
# 1. comment the DEPLOYMENTFOLDERS += qmlFolder line above, to avoid shipping your qml files with the application (instead they get compiled to the app binary)
# 2. uncomment the resources.qrc file inclusion and add any qml subfolders to the .qrc file; this compiles your qml files and js files to the app binary and protects your source code
# 3. change the setMainQmlFile() call in main.cpp to the one starting with "qrc:/" - this loads the qml files from the resources
# for more details see the "Deployment Guides" in the Felgo Documentation

# during development, use the qmlFolder deployment because you then get shorter compilation times (the qml files do not need to be compiled to the binary but are just copied)
# also, for quickest deployment on Desktop disable the "Shadow Build" option in Projects/Builds - you can then select "Run Without Deployment" from the Build menu in Qt Creator if you only changed QML files; this speeds up application start, because your app is not copied & re-compiled but just re-interpreted


# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    Moments/fc_comments_listmodel.cpp \
    Moments/fc_moments_control.cpp \
    Moments/fc_moments_like.cpp \
    Moments/fc_moments_listmodel.cpp \
    fc_buddy.cpp \
    fc_buddyitem.cpp \
    fc_buddymodel.cpp \
    fc_buddyteam.cpp \
    fc_chat_listmodel.cpp \
    fc_client.cpp \
    fc_connection.cpp \
    fc_display.cpp \
    fc_friends_handle.cpp \
    fc_friends_model.cpp \
    fc_message.cpp \
    fc_message_handle.cpp \
    fc_message_instance.cpp \
    fc_message_listmodel.cpp \
    fc_profile.cpp \
    fc_profile_handle.cpp \
    fc_status.cpp \
    fc_thread_pool.cpp \
    qabstractlistmodel.cpp


android {
    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
    OTHER_FILES += android/AndroidManifest.xml       android/build.gradle
}

ios {
    QMAKE_INFO_PLIST = ios/Project-Info.plist
    OTHER_FILES += $$QMAKE_INFO_PLIST
}

# set application icons for win and macx
win32 {
    RC_FILE += win/app_icon.rc
}
macx {
    ICON = macx/app_icon.icns
}

DISTFILES += \
    qml/components/FeedListDelegate.qml \
    qml/model/Constant.qml \
    qml/pages/Chat/SendFile.qml \
    qml/pages/ChatsView.qml \
    qml/pages/Contact/NewFriendsPage.qml \
    qml/pages/Contact/exam.qml \
    qml/pages/Contact/searchMsgPage.qml \
    qml/pages/Contact/searchPage.qml \
    qml/pages/Contact/updateRemark.qml \
    qml/pages/ContactsView.qml \
    qml/pages/DiscoverPage.qml \
    qml/pages/MainView.qml \
    qml/pages/Moments/AddPostModal.qml \
    qml/pages/Moments/AddPostPage.qml \
    qml/pages/Moments/PostPage.qml \
    qml/pages/Personal/setting.qml \
    qml/pages/Personal/updateName.qml \
    qml/pages/Personal/updateSex.qml \
    qml/pages/PersonalPage.qml \
    qml/pages/Chat/ChatPage.qml \
    qml/pages/Moments/MomentsPage.qml \
    qml/pages/RegisterPage.qml

HEADERS += \
    Moments/fc_comments_listmodel.h \
    Moments/fc_moments_control.h \
    Moments/fc_moments_like.h \
    Moments/fc_moments_listmodel.h \
    fc_base64decrypt.h \
    fc_base64encrypt.h \
    fc_buddy.h \
    fc_buddyitem.h \
    fc_buddymodel.h \
    fc_buddyteam.h \
    fc_chat_listmodel.h \
    fc_client.h \
    fc_connection.h \
    fc_display.h \
    fc_friends_handle.h \
    fc_friends_model.h \
    fc_header.h \
    fc_message.h \
    fc_message_handle.h \
    fc_message_instance.h \
    fc_message_listmodel.h \
    fc_profile.h \
    fc_profile_handle.h \
    fc_status.h \
    fc_thread_pool.h \
    qabstractlistmodel.h
