/*
FYP : 22013

Module:
    Hybrid Query Driver - Main Query Driver

Description:
    Main Query Driver of the Hybrid Query Driver, which initializes the
    Transactional and Analytical Query Drivers and executes them to perform the
    benchmarking.

*/


#include "MQD000_Main_Query_Driver.h"

/*
Description:
    Job for the thread managing the transactional query driver
*/
void* transactional_driver_thread_job(void* tqd_data_void_pointer) {
  transactional_driver_data* tqd_data_pointer = (transactional_driver_data*) tqd_data_void_pointer;

  TRANSACTIONAL_QUERY_DRIVER::experiment_results results = TRANSACTIONAL_QUERY_DRIVER::start_transactional_driver(tqd_data_pointer->tqd_config);

  tqd_data_pointer->results_pointer->throughput = results.throughput;

  tqd_data_pointer->results_pointer->number_of_successful_operations = results.number_of_successful_operations;
  pthread_exit(NULL);
}


/*
Description:
    Job for the thread managing the analytical query driver
*/
void* analytical_driver_thread_job(void* aqd_data_void_pointer) {
  analytical_driver_data* aqd_data_pointer = (analytical_driver_data*) aqd_data_void_pointer;

  ANALYTICAL_QUERY_DRIVER::experiment_results results = ANALYTICAL_QUERY_DRIVER::start_analytical_driver(aqd_data_pointer->aqd_config);

  aqd_data_pointer->results_pointer->throughput = results.throughput;

  aqd_data_pointer->results_pointer->number_of_successful_operations = results.number_of_successful_operations;
  pthread_exit(NULL);
}


/*
Description:
    Executed when valid inputs are provided, initializes the configurations for
    the transactional and the analytical query drivers and starts them on
    different threads to begin the experimentation
*/
void run_experiment(std::string config_file_name) {

  HQD_CONFIG::query_driver_config* hybrid_driver_configs = new HQD_CONFIG::query_driver_config();

  HQD_CONFIG::read_configs(hybrid_driver_configs, config_file_name);

  transactional_driver_data* tqd_data_pointer = new transactional_driver_data();

  tqd_data_pointer->tqd_config = hybrid_driver_configs->tqd_config;
  tqd_data_pointer->results_pointer = new TRANSACTIONAL_QUERY_DRIVER::experiment_results();

  analytical_driver_data* aqd_data_pointer = new analytical_driver_data();
  aqd_data_pointer->aqd_config = hybrid_driver_configs->aqd_config;
  aqd_data_pointer->results_pointer = new ANALYTICAL_QUERY_DRIVER::experiment_results();

  pthread_t transactional_thread;
  pthread_t analytical_thread;
  int t_status_code, a_status_code;

  //TODO: START QUERY DRIVERS ACCORING TO CONFIG
  int driver_activation_code = 0;
  if (hybrid_driver_configs->experiment_mode == "TRANSACTIONAL") {
    driver_activation_code = 1;
  }
  else if (hybrid_driver_configs->experiment_mode == "ANALYTICAL") {
    driver_activation_code = 2;
  }
  else {
    driver_activation_code = 3;
  }

  if (driver_activation_code == 1 || driver_activation_code == 3){
    t_status_code = pthread_create(&transactional_thread, NULL, transactional_driver_thread_job, (void*) tqd_data_pointer);
    if (t_status_code < 0) {
      std::cout<<"Error in creating transaction query driver"<<"\n";
      exit(-1);
    }
  }

  if (driver_activation_code == 2 || driver_activation_code == 3){
    a_status_code = pthread_create(&analytical_thread, NULL, analytical_driver_thread_job, (void*) aqd_data_pointer);
    if (a_status_code < 0) {
      std::cout<<"Error in creating analytical query driver"<<"\n";
      exit(-1);
    }
  }

  if (driver_activation_code == 1 || driver_activation_code == 3){
    t_status_code = pthread_join(transactional_thread, NULL);
    if (t_status_code < 0) {
      std::cout<<"Error in joining transaction query driver"<<"\n";
      exit(-1);
    }
    // std::cout<<"TRANSACTIONAL DRIVER RESULTS"<<"\n";
    // std::cout<<"Throughput (op/milliseconds): "<<tqd_data_pointer->results_pointer->throughput<<"\n";
    // std::cout<<"Number of successful operations: "<<tqd_data_pointer->results_pointer->number_of_successful_operations<<"\n";
    // std::cout<<"-----------------------------------\n";
    std::cout<<"T-THREAD#:|"<<tqd_data_pointer->tqd_config->number_of_transactional_threads<<"|T-THROUGHPUT(op/sec):|"<<tqd_data_pointer->results_pointer->throughput<<"|T-SUCCESS-OP#:|"<<tqd_data_pointer->results_pointer->number_of_successful_operations<<"|";
  }
  else {
    std::cout<<"|T-THREAD#:|"<<"0"<<"|T-THROUGHPUT(op/sec):|"<<"0"<<"|T-SUCCESS-OP#:|"<<"0"<<"|";
  }

  if (driver_activation_code == 2 || driver_activation_code == 3){
    a_status_code = pthread_join(analytical_thread, NULL);
    if (a_status_code < 0) {
      std::cout<<"Error in joining analytical query driver"<<"\n";
      exit(-1);
    }
    // std::cout<<"ANALYTICAL DRIVER RESULTS"<<"\n";
    // std::cout<<"Throughput (op/milliseconds): "<<aqd_data_pointer->results_pointer->throughput<<"\n";
    // std::cout<<"Number of successful operations: "<<aqd_data_pointer->results_pointer->number_of_successful_operations<<"\n";
    std::cout<<"A-THREAD#:|"<<aqd_data_pointer->aqd_config->number_of_analytical_threads<<"|A-THROUGHPUT(op/sec):|"<<aqd_data_pointer->results_pointer->throughput<<"|A-SUCCESS-OP#:|"<<aqd_data_pointer->results_pointer->number_of_successful_operations;
  }
  else {
    std::cout<<"A-THREAD#:|"<<"0"<<"|A-THROUGHPUT(op/sec):|"<<"0"<<"|A-SUCCESS-OP#:|"<<"0";
  }
  std::cout<<"\n";
}


/*
Description:
    Main function for the Hybrid Query Driver
*/
int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout<<"Usage: "<<argv[0]<<" <JSON config file>"<<"\n";
    exit(-1);
  }
  else {
    if (access(argv[1], F_OK) == 0) {
      std::string file_name(argv[1]);
      run_experiment(file_name);
    }
    else {
      std::cout<<"File: '"<<argv[1]<<"' does not exist"<<"\n";
      exit(-1);
    }
  }
  return 0;
}
