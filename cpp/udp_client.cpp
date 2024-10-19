#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/range.hpp>
#include <thread>
#include <iostream>
#include <string>
#include "message.pb.h"
#include <vector>



int main(){
    int i=0,j=0,i1=0;
    boost::asio::io_service service;
    boost::asio::ip::udp::socket sock(service);

    boost::asio::ip::udp::resolver resolver(service);
    boost::asio::ip::udp::resolver::query query("127.0.0.1", "3380");
    boost::asio::ip::udp::resolver::iterator iter = resolver.resolve(query);
    //Открытие сокета
    sock.open(boost::asio::ip::udp::v4());
    boost::asio::ip::udp::endpoint sender_ep;
    boost::system::error_code err;
    //Назначение устройства куда нужно отправить сообщение
    sock.bind(boost::asio::ip::udp::endpoint(*iter));
    char *a2[1330];
    message::Message2 m;
    int size;
    // Цикл для принятия двух сообщений
    for(j=0;j<2;j=j+1){
    //Принятие сообщения
    size=sock.receive_from(boost::asio::buffer(a2), sender_ep,0,err);
    //Извлечение сообщения из буфера
    m.ParseFromArray(&a2, size);
    //Цикл для вывода
    for(i=0;i<m.car().size();i=i+1){
    std::cout<<"id="<<m.car(i).id()<<" speed="<<m.car(i).speed()<<" x="<<m.car(i).x()<<" y="<<m.car(i).y()<<" w="<<m.car(i).w()<<" l="<<m.car(i).l()<<std::endl;
    }
    std::cout<<"\n";
    //Цикл очистки буфера
    for(i1=0;i1<5;i1=i1+1){
       a2[i1]=0;
    }
    m.Clear();
    size=0;
    sleep(1);
    }
    sock.close();
}
