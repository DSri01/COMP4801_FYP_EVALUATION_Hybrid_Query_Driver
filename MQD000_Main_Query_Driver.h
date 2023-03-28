/*
FYP : 22013

Module:
    Hybrid Query Driver - Main Query Driver

Description:
    Header file for the Main Query Driver of the Hybrid Query Driver

*/

#include "analytical_query_driver/AQD001_Analytical_Query_Driver.h"
#include "configuration/QDC000_HQD_Config.h"
#include "transactional_query_driver/TQD001_Transactional_Query_Driver.h"

#include <iostream>
#include <pthread.h>
#include <string>
#include <unistd.h>

#ifndef MQD000_MAIN_QUERY_DRIVER
#define MQD000_MAIN_QUERY_DRIVER

struct transactional_driver_data {
  transactional_driver_config* tqd_config;
  TRANSACTIONAL_QUERY_DRIVER::experiment_results* results_pointer;
};

struct analytical_driver_data {
  analytical_driver_config* aqd_config;
  ANALYTICAL_QUERY_DRIVER::experiment_results* results_pointer;
};

void* transactional_driver_thread_job(void*);

void* analytical_driver_thread_job(void*);

void run_experiment(std::string);

int main(int, char**);

#endif
