#ifndef FC_MOMENTS_LIKE_H
#define FC_MOMENTS_LIKE_H


#include <QObject>
#include <QString>

class LikeMsg: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString like_text READ like_text WRITE setLike_text NOTIFY like_textChanged)
    Q_PROPERTY(QString time READ time WRITE setTime NOTIFY timeChanged)
public:
    static LikeMsg* getInstance();

    //setter
    void setLike_text(const QString& text);
    void setTime(const QString& time);

    //getter
    QString like_text() const;
    QString time() const;

signals:
    void like_textChanged();
    void timeChanged();

private:
    static LikeMsg* instance;
    LikeMsg(QObject* parent = nullptr);

    QString m_like_text;
    QString m_time;
};



#endif // FC_MOMENTS_LIKE_H
