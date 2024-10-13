#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/range.hpp>
#include <thread>
#include <iostream>
#include "message.pb.h"
#include <string>
//#include <boost/lexical_cast.hpp>
//#include <google/protobuf/message_lite.h>
//using namespace google::protobuf;

int main(){
    boost::asio::io_service service;
    boost::asio::ip::udp::socket sock(service);

    //boost::asio::ip::udp::resolver resolver(service);
    //boost::asio::ip::udp::resolver::query query("localhost", "3380");
   // boost::asio::ip::udp::resolver::iterator iter = resolver.resolve( query);
    int size=0,i=0,j=0,i1=0;
    std::size_t size1;
    sock.open(boost::asio::ip::udp::v4());
    boost::asio::ip::udp::endpoint receiver_ep=boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string("192.168.1.67"), 3380);//*iter
    boost::system::error_code err;
    message::Message2 m;
    char *buf1[58];
    message::Message *m1;
    int id[5]={0,1,2,3,4};
    float s[5]={16.0,16.0,22.22,19.44,16.0},x[5]={5.0,-2.5,-2.5,0.0,0.0},y[5]={10.0,21.0,25.0,30.0,-21.0},w[5]={1.6,1.7,1.7,1.7,1.7},l[5]={4.2,4.25,4.3,4.2,4.3};
    //int id[5]={0,1,2,3};
    //float s[5]={16.0,16.0,16.0,16.44},x[5]={4.0,-1.0,0.0,0.0},y[5]={4.0,21.0,-21.0,5.0},w[5]={1.6,1.7,1.7,1.7},l[5]={4.2,4.25,4.2,4.2};
    for(i=0;i<5;i=i+1){
    message::Message *m1=m.add_car();
    m1->set_id(id[i]);
    m1->set_speed(s[i]);
    m1->set_x(x[i]);
    m1->set_y(y[i]);
    m1->set_w(w[i]);
    m1->set_l(l[i]);
    }
    size1=m.ByteSizeLong();
    i1=0;
    m.SerializeToArray(&buf1, size1);//5000
    sock.send_to(boost::asio::buffer(buf1), receiver_ep,0,err);
    sock.close();
    //std::cout<<"sizeof="<<size1<<"\n";
    //std::cout<<m.car(0).id()<<"\n";
    //std::cout<<m.car(0).speed()<<"\n";
    //std::cout<<m.car(0).x()<<"\n";
    //std::cout<<m.car(0).y()<<"\n";
    //std::cout<<m.car(0).w()<<"\n";
    //std::cout<<m.car(0).l()<<"\n";
    google::protobuf::ShutdownProtobufLibrary();
}
