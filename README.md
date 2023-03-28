# COMP4801_FYP_EVALUATION_Hybrid_Query_Driver

## FYP: 22013

### FYP Team

**Student:** SRIVASTAVA Dhruv (3035667792)

**Supervisor:** Dr. Heming Cui

## Description

Hybrid Query Driver for HTAP Graph Database Benchmark edited for the evaluation
phase of the project to work in conjunction with the Server Skeleton
```https://github.com/DSri01/COMP4801_FYP_Server_Skeleton```. Some additional
adjustments were made to the original *Hybrid Query Driver* (```https://github.com/DSri01/COMP4801_FYP_Hybrid_Query_Driver```)
to ensure compatibility with the Server Skeleton and other software modules
during the evaluation phase of the project, please refer to the final report for
these details.

## Usage Instructions

### Building the executable

Download the ```json.hpp``` file from ```https://github.com/nlohmann/json/releases/tag/v3.11.2```
and put it in the ```third_party``` folder.

The following libraries/compilers were used during development:

- nlohmann json (v3.11.2)
- g++ (version 9.3.0)

Build the executable using ```make main_driver``` command.

### Executing the Hybrid Query Driver

The ```main_driver``` executable takes a JSON configuration file as a command line
argument.

A helper python script ```build_config.py``` has been provided to generate the
configuration file. Usage: ```python3 build_config.py <name of the config file>```.


## Module Descriptions

The Hybrid Query Driver is built from the modules listed in the table below.

| Module Name | Description | Directory |
|-------------|-------------|-----------|
|AQD|This module deals with the Analytical Query Driver and its query handlers|analytical_query_driver/|
|MQD|This module deals with bringing the Transactional and Analytical Query Drivers together|./|
|QDC|This module deals with the configuration of the query drivers|configuration/|
|QDU|This module contains utility functions used across the benchmark|utils/|
|TQD|This module deals with the Transactional Query Driver and its query handlers| transactional_query_driver/|
|SSD|This module is the driver for the *Server Skeleton* and allows the *Hybrid Query Driver* to interact with the server skeleton during evaluation|server_skeleton_driver/|
