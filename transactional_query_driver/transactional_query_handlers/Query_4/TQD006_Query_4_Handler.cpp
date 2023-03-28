/*
FYP : 22013

Module:
    Hybrid Query Driver - Transactional Query Driver

Description:
    Defines the interface for generating data, executing and getting the results
    for transactional query type 4.
*/
#include "TQD006_Query_4_Handler.h"

using namespace TQ_4;

/*
Description:
    Generates the parameters for transactional query type 4
*/
void TQ_4::input_randomizer(struct input_struct* input, struct transactional_driver_config* config) {

  unsigned long company_index = generate_power_distribution_ID_sample(0, config->number_of_companies, config->query_4_configs.company_read_power_dis_param);

  input->read_company_ID = config->company_list[company_index];

}

/*
Description:
    Executes transactional query type 4 and returns the output
*/
void TQ_4::operation_handler(struct input_struct* input, struct output_struct* output, struct transactional_driver_config* config){

  /*--------------------------------------------------------------------------*/
  /*--------------------------------------------------------------------------*/

  unsigned long freshness_score_vertex_ID = input->thread_ID + config->first_freshness_score_vertex_ID;

  json request;
  request["OPERATION_ID"] = 12;
  request["READ_COMPANY_ID"] = input->read_company_ID;

  //FRESHNESS SCORE
  request["FRESHNESS_SCORE_ID"] = freshness_score_vertex_ID;
  request["FS_TRANSACTION_ID"] = input->transaction_ID;

  json response;

  //perform the operation with the help of the input and get the start and end times
  output->start_time = get_current_epoch_time_in_milliseconds();
  //perform operation here

  response = send_query(request, config->server_ip_address, config->server_port_number);

  output->end_time = get_current_epoch_time_in_milliseconds();

  output->company_name = response["COMPANY_NAME"].get<std::string>();
  output->success = response["SUCCESS"].get<bool>();

  /*--------------------------------------------------------------------------*/
  /*--------------------------------------------------------------------------*/

}

/*
Description:
    Creates the input and calls the operation handler of query type 4
*/
void TQ_4::perform_operation(struct transactional_driver_config* config, struct output_struct* output, unsigned long transaction_ID, int thread_ID) {
  input_struct* input = new input_struct();
  input->thread_ID = thread_ID;
  input->transaction_ID = transaction_ID;
  input_randomizer(input, config);
  operation_handler(input, output, config);

  delete input;
}
