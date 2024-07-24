#include <zmq.hpp> //zeromq
#include <unistd.h> //sleep function
#include <iostream> //i/o operations
#include <string> //for string
#include <thread> //for thread

/*
zmq_bind - accept incoming connections on a socket  
zmq_connect - create outgoing connection from socket
*/

void server(zmq::context_t& ctx)
{
    std::cout << "server has started" << std::endl;
    zmq::socket_t socket1(ctx, zmq::socket_type::rep);
    socket1.connect("inproc://address");

    while(true)
    {
    zmq::message_t request1;
    //recv is used by rep socket
    auto recv_result1 = socket1.recv(request1, zmq::recv_flags::none);
    if (!recv_result1) 
    {
        throw std::runtime_error("Failed to receive message on server side" + std::string(strerror(errno)));
    }
    std::string received_msg(static_cast<char*>(request1.data()), request1.size());
        std::cout << "Server received: " << received_msg << std::endl;

    zmq::message_t reply1(3);
    memcpy(reply1.data(), "Hey", 3);
    socket1.send(reply1, zmq::send_flags::none);
    }

}

void client(zmq::context_t& ctx)
{
    zmq::socket_t socket2(ctx, zmq::socket_type::req);
    socket2.connect("inproc://address");
    std::cout << "Connected to the Server!" << std::endl;

    while(true)
    {
    zmq::message_t request2(11);
    memcpy(request2.data(), "hello back", 11);
    socket2.send(request2, zmq::send_flags::none);

    zmq::message_t reply2;
    auto recv_result2 = socket2.recv(reply2);
    if (!recv_result2) {
        throw std::runtime_error("Failed to receive message on client side" + std::string(strerror(errno)));
    }
    std::string received_msg(static_cast<char*>(reply2.data()), reply2.size());
    std::cout << "Client received: " << received_msg << std::endl;

    }
}



int main()
{
    
    /*Server Side*/
    zmq::context_t ctx(1);
    //continue from here
    std::thread serverThread(server, std::ref(ctx));

    sleep(5);

    /*Client Side*/
    std::thread clientThread(client, std::ref(ctx));

    serverThread.join();
    clientThread.join();

    return 0;
}