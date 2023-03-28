/*
FYP : 22013

Module:
    Hybrid Query Driver - Transactional Query Driver

Description:
    Header file for the query handler of the transactional query type 1_A
*/
#include "../../../configuration/QDC001_TQD_Config.h"
#include "../../../utils/QDU001_Time.h"
#include "../../../utils/QDU002_Random.h"
#include "../../../server_skeleton_driver/SSD000_server_skeleton_driver.h"

#include "../../../third_party/json.hpp"

#include <map>
#include <string>

using json = nlohmann::json;

#ifndef TQD002_QUERY_1_A_HANDLER_H
#define TQD002_QUERY_1_A_HANDLER_H

namespace TQ_1_A {

  struct input_struct {

    //For Freshness Score
    int thread_ID;
    unsigned long transaction_ID;

    unsigned long trade_ID;

    unsigned long original_investor_ID;
    uint64_t original_timestamp;
    int traded_companies_list_size;
    unsigned long* trade_company_ID_list;
    int* trade_quantity_list;
    bool* trade_action_list;
  };

  struct output_struct {
    uint64_t start_time;
    uint64_t end_time;
    bool success;
  };

  void input_randomizer(struct input_struct*, struct transactional_driver_config*);

  void operation_handler(struct input_struct*, struct output_struct*, struct transactional_driver_config*);

  void perform_operation(struct transactional_driver_config*, struct output_struct*, struct input_struct*);
}

#endif
