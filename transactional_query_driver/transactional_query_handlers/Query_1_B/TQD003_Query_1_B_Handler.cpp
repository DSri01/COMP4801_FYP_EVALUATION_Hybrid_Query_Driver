/*
FYP : 22013

Module:
    Hybrid Query Driver - Transactional Query Driver

Description:
    Defines the interface for executing and getting the results for
    transactional query type 1_B.
*/
#include "TQD003_Query_1_B_Handler.h"

using namespace TQ_1_B;

/*
Description:
    Executes transactional query type 1_B and returns the output
*/
void TQ_1_B::operation_handler(struct input_struct* input, struct output_struct* output, struct transactional_driver_config* config){
  unsigned long copier_investor_ID = sample_from_3_investor_lists(config->query_1_B_configs.follower_is_copier_investor_probability,
                                              config->query_1_B_configs.leader_list_1_is_copier_investor_probability,
                                              config->query_1_B_configs.leader_list_2_is_copier_investor_probability,
                                              config->query_1_B_configs.follower_list_copier_investor_power_dis_param,
                                              config->query_1_B_configs.leader_list_1_copier_investor_power_dis_param,
                                              config->query_1_B_configs.leader_list_2_copier_investor_power_dis_param,
                                              config);
  bool not_found_trade_ID = true;

  output->head_node = new transactions_linked_list_node();
  transactions_linked_list_node* current_node = output->head_node;

  unsigned long trade_ID_to_copy = 0;

  unsigned long current_transaction_ID = input->transaction_ID;

  unsigned long freshness_score_vertex_ID = input->thread_ID + config->first_freshness_score_vertex_ID;

  output->number_of_transactions = 0;

  double copy_from_leader_list_1_prob_weight = config->query_1_B_configs.copy_from_leader_list_1_probability;
  double copy_from_leader_list_2_prob_weight = config->query_1_B_configs.copy_from_leader_list_2_probability;
  double copy_from_a_friend_prob_weight = config->query_1_B_configs.copy_a_friend_probability;

  int max_trade_ID_scan_attempts = 5;

  int current_trade_ID_scan_attempts = 0;

  while (not_found_trade_ID && current_trade_ID_scan_attempts < max_trade_ID_scan_attempts) {
    current_trade_ID_scan_attempts++;
    //sample until a copy trade ID is found

    double total_prob_weight = copy_from_leader_list_1_prob_weight
                              + copy_from_leader_list_2_prob_weight
                              + copy_from_a_friend_prob_weight;

    double select_copy_mode_random = generate_uniform_distribution_sample(0, total_prob_weight);

    if(select_copy_mode_random <= copy_from_leader_list_1_prob_weight + copy_from_leader_list_2_prob_weight){

      //get a sample from a leader list
      unsigned long leader_ID = 0;

      if (select_copy_mode_random <= copy_from_leader_list_1_prob_weight) {
        unsigned long list_index = generate_power_distribution_ID_sample(0,
                                                                        config->number_of_investors,
                                                                        config->query_1_B_configs.leader_list_1_to_copy_power_dis_param);
        leader_ID = config->leader_list_1[list_index];
      }
      else {
        unsigned long list_index = generate_power_distribution_ID_sample(0,
                                                                        config->number_of_investors,
                                                                        config->query_1_B_configs.leader_list_2_to_copy_power_dis_param);
        leader_ID = config->leader_list_2[list_index];
      }

      //perform operation 3
      TQ_3::input_struct* query_3_input = new TQ_3::input_struct();
      query_3_input->transaction_ID = current_transaction_ID;
      query_3_input->read_investor_ID = leader_ID;
      query_3_input->thread_ID = input->thread_ID;

      TQ_3::output_struct* query_3_output = new TQ_3::output_struct();

      TQ_3::operation_handler(query_3_input, query_3_output, config);
      if (query_3_output->success) {

        current_node->start_time = query_3_output->start_time;
        current_node->end_time = query_3_output->end_time;
        current_node->query_type = "TQ_3";
        current_node->transaction_ID = current_transaction_ID;

        current_transaction_ID += 1;

        output->number_of_transactions += 1;

        current_node->next = new transactions_linked_list_node();
        current_node = current_node->next;

        if(query_3_output->has_traded) {
          trade_ID_to_copy = query_3_output->latest_trade_ID;
          not_found_trade_ID = false;
        }
      }

      delete query_3_input;
      delete query_3_output;
    }
    else {
      //perform operation 6
      TQ_6::input_struct* query_6_input = new TQ_6::input_struct();
      query_6_input->transaction_ID = current_transaction_ID;
      query_6_input->read_investor_ID = copier_investor_ID;
      query_6_input->thread_ID = input->thread_ID;

      TQ_6::output_struct* query_6_output = new TQ_6::output_struct();

      TQ_6::operation_handler(query_6_input, query_6_output, config);
      if (query_6_output->success) {

        current_node->start_time = query_6_output->start_time;
        current_node->end_time = query_6_output->end_time;
        current_node->query_type = "TQ_6";
        current_node->transaction_ID = current_transaction_ID;

        current_transaction_ID += 1;

        output->number_of_transactions += 1;

        current_node->next = new transactions_linked_list_node();
        current_node = current_node->next;

        if(query_6_output->friend_trade_list_length > 0) {
          trade_ID_to_copy = query_6_output->friend_trade_list_pointer[0];
          not_found_trade_ID = false;
        }
        else {
          //the friends have 0 trades so we dont choose from friends
          copy_from_a_friend_prob_weight = 0;
        }
      }

      delete[] query_6_output->friend_trade_list_pointer;
      delete query_6_input;
      delete query_6_output;
    }
  }

  if (!not_found_trade_ID) {
    uint64_t current_timestamp = get_current_epoch_time_in_milliseconds();

    /*--------------------------------------------------------------------------*/
    /*--------------------------------------------------------------------------*/

    json request;
    request["OPERATION_ID"] = 9;
    request["TRADE_ID_TO_COPY"] = trade_ID_to_copy;
    request["COPIER_INVESTOR_ID"] = copier_investor_ID;
    request["CURRENT_TIMESTAMP"] = current_timestamp;

    //FRESHNESS SCORE
    request["FRESHNESS_SCORE_ID"] = freshness_score_vertex_ID;
    request["FS_TRANSACTION_ID"] = current_transaction_ID;

    json response;

    //perform the operation with the help of copier_investor_ID, trade_ID_to_copy and current_timestamp

    current_node->start_time = get_current_epoch_time_in_milliseconds();
    //perform operation here

    response = send_query(request, config->server_ip_address, config->server_port_number);

    current_node->end_time = get_current_epoch_time_in_milliseconds();

    output->success = response["SUCCESS"].get<bool>();

    /*--------------------------------------------------------------------------*/
    /*--------------------------------------------------------------------------*/

    current_node->query_type = "TQ_1_B";
    
    if (!output->success) {
      output->next_transaction_ID = current_transaction_ID;
    }
    else {
      current_node->transaction_ID = current_transaction_ID;
      output->number_of_transactions += 1;
      output->next_transaction_ID = current_transaction_ID + 1;
    }
  }
  else {
    output->success = false;
    output->next_transaction_ID = current_transaction_ID;
  }
}

/*
Description:
    Creates the input and calls the operation handler of query type 1_B
*/
void TQ_1_B::perform_operation(struct transactional_driver_config* config, struct output_struct* output, unsigned long transaction_ID, int thread_ID) {
  input_struct* input = new input_struct();
  input->thread_ID = thread_ID;
  input->transaction_ID = transaction_ID;
  operation_handler(input, output, config);

  delete input;
}
