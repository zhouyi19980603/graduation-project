#ifndef FC_MESSAGE_HANDLE_H
#define FC_MESSAGE_HANDLE_H

#include "fc_message.h"
#include "fc_client.h"
#include <QObject>
#include <QString>
#include <unordered_map>

class FC_Friends_Handle;
class FC_Profile;
class FC_Moments_Control;

class FC_Message_Handle
{
public:
    FC_Message_Handle(FC_Client* client);
    ~FC_Message_Handle();
    //handle recv message
    void handle_header(FC_Message*);
    void handle_body(FC_Message*);
    void handle_text_msg(FC_Message* msg);
    void handle_group_text_msg(FC_Message* msg);
    void handle_history(FC_Message* message);
    void handle_file_text_msg(FC_Message* msg);

    const char* text_body(const char* content);
    static FC_Message* generate_message(unsigned type,const char* content);//generate a message


private:
    FC_Client* _client;
    FC_Friends_Handle* _friends_handle;
    FC_Profile* _profile;
    FC_Moments_Control* _moment_handle;

};

#endif // FC_MESSAGE_HANDLE_H
