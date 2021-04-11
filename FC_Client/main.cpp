#include "fc_client.h"

#include <iostream>
#include <limits>
#include <cstdlib>
#include <cstring>
#include <json/json.h>
using namespace std;

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QFont>
#include <fstream>


void add_json_data(Json::Value item,const string& filename,const string& key)
{
    Json::Reader reader;
    Json::Value root;
    ifstream is;

    if(access(filename.c_str(),F_OK) == -1)
    {
        root[key].append(item);
        Json::FastWriter write;
        string strWrite = write.write(root);

        //表明不存在
        ofstream os;
        os.open(filename, std::ios::out | std::ios::binary);
        os << strWrite;
        os.close();

    }else
    {
        is.open(filename,std::ios::binary);
        if(reader.parse(is,root,false))
        {

            root[key].append(item);

            Json::FastWriter write;
            string strWrite = write.write(root);
    //        cout<<strWrite<<endl;
            ofstream ofs;
            ofs.open(filename);
            ofs << strWrite;
            ofs.close();
        }
    }
    is.close();
}
int main(int argc, char *argv[])
{

//    Json::Value item;
//    item["userId"]="@12345";
//    item["postId"]="@12345:04:08";
//    string filaname="./config/moments.json";

//    add_json_data(item,filaname,"@12345moments");
    FC_Client client;
    return 0;
}
