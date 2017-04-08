//
// Created by alfredo on 05/04/17.
//

#ifndef AIRWAR_SERVIDOR_H
#define AIRWAR_SERVIDOR_H


#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

/**
 * @class Servidor
 * @brief Clase encargada de inicializar el servidor.
 */
class Servidor{
public:
    int client,server,clientCount;
    int portNum;
    bool isExit;
    int bufsize;
    char buffer[];
    struct sockaddr_in server_addr;
    socklen_t size;

    Servidor();
    void inicializar();

};

/**
 * @brief Constructor de la clase Servidor
 */
Servidor::Servidor() {
    server=1;
    portNum=8115;
    isExit=false;
    bufsize=1024;
    buffer[bufsize];
    client=socket(AF_INET,SOCK_STREAM,0);

}


/**
 * @brief Metodo encargado de inicializar el servidor para la comunicacion mediante sockets
 */
void Servidor::inicializar() {

    if (client < 0)
    {
        cout << "\nError establishing socket..." << endl;
        exit(1);
    }

    cout << "\n=> Socket server has been created..." << endl;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(portNum);

    if ((bind(client, (struct sockaddr*)&server_addr,sizeof(server_addr))) < 0)
    {
        cout << "=> Error binding connection, the socket has already been established..." << endl;
    }


    size = sizeof(server_addr);
    cout << "=> Looking for clients..." << endl;

    listen(client, 1);


    int clientCount = 1;
    server = accept(client,(struct sockaddr *)&server_addr,&size);

    // first check if it is valid or not
    if (server < 0) {
        cout << "=> Error on accepting..." << endl;
    }
}


#endif //AIRWAR_SERVIDOR_H
