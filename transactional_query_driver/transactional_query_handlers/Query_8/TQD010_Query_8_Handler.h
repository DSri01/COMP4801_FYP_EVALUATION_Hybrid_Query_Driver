/*
FYP : 22013

Module:
    Hybrid Query Driver - Transactional Query Driver

Description:
    Header file for the query handler of the transactional query type 8
*/
#include "../../../configuration/QDC001_TQD_Config.h"
#include "../../../utils/QDU001_Time.h"
#include "../../../utils/QDU002_Random.h"
#include "../../../server_skeleton_driver/SSD000_server_skeleton_driver.h"

#include "../../../third_party/json.hpp"

#include <string>

using json = nlohmann::json;

#ifndef TQD010_QUERY_8_HANDLER_H
#define TQD010_QUERY_8_HANDLER_H

namespace TQ_8 {

  struct input_struct {

    //For Freshness Score
    int thread_ID;
    unsigned long transaction_ID;

    unsigned long source_tradebook_ID;
    unsigned long destination_tradebook_ID;
  };

  struct output_struct {
    uint64_t start_time;
    uint64_t end_time;
    bool success;
  };

  void operation_handler(struct input_struct*, struct output_struct*, struct transactional_driver_config*);

  void perform_operation(struct transactional_driver_config*, struct output_struct*, struct input_struct*);
}

#endif
