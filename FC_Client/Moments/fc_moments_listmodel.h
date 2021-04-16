#ifndef FC_MOMENTS_LISTMODEL_H
#define FC_MOMENTS_LISTMODEL_H
#include <QAbstractListModel>
#include <QVector>
#include "fc_comments_listmodel.h"

//一条动态
struct dynamic
{
    QString userId;
    QString headpath;
    QString nickname;
    QString con_text;
    QString con_image;//path
    QString time;
    QString dyId;//动态的id
    QString like_text;//点赞的text
    QString comments;//评论的消息
    bool is_like = false;//是否点过赞
};

class FC_Moments_Model : public QAbstractListModel
{
  Q_OBJECT
public:

    static FC_Moments_Model* getInstance();
    //重载函数
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const; //index and role data
    int rowCount(const  QModelIndex &parent = QModelIndex()) const; //row count

    QHash<int, QByteArray> roleNames() const;
    void clear();


    //handle
    void update_model(const QString& dyId,const QString& content);
    int getIndex(const QString& dyId);

    Q_INVOKABLE void add(dynamic& nic);
    Q_INVOKABLE void add();

private:
    FC_Moments_Model(QObject* parent = nullptr);
    QVector<dynamic> _data;
};

#endif // FC_MOMENTS_LISTMODEL_H
