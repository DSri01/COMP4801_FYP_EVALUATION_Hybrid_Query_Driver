/*
FYP : 22013

Module:
    Hybrid Query Driver - Query Driver Configuration

Description:
    Defines the configurer for the Transactional Query Driver, which configures
    the transactional query driver.
*/
#include "QDC001_TQD_Config.h"

using json = nlohmann::json;

using namespace TQD_CONFIG;

/*
Description:
    Provides a method to read the configurations for query type 1_A
*/
struct transactional_query_1_A_config TQD_CONFIG::read_transactional_query_1_A_configs(std::string file_name) {
  std::ifstream f(file_name);
  json configs = json::parse(f);

  transactional_query_1_A_config query_configs = {.follower_is_original_investor_probability = configs["TQD_query_1_A_follower_is_original_investor_probability"].get<double>(),
                                                 .leader_list_1_is_original_investor_probability = configs["TQD_query_1_A_leader_list_1_is_original_investor_probability"].get<double>(),
                                                 .leader_list_2_is_original_investor_probability = configs["TQD_query_1_A_leader_list_2_is_original_investor_probability"].get<double>(),
                                                 .follower_list_original_investor_power_dis_param = configs["TQD_query_1_A_follower_list_original_investor_power_dis_param"].get<double>(),
                                                 .leader_list_1_original_investor_power_dis_param = configs["TQD_query_1_A_leader_list_1_original_investor_power_dis_param"].get<double>(),
                                                 .leader_list_2_original_investor_power_dis_param = configs["TQD_query_1_A_leader_list_2_original_investor_power_dis_param"].get<double>(),
                                                 .company_trade_power_dis_param = configs["TQD_query_1_A_company_trade_power_dis_param"].get<double>(),
                                                 .max_number_of_companies_traded = configs["TQD_query_1_A_max_number_of_companies_traded"].get<int>(),
                                               };
  return query_configs;

}

/*
Description:
    Provides a method to read the configurations for query type 1_B
*/
struct transactional_query_1_B_config TQD_CONFIG::read_transactional_query_1_B_configs(std::string file_name) {
  std::ifstream f(file_name);
  json configs = json::parse(f);

  transactional_query_1_B_config query_configs = {.follower_is_copier_investor_probability = configs["TQD_query_1_B_follower_is_copier_investor_probability"].get<double>(),
                                                 .leader_list_1_is_copier_investor_probability = configs["TQD_query_1_B_leader_list_1_is_copier_investor_probability"].get<double>(),
                                                 .leader_list_2_is_copier_investor_probability = configs["TQD_query_1_B_leader_list_2_is_copier_investor_probability"].get<double>(),
                                                 .follower_list_copier_investor_power_dis_param = configs["TQD_query_1_B_follower_list_copier_investor_power_dis_param"].get<double>(),
                                                 .leader_list_1_copier_investor_power_dis_param = configs["TQD_query_1_B_leader_list_1_copier_investor_power_dis_param"].get<double>(),
                                                 .leader_list_2_copier_investor_power_dis_param = configs["TQD_query_1_B_leader_list_2_copier_investor_power_dis_param"].get<double>(),
                                                 .copy_from_leader_list_1_probability = configs["TQD_query_1_B_copy_from_leader_list_1_probability"].get<double>(),
                                                 .copy_from_leader_list_2_probability = configs["TQD_query_1_B_copy_from_leader_list_2_probability"].get<double>(),
                                                 .copy_a_friend_probability = configs["TQD_query_1_B_copy_a_friend_probability"].get<double>(),
                                                 .leader_list_1_to_copy_power_dis_param = configs["TQD_query_1_B_leader_list_1_to_copy_power_dis_param"].get<double>(),
                                                 .leader_list_2_to_copy_power_dis_param = configs["TQD_query_1_B_leader_list_2_to_copy_power_dis_param"].get<double>()
                                               };
  return query_configs;

}

/*
Description:
    Provides a method to read the configurations for query type 2
*/
struct transactional_query_2_config TQD_CONFIG::read_transactional_query_2_configs(std::string file_name) {
  std::ifstream f(file_name);
  json configs = json::parse(f);

  transactional_query_2_config query_configs = {.read_follower_profile_probability = configs["TQD_query_2_read_follower_profile_probability"].get<double>(),
                                                 .read_leader_list_1_profile_probability = configs["TQD_query_2_read_leader_list_1_profile_probability"].get<double>(),
                                                 .read_leader_list_2_profile_probability = configs["TQD_query_2_read_leader_list_2_profile_probability"].get<double>(),
                                                 .follower_list_investor_profile_power_dis_param = configs["TQD_query_2_follower_list_investor_profile_power_dis_param"].get<double>(),
                                                 .leader_list_1_investor_profile_power_dis_param = configs["TQD_query_2_leader_list_1_investor_profile_power_dis_param"].get<double>(),
                                                 .leader_list_2_investor_profile_power_dis_param = configs["TQD_query_2_leader_list_2_investor_profile_power_dis_param"].get<double>()
                                               };
  return query_configs;

}

/*
Description:
    Provides a method to read the configurations for query type 3
*/
struct transactional_query_3_config TQD_CONFIG::read_transactional_query_3_configs(std::string file_name) {
  std::ifstream f(file_name);
  json configs = json::parse(f);

  transactional_query_3_config query_configs = {.read_follower_trade_probability = configs["TQD_query_3_read_follower_trade_probability"].get<double>(),
                                                 .read_leader_list_1_trade_probability = configs["TQD_query_3_read_leader_list_1_trade_probability"].get<double>(),
                                                 .read_leader_list_2_trade_probability = configs["TQD_query_3_read_leader_list_2_trade_probability"].get<double>(),
                                                 .follower_list_read_trade_power_dis_param = configs["TQD_query_3_follower_list_read_trade_power_dis_param"].get<double>(),
                                                 .leader_list_1_read_trade_power_dis_param = configs["TQD_query_3_leader_list_1_read_trade_power_dis_param"].get<double>(),
                                                 .leader_list_2_read_trade_power_dis_param = configs["TQD_query_3_leader_list_2_read_trade_power_dis_param"].get<double>()
                                               };
  return query_configs;

}

/*
Description:
    Provides a method to read the configurations for query type 4
*/
struct transactional_query_4_config TQD_CONFIG::read_transactional_query_4_configs(std::string file_name) {
  std::ifstream f(file_name);
  json configs = json::parse(f);

  transactional_query_4_config query_configs = {.company_read_power_dis_param = configs["TQD_query_4_company_read_power_dis_param"].get<double>()
                                               };
  return query_configs;

}

/*
Description:
    Provides a method to read the configurations for query type 5
*/
struct transactional_query_5_config TQD_CONFIG::read_transactional_query_5_configs(std::string file_name) {
  std::ifstream f(file_name);
  json configs = json::parse(f);

  transactional_query_5_config query_configs = {.read_follower_mirrorers_probability = configs["TQD_query_5_read_follower_mirrorers_probability"].get<double>(),
                                                 .read_leader_list_1_mirrorers_probability = configs["TQD_query_5_read_leader_list_1_mirrorers_probability"].get<double>(),
                                                 .read_leader_list_2_mirrorers_probability = configs["TQD_query_5_read_leader_list_2_mirrorers_probability"].get<double>(),
                                                 .follower_list_read_mirrorers_power_dis_param = configs["TQD_query_5_follower_list_read_mirrorers_power_dis_param"].get<double>(),
                                                 .leader_list_1_read_mirrorers_power_dis_param = configs["TQD_query_5_leader_list_1_read_mirrorers_power_dis_param"].get<double>(),
                                                 .leader_list_2_read_mirrorers_power_dis_param = configs["TQD_query_5_leader_list_2_read_mirrorers_power_dis_param"].get<double>()
                                               };
  return query_configs;

}

/*
Description:
    Provides a method to read the configurations for query type 6
*/
struct transactional_query_6_config TQD_CONFIG::read_transactional_query_6_configs(std::string file_name) {
  std::ifstream f(file_name);
  json configs = json::parse(f);

  transactional_query_6_config query_configs = {.read_follower_friend_trade_probability = configs["TQD_query_6_read_follower_friend_trade_probability"].get<double>(),
                                                 .read_leader_list_1_friend_trade_probability = configs["TQD_query_6_read_leader_list_1_friend_trade_probability"].get<double>(),
                                                 .read_leader_list_2_friend_trade_probability = configs["TQD_query_6_read_leader_list_2_friend_trade_probability"].get<double>(),
                                                 .follower_list_read_friend_trade_power_dis_param = configs["TQD_query_6_follower_list_read_friend_trade_power_dis_param"].get<double>(),
                                                 .leader_list_1_read_friend_trade_power_dis_param = configs["TQD_query_6_leader_list_1_read_friend_trade_power_dis_param"].get<double>(),
                                                 .leader_list_2_read_friend_trade_power_dis_param = configs["TQD_query_6_leader_list_2_read_friend_trade_power_dis_param"].get<double>()
                                               };
  return query_configs;

}

/*
Description:
    Provides a method to read the configurations for query type 7
*/
struct transactional_query_7_config TQD_CONFIG::read_transactional_query_7_configs(std::string file_name) {
  std::ifstream f(file_name);
  json configs = json::parse(f);

  transactional_query_7_config query_configs = {.follower_update_amount_probability = configs["TQD_query_7_follower_update_amount_probability"].get<double>(),
                                                 .leader_list_1_update_amount_probability = configs["TQD_query_7_leader_list_1_update_amount_probability"].get<double>(),
                                                 .leader_list_2_update_amount_probability = configs["TQD_query_7_leader_list_2_update_amount_probability"].get<double>(),
                                                 .follower_list_update_amount_power_dis_param = configs["TQD_query_7_follower_list_update_amount_power_dis_param"].get<double>(),
                                                 .leader_list_1_update_amount_power_dis_param = configs["TQD_query_7_leader_list_1_update_amount_power_dis_param"].get<double>(),
                                                 .leader_list_2_update_amount_power_dis_param = configs["TQD_query_7_leader_list_2_update_amount_power_dis_param"].get<double>()
                                               };
  return query_configs;

}

/*
Description:
    Provides a method to read the configurations for query type 8
*/
struct transactional_query_8_config TQD_CONFIG::read_transactional_query_8_configs(std::string file_name) {
  std::ifstream f(file_name);
  json configs = json::parse(f);

  transactional_query_8_config query_configs = {};
  return query_configs;

}

/*
Description:
    Provides a method to read the vertex lists from their respective files
*/
void TQD_CONFIG::read_vertex_list(std::string file_name, unsigned long list_length, int number_of_message_lines, unsigned long* list_pointer) {
  std::fstream list_file;
  list_file.open(file_name, std::ios::in);
  if (list_file.is_open()) {
    std::string line;
    for (int i = 0; i < number_of_message_lines; i++) {
      getline(list_file, line);
    }
    int list_index = 0;
    while (getline(list_file, line)) {
      unsigned long list_element = std::stoul(line);
      list_pointer[list_index] = list_element;
      list_index++;
    }
  }
  else {
    std::cout<<"Error Opening:"<<file_name<<"\n";
    exit(-1);
  }
}

/*
Description:
    Provides a method to read the remove mirror list from its file
*/
void TQD_CONFIG::read_remove_mirror_list(std::string file_name, unsigned long* source_list, unsigned long* destination_list, int number_of_message_lines) {
  std::fstream list_file;
  list_file.open(file_name, std::ios::in);
  if (list_file.is_open()) {
    std::string line;
    for (int i = 0; i < number_of_message_lines; i++) {
      getline(list_file, line);
    }
    int list_index = 0;
    while (getline(list_file, line)) {
      int divider_index = line.find("|");
      unsigned long source_ID = std::stoul(line.substr(0,divider_index));
      unsigned long destination_ID = std::stoul(line.substr(divider_index+1));
      source_list[list_index] = source_ID;
      destination_list[list_index] = destination_ID;
      list_index++;
    }
  }
  else {
    std::cout<<"Error Opening:"<<file_name<<"\n";
    exit(-1);
  }
}

/*
Description:
    Provides a method to read the configurations for the transactional query
    driver along with the transactional query types.
*/
void TQD_CONFIG::read_transactional_query_driver_configs(struct transactional_driver_config* config_pointer,
                                             std::string file_name){
  std::ifstream f(file_name);
  json configs = json::parse(f);

  config_pointer->server_ip_address = configs["IP_ADDRESS"].get<std::string>();
  config_pointer->server_port_number = configs["PORT_NUMBER"].get<int>();
  
  config_pointer->number_of_transactional_threads = configs["number_of_transactional_threads"].get<int>();

  config_pointer->is_freshness_score_calculation_active = configs["enable_freshness_score"].get<bool>();

  config_pointer->enable_query_1A = configs["enable_transactional_query_1_A"].get<bool>();
  config_pointer->enable_query_1B = configs["enable_transactional_query_1_B"].get<bool>();
  config_pointer->enable_query_2 = configs["enable_transactional_query_2"].get<bool>();
  config_pointer->enable_query_3 = configs["enable_transactional_query_3"].get<bool>();
  config_pointer->enable_query_4 = configs["enable_transactional_query_4"].get<bool>();
  config_pointer->enable_query_5 = configs["enable_transactional_query_5"].get<bool>();
  config_pointer->enable_query_6 = configs["enable_transactional_query_6"].get<bool>();
  config_pointer->enable_query_7 = configs["enable_transactional_query_7"].get<bool>();
  config_pointer->enable_query_8 = configs["enable_transactional_query_8"].get<bool>();

  config_pointer->query_1_A_probabilistic_weight = configs["transactional_query_1_A_probabilistic_weight"].get<double>();
  config_pointer->query_1_B_probabilistic_weight = configs["transactional_query_1_B_probabilistic_weight"].get<double>();
  config_pointer->query_2_probabilistic_weight = configs["transactional_query_2_probabilistic_weight"].get<double>();
  config_pointer->query_3_probabilistic_weight = configs["transactional_query_3_probabilistic_weight"].get<double>();
  config_pointer->query_4_probabilistic_weight = configs["transactional_query_4_probabilistic_weight"].get<double>();
  config_pointer->query_5_probabilistic_weight = configs["transactional_query_5_probabilistic_weight"].get<double>();
  config_pointer->query_6_probabilistic_weight = configs["transactional_query_6_probabilistic_weight"].get<double>();
  config_pointer->query_7_probabilistic_weight = configs["transactional_query_7_probabilistic_weight"].get<double>();
  config_pointer->query_8_probabilistic_weight = configs["transactional_query_8_probabilistic_weight"].get<double>();

  config_pointer->query_1_A_configs = read_transactional_query_1_A_configs(file_name);
  config_pointer->query_1_B_configs = read_transactional_query_1_B_configs(file_name);
  config_pointer->query_2_configs = read_transactional_query_2_configs(file_name);
  config_pointer->query_3_configs = read_transactional_query_3_configs(file_name);
  config_pointer->query_4_configs = read_transactional_query_4_configs(file_name);
  config_pointer->query_5_configs = read_transactional_query_5_configs(file_name);
  config_pointer->query_6_configs = read_transactional_query_6_configs(file_name);
  config_pointer->query_7_configs = read_transactional_query_7_configs(file_name);
  config_pointer->query_8_configs = read_transactional_query_8_configs(file_name);

  config_pointer->number_of_investors = configs["number_of_investors"].get<unsigned long>();
  config_pointer->number_of_companies = configs["number_of_companies"].get<unsigned long>();
  config_pointer->number_of_freshness_score_vertices = configs["number_of_freshness_score_vertices"].get<unsigned long>();
  config_pointer->remove_mirror_edge_list_length = configs["remove_mirror_edge_list_length"].get<unsigned long>();

  std::string follower_list_file_name = configs["follower_list_file_name"].get<std::string>();
  std::string leader_list_1_file_name = configs["leader_list_1_file_name"].get<std::string>();
  std::string leader_list_2_file_name = configs["leader_list_2_file_name"].get<std::string>();
  std::string company_list_file_name = configs["company_list_file_name"].get<std::string>();
  std::string remove_mirror_edges_file_name = configs["remove_mirror_edges_file_name"].get<std::string>();

  config_pointer->follower_list = new unsigned long[config_pointer->number_of_investors];
  config_pointer->leader_list_1 = new unsigned long[config_pointer->number_of_investors];
  config_pointer->leader_list_2 = new unsigned long[config_pointer->number_of_investors];
  config_pointer->company_list = new unsigned long[config_pointer->number_of_companies];

  read_vertex_list(follower_list_file_name, config_pointer->number_of_investors, 1, config_pointer->follower_list);
  read_vertex_list(leader_list_1_file_name, config_pointer->number_of_investors, 1, config_pointer->leader_list_1);
  read_vertex_list(leader_list_2_file_name, config_pointer->number_of_investors, 1, config_pointer->leader_list_2);
  read_vertex_list(company_list_file_name, config_pointer->number_of_companies, 1, config_pointer->company_list);

  config_pointer->remove_mirror_edge_source_ID_list = new unsigned long[config_pointer->remove_mirror_edge_list_length];
  config_pointer->remove_mirror_edge_destination_ID_list = new unsigned long[config_pointer->remove_mirror_edge_list_length];

  read_remove_mirror_list(remove_mirror_edges_file_name, config_pointer->remove_mirror_edge_source_ID_list, config_pointer->remove_mirror_edge_destination_ID_list, 2);

  config_pointer->result_directory = configs["freshness_score_results_directory"].get<std::string>() + "Transactional/";

  config_pointer->first_freshness_score_vertex_ID = 2 * config_pointer->number_of_investors + config_pointer->number_of_companies;
  config_pointer->first_trade_vertex_ID = config_pointer->first_freshness_score_vertex_ID + config_pointer->number_of_freshness_score_vertices;
}
