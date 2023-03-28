/*
FYP : 22013

Module:
    Hybrid Query Driver - Transactional Query Driver

Description:
    Defines the interface for generating data, executing and getting the results
    for transactional query type 2.
*/
#include "TQD004_Query_2_Handler.h"

using namespace TQ_2;

/*
Description:
    Generates the parameters for transactional query type 2
*/
void TQ_2::input_randomizer(struct input_struct* input, struct transactional_driver_config* config) {
  //Trade ID is supplied by the Driver
  input->read_investor_ID = sample_from_3_investor_lists(config->query_2_configs.read_follower_profile_probability,
                                                          config->query_2_configs.read_leader_list_1_profile_probability,
                                                          config->query_2_configs.read_leader_list_2_profile_probability,
                                                          config->query_2_configs.follower_list_investor_profile_power_dis_param,
                                                          config->query_2_configs.leader_list_1_investor_profile_power_dis_param,
                                                          config->query_2_configs.leader_list_2_investor_profile_power_dis_param,
                                                          config);

}

/*
Description:
    Executes transactional query type 2 and returns the output
*/
void TQ_2::operation_handler(struct input_struct* input, struct output_struct* output, struct transactional_driver_config* config){

  /*--------------------------------------------------------------------------*/
  /*--------------------------------------------------------------------------*/

  unsigned long freshness_score_vertex_ID = input->thread_ID + config->first_freshness_score_vertex_ID;

  json request;
  request["OPERATION_ID"] = 10;
  request["READ_INVESTOR_ID"] = input->read_investor_ID;

  //FRESHNESS SCORE
  request["FRESHNESS_SCORE_ID"] = freshness_score_vertex_ID;
  request["FS_TRANSACTION_ID"] = input->transaction_ID;

  json response;

  //perform the operation with the help of the input and get the start and end times
  output->start_time = get_current_epoch_time_in_milliseconds();
  //perform operation here

  response = send_query(request, config->server_ip_address, config->server_port_number);

  output->end_time = get_current_epoch_time_in_milliseconds();

  output->success = response["SUCCESS"].get<bool>();
  output->investor_name = response["INVESTOR_NAME"].get<std::string>();
  output->investment_ampunt = response["INVESTMENT_AMOUNT"].get<int>();

  /*--------------------------------------------------------------------------*/
  /*--------------------------------------------------------------------------*/

}

/*
Description:
    Creates the input and calls the operation handler of query type 2
*/
void TQ_2::perform_operation(struct transactional_driver_config* config, struct output_struct* output, unsigned long transaction_ID, int thread_ID) {
  input_struct* input = new input_struct();
  input->thread_ID = thread_ID;
  input->transaction_ID = transaction_ID;
  input_randomizer(input, config);
  operation_handler(input, output, config);

  delete input;
}
