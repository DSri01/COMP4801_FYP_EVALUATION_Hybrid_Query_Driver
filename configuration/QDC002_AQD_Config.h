/*
FYP : 22013

Module:
    Hybrid Query Driver - Query Driver Configuration

Description:
    Header file for the configuration of the Analytical Query Driver.
*/
#include "../third_party/json.hpp"

#include <fstream>
#include <iostream>
#include <string>

#ifndef QDC002_AQD_CONFIG_H
#define QDC002_AQD_CONFIG_H

struct analytical_query_1_config{
  /*
  Description:
    Configurations for Analytical Query 1: BFS
  */
  double select_bfs_root_from_follower_list_prob_weight;
  double select_bfs_root_from_leader_list_1_prob_weight;
  double select_bfs_root_from_leader_list_2_prob_weight;

  double follower_list_bfs_root_power_dis_param;
  double leader_list_1_bfs_root_power_dis_param;
  double leader_list_2_bfs_root_power_dis_param;
};

struct analytical_query_2_config{
  /*
  Description:
    Configurations for Analytical Query 2: PageRank
  */
  int pr_max_iterations;
  double pr_damping_factor;
};

struct analytical_query_3_config{
  /*
  Description:
    Configurations for Analytical Query 3: WCC
  */

};

struct analytical_query_4_config{
  /*
  Description:
    Configurations for Analytical Query 4: LCC
  */

};

struct analytical_query_5_config{
  /*
  Description:
    Configurations for Analytical Query 5: CDLP
  */
  int cdlp_max_iterations;
};

struct analytical_query_6_config{
  /*
  Description:
    Configurations for Analytical Query 6: SSSP
  */
  double select_sssp_root_from_follower_list_prob_weight;
  double select_sssp_root_from_leader_list_1_prob_weight;
  double select_sssp_root_from_leader_list_2_prob_weight;

  double follower_list_sssp_root_power_dis_param;
  double leader_list_1_sssp_root_power_dis_param;
  double leader_list_2_sssp_root_power_dis_param;
};

struct analytical_driver_config{
  /*
  Description:
    Configurations for the Analytical Query Driver
  */

  std::string server_ip_address;
  int server_port_number;

  int number_of_analytical_threads;
  int number_of_transactional_threads;

  bool is_freshness_score_calculation_active;

  bool enable_query_1;
  bool enable_query_2;
  bool enable_query_3;
  bool enable_query_4;
  bool enable_query_5;
  bool enable_query_6;

  double query_1_probabilistic_weight;
  double query_2_probabilistic_weight;
  double query_3_probabilistic_weight;
  double query_4_probabilistic_weight;
  double query_5_probabilistic_weight;
  double query_6_probabilistic_weight;

  struct analytical_query_1_config query_1_configs;
  struct analytical_query_2_config query_2_configs;
  struct analytical_query_3_config query_3_configs;
  struct analytical_query_4_config query_4_configs;
  struct analytical_query_5_config query_5_configs;
  struct analytical_query_6_config query_6_configs;

  uint64_t end_warmup_timestamp;
  uint64_t end_data_collection_timestamp;

  unsigned long number_of_investors;
  unsigned long number_of_companies;
  unsigned long number_of_freshness_score_vertices;

  unsigned long* follower_list;
  unsigned long* leader_list_1;
  unsigned long* leader_list_2;

  std::string result_directory;

  unsigned long first_freshness_score_vertex_ID;
  //
  // unsigned long remove_mirror_edge_list_length;
  //
  // unsigned long* follower_list;
  // unsigned long* leader_list_1;
  // unsigned long* leader_list_2;
  // unsigned long* company_list;
  // unsigned long* remove_mirror_edge_source_ID_list;
  // unsigned long* remove_mirror_edge_destination_ID_list;
};

namespace AQD_CONFIG{
  struct analytical_query_1_config read_analytical_query_1_configs(std::string);

  struct analytical_query_2_config read_analytical_query_2_configs(std::string);

  struct analytical_query_3_config read_analytical_query_3_configs(std::string);

  struct analytical_query_4_config read_analytical_query_4_configs(std::string);

  struct analytical_query_5_config read_analytical_query_5_configs(std::string);

  struct analytical_query_6_config read_analytical_query_6_configs(std::string);

  void read_vertex_list(std::string, unsigned long, int, unsigned long*);

  void read_analytical_query_driver_configs(struct analytical_driver_config*,
                                            std::string);
}

#endif
