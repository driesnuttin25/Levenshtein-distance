#include <iostream>
#include <zmq.hpp>
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>
#define sleep(n)    Sleep(n)
#endif

int main() {
    try {
        zmq::context_t context(1);

        // Set up push socket to send messages
        zmq::socket_t pusher(context, ZMQ_PUSH);
        pusher.connect("tcp://benternet.pxl-ea-ict.be:24041");

        // Set up subscriber socket to listen for responses
        zmq::socket_t subscriber(context, ZMQ_SUB);
        subscriber.connect("tcp://benternet.pxl-ea-ict.be:24042");
        std::string responseTopic = "dries>correct>";
        subscriber.setsockopt(ZMQ_SUBSCRIBE, responseTopic.c_str(), responseTopic.length());

        // Input from user
        std::string variableWord;
        std::cout << "Enter a word: ";
        std::cin >> variableWord;

        // Construct and send message
        std::string message = "dries>spelling>" + variableWord + ">";
        pusher.send(message.c_str(), message.size());
        std::cout << "Sent: [" << message << "]" << std::endl;

        // Listen for response
        zmq::message_t response;
        subscriber.recv(&response);
        std::string receivedResponse(static_cast<char*>(response.data()), response.size());
        std::cout << std::endl << "Response Received: [" << receivedResponse << "]" << std::endl;
    }
    catch(zmq::error_t& e) {
        std::cerr << "Caught an exception: " << e.what() << std::endl;
    }

    return 0;
}
