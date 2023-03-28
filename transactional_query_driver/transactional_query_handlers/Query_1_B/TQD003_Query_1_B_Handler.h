/*
FYP : 22013

Module:
    Hybrid Query Driver - Transactional Query Driver

Description:
    Header file for the query handler of the transactional query type 1_B
*/
#include "../../../configuration/QDC001_TQD_Config.h"
#include "../../../utils/QDU001_Time.h"
#include "../../../utils/QDU002_Random.h"
#include "../Query_3/TQD005_Query_3_Handler.h"
#include "../Query_6/TQD008_Query_6_Handler.h"
#include "../../../server_skeleton_driver/SSD000_server_skeleton_driver.h"

#include "../../../third_party/json.hpp"

#include <string>

using json = nlohmann::json;

#ifndef TQD003_QUERY_1_B_HANDLER_H
#define TQD003_QUERY_1_B_HANDLER_H

namespace TQ_1_B {

  struct input_struct {

    //For Freshness Score
    int thread_ID;
    unsigned long transaction_ID;
  };

  struct transactions_linked_list_node {
    uint64_t start_time;
    uint64_t end_time;
    std::string query_type;
    unsigned long transaction_ID;
    transactions_linked_list_node* next;
  };

  struct output_struct {
    transactions_linked_list_node* head_node;
    int number_of_transactions;
    unsigned long next_transaction_ID;
    bool success;
  };

  void operation_handler(struct input_struct*, struct output_struct*, struct transactional_driver_config*);

  void perform_operation(struct transactional_driver_config*, struct output_struct*, unsigned long, int);
}

#endif
