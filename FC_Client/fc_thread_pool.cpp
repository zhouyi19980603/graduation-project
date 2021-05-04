#include "fc_thread_pool.h"
#include <QDebug>
#include <boost/bind.hpp>

//==============================================
//  public function
//==============================================

FC_Thread_Pool::FC_Thread_Pool(int num):_thread_num(num)
{
    this->_thread_group = new thread_group;
    for(int i=0;i<1;++i){
        this->_io_services.push_back(new io_service);
        this->_timers.push_back(new steady_timer(*_io_services[i]));
        this->_timers[i]->expires_after(std::chrono::seconds(1));
        this->_timers[i]->async_wait(boost::bind(&FC_Thread_Pool::timer_handle,this,i,_1));
    }
    init_thread_pool();
}

FC_Thread_Pool::~FC_Thread_Pool(){
    this->_thread_group->join_all();
    delete this->_thread_group;
}

io_service* FC_Thread_Pool::get_logic_service(){
    //client thread_pool nums = 1
    return this->_io_services[FC_LOGIC_SERVICE];
}


//==============================================
//  private function
//==============================================
void FC_Thread_Pool::init_thread_pool(){
    for(int i=0;i<_thread_num;++i){
        auto thread =  this->_thread_group->create_thread(boost::bind(&io_service::run,this->_io_services[i]));
        this->_threads.push_back(thread);
    }
}

void FC_Thread_Pool::timer_handle(int i,const boost::system::error_code& err){
    if(!err){
//        qDebug() << "time out " << this->_threads[i]->thread::get_id()  << std::endl;
        _timers[i]->expires_after(std::chrono::seconds(1));
        _timers[i]->async_wait(boost::bind(&FC_Thread_Pool::timer_handle,this,i,_1));
    }else{
       qDebug()<< "timer_handle error:" << err.message().data();
        exit(err.value());
    }
}
