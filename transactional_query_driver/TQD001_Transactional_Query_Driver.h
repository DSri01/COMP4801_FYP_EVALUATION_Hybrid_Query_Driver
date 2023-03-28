/*
FYP : 22013

Module:
    Hybrid Query Driver - Transactional Query Driver

Description:
    Header file for the transactional query driver of the Hybrid Query Driver
*/

#include "../configuration/QDC001_TQD_Config.h"
#include "../utils/QDU001_Time.h"
#include "../utils/QDU002_Random.h"
#include "transactional_query_handlers/Query_1_A/TQD002_Query_1_A_Handler.h"
#include "transactional_query_handlers/Query_1_B/TQD003_Query_1_B_Handler.h"
#include "transactional_query_handlers/Query_2/TQD004_Query_2_Handler.h"
#include "transactional_query_handlers/Query_3/TQD005_Query_3_Handler.h"
#include "transactional_query_handlers/Query_4/TQD006_Query_4_Handler.h"
#include "transactional_query_handlers/Query_5/TQD007_Query_5_Handler.h"
#include "transactional_query_handlers/Query_6/TQD008_Query_6_Handler.h"
#include "transactional_query_handlers/Query_7/TQD009_Query_7_Handler.h"
#include "transactional_query_handlers/Query_8/TQD010_Query_8_Handler.h"


#include <fstream>
#include <iostream>
#include <pthread.h>
#include <string>

#ifndef TQD001_TRANSACTION_QUERY_DRIVER
#define TQD001_TRANSACTION_QUERY_DRIVER

namespace TRANSACTIONAL_QUERY_DRIVER {

  struct experiment_results {
    double throughput;
    unsigned long long number_of_successful_operations;
  };

  struct global_data {
    unsigned long* transaction_completion_list;
    double* query_selection_probability_list;
    double total_prob_weight;
  };

  struct thread_data{
    int thread_id;
    transactional_driver_config* config;
    global_data* shared_data;
    std::string output_file_name;

    unsigned long current_transaction_ID;

    unsigned long current_trade_ID;

    unsigned long remove_list_current_index_for_thread;
    unsigned long remove_list_last_index_for_thread;
  };

  double setup_query_selection_probability_weights(transactional_driver_config*, double*);

  int sample_query_type(double*, double, bool);

  bool execute_query_1_A(thread_data*, std::string*, transactional_driver_config*);

  bool execute_query_1_B(thread_data*, std::string*, transactional_driver_config*);

  bool execute_query_2(thread_data*, std::string*, transactional_driver_config*);

  bool execute_query_3(thread_data*, std::string*, transactional_driver_config*);

  bool execute_query_4(thread_data*, std::string*, transactional_driver_config*);

  bool execute_query_5(thread_data*, std::string*, transactional_driver_config*);

  bool execute_query_6(thread_data*, std::string*, transactional_driver_config*);

  bool execute_query_7(thread_data*, std::string*, transactional_driver_config*);

  bool execute_query_8(thread_data*, std::string*, transactional_driver_config*);

  void* thread_job (void*);

  experiment_results start_transactional_driver(transactional_driver_config*);
}

#endif
