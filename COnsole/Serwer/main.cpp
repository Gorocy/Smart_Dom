#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include <vector>
#include "smart_home_logic.h"

using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;

void checkActivity(tcp::socket& server_socket, bool& doThread, std::atomic<bool>& activityDetected) {
    std::chrono::seconds timeout(30); // Określenie czasu bezczynności w sekundach

    while (doThread) {
        std::this_thread::sleep_for(timeout); // Oczekiwanie na timeout
        if (!activityDetected.load()) {
            std::cout << "No activity detected. Closing connection." << std::endl;
            server_socket.close(); // Zamknięcie połączenia
            doThread = false; // Zakończenie wątku obsługi
            break;
        }
        activityDetected.store(false); // Zresetowanie flagi aktywności
    }
}

string waitGetData(tcp::socket& socket) {
    boost::asio::streambuf buf;
    try {
        boost::asio::read_until(socket, buf, "\n");
    } catch (const boost::system::system_error& e) {
        cerr << "Error receiving data: " << e.what() << endl;
        return "ERROR";
    }

    string data = buffer_cast<const char*>(buf.data());
    return data;

}

void sendData(tcp::socket& socket, const string& message) {
    try {
        write(socket, buffer(message + "\n"));
    } catch (const boost::system::system_error& e) {
        cerr << "Error sending data: " << e.what() << endl;
        socket.close();
    }
}

// string waitGetData(tcp::socket& socket) {
//     string reply = "";
//     while(reply == "") {
//         try {
//
//                 reply = getData(socket);
//
//         } catch (const std::invalid_argument& e) {
//
//         }
//     }
//     return reply;
// }

void handleConnection(tcp::socket server_socket, SmartHomeLogic& smartHomeLogic) {
    try {
    	
        string u_name = "";
        u_name = waitGetData(server_socket);

        u_name.pop_back();


        string reply = "Hello " + u_name + "!"+"\n Menu:"+
        "\n1 for door, 11 to check stats of doors, 12 to set status of door(you will chose which)"+
        "\n2 for gate,  21 to check status of gate and garage, 22 to set status of gate and garage"+
        "\n3 for monitoring, [ BROKEN ]"+
        "\n4 for pet feeder, 41 to check feeding time, to feed now"+
        "\n5 for roller shutter, 51 to check status of doors, 52 to set status of roller shutter(you will chose which)"+
        "\n6 for thermostat, 61 to check temperature, 62 to set temperature";//+
        //"7 for";

        sendData(server_socket, reply);
        cout << "Server to  "<<u_name << " :" << reply << endl;

           bool doThread = true;
    std::atomic<bool> activityDetected(false);

    // Rozpoczęcie wątku monitorującego aktywność
    std::thread activityThread(checkActivity, std::ref(server_socket), std::ref(doThread), std::ref(activityDetected));

    while (doThread) {
        std::string response = waitGetData(server_socket);
        if (response.empty()) {
            continue; // Brak danych od klienta
        }

        // Oznaczenie aktywności klienta
        activityDetected.store(true);
            std::cout << u_name << ": " << response << std::endl;

                switch (stoi(response)) {
                    //DOOR
                    case 1: {
                        reply = "1 for door, 11 to check stats of doors, 12 to set status of door(you will chose which)";
                        sendData(server_socket, reply);
                        //response = waitGetData(server_socket);
                        break;
                    }
                    case 11: {
                        reply = "\nDoor[1] :" + std::to_string(smartHomeLogic.checkDoor(0)) + "\nDoor[2] : "+
                        std::to_string(smartHomeLogic.checkDoor(1)) + "\nDoor[3]"+
                            std::to_string(smartHomeLogic.checkDoor(2))+
                        +"\nDoor[4] : "+ std::to_string(smartHomeLogic.checkDoor(3)) ;
                        sendData(server_socket, reply);
                        //response = waitGetData(server_socket);
                        break;
                    }
                    case 12: {
                        reply = "Which door you want to set new status\nDoor[1] :" + std::to_string(smartHomeLogic.checkDoor(0)) + "\nDoor[2] : "+
                        std::to_string(smartHomeLogic.checkDoor(1)) + "\nDoor[3]"+
                            std::to_string(smartHomeLogic.checkDoor(2))+
                        +"\nDoor[4] : "+ std::to_string(smartHomeLogic.checkDoor(3))+
                            "\n First how many";

                        sendData(server_socket, reply);
                        int amount = stoi(waitGetData(server_socket));
                        for(int i = 0; i < amount; i++) {
                            reply ="Which door?";
                            sendData(server_socket, reply);
                            int choosenDoor = stoi(waitGetData(server_socket));
                            while(choosenDoor<1 || choosenDoor >4) {
                                reply = reply ="Which door? [ 1 to 4 ]";
                                choosenDoor = stoi(waitGetData(server_socket));
                            }
                            reply ="Set new status 0 for open 1 for close";
                            sendData(server_socket, reply);
                            int newStatus = stoi(waitGetData(server_socket));
                            smartHomeLogic.controlDoor(choosenDoor, newStatus);

                        }
                        break;
                    }
                    //GATE
                    case 2: {
                        reply="2 for gate,  21 to check status of gate and garage, 22 to set status of gate and garage";
                        sendData(server_socket, reply);
                        //response= waitGetData(server_socket);
                        break;
                    }
                    case 21: {
                        reply ="Gate and garage: "+ std::to_string(smartHomeLogic.checkGateAndGarage());
                        sendData(server_socket, reply);
                        //response= waitGetData(server_socket);
                        break;
                    }
                    case 22: {
                        reply ="Set new status for gate and garage: "+ std::to_string(smartHomeLogic.checkGateAndGarage());
                        sendData(server_socket, reply);
                        int newStatus = stoi(waitGetData(server_socket));
                        smartHomeLogic.controlGateAndGarage(newStatus);
                        //response= waitGetData(server_socket);
                        break;
                    }

                    //MONITORING
                    case 3: {
                        reply = +"3 for monitoring, [ BROKEN ], OK?";
                        sendData(server_socket,reply);
                        //response = waitGetData(server_socket);
                        //cout<<u_name<<" :"<< response;
                        break;
                    }
                    case 31: {
                        reply = +"3 for monitoring, [ BROKEN ], OK?";
                        sendData(server_socket,reply);
                       // response = waitGetData(server_socket);
                        //cout<<u_name<<" :"<< response;
                        // Do something for case M/m
                        break;
                    }
                    case 32:{
                        reply = +"3 for monitoring, [ BROKEN ], OK?";
                        sendData(server_socket,reply);
                       // response = waitGetData(server_socket);
                       // cout<<u_name<<" :"<< response;

                        break;
                    }
                    //PET FEEDER
                    case 4: {
                        reply = "4 for pet feeder, 41 to check feeding time, to feed now, OK?";
                        sendData(server_socket,reply);
                        //response = waitGetData(server_socket);
                        //cout<<u_name<<" :"<< response;
                        break;
                    }
                    case 41: {
                        reply="time feeding: "+std::to_string(smartHomeLogic.checkPetFeeder());
                        sendData(server_socket, reply);
                        //response = waitGetData(server_socket);

                        break;
                    }
                    case 42: {
                        reply = "Actual time feeding :"+std::to_string(smartHomeLogic.checkPetFeeder())+
                            "\n What new set : ";
                        sendData(server_socket, reply);
                        //response = waitGetData(server_socket);
                        break;
                    }
                    //RLLER SHUTTER
                    case 5: {
                        reply = "5 for roller shutter, 51 to check status of doors, 52 to set status of roller shutter(you will chose which)";
                        sendData(server_socket, reply);
                        //response = waitGetData(server_socket);

                        break;
                    }

                    case 51: {
                        reply = "Roller shutter[1] :" + std::to_string(smartHomeLogic.checkRollerShutter(0)) +
                            "\nRoller shutter[2] : "+ std::to_string(smartHomeLogic.checkRollerShutter(1)) +
                            "\nRoller shutter[3]"+std::to_string(smartHomeLogic.checkRollerShutter(2))+
                        +"\nRoller shutter[4] : "+ std::to_string(smartHomeLogic.checkRollerShutter(3)) ;
                        sendData(server_socket, reply);
                        //response = waitGetData(server_socket);
                        break;
                    }
                    case 52: {
                        reply = "Which door you want to set new status \nRoller shutter[1] :" + std::to_string(smartHomeLogic.checkRollerShutter(0)) +
                            "\nRoller shutter[2] : "+ std::to_string(smartHomeLogic.checkRollerShutter(1)) +
                            "\nRoller shutter[3]"+std::to_string(smartHomeLogic.checkRollerShutter(2))+
                         "\nRoller shutter[4] : "+ std::to_string(smartHomeLogic.checkRollerShutter(3)) +
                            "\n First how many";

                        sendData(server_socket, reply);
                        int amount = stoi(waitGetData(server_socket));
                        for(int i = 0; i < amount; i++) {
                            reply ="Which roller shutter?";
                            sendData(server_socket, reply);
                            int choosenDoor = stoi(waitGetData(server_socket));
                            while(choosenDoor<1 || choosenDoor >4) {
                                reply = reply ="Which roller shutter? [ 1 to 4 ]";
                                choosenDoor = stoi(waitGetData(server_socket));
                            }
                            reply ="Set new status 0 for open 1 for close";
                            sendData(server_socket, reply);
                            int newStatus = stoi(waitGetData(server_socket));
                            smartHomeLogic.controlDoor(choosenDoor, newStatus);

                        }
                        //response = waitGetData(server_socket);
                        break;
                    }
                    //THERMOSTAT
                    case 6: {
                        reply = "6 for thermostat, 61 to check temperature, 62 to set temperature";
                        sendData(server_socket, reply);
                      //  response = waitGetData(server_socket);

                        break;
                    }
                    case 61: {
                        reply = "Actual temperature : "+std::to_string(smartHomeLogic.checkThermostat());
                        sendData(server_socket, reply);
                       // response = waitGetData(server_socket);
                        break;
                    }
                    case 62: {
                        reply = "Actual temperature : "+std::to_string(smartHomeLogic.checkThermostat())+
                            "\nNew temperature";
                        sendData(server_socket, reply);
                       response = waitGetData(server_socket);
                        while(stoi(response)<0 || stoi(response)>30) {
                            reply = "Wrong temperature set new: ";
                            sendData(server_socket, reply);
                            response = waitGetData(server_socket);
                        }
                        smartHomeLogic.setThermostat(stoi(response));
                        break;
                    }
                    //case 7:
                    default:
                        cout << "Server: Invalid command. Ending connection\n";
                    doThread = false;
                    break;




            }


            if (response == "exit") {
                cout << u_name << " left!" << endl;
                doThread = false;
                break;
            }
            response ="";


            response = "";
            reply = "";

        }

            server_socket.close();
    if (activityThread.joinable()) {
        activityThread.join();
    }
    } catch (const boost::system::system_error& e) {
        server_socket.close();
    }
}

int main() {
    SmartHomeLogic smartHomeLogic;
    smartHomeLogic.setThermostat(25);
    boost::asio::io_context io_context;

    try {
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8080));

        while (true) {

            tcp::socket socket(io_context);
            acceptor.accept(socket);

            std::thread(handleConnection, std::move(socket), std::ref(smartHomeLogic)).detach();
            auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::tm* currentTime = std::localtime(&now);
            int currentHour = currentTime->tm_hour;

            // Sprawdzanie, czy nadszedł czas na karmienie
            if (currentHour == smartHomeLogic.checkPetFeeder()) {
                std::cout << "Nadszedł czas karmienia!" << std::endl;
                smartHomeLogic.feedingPet();
                break; // Zatrzymaj pętlę po karmieniu
            }
        }

    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
