#ifndef VIEWER_H
#define VIEWER_H

#include "fc_observer.h"
#include "fc_subject.h"
#include <string>


using std::string;
class FC_Server;
class FC_Message;
class Viewer : public Observer
{
private:
    FC_Server* _server = nullptr;
    string _viewid; //观察者标识
public:
    Viewer(FC_Server* server,const string& account); //初始化值
//    void sendCommonts(const std::string &content) override;
//    void receiveCommonts(const std::string &content) override;

    FC_Message* generate_message(unsigned type,const char* content);
    void update(const std::string &content,unsigned type) override;
};

#endif // VIEWER_H
