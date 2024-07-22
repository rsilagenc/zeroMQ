#include <zmq.hpp>
#include <unistd.h>
#include <iostream>
#include <string>

int main()
{
    /*Server Side*/
    zmq::context_t ctx(1);
    zmq::socket_t socket1(ctx, zmq::socket_type::rep);
    socket1.bind("tcp://*5555");

    zmq::message_t request;
    //recv is used by rep socket
    socket1.recv(request, zmq::recv_flags::none);
    std::cout << " " << std::endl;

    zmq::message_t reply(4);
    memcpy(reply.data(), "Hey", 4);
    socket1.send(reply, zmq::send_flags::none);

    /*Client Side*/
    zmq::socket_t socket2(ctx, zmq::socket_type::req);
    socket2.connect("tcp://127.0.0.1:5555");
    std::cout << "Connected to the Server!" << std::endl;

    memcpy(request.data(), " ", 13);
    socket2.send(request, zmq::send_flags::none);

    socket2.recv(reply);

    return 0;
}