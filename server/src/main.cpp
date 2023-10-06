/*

author : Yekuuun
github : https://github.com/yekuuun

Entry point of server.

*/
#include <iostream>
#include "server.hpp"

int main(){
    int server = launch_udp_server();

    if(server != 0){
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}