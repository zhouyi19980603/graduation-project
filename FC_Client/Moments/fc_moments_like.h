#ifndef FC_MOMENTS_LIKE_H
#define FC_MOMENTS_LIKE_H


#include <QObject>
#include <QString>

//这个可以用于判断用户是否点过赞
class LikeMsg: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString like_text READ like_text WRITE setLike_text NOTIFY like_textChanged)
    Q_PROPERTY(QString time READ time WRITE setTime NOTIFY timeChanged)
    Q_PROPERTY(bool isLike READ isLike WRITE setIsLike NOTIFY isLikeChanged)
public:
    static LikeMsg* getInstance();

    //setter
    void setLike_text(const QString& text);
    void setTime(const QString& time);
    void setIsLike(const bool& value);

    //getter
    QString like_text() const;
    bool isLike() const;
    QString time() const;

signals:
    void like_textChanged();
    void timeChanged();
    void isLikeChanged();

private:
    static LikeMsg* instance;
    LikeMsg(QObject* parent = nullptr);

    QString m_like_text;
    QString m_time;
    bool m_isLike;
};



#endif // FC_MOMENTS_LIKE_H
