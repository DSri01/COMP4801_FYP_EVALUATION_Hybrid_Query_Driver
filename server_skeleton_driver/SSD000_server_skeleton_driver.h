/*
FYP : 22013

Module:
    Hybrid Query Driver - Server Skeleton Driver

Description:
    Header file for the Server Skeleton Driver of the Hybrid Query Driver
*/

#include "../third_party/json.hpp"

#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

using json = nlohmann::json;

#ifndef SSD000_SERVER_SKELETON_DRIVER
#define SSD000_SERVER_SKELETON_DRIVER

json send_query(json, std::string, int);

#endif
