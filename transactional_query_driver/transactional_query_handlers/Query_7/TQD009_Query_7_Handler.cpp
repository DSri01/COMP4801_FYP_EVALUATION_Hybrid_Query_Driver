/*
FYP : 22013

Module:
    Hybrid Query Driver - Transactional Query Driver

Description:
    Defines the interface for generating data, executing and getting the results
    for transactional query type 7.
*/
#include "TQD009_Query_7_Handler.h"

using namespace TQ_7;

/*
Description:
    Generates the parameters for transactional query type 7
*/
void TQ_7::input_randomizer(struct input_struct* input, struct transactional_driver_config* config) {

  input->update_investor_ID = sample_from_3_investor_lists(config->query_7_configs.follower_update_amount_probability,
                                                          config->query_7_configs.leader_list_1_update_amount_probability,
                                                          config->query_7_configs.leader_list_2_update_amount_probability,
                                                          config->query_7_configs.follower_list_update_amount_power_dis_param,
                                                          config->query_7_configs.leader_list_1_update_amount_power_dis_param,
                                                          config->query_7_configs.leader_list_2_update_amount_power_dis_param,
                                                          config);
  input->new_investment_amount = generate_uniform_distribution_sample(15000, 1600000);
}

/*
Description:
    Executes transactional query type 7 and returns the output
*/
void TQ_7::operation_handler(struct input_struct* input, struct output_struct* output, struct transactional_driver_config* config){

  /*--------------------------------------------------------------------------*/
  /*--------------------------------------------------------------------------*/

  unsigned long freshness_score_vertex_ID = input->thread_ID + config->first_freshness_score_vertex_ID;

  json request;
  request["OPERATION_ID"] = 15;
  request["UPDATE_INVESTOR_ID"] = input->update_investor_ID;
  request["NEW_INVESTMENT_AMOUNT"] = input->new_investment_amount;

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

  /*--------------------------------------------------------------------------*/
  /*--------------------------------------------------------------------------*/

}

/*
Description:
    Creates the input and calls the operation handler of query type 7
*/
void TQ_7::perform_operation(struct transactional_driver_config* config, struct output_struct* output, unsigned long transaction_ID, int thread_ID) {
  input_struct* input = new input_struct();
  input->thread_ID = thread_ID;
  input->transaction_ID = transaction_ID;
  input_randomizer(input, config);
  operation_handler(input, output, config);

  delete input;
}
