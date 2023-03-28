/*
FYP : 22013

Module:
    Hybrid Query Driver - Query Driver Configuration

Description:
    Defines the configurer for the Analytical Query Driver, which configures
    the analytical query driver.
*/

#include "QDC002_AQD_Config.h"

using json = nlohmann::json;

using namespace AQD_CONFIG;

/*
Description:
    Provides a method to read the configurations for query type 1
*/
struct analytical_query_1_config AQD_CONFIG::read_analytical_query_1_configs(std::string file_name) {
  std::ifstream f(file_name);
  json configs = json::parse(f);

  analytical_query_1_config query_configs = {.select_bfs_root_from_follower_list_prob_weight = configs["AQD_query_1_follower_is_bfs_root_probability"].get<double>(),
                                             .select_bfs_root_from_leader_list_1_prob_weight = configs["AQD_query_1_leader_list_1_is_bfs_root_probability"].get<double>(),
                                             .select_bfs_root_from_leader_list_2_prob_weight = configs["AQD_query_1_leader_list_2_is_bfs_root_probability"].get<double>(),
                                             .follower_list_bfs_root_power_dis_param = configs["AQD_query_1_follower_list_bfs_root_power_dis_param"].get<double>(),
                                             .leader_list_1_bfs_root_power_dis_param = configs["AQD_query_1_leader_list_1_bfs_root_power_dis_param"].get<double>(),
                                             .leader_list_2_bfs_root_power_dis_param = configs["AQD_query_1_leader_list_2_bfs_root_power_dis_param"].get<double>()
                                             };
  return query_configs;
}

/*
Description:
    Provides a method to read the configurations for query type 2
*/
struct analytical_query_2_config AQD_CONFIG::read_analytical_query_2_configs(std::string file_name) {
  std::ifstream f(file_name);
  json configs = json::parse(f);

  analytical_query_2_config query_configs = {.pr_max_iterations = configs["AQD_query_2_pr_max_iterations"].get<int>(),
                                             .pr_damping_factor = configs["AQD_query_2_pr_damping_factor"].get<double>()
                                              };
  return query_configs;
}

/*
Description:
    Provides a method to read the configurations for query type 3
*/
struct analytical_query_3_config AQD_CONFIG::read_analytical_query_3_configs(std::string file_name) {
  std::ifstream f(file_name);
  json configs = json::parse(f);

  analytical_query_3_config query_configs = {};
  return query_configs;
}

/*
Description:
    Provides a method to read the configurations for query type 4
*/
struct analytical_query_4_config AQD_CONFIG::read_analytical_query_4_configs(std::string file_name) {
  std::ifstream f(file_name);
  json configs = json::parse(f);

  analytical_query_4_config query_configs = {};
  return query_configs;
}

/*
Description:
    Provides a method to read the configurations for query type 5
*/
struct analytical_query_5_config AQD_CONFIG::read_analytical_query_5_configs(std::string file_name) {
  std::ifstream f(file_name);
  json configs = json::parse(f);

  analytical_query_5_config query_configs = {.cdlp_max_iterations = configs["AQD_query_5_cdlp_max_iterations"].get<int>()};
  return query_configs;
}

/*
Description:
    Provides a method to read the configurations for query type 6
*/
struct analytical_query_6_config AQD_CONFIG::read_analytical_query_6_configs(std::string file_name) {
  std::ifstream f(file_name);
  json configs = json::parse(f);

  analytical_query_6_config query_configs = {.select_sssp_root_from_follower_list_prob_weight = configs["AQD_query_6_follower_is_sssp_root_probability"].get<double>(),
                                             .select_sssp_root_from_leader_list_1_prob_weight = configs["AQD_query_6_leader_list_1_is_sssp_root_probability"].get<double>(),
                                             .select_sssp_root_from_leader_list_2_prob_weight = configs["AQD_query_6_leader_list_2_is_sssp_root_probability"].get<double>(),
                                             .follower_list_sssp_root_power_dis_param = configs["AQD_query_6_follower_list_sssp_root_power_dis_param"].get<double>(),
                                             .leader_list_1_sssp_root_power_dis_param = configs["AQD_query_6_leader_list_1_sssp_root_power_dis_param"].get<double>(),
                                             .leader_list_2_sssp_root_power_dis_param = configs["AQD_query_6_leader_list_2_sssp_root_power_dis_param"].get<double>()
                                             };
  return query_configs;
}

/*
Description:
    Provides a method to read the vertex lists from their respective files
*/
void AQD_CONFIG::read_vertex_list(std::string file_name, unsigned long list_length, int number_of_message_lines, unsigned long* list_pointer) {
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
    Provides a method to read the configurations for the analytical query driver
    along with the analytical query types.
*/
void AQD_CONFIG::read_analytical_query_driver_configs(struct analytical_driver_config* config_pointer,
                                          std::string file_name){
  std::ifstream f(file_name);
  json configs = json::parse(f);

  config_pointer->server_ip_address = configs["IP_ADDRESS"].get<std::string>();
  config_pointer->server_port_number = configs["PORT_NUMBER"].get<int>();

  config_pointer->number_of_analytical_threads = configs["number_of_analytical_threads"].get<int>();
  config_pointer->number_of_transactional_threads = configs["number_of_transactional_threads"].get<int>();

  config_pointer->is_freshness_score_calculation_active = configs["enable_freshness_score"].get<bool>();

  config_pointer->enable_query_1 = configs["enable_analytical_query_1"].get<bool>();
  config_pointer->enable_query_2 = configs["enable_analytical_query_2"].get<bool>();
  config_pointer->enable_query_3 = configs["enable_analytical_query_3"].get<bool>();
  config_pointer->enable_query_4 = configs["enable_analytical_query_4"].get<bool>();
  config_pointer->enable_query_5 = configs["enable_analytical_query_5"].get<bool>();
  config_pointer->enable_query_6 = configs["enable_analytical_query_6"].get<bool>();


  config_pointer->query_1_probabilistic_weight = configs["analytical_query_1_probabilistic_weight"].get<double>();
  config_pointer->query_2_probabilistic_weight = configs["analytical_query_2_probabilistic_weight"].get<double>();
  config_pointer->query_3_probabilistic_weight = configs["analytical_query_3_probabilistic_weight"].get<double>();
  config_pointer->query_4_probabilistic_weight = configs["analytical_query_4_probabilistic_weight"].get<double>();
  config_pointer->query_5_probabilistic_weight = configs["analytical_query_5_probabilistic_weight"].get<double>();
  config_pointer->query_6_probabilistic_weight = configs["analytical_query_6_probabilistic_weight"].get<double>();

  config_pointer->query_1_configs = read_analytical_query_1_configs(file_name);
  config_pointer->query_2_configs = read_analytical_query_2_configs(file_name);
  config_pointer->query_3_configs = read_analytical_query_3_configs(file_name);
  config_pointer->query_4_configs = read_analytical_query_4_configs(file_name);
  config_pointer->query_5_configs = read_analytical_query_5_configs(file_name);
  config_pointer->query_6_configs = read_analytical_query_6_configs(file_name);

  config_pointer->number_of_investors = configs["number_of_investors"].get<unsigned long>();
  config_pointer->number_of_companies = configs["number_of_companies"].get<unsigned long>();
  config_pointer->number_of_freshness_score_vertices = configs["number_of_freshness_score_vertices"].get<unsigned long>();

  config_pointer->follower_list = new unsigned long[config_pointer->number_of_investors];
  config_pointer->leader_list_1 = new unsigned long[config_pointer->number_of_investors];
  config_pointer->leader_list_2 = new unsigned long[config_pointer->number_of_investors];

  std::string follower_list_file_name = configs["follower_list_file_name"].get<std::string>();
  std::string leader_list_1_file_name = configs["leader_list_1_file_name"].get<std::string>();
  std::string leader_list_2_file_name = configs["leader_list_2_file_name"].get<std::string>();

  read_vertex_list(follower_list_file_name, config_pointer->number_of_investors, 1, config_pointer->follower_list);
  read_vertex_list(leader_list_1_file_name, config_pointer->number_of_investors, 1, config_pointer->leader_list_1);
  read_vertex_list(leader_list_2_file_name, config_pointer->number_of_investors, 1, config_pointer->leader_list_2);

  config_pointer->result_directory = configs["freshness_score_results_directory"].get<std::string>() + "Analytical/";

  config_pointer->first_freshness_score_vertex_ID = 2 * config_pointer->number_of_investors + config_pointer->number_of_companies;

}
