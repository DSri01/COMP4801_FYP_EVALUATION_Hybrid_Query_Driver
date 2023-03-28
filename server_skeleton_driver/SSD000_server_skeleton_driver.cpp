/*
FYP : 22013

Module:
    Hybrid Query Driver - Server Skeleton Driver

Description:
    Driver for the Server Skeleton module for the evaluation phase of HTAP Graph
    Database Benchmark development. Allows this Hybrid Query Driver to interact
    with the System Under Test (SUT) via the Server Skeleton interface.

*/

#include "SSD000_server_skeleton_driver.h"

json send_query(json query, std::string IP_ADDRESS, int PORT_NUMBER) {

  int socket_fd;
  struct sockaddr_in serv_addr;

  json error_message;
  error_message["SUCCESS"] = false;

  socket_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (socket_fd < 0) {
    perror("Socket Allocation Error\n");
    return error_message;
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT_NUMBER);

  if (inet_pton(AF_INET, IP_ADDRESS.c_str(), &serv_addr.sin_addr) <= 0) {
    printf("Invalid address\n");
    return error_message;
  }

  if ((connect(socket_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
    printf("Connection Failed\n");
    return error_message;
  }

  std::string query_message = query.dump() + "|";

  int number_of_bytes_to_send = query_message.length();
  while (number_of_bytes_to_send > 0){

    int start_pos = query_message.length() - number_of_bytes_to_send;
    std::string remaining_substring = query_message.substr(start_pos, number_of_bytes_to_send);

    int sent_bytes = send(socket_fd, remaining_substring.c_str(), std::strlen(remaining_substring.c_str()), 0);
    number_of_bytes_to_send = number_of_bytes_to_send - sent_bytes;
  }

  char buffer[1] = {0};
  std::string json_response_string = "";

  while (true) {
  int value_from_socket = read(socket_fd, buffer, 1);
    if (buffer[0] == '|') {
      break;
    }
    else {
      json_response_string = json_response_string + buffer[0];
    }
  }

  json response = json::parse(json_response_string);

  close(socket_fd);
  return response;
}
