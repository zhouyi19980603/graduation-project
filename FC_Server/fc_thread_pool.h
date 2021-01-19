#ifndef FC_THREAD_POOL_H
#define FC_THREAD_POOL_H

#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/timer.hpp>
#include <vector>
#include <unordered_map>
#include <boost/enable_shared_from_this.hpp>

using boost::thread_group;
using boost::thread;
using boost::enable_shared_from_this;
using boost::asio::steady_timer;
using boost::asio::io_service;
using std::vector;
using std::unordered_map;

class FC_Thread_Pool:public enable_shared_from_this<FC_Thread_Pool>
{
public:
    FC_Thread_Pool(int num);
    ~FC_Thread_Pool();

    io_service* get_logic_service(); //get io socket service
    io_service* get_acceptor_service(); //get acceptor service

    void init_thread_pool(); // initilize thread pool

private:
    void timer_handle(int i,const boost::system::error_code& err); //timeout to restart timer

private:
    thread_group* _thread_group;
    vector<io_service*> _io_services;
    vector<thread*> _threads;
    vector<steady_timer*> _timers;
    unordered_map<int,thread*> _map;
    int _thread_num;

    enum{FC_ACCEPTOR=1,FC_LOGIC_START=2};
    int _logic_turns;
};

#endif // FC_THREAD_POOL_H
