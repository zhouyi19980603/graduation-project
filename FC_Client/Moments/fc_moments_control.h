#ifndef FC_MOMENTS_CONTROL_H
#define FC_MOMENTS_CONTROL_H

#include <QObject>
#include <QString>
#include "fc_moments_listmodel.h"
#include <QVector>
#include <iostream>

class FC_Client;
class ProfileMsg;
class FC_Message_Handle;
class LikeMsg;
class CommentsModel;

class FC_Moments_Control : public QObject
{
  Q_OBJECT
public:
    FC_Moments_Control(FC_Client* client,QObject* parent = nullptr);
    ~FC_Moments_Control();
    std::string getCurrentTime();

    Q_INVOKABLE void publish_dynamic(const QString& text,const QString& image);
    Q_INVOKABLE void like(bool is_like,QString id);
    Q_INVOKABLE void request_dynamic_data();
    Q_INVOKABLE void parsing();
    Q_INVOKABLE void request_post_comments_data(const QString& post_id);
    Q_INVOKABLE void send_reply_comment(QVector<QString> con);
    Q_INVOKABLE void send_comment(QVector<QString> con);

    //hander message
    void handle_new_moments(const char* content);
    void handle_like_message(const char* content);
    void handle_replay_dy(const char* content);
    void handle_replay_comments(const char* content);
    void handle_comment_reply(const char* content,unsigned type);

    QString arrange_likes_tex();//处理点赞的text信息

signals:
    void comments_data(QString data);
    void comments();
private:
    FC_Client* _client = nullptr;
    FC_Moments_Model* _model = nullptr;
    CommentsModel* _comment_model = nullptr;
    ProfileMsg* _profile = nullptr;
    LikeMsg* _msg = nullptr;
};

#endif // FC_MOMENTS_CONTROL_H
