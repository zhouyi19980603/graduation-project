#ifndef FC_MOMENTS_CONTROL_H
#define FC_MOMENTS_CONTROL_H

#include <QObject>
#include <QString>
#include "fc_moments_listmodel.h"

class FC_Client;
class ProfileMsg;
class FC_Message_Handle;

class FC_Moments_Control : public QObject
{
  Q_OBJECT
public:
    FC_Moments_Control(FC_Client* client,QObject* parent = nullptr);
    ~FC_Moments_Control();

    Q_INVOKABLE void publish_dynamic();
    Q_INVOKABLE void like(QString id);
    void handle_new_moments(const char* content);
private:
    FC_Client* _client = nullptr;
    FC_Moments_Model* _model = nullptr;
    ProfileMsg* _profile = nullptr;

};

#endif // FC_MOMENTS_CONTROL_H