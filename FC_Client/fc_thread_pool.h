#ifndef FC_THREAD_POOL_H
#define FC_THREAD_POOL_H

#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <vector>
#include <unordered_map>

using boost::thread;
using boost::thread_group;
using boost::asio::io_service;
using std::vector;
using std::unordered_map;
using boost::asio::steady_timer;

class FC_Thread_Pool
{
public:
    FC_Thread_Pool(int num=1);
    ~FC_Thread_Pool();
    io_service* get_logic_service();

private:
    void init_thread_pool();// initilize thread pool
    void timer_handle(int i,const boost::system::error_code& err); //timeout to restart timer

private:
    thread_group* _thread_group = nullptr;
    vector<io_service*> _io_services;
    vector<thread*> _threads;
    vector<steady_timer*> _timers;
    unordered_map<int,thread*> _map;
    int _thread_num;
    enum{FC_LOGIC_SERVICE=0};
};

#endif // FC_THREAD_POOL_H
