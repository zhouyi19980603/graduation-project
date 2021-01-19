#ifndef QABSTRACTLISTMODEL_H
#define QABSTRACTLISTMODEL_H

#include <QAbstractListModel>
#include <QString>
#include <QVector>

struct frmsg{
    QString m_header; //存放图片的路径
    QString m_nick;
    QString m_message;//第一条消息
    QString m_mark;//备注
};

class FC_FrMsg_Model : public QAbstractListModel
{
public:
    FC_FrMsg_Model(QObject* parent = nullptr);
    ~FC_FrMsg_Model();

    void addmodel();
    QVariant data(const QModelIndex &index, int role =Qt::DisplayRole) const;

    //虚函数     获取model行数
    int rowCount(const QModelIndex &parent  = QModelIndex() ) const;



    // 虚函数 内容的别名  qml 内部调用
    QHash<int, QByteArray> roleNames()  const;
private:
    QVector<frmsg> _vec;
};

#endif // QABSTRACTLISTMODEL_H
