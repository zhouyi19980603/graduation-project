#ifndef FC_COMMENTS_LISTMODEL_H
#define FC_COMMENTS_LISTMODEL_H
#include <QAbstractListModel>
#include <QVector>
#include <QObject>

/**************************************************************

  @brief....:评论的model
  @author...: zhouyi
  @date.....:2021-04-13

  ************************************************************/

struct Comment{
    QString id;
    QString post_id;
    QString content;
    QString user_id;//评论的用户id
    QString parent_id;//表明是否为回复
    QString time; //评论的时间
    QString name;//显示的name
};
//每次点击到这个界面内容都会被全部刷新

class CommentsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    static CommentsModel* getInstance();

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const; //index and role data
    int rowCount(const  QModelIndex &parent = QModelIndex()) const; //row count

    QHash<int, QByteArray> roleNames() const;
    Q_INVOKABLE void parsing();
   // bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
private:
    CommentsModel(QObject* parent = nullptr);
    QVector<Comment> _data;//在里面去查找id是属于多少项，找到对应的项数
};


#endif // FC_COMMENTS_LISTMODEL_H
