/*
FYP : 22013

Module:
    Hybrid Query Driver - Query Driver Configuration

Description:
    Defines the configurer for the Hybrid Query Driver, which configures both
    transactional and analytical query drivers along with the hybrid
    configurations.
*/
#include "QDC000_HQD_Config.h"

using json = nlohmann::json;

using namespace HQD_CONFIG;

/*
Description:
    Provides a method to configure both transactional and analytical query
    driver configurations.
*/
void HQD_CONFIG::read_configs(struct query_driver_config* driver_config_pointer, std::string file_name) {

  transactional_driver_config* tqd_config_pointer = new transactional_driver_config();
  analytical_driver_config* aqd_config_pointer = new analytical_driver_config();

  TQD_CONFIG::read_transactional_query_driver_configs(tqd_config_pointer,file_name);

  AQD_CONFIG::read_analytical_query_driver_configs(aqd_config_pointer, file_name);

  driver_config_pointer->tqd_config = tqd_config_pointer;
  driver_config_pointer->aqd_config = aqd_config_pointer;

  std::ifstream f(file_name);
  json configs = json::parse(f);

  driver_config_pointer->experiment_mode = configs["experiment_mode"].get<std::string>();

  //both durations are in milliseconds

  int warm_up_duration = configs["warm_up_duration"].get<unsigned long>();

  int data_collection_duration = configs["data_collection_duration"].get<unsigned long>();

  driver_config_pointer->benchmark_start_timestamp = get_current_epoch_time_in_milliseconds();

  uint64_t end_warm_up_timestamp = driver_config_pointer->benchmark_start_timestamp + warm_up_duration;

  uint64_t end_benchmark_timestamp = end_warm_up_timestamp + data_collection_duration;

  driver_config_pointer->tqd_config->end_warmup_timestamp = end_warm_up_timestamp;
  driver_config_pointer->tqd_config->end_data_collection_timestamp = end_benchmark_timestamp;

  driver_config_pointer->aqd_config->end_warmup_timestamp = end_warm_up_timestamp;
  driver_config_pointer->aqd_config->end_data_collection_timestamp = end_benchmark_timestamp;
}
