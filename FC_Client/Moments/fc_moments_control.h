#ifndef FC_MOMENTS_CONTROL_H
#define FC_MOMENTS_CONTROL_H

#include <QObject>
#include <QString>
#include "fc_moments_listmodel.h"

class FC_Client;
class ProfileMsg;
class FC_Message_Handle;
class LikeMsg;

class FC_Moments_Control : public QObject
{
  Q_OBJECT
public:
    FC_Moments_Control(FC_Client* client,QObject* parent = nullptr);
    ~FC_Moments_Control();

    Q_INVOKABLE void publish_dynamic();
    Q_INVOKABLE void like(QString id);
    Q_INVOKABLE void request_dynamic_data();

    //hander message
    void handle_new_moments(const char* content);
    void handle_like_message(const char* content);
    void handle_replay_dy(const char* content);
    QString arrange_likes_tex();//处理点赞的text信息
private:
    FC_Client* _client = nullptr;
    FC_Moments_Model* _model = nullptr;
    ProfileMsg* _profile = nullptr;
    LikeMsg* _msg = nullptr;
};

#endif // FC_MOMENTS_CONTROL_H
