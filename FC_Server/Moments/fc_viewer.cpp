#include "fc_viewer.h"
#include <iostream>
#include "fc_server.h"
#include "fc_header.h"
#include "fc_message.h"

//这个可以看成朋友圈的控制类
Viewer::Viewer(FC_Server* server,const std::string &account)
    :_server(server),_viewid(account)
{
}

FC_Message *Viewer::generate_message(unsigned type, const char *content)
{
    FC_Message* message = new FC_Message;//delete in on_write()
    unsigned msg_size = strlen(content)+1;
    message->set_header(type,msg_size);
    message->set_body(content,msg_size);
    return message;
}

void Viewer::update(const std::string &content,unsigned type)
{
    FC_Message* msg = generate_message(type,content.c_str());
    _server->forward_message(_viewid,msg);
}
