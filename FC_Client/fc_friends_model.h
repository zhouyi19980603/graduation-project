#ifndef FC_FRIENDS_MODEL_H
#define FC_FRIENDS_MODEL_H
#include <QObject>
#include <QAbstractListModel>
#include <QVector>

struct FMsg{
    QString account;
    QString heading;
    QString content;
    QString name;
};


class FMsgModel : public QAbstractListModel
{
  Q_OBJECT
public:
    static FMsgModel *getInstance();

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const; //index and role data
    int rowCount(const  QModelIndex &parent = QModelIndex()) const; //row count

    QHash<int, QByteArray> roleNames() const;

    void insert(FMsg& item);
private:
    QVector<FMsg> _data;
    FMsgModel(QObject* parent = nullptr);
};

#endif // FC_FRIENDS_MODEL_H
