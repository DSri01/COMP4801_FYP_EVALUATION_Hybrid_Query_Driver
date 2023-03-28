/*
FYP : 22013

Module:
    Hybrid Query Driver - Analytical Query Driver

Description:
    Header file for the query handler of the analytical query type 6
*/
#include "../../../configuration/QDC002_AQD_Config.h"
#include "../../../utils/QDU001_Time.h"
#include "../../../utils/QDU002_Random.h"
#include "../../../server_skeleton_driver/SSD000_server_skeleton_driver.h"

#include "../../../third_party/json.hpp"

#include <map>
#include <string>

using json = nlohmann::json;

#ifndef AQD007_QUERY_6_HANDLER_H
#define AQD007_QUERY_6_HANDLER_H

namespace AQ_6 {

  // ANALYTICAL QUERY 6: SSSP

  struct input_struct {
    unsigned long root_vertex_ID;
  };

  struct output_struct {
    uint64_t start_time;
    uint64_t end_time;
    bool success = true;
    unsigned long* freshness_score_transaction_id_for_each_thread_list;
  };

  void input_randomizer(struct input_struct*, struct analytical_driver_config*);

  void operation_handler(struct input_struct*, struct output_struct*, struct analytical_driver_config*);

  void perform_operation(struct analytical_driver_config*, struct output_struct*, struct input_struct*);
}

#endif
