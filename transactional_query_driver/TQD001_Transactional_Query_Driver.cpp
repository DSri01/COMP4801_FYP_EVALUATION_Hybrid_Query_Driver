/*
FYP : 22013

Module:
    Hybrid Query Driver - Transactional Query Driver

Description:
    Defines the transactional query driver for the Hybrid Query Driver, which
    manages the transactional threads to run the experiments for the
    transacitonal side of the benchmark.
*/

#include "TQD001_Transactional_Query_Driver.h"

using namespace TRANSACTIONAL_QUERY_DRIVER;

/*
Description:
    Sets probability weights of the query types according to which queries are
    enabled.
*/
double TRANSACTIONAL_QUERY_DRIVER::setup_query_selection_probability_weights(transactional_driver_config* config, double* prob_weight_list) {
  double total_prob_weight = 0;

  if (config->enable_query_1A) {
    total_prob_weight += config->query_1_A_probabilistic_weight;
    prob_weight_list[0] = total_prob_weight;
  }
  else {
    prob_weight_list[0] = -1;
  }

  if (config->enable_query_1B && config->enable_query_1A && config->enable_query_3 && config->enable_query_6) {
    total_prob_weight += config->query_1_B_probabilistic_weight;
    prob_weight_list[1] = total_prob_weight;
  }
  else {
    prob_weight_list[1] = -1;
  }

  if (config->enable_query_2) {
    total_prob_weight += config->query_2_probabilistic_weight;
    prob_weight_list[2] = total_prob_weight;
  }
  else {
    prob_weight_list[2] = -1;
  }

  if (config->enable_query_3) {
    total_prob_weight += config->query_3_probabilistic_weight;
    prob_weight_list[3] = total_prob_weight;
  }
  else {
    prob_weight_list[3] = -1;
  }

  if (config->enable_query_4) {
    total_prob_weight += config->query_4_probabilistic_weight;
    prob_weight_list[4] = total_prob_weight;
  }
  else {
    prob_weight_list[4] = -1;
  }

  if (config->enable_query_5) {
    total_prob_weight += config->query_5_probabilistic_weight;
    prob_weight_list[5] = total_prob_weight;
  }
  else {
    prob_weight_list[5] = -1;
  }

  if (config->enable_query_6) {
    total_prob_weight += config->query_6_probabilistic_weight;
    prob_weight_list[6] = total_prob_weight;
  }
  else {
    prob_weight_list[6] = -1;
  }

  if (config->enable_query_7) {
    total_prob_weight += config->query_7_probabilistic_weight;
    prob_weight_list[7] = total_prob_weight;
  }
  else {
    prob_weight_list[7] = -1;
  }

  if (config->enable_query_8) {
    total_prob_weight += config->query_8_probabilistic_weight;
    prob_weight_list[8] = total_prob_weight;
  }
  else {
    prob_weight_list[8] = -1;
  }

  return total_prob_weight;
}

/*
Description:
    This method samples the query type.
*/
int TRANSACTIONAL_QUERY_DRIVER::sample_query_type(double* query_selection_probability_list, double total_prob_weight, bool sample_query_8) {
  double uni_dis_sample = generate_uniform_distribution_sample(0, total_prob_weight);
  for (int i = 0; i < 8; i++) {
    if (uni_dis_sample <= query_selection_probability_list[i]) {
      return i;
    }
  }

  if (sample_query_8 && (query_selection_probability_list[8] > 0)){
    return 8;
  }
  else {
    for (int i = 0; i < 8; i++) {
      if (query_selection_probability_list[i] > 0) {
        return i;
      }
    }
  }
  return 0;
}

/*
Description:
    This method executes query type 1_A.
*/
bool TRANSACTIONAL_QUERY_DRIVER::execute_query_1_A(thread_data* t_data_pointer,
                                                    std::string* line_pointer,
                                                    transactional_driver_config* config) {

  TQ_1_A::input_struct* op_input = new TQ_1_A::input_struct();
  op_input->thread_ID = t_data_pointer->thread_id;
  op_input->transaction_ID = t_data_pointer->current_transaction_ID;
  op_input->trade_ID = t_data_pointer->current_trade_ID;

  TQ_1_A::output_struct* op_output = new TQ_1_A::output_struct();
  TQ_1_A::perform_operation(config, op_output, op_input);
  *line_pointer = std::to_string(t_data_pointer->current_transaction_ID)
                  + "|TQ_1_A"
                  + "|" + std::to_string(op_output->start_time)
                  + "|" + std::to_string(op_output->end_time)
                  + "\n";
  t_data_pointer->current_trade_ID += config->number_of_transactional_threads;
  if (op_output->success) {
    t_data_pointer->current_transaction_ID += 1;
  }

  bool success = op_output->success;

  delete op_input;
  delete op_output;

  return success;
}

/*
Description:
    This method executes query type 1_B.
*/
bool TRANSACTIONAL_QUERY_DRIVER::execute_query_1_B(thread_data* t_data_pointer,
                                                    std::string* line_pointer,
                                                    transactional_driver_config* config) {

  TQ_1_B::output_struct* op_output = new TQ_1_B::output_struct();
  TQ_1_B::perform_operation(config, op_output, t_data_pointer->current_transaction_ID, t_data_pointer->thread_id);
  t_data_pointer->current_transaction_ID = op_output->next_transaction_ID;
  TQ_1_B::transactions_linked_list_node* current_node_pointer = op_output->head_node;
  TQ_1_B::transactions_linked_list_node* to_delete_pointer = current_node_pointer;
  for (int i = 0; i < op_output->number_of_transactions; i++) {
    *line_pointer = *line_pointer + std::to_string(current_node_pointer->transaction_ID)
                    + "|" + current_node_pointer->query_type
                    + "|" + std::to_string(current_node_pointer->start_time)
                    + "|" + std::to_string(current_node_pointer->end_time)
                    + "\n";
    current_node_pointer = current_node_pointer->next;
    delete to_delete_pointer;
    to_delete_pointer = current_node_pointer;
  }
  if (to_delete_pointer != nullptr) {
    delete to_delete_pointer;
  }
  delete op_output;

  return true;
}

/*
Description:
    This method executes query type 2.
*/
bool TRANSACTIONAL_QUERY_DRIVER::execute_query_2(thread_data* t_data_pointer,
                                                    std::string* line_pointer,
                                                    transactional_driver_config* config) {

  TQ_2::output_struct* op_output = new TQ_2::output_struct();
  TQ_2::perform_operation(config, op_output, t_data_pointer->current_transaction_ID, t_data_pointer->thread_id);
  *line_pointer = std::to_string(t_data_pointer->current_transaction_ID)
                  + "|TQ_2"
                  + "|" + std::to_string(op_output->start_time)
                  + "|" + std::to_string(op_output->end_time)
                  + "\n";
  if (op_output->success) {
    t_data_pointer->current_transaction_ID += 1;
  }

  bool success = op_output->success;

  delete op_output;

  return success;
}

/*
Description:
    This method executes query type 3.
*/
bool TRANSACTIONAL_QUERY_DRIVER::execute_query_3(thread_data* t_data_pointer,
                                                    std::string* line_pointer,
                                                    transactional_driver_config* config) {

  TQ_3::output_struct* op_output = new TQ_3::output_struct();
  TQ_3::perform_operation(config, op_output, t_data_pointer->current_transaction_ID, t_data_pointer->thread_id);
  *line_pointer = std::to_string(t_data_pointer->current_transaction_ID)
                  + "|TQ_3"
                  + "|" + std::to_string(op_output->start_time)
                  + "|" + std::to_string(op_output->end_time)
                  + "\n";
  if (op_output->success) {
    t_data_pointer->current_transaction_ID += 1;
  }

  bool success = op_output->success;

  delete op_output;

  return success;
}

/*
Description:
    This method executes query type 4.
*/
bool TRANSACTIONAL_QUERY_DRIVER::execute_query_4(thread_data* t_data_pointer,
                                                    std::string* line_pointer,
                                                    transactional_driver_config* config) {

  TQ_4::output_struct* op_output = new TQ_4::output_struct();
  TQ_4::perform_operation(config, op_output, t_data_pointer->current_transaction_ID, t_data_pointer->thread_id);
  *line_pointer = std::to_string(t_data_pointer->current_transaction_ID)
                  + "|TQ_4"
                  + "|" + std::to_string(op_output->start_time)
                  + "|" + std::to_string(op_output->end_time)
                  + "\n";
  if (op_output->success) {
    t_data_pointer->current_transaction_ID += 1;
  }
  bool success = op_output->success;

  delete op_output;

  return success;
}

/*
Description:
    This method executes query type 5.
*/
bool TRANSACTIONAL_QUERY_DRIVER::execute_query_5(thread_data* t_data_pointer,
                                                    std::string* line_pointer,
                                                    transactional_driver_config* config) {

  TQ_5::output_struct* op_output = new TQ_5::output_struct();
  TQ_5::perform_operation(config, op_output, t_data_pointer->current_transaction_ID, t_data_pointer->thread_id);
  *line_pointer = std::to_string(t_data_pointer->current_transaction_ID)
                  + "|TQ_5"
                  + "|" + std::to_string(op_output->start_time)
                  + "|" + std::to_string(op_output->end_time)
                  + "\n";
  if (op_output->success) {
    t_data_pointer->current_transaction_ID += 1;
  }
  bool success = op_output->success;

  delete[] op_output->mirroring_investor_list_pointer;
  delete op_output;

  return success;
}

/*
Description:
    This method executes query type 6.
*/
bool TRANSACTIONAL_QUERY_DRIVER::execute_query_6(thread_data* t_data_pointer,
                                                    std::string* line_pointer,
                                                    transactional_driver_config* config) {

  TQ_6::output_struct* op_output = new TQ_6::output_struct();
  TQ_6::perform_operation(config, op_output, t_data_pointer->current_transaction_ID, t_data_pointer->thread_id);
  *line_pointer = std::to_string(t_data_pointer->current_transaction_ID)
                  + "|TQ_6"
                  + "|" + std::to_string(op_output->start_time)
                  + "|" + std::to_string(op_output->end_time)
                  + "\n";
  if (op_output->success) {
    t_data_pointer->current_transaction_ID += 1;
  }
  bool success = op_output->success;

  delete[] op_output->friend_trade_list_pointer;
  delete op_output;

  return success;
}

/*
Description:
    This method executes query type 7.
*/
bool TRANSACTIONAL_QUERY_DRIVER::execute_query_7(thread_data* t_data_pointer,
                                                    std::string* line_pointer,
                                                    transactional_driver_config* config) {

  TQ_7::output_struct* op_output = new TQ_7::output_struct();
  TQ_7::perform_operation(config, op_output, t_data_pointer->current_transaction_ID, t_data_pointer->thread_id);
  *line_pointer = std::to_string(t_data_pointer->current_transaction_ID)
                  + "|TQ_7"
                  + "|" + std::to_string(op_output->start_time)
                  + "|" + std::to_string(op_output->end_time)
                  + "\n";
  if (op_output->success) {
    t_data_pointer->current_transaction_ID += 1;
  }
  bool success = op_output->success;

  delete op_output;

  return success;
}

/*
Description:
    This method executes query type 8.
*/
bool TRANSACTIONAL_QUERY_DRIVER::execute_query_8(thread_data* t_data_pointer,
                                                    std::string* line_pointer,
                                                    transactional_driver_config* config) {

  TQ_8::input_struct* op_input = new TQ_8::input_struct();
  op_input->thread_ID = t_data_pointer->thread_id;
  op_input->transaction_ID = t_data_pointer->current_transaction_ID;
  op_input->source_tradebook_ID = config->remove_mirror_edge_source_ID_list[t_data_pointer->remove_list_current_index_for_thread];
  op_input->destination_tradebook_ID = config->remove_mirror_edge_destination_ID_list[t_data_pointer->remove_list_current_index_for_thread];

  TQ_8::output_struct* op_output = new TQ_8::output_struct();
  TQ_8::perform_operation(config, op_output, op_input);
  *line_pointer = std::to_string(t_data_pointer->current_transaction_ID)
                  + "|TQ_8"
                  + "|" + std::to_string(op_output->start_time)
                  + "|" + std::to_string(op_output->end_time)
                  + "\n";
  if (op_output->success) {
    t_data_pointer->current_transaction_ID += 1;
    t_data_pointer->remove_list_current_index_for_thread += 1;
  }
  bool success = op_output->success;

  delete op_input;
  delete op_output;

  return success;
}

/*
Description:
    Describes the thread job for the transactional threads in the benchmark.
*/
void* TRANSACTIONAL_QUERY_DRIVER::thread_job(void* thread_input) {
  thread_data* t_data_pointer = (thread_data*) thread_input;
  thread_data t_data = *t_data_pointer;

  unsigned long number_of_successful_operations = 0;

  std::ofstream output_file_stream;
  if (t_data.config->is_freshness_score_calculation_active) {
    output_file_stream.open(t_data.output_file_name);
    output_file_stream<<"Freshness Score Data for Transactional Thread "<<t_data.thread_id<<"\n";
    output_file_stream<<"Transaction ID|Query Type|Start Time|End Time"<<"\n";
  }

  while (get_current_epoch_time_in_milliseconds() < t_data.config->end_data_collection_timestamp) {

    std::string current_line = "";
    bool current_operation_success = false;
    bool remove_mirror_edge_list_exist = (t_data.remove_list_current_index_for_thread <= t_data.remove_list_last_index_for_thread);
    int query_type= sample_query_type(t_data.shared_data->query_selection_probability_list, t_data.shared_data->total_prob_weight, remove_mirror_edge_list_exist);
    switch(query_type) {
      case 0:
        //run query 1_A
        //convert output to line
        current_operation_success = execute_query_1_A(&t_data, &current_line, t_data.config);
        break;
      case 1:
        //run query 1_B
        //convert output to line
        if (get_current_epoch_time_in_milliseconds() > t_data.config->end_warmup_timestamp) {
          current_operation_success = execute_query_1_B(&t_data, &current_line, t_data.config);
        }
        else {
          current_operation_success = false;
        }
        break;
      case 2:
        //run query 2
        //convert output to line
        current_operation_success = execute_query_2(&t_data, &current_line, t_data.config);
        break;
      case 3:
        //run query 3
        //convert output to line
        current_operation_success = execute_query_3(&t_data, &current_line, t_data.config);
        break;
      case 4:
        //run query 4
        //convert output to line
        current_operation_success = execute_query_4(&t_data, &current_line, t_data.config);
        break;
      case 5:
        //run query 5
        //convert output to line
        current_operation_success = execute_query_5(&t_data, &current_line, t_data.config);
        break;
      case 6:
        //run query 6
        //convert output to line
        current_operation_success = execute_query_6(&t_data, &current_line, t_data.config);
        break;
      case 7:
        //run query 7
        //convert output to line
        current_operation_success = execute_query_7(&t_data, &current_line, t_data.config);
        break;
      default:
        //run query 8
        //convert output to line
        current_operation_success = execute_query_8(&t_data, &current_line, t_data.config);
    }

    if (!current_operation_success) {
      continue;
    }
    else {
      uint64_t current_time = get_current_epoch_time_in_milliseconds();
      if (current_time > t_data.config->end_warmup_timestamp && current_time < t_data.config->end_data_collection_timestamp) {
        number_of_successful_operations++;
      }
    }

    //output line to file if freshness score collection enabled
    if (t_data.config->is_freshness_score_calculation_active) {
      //output line to file
      output_file_stream<<current_line;
    }
  }
  if (t_data.config->is_freshness_score_calculation_active) {
    output_file_stream.close();
  }
  //give number_of_successful_operations to global data
  t_data.shared_data->transaction_completion_list[t_data.thread_id] = number_of_successful_operations;
  pthread_exit(NULL);
}

/*
Description:
    This method sets up the transactional threads and waits for the experiments
    to finish before returning the experiment results for the transactional side
*/
experiment_results TRANSACTIONAL_QUERY_DRIVER::start_transactional_driver(transactional_driver_config* config) {
  //set the thread data
  pthread_t* thread_list = new pthread_t[config->number_of_transactional_threads];

  global_data* g_data = new global_data();

  g_data->transaction_completion_list = new unsigned long[config->number_of_transactional_threads];

  g_data->query_selection_probability_list = new double[9];

  g_data->total_prob_weight = setup_query_selection_probability_weights(config, g_data->query_selection_probability_list);

  thread_data* t_data = new thread_data[config->number_of_transactional_threads];

  for (int i = 0; i < config->number_of_transactional_threads; i++) {
    t_data[i] = {.thread_id = i,
                          .config = config,
                          .shared_data = g_data,
                          .output_file_name = config->result_directory + "thread_" + std::to_string(i) + ".csv",
                          .current_transaction_ID = 0,
                          .current_trade_ID = config->first_trade_vertex_ID + i,
                          .remove_list_current_index_for_thread = i * (config->remove_mirror_edge_list_length / config->number_of_transactional_threads),
                          .remove_list_last_index_for_thread = ((i == config->number_of_transactional_threads - 1) ? (config->remove_mirror_edge_list_length - 1) : ((i + 1) * (config->remove_mirror_edge_list_length / config->number_of_transactional_threads) - 1))
                          };
    int status_code = pthread_create(&thread_list[i], NULL, thread_job, (void*) &t_data[i]);

    if (status_code < 0) {
      std::cout<<"Error in starting transaction query driver thread"<<"\n";
      exit(-1);
    }
  }

  for (int i = 0; i < config->number_of_transactional_threads; i++) {
    int status_code = pthread_join(thread_list[i], NULL);
    if (status_code < 0) {
      std::cout<<"Error in joining transaction query driver thread"<<"\n";
      exit(-1);
    }
  }
  //do throughput calculation
  unsigned long long number_of_successful_operations = 0;
  for (int i = 0; i < config->number_of_transactional_threads; i++) {
    number_of_successful_operations += g_data->transaction_completion_list[i];
  }

  double throughput = number_of_successful_operations * 1.5 / (config->end_data_collection_timestamp - config->end_warmup_timestamp);

  experiment_results results = {.throughput = throughput / 1.5 * 1000,
                                .number_of_successful_operations = number_of_successful_operations};

  delete[] thread_list;
  delete[] g_data->transaction_completion_list;
  delete[] g_data->query_selection_probability_list;
  delete g_data;
  delete[] t_data;

  return results;
}
