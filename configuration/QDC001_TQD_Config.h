/*
FYP : 22013

Module:
    Hybrid Query Driver - Query Driver Configuration

Description:
    Header file for the configuration of the Transactional Query Driver.
*/
#include "../third_party/json.hpp"

#include <fstream>
#include <iostream>
#include <string>

#ifndef QDC001_TQD_CONFIG_H
#define QDC001_TQD_CONFIG_H

struct transactional_query_1_A_config{
  /*
  Description:
    Configurations for Query 1A: Make Original Trade
  */

  double follower_is_original_investor_probability;
  double leader_list_1_is_original_investor_probability;
  double leader_list_2_is_original_investor_probability;

  double follower_list_original_investor_power_dis_param;
  double leader_list_1_original_investor_power_dis_param;
  double leader_list_2_original_investor_power_dis_param;

  double company_trade_power_dis_param;
  int max_number_of_companies_traded;
};

struct transactional_query_1_B_config{
  /*
  Description:
    Configurations for Query 1B: Make Copy Trade
  */

  double follower_is_copier_investor_probability;
  double leader_list_1_is_copier_investor_probability;
  double leader_list_2_is_copier_investor_probability;

  double follower_list_copier_investor_power_dis_param;
  double leader_list_1_copier_investor_power_dis_param;
  double leader_list_2_copier_investor_power_dis_param;

  double copy_from_leader_list_1_probability;
  double copy_from_leader_list_2_probability;
  double copy_a_friend_probability;

  double leader_list_1_to_copy_power_dis_param;
  double leader_list_2_to_copy_power_dis_param;
};

struct transactional_query_2_config{
  /*
  Description:
    Configurations for Query 2: Read Investor Profile
  */

  double read_follower_profile_probability;
  double read_leader_list_1_profile_probability;
  double read_leader_list_2_profile_probability;

  double follower_list_investor_profile_power_dis_param;
  double leader_list_1_investor_profile_power_dis_param;
  double leader_list_2_investor_profile_power_dis_param;
};

struct transactional_query_3_config{
  /*
  Description:
    Configurations for Query 3: Read Investor's Most Recent Trade
  */

  double read_follower_trade_probability;
  double read_leader_list_1_trade_probability;
  double read_leader_list_2_trade_probability;

  double follower_list_read_trade_power_dis_param;
  double leader_list_1_read_trade_power_dis_param;
  double leader_list_2_read_trade_power_dis_param;
};

struct transactional_query_4_config{
  /*
  Description:
    Configurations for Query 4: Read Company
  */

  double company_read_power_dis_param;
};

struct transactional_query_5_config{
  /*
  Description:
    Configurations for Query 5: Read All Mirroring Investors
  */

  double read_follower_mirrorers_probability;
  double read_leader_list_1_mirrorers_probability;
  double read_leader_list_2_mirrorers_probability;

  double follower_list_read_mirrorers_power_dis_param;
  double leader_list_1_read_mirrorers_power_dis_param;
  double leader_list_2_read_mirrorers_power_dis_param;
};

struct transactional_query_6_config{
  /*
  Description:
    Configurations for Query 6: Read Most Recent Trades of all Friends
  */

  double read_follower_friend_trade_probability;
  double read_leader_list_1_friend_trade_probability;
  double read_leader_list_2_friend_trade_probability;

  double follower_list_read_friend_trade_power_dis_param;
  double leader_list_1_read_friend_trade_power_dis_param;
  double leader_list_2_read_friend_trade_power_dis_param;
};

struct transactional_query_7_config{
  /*
  Description:
    Configurations for Query 7: Update Investment Amount
  */

  double follower_update_amount_probability;
  double leader_list_1_update_amount_probability;
  double leader_list_2_update_amount_probability;

  double follower_list_update_amount_power_dis_param;
  double leader_list_1_update_amount_power_dis_param;
  double leader_list_2_update_amount_power_dis_param;
};

struct transactional_query_8_config{
  /*
  Description:
    Configurations for Query 8: Remove Mirror Edge
  */

};

struct transactional_driver_config{
  /*
  Description:
    Configurations for the Transactional Query Driver
  */

  std::string server_ip_address;
  int server_port_number;

  int number_of_transactional_threads;

  bool is_freshness_score_calculation_active;

  bool enable_query_1A;
  bool enable_query_1B;
  bool enable_query_2;
  bool enable_query_3;
  bool enable_query_4;
  bool enable_query_5;
  bool enable_query_6;
  bool enable_query_7;
  bool enable_query_8;

  double query_1_A_probabilistic_weight;
  double query_1_B_probabilistic_weight;
  double query_2_probabilistic_weight;
  double query_3_probabilistic_weight;
  double query_4_probabilistic_weight;
  double query_5_probabilistic_weight;
  double query_6_probabilistic_weight;
  double query_7_probabilistic_weight;
  double query_8_probabilistic_weight;

  struct transactional_query_1_A_config query_1_A_configs;
  struct transactional_query_1_B_config query_1_B_configs;
  struct transactional_query_2_config query_2_configs;
  struct transactional_query_3_config query_3_configs;
  struct transactional_query_4_config query_4_configs;
  struct transactional_query_5_config query_5_configs;
  struct transactional_query_6_config query_6_configs;
  struct transactional_query_7_config query_7_configs;
  struct transactional_query_8_config query_8_configs;

  uint64_t end_warmup_timestamp;
  uint64_t end_data_collection_timestamp;

  unsigned long number_of_investors;
  unsigned long number_of_companies;
  unsigned long number_of_freshness_score_vertices;

  unsigned long remove_mirror_edge_list_length;

  unsigned long* follower_list;
  unsigned long* leader_list_1;
  unsigned long* leader_list_2;
  unsigned long* company_list;
  unsigned long* remove_mirror_edge_source_ID_list;
  unsigned long* remove_mirror_edge_destination_ID_list;

  std::string result_directory;

  unsigned long first_freshness_score_vertex_ID;
  unsigned long first_trade_vertex_ID;
};

namespace TQD_CONFIG{
  struct transactional_query_1_A_config read_transactional_query_1_A_configs(std::string);

  struct transactional_query_1_B_config read_transactional_query_1_B_configs(std::string);

  struct transactional_query_2_config read_transactional_query_2_configs(std::string);

  struct transactional_query_3_config read_transactional_query_3_configs(std::string);

  struct transactional_query_4_config read_transactional_query_4_configs(std::string);

  struct transactional_query_5_config read_transactional_query_5_configs(std::string);

  struct transactional_query_6_config read_transactional_query_6_configs(std::string);

  struct transactional_query_7_config read_transactional_query_7_configs(std::string);

  struct transactional_query_8_config read_transactional_query_8_configs(std::string);

  void read_vertex_list(std::string, unsigned long, int, unsigned long*);

  void read_remove_mirror_list(std::string, unsigned long*, unsigned long*, int);

  void read_transactional_query_driver_configs(struct transactional_driver_config*,
                                                std::string);
}

#endif
