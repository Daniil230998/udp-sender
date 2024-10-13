#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/range.hpp>
#include <thread>
#include <iostream>
#include <string>
#include "message.pb.h"
#include <vector>
//#include "overtaking.hpp"
//struct Point{
//  float x;
//  float y;
//};



int main(){
    int i=0,j=0,i1=0;
    boost::asio::io_service service;
    boost::asio::ip::udp::socket sock(service);

    //boost::asio::ip::udp::resolver resolver(service);
    //boost::asio::ip::udp::resolver::query query("localhost", "3380");
    //boost::asio::ip::udp::resolver::iterator iter = resolver.resolve(query);

    sock.open(boost::asio::ip::udp::v4());
    boost::asio::ip::udp::endpoint sender_ep;
    boost::system::error_code err;
    sock.bind(boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string("192.168.1.67"), 3380));//*iter
    char *a2[1330];
    message::Message2 m;
    int size;//=133;
    //std::vector<Point> b;

    size=sock.receive_from(boost::asio::buffer(a2), sender_ep,0,err);
    
    m.ParseFromArray(&a2, size);
    //b=overtaking(m);
    //for(i=0;i<b.size();i=i+2){
    //        std::cout<<"i="<<i<<"\n";
    // std::cout<<"b.x="<<b[i].x<<" b.y="<<b[i].y<<"\n";
    // std::cout<<"b.x="<<b[i+1].x<<" b.y="<<b[i+1].y<<"\n";
    //}
    std::cout<<"size="<<size<<"\n";
    for(i=0;i<m.car().size();i=i+1){
    std::cout<<"id="<<m.car(i).id()<<" speed="<<m.car(i).speed()<<" x="<<m.car(i).x()<<" y="<<m.car(i).y()<<" w="<<m.car(i).w()<<" l="<<m.car(i).l()<<std::endl;
    }
    sock.close();
}
