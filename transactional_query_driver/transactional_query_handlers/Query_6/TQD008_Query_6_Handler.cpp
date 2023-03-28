/*
FYP : 22013

Module:
    Hybrid Query Driver - Transactional Query Driver

Description:
    Defines the interface for generating data, executing and getting the results
    for transactional query type 6.
*/
#include "TQD008_Query_6_Handler.h"

using namespace TQ_6;

/*
Description:
    Generates the parameters for transactional query type 6
*/
void TQ_6::input_randomizer(struct input_struct* input, struct transactional_driver_config* config) {

  input->read_investor_ID = sample_from_3_investor_lists(config->query_6_configs.read_follower_friend_trade_probability,
                                                          config->query_6_configs.read_leader_list_1_friend_trade_probability,
                                                          config->query_6_configs.read_leader_list_2_friend_trade_probability,
                                                          config->query_6_configs.follower_list_read_friend_trade_power_dis_param,
                                                          config->query_6_configs.leader_list_1_read_friend_trade_power_dis_param,
                                                          config->query_6_configs.leader_list_2_read_friend_trade_power_dis_param,
                                                          config);

}

/*
Description:
    Executes transactional query type 6 and returns the output
*/
void TQ_6::operation_handler(struct input_struct* input, struct output_struct* output, struct transactional_driver_config* config){

  /*--------------------------------------------------------------------------*/
  /*--------------------------------------------------------------------------*/

  //perform the operation with the help of the input and get the start and end times
  unsigned long freshness_score_vertex_ID = input->thread_ID + config->first_freshness_score_vertex_ID;

  json request;
  request["OPERATION_ID"] = 14;
  request["READ_INVESTOR_ID"] = input->read_investor_ID;

  //FRESHNESS SCORE
  request["FRESHNESS_SCORE_ID"] = freshness_score_vertex_ID;
  request["FS_TRANSACTION_ID"] = input->transaction_ID;

  json response;

  output->start_time = get_current_epoch_time_in_milliseconds();
  //perform operation here

  response = send_query(request, config->server_ip_address, config->server_port_number);

  output->end_time = get_current_epoch_time_in_milliseconds();

  std::vector <unsigned long> friend_trade_vector = response["FRIEND_TRADE_LIST"].get<std::vector <unsigned long>>();
  output->success = response["SUCCESS"].get<bool>();

  output->friend_trade_list_length = friend_trade_vector.size();
  output->friend_trade_list_pointer = new unsigned long[output->friend_trade_list_length];

  for (int i=0; i < output->friend_trade_list_length; i++) {
    output->friend_trade_list_pointer[i] = friend_trade_vector[i];
  }

  /*--------------------------------------------------------------------------*/
  /*--------------------------------------------------------------------------*/
}

/*
Description:
    Creates the input and calls the operation handler of query type 6
*/
void TQ_6::perform_operation(struct transactional_driver_config* config, struct output_struct* output, unsigned long transaction_ID, int thread_ID) {
  input_struct* input = new input_struct();
  input->thread_ID = thread_ID;
  input->transaction_ID = transaction_ID;
  input_randomizer(input, config);
  operation_handler(input, output, config);

  delete input;
}
