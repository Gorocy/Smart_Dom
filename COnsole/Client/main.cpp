#include <boost/asio.hpp>
#include <iostream>
using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;

string getData(tcp::socket& socket)
{
    boost::asio::streambuf buf;
    try {
        boost::asio::read_until(socket, buf, "\n");
    } catch (const boost::system::system_error& e) {
        cerr << "Error receiving data: " << e.what() << endl;


    }



    string data = buffer_cast<const char*>(buf.data());
    return data;
}

void sendData(tcp::socket& socket, const string& message)
{
    try {
        write(socket, buffer(message + "\n"));
    } catch (const boost::system::system_error& e) {
        cerr << "Error sending data: " << e.what() << endl;


    }
}

int main(int argc, char* argv[])
{
    io_service io_service;
    // socket creation
    ip::tcp::socket client_socket(io_service);

    client_socket.connect(tcp::endpoint(address::from_string("127.0.0.1"),8080));

    // Getting username from user
    cout << "Enter your name: ";
    string u_name, reply, response;
    getline(cin, u_name);

    // Sending username to another end
    // to initiate the conversation
    sendData(client_socket, u_name);

    response = getData(client_socket);

    // Infinite loop for chit-chat
    while (true) {





        if (response == "exit") {
            cout << "Connection terminated" << endl;
            break;
        }
        cout << "Server: " << response << endl;

        // Reading new message from input stream
        cout << u_name << " : " ;
        getline(cin, reply);
        
        
        sendData(client_socket, reply);

        if (reply == "exit")
            break;
        response = getData(client_socket);
        response.pop_back();
        
    }
    return 0;
}
