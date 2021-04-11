#include "fc_thread_pool.h"
#include <QDebug>

//==============================================
//  public function
//==============================================

FC_Thread_Pool::FC_Thread_Pool(int num):_thread_num(num)
{
    _logic_turns = FC_LOGIC_START;
    _thread_group = new thread_group;
    for(int i=0;i<num;++i){
        _io_services.push_back(new io_service);
        _timers.push_back(new steady_timer(*_io_services[i]));
//        _timers.push_back(new steady_timer(*_io_services[i],std::chrono::steady_clock::now() + std::chrono::seconds(60)));
        _timers[i]->expires_after(std::chrono::seconds(1));
//        _timers[i]->async_wait(boost::bind(&FC_Thread_Pool::timer_handle,shared_from_this(),_1));
        _timers[i]->async_wait(boost::bind(&FC_Thread_Pool::timer_handle,this,i,_1));
    }
}

FC_Thread_Pool::~FC_Thread_Pool(){
    delete _thread_group;
    for(int i=0;i<_thread_num;++i){
        delete _io_services[i];
    }
}

io_service* FC_Thread_Pool::get_logic_service(){
    auto result = _io_services[_logic_turns];
    ++_logic_turns;
    if(_logic_turns>=_thread_num)
        _logic_turns=FC_LOGIC_START;
    return result;
}
io_service* FC_Thread_Pool::get_acceptor_service(){
    return _io_services[FC_ACCEPTOR];
}


void FC_Thread_Pool::init_thread_pool(){
    for(int i=0;i<_thread_num;++i){
        auto thread = _thread_group->create_thread(boost::bind(&io_service::run,_io_services[i]));
        thread->get_id();
        _threads.push_back(thread);
    }

    for(int i=0;i<_thread_num;++i){
        _threads[i]->join();
    }
//    this->_thread_group->join_all();
}


void FC_Thread_Pool::timer_handle(int i,const boost::system::error_code& err){
    if(!err){
        _timers[i]->expires_after(std::chrono::seconds(1));
        _timers[i]->async_wait(boost::bind(&FC_Thread_Pool::timer_handle,this,i,_1));
    }else{
        qDebug() << "timer_handle" << err.message().data() ;
        exit(err.value());
    }
}
