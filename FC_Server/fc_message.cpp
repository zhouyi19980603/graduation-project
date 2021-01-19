
#include "fc_message.h"
#include <cstdlib>
#include <cstring>
#include "fc_header.h"

//==============================================
//  public function
//==============================================

FC_Message::FC_Message()
{
    this->_data = (char *)malloc(FC_MESSAGE_HEADER_LENGTH+1);
    memset(this->_data,'\0',FC_MESSAGE_HEADER_LENGTH+1);
}

FC_Message::FC_Message(const FC_Message& msg){ //拷贝构造函数
    this->_data = (char *)malloc(header_length()); //申请空间
    memcpy(this->_data,msg._data,header_length());
    this->set_body_length(msg.body_length());
    memcpy(this->_data,msg._data,mess_length());
}

FC_Message &FC_Message::operator=(const FC_Message &msg) //拷贝赋值构造
{
    this->_data=(char*)malloc(header_length());
    memcpy(this->_data,msg._data,header_length());
    this->set_body_length(msg.body_length());
    memcpy(this->_data,msg._data,mess_length());
    return *this;
}

FC_Message::~FC_Message(){
    free(this->_data);
}

//getter unsigned若省略后一个关键字，大多数编译器都会认为是unsigned int
unsigned FC_Message::header_length()const{
    return FC_MESSAGE_HEADER_LENGTH;
}
unsigned FC_Message::body_length()const{
    unsigned body_length = 0;
    memcpy(&body_length,this->_data+sizeof (unsigned),sizeof (unsigned));
    return body_length;
}
unsigned FC_Message::mess_length()const{
    return this->header_length()+body_length();
}
unsigned FC_Message::mess_type()const{
    unsigned mess_type=0;
    //第一个参数为存储复制内容，第二个参数为原位置，第三个参数为大小
    memcpy(&mess_type,this->_data,sizeof (mess_type));
    //四个字节
    return mess_type;
}
char* FC_Message::header()const{
    return this->_data;
}

char* FC_Message::body()const{
    //返回body部分的值
    return this->_data+FC_MESSAGE_HEADER_LENGTH;
}

char *FC_Message::get_friends_identify() const
{
    char* sd=(char*)malloc(FC_ACC_LEN+1);
    memset(sd,'\0',FC_ACC_LEN+1);
    memcpy(sd,this->_data+FC_MESSAGE_HEADER_LENGTH,FC_ACC_LEN);
    return sd;
}

char *FC_Message::get_self_identify() const
{
    char* sd=(char*)malloc(FC_ACC_LEN+1);
    memset(sd,'\0',FC_ACC_LEN+1);
    memcpy(sd,this->_data+FC_MESSAGE_HEADER_LENGTH+FC_ACC_LEN,FC_ACC_LEN);
    return sd;
}

char *FC_Message::get_core_body() const
{
    return this->_data + FC_MESSAGE_HEADER_LENGTH + 2 * FC_ACC_LEN;
}

//setter
void FC_Message::set_body_length(unsigned body_len){
    memcpy(this->_data+sizeof (unsigned),&body_len,sizeof (unsigned));
    this->apply_memory(this->mess_length()); //申请空间
}
void FC_Message::set_message_type(unsigned type){
    memcpy(this->_data,&type,sizeof (type));
}
void FC_Message::set_body(const char*data,unsigned len){
//    this->apply_memory(this->mess_length()); //lazy fetch
    memcpy(this->_data+sizeof (unsigned)*2,data,len);
}

void FC_Message::set_friend_identify(const char *data)
{
    memcpy(this->_data+sizeof (unsigned)*2,data,FC_ACC_LEN); //位置 长度
}

void FC_Message::set_self_identify(const char *data)
{
    memcpy(this->_data+sizeof (unsigned)*2 + FC_ACC_LEN,data,FC_ACC_LEN);
}

void FC_Message::set_core_body(const char *data, unsigned len)
{
    memcpy(this->_data+sizeof (unsigned)*2 + 2 *FC_ACC_LEN,data,len);
}

void FC_Message::reset_message(){ //reset this message
    this -> set_message_type(0);
    this -> set_body_length(0);
}

//==============================================
//  private function
//==============================================

void FC_Message::apply_memory(unsigned len){ //apply for new memory
    //apply new memory for message_body
    char *tmp = (char *)malloc(len+1);
    memset(tmp,'\0',len+1);
    memcpy(tmp,this->_data,FC_MESSAGE_HEADER_LENGTH);
    free(this->_data);
    this->_data = tmp;
}

void FC_Message::set_header(unsigned type,unsigned int body_len){
    memcpy(this->_data,&type,sizeof(unsigned));
    memcpy(this->_data+sizeof (unsigned),&body_len,sizeof (unsigned));
    this->apply_memory(this->mess_length());
}
