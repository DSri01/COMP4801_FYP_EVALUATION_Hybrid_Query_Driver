/*
FYP : 22013

Module:
    Hybrid Query Driver - Transactional Query Driver

Description:
    Header file for the analytical query driver of the Hybrid Query Driver
*/
#include "../configuration/QDC002_AQD_Config.h"
#include "../utils/QDU001_Time.h"
#include "../utils/QDU002_Random.h"
#include "analytical_query_handlers/Query_1/AQD002_Query_1_Handler.h"
#include "analytical_query_handlers/Query_2/AQD003_Query_2_Handler.h"
#include "analytical_query_handlers/Query_3/AQD004_Query_3_Handler.h"
#include "analytical_query_handlers/Query_4/AQD005_Query_4_Handler.h"
#include "analytical_query_handlers/Query_5/AQD006_Query_5_Handler.h"
#include "analytical_query_handlers/Query_6/AQD007_Query_6_Handler.h"

#include <fstream>
#include <iostream>
#include <pthread.h>
#include <string>

#ifndef AQD001_ANALYTICAL_QUERY_DRIVER
#define AQD001_ANALYTICAL_QUERY_DRIVER

namespace ANALYTICAL_QUERY_DRIVER {
  struct experiment_results {
    double throughput;
    unsigned long long number_of_successful_operations;
  };

  struct global_data {
    unsigned long* analytical_query_completion_list;
    double* query_selection_probability_list;
    double total_prob_weight;
  };

  struct thread_data {
    int thread_id;
    analytical_driver_config* config;
    global_data* shared_data;
    std::string output_file_name;
    unsigned long current_analytical_query_ID;
  };

  double setup_query_selection_probability_weights(analytical_driver_config*, double*);

  int sample_query_type(double*, double);

  void fill_output_line(std::string*, unsigned long, std::string, uint64_t, uint64_t, unsigned long*, int);

  bool execute_query_1(thread_data*, std::string*, analytical_driver_config*);

  bool execute_query_2(thread_data*, std::string*, analytical_driver_config*);

  bool execute_query_3(thread_data*, std::string*, analytical_driver_config*);

  bool execute_query_4(thread_data*, std::string*, analytical_driver_config*);

  bool execute_query_5(thread_data*, std::string*, analytical_driver_config*);

  bool execute_query_6(thread_data*, std::string*, analytical_driver_config*);

  void* thread_job(void*);

  experiment_results start_analytical_driver(analytical_driver_config*);
}

#endif
