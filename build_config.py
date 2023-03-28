"""
FYP : 22013

Module:
    Hybrid Query Driver

Description:
    This python script is a supporting script to generate the JSON configuration
    file for the Hybrid Query Driver.
"""

import json
import sys

configs = {}

configs["IP_ADDRESS"] = "127.0.0.1"
configs["PORT_NUMBER"] = 12560

configs["experiment_mode"] = "HYBRID"
configs["warm_up_duration"] = 10000
configs["data_collection_duration"] = 10000
configs["number_of_analytical_threads"] = 4
configs["number_of_transactional_threads"] = 4
configs["enable_freshness_score"] = False


configs["number_of_investors"] = 10000
configs["number_of_companies"] = 2000
configs["number_of_freshness_score_vertices"] = 10000
configs["remove_mirror_edge_list_length"] = 143
configs["follower_list_file_name"] = "Data/FollowerList.txt"
configs["leader_list_1_file_name"] = "Data/LeaderList1.txt"
configs["leader_list_2_file_name"] = "Data/LeaderList2.txt"
configs["company_list_file_name"] = "Data/CompanyList.txt"
configs["remove_mirror_edges_file_name"] = "Data/RemoveMirrorEdges.csv"

configs["freshness_score_results_directory"] = "Freshness_Score_Output/"


#TRANSACTIONAL DRIVER SETTINGS

configs["enable_transactional_query_1_A"] = True
configs["enable_transactional_query_1_B"] = True
configs["enable_transactional_query_2"] = True
configs["enable_transactional_query_3"] = True
configs["enable_transactional_query_4"] = True
configs["enable_transactional_query_5"] = True
configs["enable_transactional_query_6"] = True
configs["enable_transactional_query_7"] = True
configs["enable_transactional_query_8"] = True

configs["transactional_query_1_A_probabilistic_weight"] = 1/9
configs["transactional_query_1_B_probabilistic_weight"] = 1/9
configs["transactional_query_2_probabilistic_weight"] = 1/9
configs["transactional_query_3_probabilistic_weight"] = 1/9
configs["transactional_query_4_probabilistic_weight"] = 1/9
configs["transactional_query_5_probabilistic_weight"] = 1/9
configs["transactional_query_6_probabilistic_weight"] = 1/9
configs["transactional_query_7_probabilistic_weight"] = 1/9
configs["transactional_query_8_probabilistic_weight"] = 1/9


#ANALYTICAL DRIVER SETTINGS

configs["enable_analytical_query_1"] = True
configs["enable_analytical_query_2"] = True
configs["enable_analytical_query_3"] = True
configs["enable_analytical_query_4"] = True
configs["enable_analytical_query_5"] = True
configs["enable_analytical_query_6"] = True


configs["analytical_query_1_probabilistic_weight"] = 1/6
configs["analytical_query_2_probabilistic_weight"] = 1/6
configs["analytical_query_3_probabilistic_weight"] = 1/6
configs["analytical_query_4_probabilistic_weight"] = 1/6
configs["analytical_query_5_probabilistic_weight"] = 1/6
configs["analytical_query_6_probabilistic_weight"] = 1/6


#TRANSACTIONAL QUERY SETTINGS

#TQ_1_A
configs["TQD_query_1_A_follower_is_original_investor_probability"] = 1/3
configs["TQD_query_1_A_leader_list_1_is_original_investor_probability"] = 1/3
configs["TQD_query_1_A_leader_list_2_is_original_investor_probability"] = 1/3
configs["TQD_query_1_A_follower_list_original_investor_power_dis_param"] = 10
configs["TQD_query_1_A_leader_list_1_original_investor_power_dis_param"] = 8
configs["TQD_query_1_A_leader_list_2_original_investor_power_dis_param"] = 9
configs["TQD_query_1_A_company_trade_power_dis_param"] = 3
configs["TQD_query_1_A_max_number_of_companies_traded"] = 5

#TQ_1_B
configs["TQD_query_1_B_follower_is_copier_investor_probability"] = 95/100
configs["TQD_query_1_B_leader_list_1_is_copier_investor_probability"] = 4/100
configs["TQD_query_1_B_leader_list_2_is_copier_investor_probability"] = 1/100
configs["TQD_query_1_B_follower_list_copier_investor_power_dis_param"] = 10
configs["TQD_query_1_B_leader_list_1_copier_investor_power_dis_param"] = 8
configs["TQD_query_1_B_leader_list_2_copier_investor_power_dis_param"] = 9
configs["TQD_query_1_B_copy_from_leader_list_1_probability"] = 28/100
configs["TQD_query_1_B_copy_from_leader_list_2_probability"] = 70/100
configs["TQD_query_1_B_copy_a_friend_probability"] = 2/100
configs["TQD_query_1_B_leader_list_1_to_copy_power_dis_param"] = 5
configs["TQD_query_1_B_leader_list_2_to_copy_power_dis_param"] = 4

#TQ_2
configs["TQD_query_2_read_follower_profile_probability"] = 5/100
configs["TQD_query_2_read_leader_list_1_profile_probability"] = 49/100
configs["TQD_query_2_read_leader_list_2_profile_probability"] = 46/100
configs["TQD_query_2_follower_list_investor_profile_power_dis_param"] = 10
configs["TQD_query_2_leader_list_1_investor_profile_power_dis_param"] = 8
configs["TQD_query_2_leader_list_2_investor_profile_power_dis_param"] = 9

#TQ_3
configs["TQD_query_3_read_follower_trade_probability"] = 5/100
configs["TQD_query_3_read_leader_list_1_trade_probability"] = 49/100
configs["TQD_query_3_read_leader_list_2_trade_probability"] = 46/100
configs["TQD_query_3_follower_list_read_trade_power_dis_param"] = 10
configs["TQD_query_3_leader_list_1_read_trade_power_dis_param"] = 8
configs["TQD_query_3_leader_list_2_read_trade_power_dis_param"] = 9

#TQ_4
configs["TQD_query_4_company_read_power_dis_param"] = 5

#TQ_5
configs["TQD_query_5_read_follower_mirrorers_probability"] = 5/100
configs["TQD_query_5_read_leader_list_1_mirrorers_probability"] = 50/100
configs["TQD_query_5_read_leader_list_2_mirrorers_probability"] = 45/100
configs["TQD_query_5_follower_list_read_mirrorers_power_dis_param"] = 10
configs["TQD_query_5_leader_list_1_read_mirrorers_power_dis_param"] = 8
configs["TQD_query_5_leader_list_2_read_mirrorers_power_dis_param"] = 9

#TQ_6
configs["TQD_query_6_read_follower_friend_trade_probability"] = 25/100
configs["TQD_query_6_read_leader_list_1_friend_trade_probability"] = 45/100
configs["TQD_query_6_read_leader_list_2_friend_trade_probability"] = 30/100
configs["TQD_query_6_follower_list_read_friend_trade_power_dis_param"] = 10
configs["TQD_query_6_leader_list_1_read_friend_trade_power_dis_param"] = 8
configs["TQD_query_6_leader_list_2_read_friend_trade_power_dis_param"] = 9

#TQ_7
configs["TQD_query_7_follower_update_amount_probability"] = 30/100
configs["TQD_query_7_leader_list_1_update_amount_probability"] = 40/100
configs["TQD_query_7_leader_list_2_update_amount_probability"] = 30/100
configs["TQD_query_7_follower_list_update_amount_power_dis_param"] = 10
configs["TQD_query_7_leader_list_1_update_amount_power_dis_param"] = 8
configs["TQD_query_7_leader_list_2_update_amount_power_dis_param"] = 9


# ANALYTICAL QUERY SETTINGS

#AQ_1
configs["AQD_query_1_follower_is_bfs_root_probability"] = 1/3
configs["AQD_query_1_leader_list_1_is_bfs_root_probability"] = 1/3
configs["AQD_query_1_leader_list_2_is_bfs_root_probability"] = 1/3
configs["AQD_query_1_follower_list_bfs_root_power_dis_param"] = 10
configs["AQD_query_1_leader_list_1_bfs_root_power_dis_param"] = 8
configs["AQD_query_1_leader_list_2_bfs_root_power_dis_param"] = 9

#AQ_2
configs["AQD_query_2_pr_max_iterations"] = 10000
configs["AQD_query_2_pr_damping_factor"] = 0.85

#AQ_3
configs["AQD_query_5_cdlp_max_iterations"] = 10000

#AQ_6
configs["AQD_query_6_follower_is_sssp_root_probability"] = 1/3
configs["AQD_query_6_leader_list_1_is_sssp_root_probability"] = 1/3
configs["AQD_query_6_leader_list_2_is_sssp_root_probability"] = 1/3
configs["AQD_query_6_follower_list_sssp_root_power_dis_param"] = 10
configs["AQD_query_6_leader_list_1_sssp_root_power_dis_param"] = 8
configs["AQD_query_6_leader_list_2_sssp_root_power_dis_param"] = 9

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage:", sys.argv[0],"<destination JSON file name>")
    else:
        with open(sys.argv[1], 'w') as file:
            file.write(json.dumps(configs))
            file.close()
