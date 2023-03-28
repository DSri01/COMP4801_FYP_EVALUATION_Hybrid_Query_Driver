/*
FYP : 22013

Module:
    Hybrid Query Driver - Query Driver Utilities

Description:
    Defines the random-sampling-related utilities of the Hybrid Query Driver,
    which are used across the benchmarking system..
*/

#include "QDU002_Random.h"

/*
Description:
    Provides a common method to generate samples from the uniform distribution
    across the benchmarking system.
*/
double generate_uniform_distribution_sample(double start, double end) {
  std::random_device generator;
  std::uniform_real_distribution<double> distribution(start, end);
  double uniform_distribution_sample = distribution(generator);
  return uniform_distribution_sample;
}

/*
Description:
    Provides a common method to generate samples from the power distribution
    across the benchmarking system.
*/
double generate_power_distribution_sample(double distribution_parameter) {
  double uni_sample = generate_uniform_distribution_sample(0.0, 1.0);

  // Power distribution sample between 0 and 1: uni_sample ^ (1/distribution_parameter)
  double power_distribution_sample_between_0_and_1 = pow(uni_sample, 1 / distribution_parameter);

  return power_distribution_sample_between_0_and_1;
}

/*
Description:
    Provides a common method to generate IDs from the list using IIDILS
    across the benchmarking system.
*/
unsigned long generate_power_distribution_ID_sample(unsigned long start_ID, unsigned long number_of_elements, double distribution_parameter) {
  double power_distribution_sample_between_0_and_1 = generate_power_distribution_sample(distribution_parameter);

  unsigned long generated_ID = power_distribution_sample_between_0_and_1 * (number_of_elements) + start_ID;

  if (generated_ID > start_ID + number_of_elements - 1) {
    generated_ID = start_ID + number_of_elements - 1;
  }

  return generated_ID;
}

/*
Description:
    Provides a common method to generate ID samples from the list using IIDILS
    without replacement across the benchmarking system.
*/
void sample_without_replacement_power_distribution_ID_samples(unsigned long number_of_elements, double distribution_parameter, unsigned long* list_pointer, int list_length) {
  std::unordered_set <unsigned long> selected_items_set;
  int count_generated = 0;
  while (count_generated < list_length){
    unsigned long sampled_element = generate_power_distribution_ID_sample(0, number_of_elements, distribution_parameter);
    if (selected_items_set.find(sampled_element) == selected_items_set.end()) {
      //item has not been selected so far
      selected_items_set.insert(sampled_element);
      list_pointer[count_generated] = sampled_element;
      count_generated++;
    }
  }
}

/*
Description:
    Provides a common method to generate IDs from the list using IIDILS after
    selecting the investor list to use using the discrete probability
    distribution provided by the probability weight for each investor list for
    the transactional query driver.
*/
unsigned long sample_from_3_investor_lists(double follower_list_prob_weight,
                                            double leader_list_1_prob_weight,
                                            double leader_list_2_prob_weight,
                                            double follower_list_dis_param,
                                            double leader_list_1_dis_param,
                                            double leader_list_2_dis_param,
                                            struct transactional_driver_config* config) {

  double total_prob_weight = follower_list_prob_weight
                            + leader_list_1_prob_weight
                            + leader_list_2_prob_weight;

  double select_investor_list_random = generate_uniform_distribution_sample(0, total_prob_weight);

  if (select_investor_list_random <= follower_list_prob_weight) {
    //select from follower list
    unsigned long list_index = generate_power_distribution_ID_sample(0,
                                                                    config->number_of_investors,
                                                                    follower_list_dis_param);
    return config->follower_list[list_index];
  }
  else if (select_investor_list_random <= follower_list_prob_weight + leader_list_1_prob_weight) {
    //select from leader_list_1
    unsigned long list_index = generate_power_distribution_ID_sample(0,
                                                                    config->number_of_investors,
                                                                    leader_list_1_dis_param);
    return config->leader_list_1[list_index];
  }
  else {
    //select from leader_list_2
    unsigned long list_index = generate_power_distribution_ID_sample(0,
                                                                    config->number_of_investors,
                                                                    leader_list_2_dis_param);
    return config->leader_list_2[list_index];
  }
}

/*
Description:
    Provides a common method to generate IDs from the list using IIDILS after
    selecting the investor list to use using the discrete probability
    distribution provided by the probability weight for each investor list for
    the analytical query driver.
*/
unsigned long sample_from_3_investor_lists(double follower_list_prob_weight,
                                            double leader_list_1_prob_weight,
                                            double leader_list_2_prob_weight,
                                            double follower_list_dis_param,
                                            double leader_list_1_dis_param,
                                            double leader_list_2_dis_param,
                                            struct analytical_driver_config* config) {

  double total_prob_weight = follower_list_prob_weight
                            + leader_list_1_prob_weight
                            + leader_list_2_prob_weight;

  double select_investor_list_random = generate_uniform_distribution_sample(0, total_prob_weight);

  if (select_investor_list_random <= follower_list_prob_weight) {
    //select from follower list
    unsigned long list_index = generate_power_distribution_ID_sample(0,
                                                                    config->number_of_investors,
                                                                    follower_list_dis_param);
    return config->follower_list[list_index];
  }
  else if (select_investor_list_random <= follower_list_prob_weight + leader_list_1_prob_weight) {
    //select from leader_list_1
    unsigned long list_index = generate_power_distribution_ID_sample(0,
                                                                    config->number_of_investors,
                                                                    leader_list_1_dis_param);
    return config->leader_list_1[list_index];
  }
  else {
    //select from leader_list_2
    unsigned long list_index = generate_power_distribution_ID_sample(0,
                                                                    config->number_of_investors,
                                                                    leader_list_2_dis_param);
    return config->leader_list_2[list_index];
  }
}
