/*

author : Yekuuun
github : https://github.com/yekuuun

entry point of server program.

*/
#include <iostream>
#include <winsock2.h>
#include <wS2tcpip.h>
#include <synchapi.h>
#include "logs.hpp"

void display_server_message();

//launching tcp bladerunner server
int launch_tcp_server(){
    
    //initializing winsock library
    WSADATA ws;

    int ws_result = WSAStartup(MAKEWORD(2,2), &ws);

    if(ws_result != 0){
        std::cout << "[ERROR] while trying to initialize winsock library..." << std::endl;
        return EXIT_FAILURE;
    }

    display_server_message();

    //path to logs folder - adpat it
    std::string folderPath = "YOUR FOLDER PATH";

    //bind
    struct addrinfo *bind_address = NULL;

    //config local address
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    //get address
    int getaddrinfo_result = getaddrinfo(0, "5050", &hints, &bind_address);

    if(getaddrinfo_result != 0){
        std::cout << "[ERROR] unable to use getaddrinfo() with error: " << WSAGetLastError() << std::endl;
        goto CLEANUP;
    }

    //creating server socket
    SOCKET socket_listen;
    socket_listen = socket(bind_address->ai_family, bind_address->ai_socktype, bind_address->ai_protocol);

    if(socket_listen == INVALID_SOCKET){
        std::cout << "[ERROR] unable to create socket..." << std::endl;
        goto CLEANUP;
    }

    std::cout << "Binding socker to local address..." << std::endl;

    int bind_result = bind(socket_listen, bind_address->ai_addr, bind_address->ai_addrlen);

    if(bind_result != 0){
        std::cout << "[ERROR] while trying to bind local address with socket..." << std::endl;
        goto CLEANUP;
    }
    
    //listen for connexion
    int listen_result = listen(socket_listen, 1);

    if(listen_result != 0){
        std::cout << "[ERROR] Failed using listen() with error: " << WSAGetLastError() << std::endl;
        goto CLEANUP;
    }

   std::cout << "Waiting for client connection..." << std::endl;
    struct sockaddr_storage client_address;
    socklen_t client_len = sizeof(client_address);

    SOCKET client_socket = accept(socket_listen,(struct sockaddr*) &client_address, &client_len);

    if(client_socket == INVALID_SOCKET){
        std::cout << "[ERROR] while trying to connect client" << WSAGetLastError() << std::endl;
        goto CLEANUP;
    }

    std::cout << "Client Connected successfully! "<< std::endl;

    //exchange part
    char command[100];

    while(1){
        // Receive command from the server
        char received_command[100];
        memset(received_command, 0, sizeof(received_command));

        if (recv(client_socket, received_command, sizeof(received_command), 0) == SOCKET_ERROR) {
            perror("recv failed");
            goto CLEANUP;
        }

        std::cout << "Received command from server: " << received_command << std::endl;

        if(strcmp(received_command, "CLOSE") == 0){
            goto CLEANUP;
        }

        int logs = create_logs(folderPath, received_command);

        if(logs != 0){
            break;
        } 
    }


    //cleaning
    CLEANUP:
        freeaddrinfo(bind_address);

        if(socket_listen){
            closesocket(socket_listen);
            std::cout << "Closing server socket..." << std::endl;
        }

        if(client_socket){
            closesocket(client_socket);
            std::cout << "Closing client socket..." << std::endl;
        }

        WSACleanup();
        std::cout << "Finished." << std::endl;

    return EXIT_SUCCESS;
}

//display main server message.
void display_server_message(){
        std::cout << "\x1b[35m"
              << " ____  _           _      ____                              " << std::endl
              << "| __ )| | __ _  __| | ___|  _ \\ _   _ _ __  _ __   ___ _ __ " << std::endl
              << "|  _ \\| |/ _` |/ _` |/ _ \\ |_) | | | | '_ \\| '_ \\ / _ \\ '__|" << std::endl
              << "| |_) | | (_| | (_| |  __/  _ <| |_| | | | | | | |  __/ |   " << std::endl
              << "|____/|_|\\__,_|\\__,_|\\___|_| \\_\\__,_ |_| |_|_| |_|\\___|_|   " << std::endl
              << "\x1b[0m"; // Réinitialisation de la couleur
        std::cout << "\n" << std::endl;
        std::cout << "Launching server...\n" << std::endl;
}