/*
FYP : 22013

Module:
    Hybrid Query Driver - Analytical Query Driver

Description:
    Header file for the query handler of the analytical query type 5
*/
#include "../../../configuration/QDC002_AQD_Config.h"
#include "../../../utils/QDU001_Time.h"
#include "../../../server_skeleton_driver/SSD000_server_skeleton_driver.h"

#include "../../../third_party/json.hpp"

#include <map>
#include <string>

using json = nlohmann::json;

#ifndef AQD006_QUERY_5_HANDLER_H
#define AQD006_QUERY_5_HANDLER_H

namespace AQ_5 {

  // ANALYTICAL QUERY 5: CDLP

  struct input_struct {
  };

  struct output_struct {
    uint64_t start_time;
    uint64_t end_time;
    bool success = true;
    unsigned long* freshness_score_transaction_id_for_each_thread_list;
  };

  void operation_handler(struct input_struct*, struct output_struct*, struct analytical_driver_config*);

  void perform_operation(struct analytical_driver_config*, struct output_struct*, struct input_struct*);
}

#endif
