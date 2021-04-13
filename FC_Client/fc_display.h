#ifndef FC_DISPLAY_H
#define FC_DISPLAY_H

#include <QVariant>
#include <vector>

class QGuiApplication;
class QQmlApplicationEngine;
class FC_Client;
class FC_Message_Handle;
class FC_Profile;
class ProfileMsg;
class BuddyModel;
class Buddy;
class FC_Message_ListModel;
class FC_Friends_Handle;
class FC_Chat_ListModel;
class FC_Message;
class FC_MessageStatus;
class FC_Moments_Model;
class FC_Moments_Control;
class CommentsModel;
class LikeMsg;

class FC_Display
{
public:
    FC_Display(FC_Client* client,FC_Profile* profile);
    ~FC_Display();
    
    void show();
    
   // void FC_Display::recv(std::vector<std::string> vs);
    
    //show ui
    void recv(QString s); //display receive message
    void recv_group_msg(std::vector<std::string> vs);
    void recv(std::vector<std::string> vs); //display receive message
    void recv_history(FC_Message* msg);

private:
    FC_Client* _client = nullptr;
    FC_Profile* _profile = nullptr;
    ProfileMsg* _profilemsg=nullptr;
    BuddyModel* _model = nullptr;
    FC_Message_ListModel* _list_model = nullptr;
    FC_Chat_ListModel* _chat_listModel = nullptr;
    FC_Message_Handle* _handle = nullptr;
    FC_Friends_Handle* _fhandle =nullptr;
    FC_MessageStatus* _status = nullptr;
    FC_Moments_Model* _moments_model = nullptr;
    FC_Moments_Control* _control = nullptr;
    CommentsModel* _comments_model = nullptr;
    LikeMsg* _msg = nullptr;
    Buddy* _buddy = nullptr;

    QGuiApplication* _app_ui = nullptr;
    QQmlApplicationEngine* _engine = nullptr;
};

#endif // FC_DISPLAY_H
