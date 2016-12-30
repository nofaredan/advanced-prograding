//
// Created by rotem on 27/12/16.
//

#ifndef EX2_COMMUNICATIONMANAGER_H
#define EX2_COMMUNICATIONMANAGER_H

#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>


class CommunicationManager {
public:
    int createSocket();
};


#endif //EX2_COMMUNICATIONMANAGER_H
