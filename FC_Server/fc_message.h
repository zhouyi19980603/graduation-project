#ifndef FC_MESSAGE_H
#define FC_MESSAGE_H

#include <cstdlib>

#define FC_MESSAGE_HEADER_LENGTH 8
/*
 * 消息包括消息头部和消息body
 * 	消息头部包括消息类型和消息body的大小
 * 	消息body包括消息的具体内容
 *
 * this->_body_length include the last '\0'
 */

class FC_Message
{
public:
    FC_Message(); //构造函数
    FC_Message(const FC_Message& msg);
    FC_Message& operator=(FC_Message const& msg);

    ~FC_Message();

    //getter
    unsigned header_length()const; //获得头部的长度

    unsigned body_length()const; //消息长度
    unsigned mess_length()const;
    unsigned mess_type()const;
    char* header()const;
    char* body()const;
    char* get_friends_identify() const;
    char* get_self_identify() const;
    char* get_core_body() const;

    //setter
    void set_body_length(unsigned body_len);
    void set_message_type(unsigned type);
    void set_body(const char* data,unsigned len);
    void set_header(unsigned type,unsigned int body_len);


    //set new data package design
    void set_friend_identify(const char* data);
    void set_self_identify(const char* data);
    void set_core_body(const char* data,unsigned len);

    //reset message
    void reset_message();
private:
    void apply_memory(unsigned len); //apply for new memory
private:
    char* _data;
};

#endif // FC_MESSAGE_H
