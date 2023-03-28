/*
FYP : 22013

Module:
    Hybrid Query Driver - Query Driver Configuration

Description:
    Header file for the configuration of the Hybrid Query Driver.
*/
#include "../third_party/json.hpp"
#include "../utils/QDU001_Time.h"
#include "QDC001_TQD_Config.h"
#include "QDC002_AQD_Config.h"

#include <fstream>
#include <string>

#ifndef QDC000_HQD_CONFIG_H
#define QDC000_HQD_CONFIG_H

namespace HQD_CONFIG{
  struct query_driver_config{
    struct transactional_driver_config* tqd_config;
    struct analytical_driver_config* aqd_config;

    std::string experiment_mode;

    uint64_t benchmark_start_timestamp;
  };

  void read_configs(struct query_driver_config*, std::string);
}

#endif
