/*
FYP : 22013

Module:
    Hybrid Query Driver - Analytical Query Driver

Description:
    Defines the analytical query driver for the Hybrid Query Driver, which
    manages the analytical threads to run the experiments for the analytical
    side of the benchmark.
*/
#include "AQD001_Analytical_Query_Driver.h"

using namespace ANALYTICAL_QUERY_DRIVER;

/*
Description:
    Sets probability weights of the query types according to which queries are
    enabled.
*/
double ANALYTICAL_QUERY_DRIVER::setup_query_selection_probability_weights(analytical_driver_config* config, double* prob_weight_list) {
  double total_prob_weight = 0;

  if (config->enable_query_1) {
    total_prob_weight += config->query_1_probabilistic_weight;
    prob_weight_list[0] = total_prob_weight;
  }
  else {
    prob_weight_list[0] = -1;
  }

  if (config->enable_query_2) {
    total_prob_weight += config->query_2_probabilistic_weight;
    prob_weight_list[1] = total_prob_weight;
  }
  else {
    prob_weight_list[1] = -1;
  }

  if (config->enable_query_3) {
    total_prob_weight += config->query_3_probabilistic_weight;
    prob_weight_list[2] = total_prob_weight;
  }
  else {
    prob_weight_list[2] = -1;
  }

  if (config->enable_query_4) {
    total_prob_weight += config->query_4_probabilistic_weight;
    prob_weight_list[3] = total_prob_weight;
  }
  else {
    prob_weight_list[3] = -1;
  }

  if (config->enable_query_5) {
    total_prob_weight += config->query_5_probabilistic_weight;
    prob_weight_list[4] = total_prob_weight;
  }
  else {
    prob_weight_list[4] = -1;
  }

  if (config->enable_query_6) {
    total_prob_weight += config->query_6_probabilistic_weight;
    prob_weight_list[5] = total_prob_weight;
  }
  else {
    prob_weight_list[5] = -1;
  }

  return total_prob_weight;
}

/*
Description:
    This method samples the query type.
*/
int ANALYTICAL_QUERY_DRIVER::sample_query_type(double* query_selection_probability_list, double total_prob_weight) {
  double uni_dis_sample = generate_uniform_distribution_sample(0, total_prob_weight);
  for (int i = 0; i < 5; i++) {
    if (uni_dis_sample <= query_selection_probability_list[i]) {
      return i;
    }
  }

  if (query_selection_probability_list[5] > 0){
    return 5;
  }
  else {
    for (int i = 0; i < 5; i++) {
      if (query_selection_probability_list[i] > 0) {
        return i;
      }
    }
  }
  return 0;
}

/*
Description:
    This method creates the output line for freshness score to be outputted in
    the analytical thread file.
*/
void ANALYTICAL_QUERY_DRIVER::fill_output_line(std::string* line_pointer,
                        unsigned long current_analytical_query_ID,
                        std::string query_type,
                        uint64_t start_time,
                        uint64_t end_time,
                        unsigned long* transaction_ID_list,
                        int number_of_transactional_threads){
  *line_pointer = std::to_string(current_analytical_query_ID)
                  + "|" + query_type
                  + "|" + std::to_string(start_time)
                  + "|" + std::to_string(end_time);
  for (int i = 0; i < number_of_transactional_threads; i++) {
    *line_pointer = *line_pointer + "|" + std::to_string(transaction_ID_list[i]);
  }
  *line_pointer = *line_pointer + "\n";
}

/*
Description:
    This method executes query type 1.
*/
bool ANALYTICAL_QUERY_DRIVER::execute_query_1(thread_data* t_data_pointer,
                      std::string* line_pointer,
                      analytical_driver_config* config) {

  AQ_1::input_struct* op_input = new AQ_1::input_struct();
  AQ_1::output_struct* op_output = new AQ_1::output_struct();

  op_output->freshness_score_transaction_id_for_each_thread_list = new unsigned long[config->number_of_transactional_threads];

  AQ_1::perform_operation(config, op_output, op_input);

  fill_output_line(line_pointer,
                   t_data_pointer->current_analytical_query_ID,
                   "AQ_1",
                   op_output->start_time,
                   op_output->end_time,
                   op_output->freshness_score_transaction_id_for_each_thread_list,
                   config->number_of_transactional_threads);

  bool success =op_output->success;

  delete[] op_output->freshness_score_transaction_id_for_each_thread_list;
  delete op_input;
  delete op_output;

  return success;
}

/*
Description:
    This method executes query type 2.
*/
bool ANALYTICAL_QUERY_DRIVER::execute_query_2(thread_data* t_data_pointer,
                      std::string* line_pointer,
                      analytical_driver_config* config) {

  AQ_2::input_struct* op_input = new AQ_2::input_struct();
  AQ_2::output_struct* op_output = new AQ_2::output_struct();

  op_output->freshness_score_transaction_id_for_each_thread_list = new unsigned long[config->number_of_transactional_threads];

  AQ_2::perform_operation(config, op_output, op_input);

  fill_output_line(line_pointer,
                   t_data_pointer->current_analytical_query_ID,
                   "AQ_2",
                   op_output->start_time,
                   op_output->end_time,
                   op_output->freshness_score_transaction_id_for_each_thread_list,
                   config->number_of_transactional_threads);

  bool success =op_output->success;

  delete[] op_output->freshness_score_transaction_id_for_each_thread_list;
  delete op_input;
  delete op_output;

  return success;
}

/*
Description:
    This method executes query type 3.
*/
bool ANALYTICAL_QUERY_DRIVER::execute_query_3(thread_data* t_data_pointer,
                      std::string* line_pointer,
                      analytical_driver_config* config) {

  AQ_3::input_struct* op_input = new AQ_3::input_struct();
  AQ_3::output_struct* op_output = new AQ_3::output_struct();

  op_output->freshness_score_transaction_id_for_each_thread_list = new unsigned long[config->number_of_transactional_threads];

  AQ_3::perform_operation(config, op_output, op_input);

  fill_output_line(line_pointer,
                   t_data_pointer->current_analytical_query_ID,
                   "AQ_3",
                   op_output->start_time,
                   op_output->end_time,
                   op_output->freshness_score_transaction_id_for_each_thread_list,
                   config->number_of_transactional_threads);

  bool success =op_output->success;

  delete[] op_output->freshness_score_transaction_id_for_each_thread_list;
  delete op_input;
  delete op_output;

  return success;
}

/*
Description:
    This method executes query type 4.
*/
bool ANALYTICAL_QUERY_DRIVER::execute_query_4(thread_data* t_data_pointer,
                      std::string* line_pointer,
                      analytical_driver_config* config) {

  AQ_4::input_struct* op_input = new AQ_4::input_struct();
  AQ_4::output_struct* op_output = new AQ_4::output_struct();

  op_output->freshness_score_transaction_id_for_each_thread_list = new unsigned long[config->number_of_transactional_threads];

  AQ_4::perform_operation(config, op_output, op_input);

  fill_output_line(line_pointer,
                   t_data_pointer->current_analytical_query_ID,
                   "AQ_4",
                   op_output->start_time,
                   op_output->end_time,
                   op_output->freshness_score_transaction_id_for_each_thread_list,
                   config->number_of_transactional_threads);

  bool success =op_output->success;

  delete[] op_output->freshness_score_transaction_id_for_each_thread_list;
  delete op_input;
  delete op_output;

  return success;
}

/*
Description:
    This method executes query type 5.
*/
bool ANALYTICAL_QUERY_DRIVER::execute_query_5(thread_data* t_data_pointer,
                      std::string* line_pointer,
                      analytical_driver_config* config) {

  AQ_5::input_struct* op_input = new AQ_5::input_struct();
  AQ_5::output_struct* op_output = new AQ_5::output_struct();

  op_output->freshness_score_transaction_id_for_each_thread_list = new unsigned long[config->number_of_transactional_threads];

  AQ_5::perform_operation(config, op_output, op_input);

  fill_output_line(line_pointer,
                   t_data_pointer->current_analytical_query_ID,
                   "AQ_5",
                   op_output->start_time,
                   op_output->end_time,
                   op_output->freshness_score_transaction_id_for_each_thread_list,
                   config->number_of_transactional_threads);

  bool success =op_output->success;

  delete[] op_output->freshness_score_transaction_id_for_each_thread_list;
  delete op_input;
  delete op_output;

  return success;
}

/*
Description:
    This method executes query type 6.
*/
bool ANALYTICAL_QUERY_DRIVER::execute_query_6(thread_data* t_data_pointer,
                      std::string* line_pointer,
                      analytical_driver_config* config) {

  AQ_6::input_struct* op_input = new AQ_6::input_struct();
  AQ_6::output_struct* op_output = new AQ_6::output_struct();

  op_output->freshness_score_transaction_id_for_each_thread_list = new unsigned long[config->number_of_transactional_threads];

  AQ_6::perform_operation(config, op_output, op_input);

  fill_output_line(line_pointer,
                   t_data_pointer->current_analytical_query_ID,
                   "AQ_6",
                   op_output->start_time,
                   op_output->end_time,
                   op_output->freshness_score_transaction_id_for_each_thread_list,
                   config->number_of_transactional_threads);

  bool success =op_output->success;

  delete[] op_output->freshness_score_transaction_id_for_each_thread_list;
  delete op_input;
  delete op_output;

  return success;
}

/*
Description:
    Describes the thread job for the analytical threads in the benchmark.
*/
void* ANALYTICAL_QUERY_DRIVER::thread_job(void* thread_input) {
  thread_data* t_data_pointer = (thread_data*) thread_input;
  thread_data t_data = *t_data_pointer;

  unsigned long number_of_successful_operations = 0;

  std::ofstream output_file_stream;
  if (t_data.config->is_freshness_score_calculation_active) {
    output_file_stream.open(t_data.output_file_name);
    output_file_stream<<"Freshness Score Data for Analytical Thread "<<t_data.thread_id<<"\n";
    output_file_stream<<"Analytical Query ID|Query Type|Start Time|End Time|Transaction ID for Transactional Thread 0|Transaction ID for Transactional Thread 1|..."<<"\n";
  }

  while (get_current_epoch_time_in_milliseconds() < t_data.config->end_data_collection_timestamp) {

    std::string current_line = "";
    bool current_operation_success = false;
    int query_type = sample_query_type(t_data.shared_data->query_selection_probability_list, t_data.shared_data->total_prob_weight);
    switch(query_type) {
      case 0:
        //run query 1
        //convert output to line
        current_operation_success = execute_query_1(&t_data, &current_line, t_data.config);
        break;
      case 1:
        //run query 2
        //convert output to line
        current_operation_success = execute_query_2(&t_data, &current_line, t_data.config);
        break;
      case 2:
        //run query 3
        //convert output to line
        current_operation_success = execute_query_3(&t_data, &current_line, t_data.config);
        break;
      case 3:
        //run query 4
        //convert output to line
        current_operation_success = execute_query_4(&t_data, &current_line, t_data.config);
        break;
      case 4:
        //run query 5
        //convert output to line
        current_operation_success = execute_query_5(&t_data, &current_line, t_data.config);
        break;
      default:
        //run query 6
        //convert output to line
        current_operation_success = execute_query_6(&t_data, &current_line, t_data.config);
    }

    if (!current_operation_success) {
      continue;
    }
    else {
      uint64_t current_time = get_current_epoch_time_in_milliseconds();
      if (current_time > t_data.config->end_warmup_timestamp && current_time < t_data.config->end_data_collection_timestamp) {
        number_of_successful_operations++;
        t_data.current_analytical_query_ID += 1;
        //output line to file if freshness score collection enabled
        if (t_data.config->is_freshness_score_calculation_active) {
          //output line to file
          output_file_stream<<current_line;
        }
      }
    }
  }
  if (t_data.config->is_freshness_score_calculation_active) {
    output_file_stream.close();
  }
  //give number_of_successful_operations to global data
  t_data.shared_data->analytical_query_completion_list[t_data.thread_id] = number_of_successful_operations;
  pthread_exit(NULL);
}

/*
Description:
    This method sets up the analytical threads and waits for the experiments
    to finish before returning the experiment results for the analytical side
*/
experiment_results ANALYTICAL_QUERY_DRIVER::start_analytical_driver(analytical_driver_config* config) {
  //set the thread data
  pthread_t* thread_list = new pthread_t[config->number_of_analytical_threads];

  global_data* g_data = new global_data();

  g_data->analytical_query_completion_list = new unsigned long[config->number_of_analytical_threads];

  g_data->query_selection_probability_list = new double[6];

  g_data->total_prob_weight = setup_query_selection_probability_weights(config, g_data->query_selection_probability_list);

  thread_data* t_data = new thread_data[config->number_of_analytical_threads];

  for (int i = 0; i < config->number_of_analytical_threads; i++) {
    t_data[i] = {.thread_id = i,
                          .config = config,
                          .shared_data = g_data,
                          .output_file_name = config->result_directory + "thread_" + std::to_string(i) + ".csv",
                          .current_analytical_query_ID = 0
                          };
    int status_code = pthread_create(&thread_list[i], NULL, thread_job, (void*) &t_data[i]);

    if (status_code < 0) {
      std::cout<<"Error in starting analytical query driver thread"<<"\n";
      exit(-1);
    }
  }

  for (int i = 0; i < config->number_of_analytical_threads; i++) {
    int status_code = pthread_join(thread_list[i], NULL);
    if (status_code < 0) {
      std::cout<<"Error in joining analytical query driver thread"<<"\n";
      exit(-1);
    }
  }
  //do throughput calculation
  unsigned long long number_of_successful_operations = 0;
  for (int i = 0; i < config->number_of_analytical_threads; i++) {
    number_of_successful_operations += g_data->analytical_query_completion_list[i];
  }

  double throughput = number_of_successful_operations *1.5 / (config->end_data_collection_timestamp - config->end_warmup_timestamp);

  experiment_results results = {.throughput = throughput / 1.5 * 1000,
                                .number_of_successful_operations = number_of_successful_operations};

  delete[] thread_list;
  delete[] g_data->analytical_query_completion_list;
  delete[] g_data->query_selection_probability_list;
  delete g_data;
  delete[] t_data;


  return results;
}
