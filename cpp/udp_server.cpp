#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/range.hpp>
#include <thread>
#include <iostream>
#include "message.pb.h"
#include <string>

int main(){
    boost::asio::io_service service;
    boost::asio::ip::udp::socket sock(service);

    boost::asio::ip::udp::resolver resolver(service);
    boost::asio::ip::udp::resolver::query query("127.0.0.1", "3380");
    boost::asio::ip::udp::resolver::iterator iter = resolver.resolve( query);
    
    int size=0,i=0,j=0,i1=0;
    std::size_t size1;
    //Открытие сокета
    sock.open(boost::asio::ip::udp::v4());
    //Назначение устройства куда нужно отправить сообщение
    boost::asio::ip::udp::endpoint receiver_ep=boost::asio::ip::udp::endpoint(*iter);
    boost::system::error_code err;
    message::Message2 m;
    char *buf1[58];
    message::Message *m1;
    //Создание дыух массивов, которые нужно передать
    int id[5]={0,1,2,3,4};
    float s[5]={16.0,16.0,22.22,19.44,16.0},x[5]={5.0,-2.5,-2.5,0.0,0.0},y[5]={10.0,21.0,25.0,30.0,-21.0},w[5]={1.6,1.7,1.7,1.7,1.7},l[5]={4.2,4.25,4.3,4.2,4.3};
    int id1[5]={0,1,2,3};
    float s1[5]={16.0,16.0,16.0,16.44},x1[5]={4.0,-1.0,0.0,0.0},y1[5]={4.0,21.0,-21.0,5.0},w1[5]={1.6,1.7,1.7,1.7},l1[5]={4.2,4.25,4.2,4.2};
    //Основной цикл отправки сообщение
    for(j=0;j<2;j=j+1){
    //Цикл для задания данных в сообщении
    for(i=0;i<5;i=i+1){
    message::Message *m1=m.add_car();
    m1->set_id(id[i]);
    m1->set_speed(s[i]);
    m1->set_x(x[i]);
    m1->set_y(y[i]);
    m1->set_w(w[i]);
    m1->set_l(l[i]);
    }
    //Размер полученного сообщения в байтах
    size1=m.ByteSizeLong();
    i1=0;
    //записьс полученного массива в буфер для передачи
    m.SerializeToArray(&buf1, size1);
    //Отправка сообщения
    sock.send_to(boost::asio::buffer(buf1), receiver_ep,0,err);
    //Цикл обнуления данных
    for(i1=0;i1<5;i1=i1+1){
       id[i1]=0;
       s[i1]=0;
       x[i1]=0;
       y[i1]=0;
       w[i1]=0;
       l[i1]=0;
    }
    //Цикл для записи второго пакета для передачи
    for(i1=0;i1<4;i1=i1+1){
       id[i1]=id1[i1];
       s[i1]=s1[i1];
       x[i1]=x1[i1];
       y[i1]=y1[i1];
       w[i1]=w1[i1];
       l[i1]=l1[i1];
    }
    //Очистка классов
    m1->Clear();
    m.Clear();
    sleep(1);
    }
    //Закрытие сокета
    sock.close();
    //Уничтожение объекта класса protobuf   
    google::protobuf::ShutdownProtobufLibrary();
}
