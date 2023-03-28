/*
FYP : 22013

Module:
    Hybrid Query Driver - Query Driver Utilities

Description:
    Header file for the random-sampling-related utility of the Hybrid Query
    Driver
*/
#include "../configuration/QDC001_TQD_Config.h"
#include "../configuration/QDC002_AQD_Config.h"

#include <cmath>
#include <random>
#include <unordered_set>

#ifndef QDU002_RANDOM_H
#define QDU002_RANDOM_H

double generate_uniform_distribution_sample(double, double);

double generate_power_distribution_sample(double);

unsigned long generate_power_distribution_ID_sample(unsigned long, unsigned long, double);

void sample_without_replacement_power_distribution_ID_samples(unsigned long, double, unsigned long*, int);

unsigned long sample_from_3_investor_lists(double, double, double, double, double, double, struct transactional_driver_config*);

unsigned long sample_from_3_investor_lists(double, double, double, double, double, double, struct analytical_driver_config*);

#endif
