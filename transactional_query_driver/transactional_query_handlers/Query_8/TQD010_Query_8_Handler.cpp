/*
FYP : 22013

Module:
    Hybrid Query Driver - Transactional Query Driver

Description:
    Defines the interface for executing and getting the results for
    transactional query type 8.
*/
#include "TQD010_Query_8_Handler.h"

using namespace TQ_8;

/*
Description:
    Executes transactional query type 8 and returns the output
*/
void TQ_8::operation_handler(struct input_struct* input, struct output_struct* output, struct transactional_driver_config* config){

  /*--------------------------------------------------------------------------*/
  /*--------------------------------------------------------------------------*/

  unsigned long freshness_score_vertex_ID = input->thread_ID + config->first_freshness_score_vertex_ID;

  json request;
  request["OPERATION_ID"] = 16;
  request["SOURCE_TRADEBOOK_ID"] = input->source_tradebook_ID;
  request["DESTINATION_TRADEBOOK_ID"] = input->destination_tradebook_ID;

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
    Calls the operation handler of query type 8
*/
void TQ_8::perform_operation(struct transactional_driver_config* config, struct output_struct* output, struct input_struct* input) {
  operation_handler(input, output, config);
}
