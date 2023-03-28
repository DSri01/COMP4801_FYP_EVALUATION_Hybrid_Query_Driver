# FYP : 22013
# Description:
# 		Makefile for the Hybrid Query Driver

FLAGS = --std=c++11

QDC001_TQD_Config.o: configuration/QDC001_TQD_Config.cpp configuration/QDC001_TQD_Config.h
	g++ $(FLAGS) -c $<

QDC002_AQD_Config.o: configuration/QDC002_AQD_Config.cpp configuration/QDC002_AQD_Config.h
	g++ $(FLAGS) -c $<

QDU001_Time.o: utils/QDU001_Time.cpp utils/QDU001_Time.h
	g++ $(FLAGS) -c $<

QDU002_Random.o: utils/QDU002_Random.cpp utils/QDU002_Random.h QDC001_TQD_Config.o QDC002_AQD_Config.o
	g++ $(FLAGS) -c $<

QDC000_HQD_Config.o: configuration/QDC000_HQD_Config.cpp configuration/QDC000_HQD_Config.h QDC001_TQD_Config.o QDC002_AQD_Config.o QDU001_Time.o
	g++ $(FLAGS) -c $<

SSD000_server_skeleton_driver.o: server_skeleton_driver/SSD000_server_skeleton_driver.cpp server_skeleton_driver/SSD000_server_skeleton_driver.h
	g++ $(FLAGS) -c $<

#TRANSACTIONAL QUERY HANDLERS

TQD002_Query_1_A_Handler.o: transactional_query_driver/transactional_query_handlers/Query_1_A/TQD002_Query_1_A_Handler.cpp transactional_query_driver/transactional_query_handlers/Query_1_A/TQD002_Query_1_A_Handler.h QDU001_Time.o QDC001_TQD_Config.o QDU002_Random.o SSD000_server_skeleton_driver.o
	g++ $(FLAGS) -c $<

TQD004_Query_2_Handler.o: transactional_query_driver/transactional_query_handlers/Query_2/TQD004_Query_2_Handler.cpp transactional_query_driver/transactional_query_handlers/Query_2/TQD004_Query_2_Handler.h QDU001_Time.o QDC001_TQD_Config.o QDU002_Random.o SSD000_server_skeleton_driver.o
	g++ $(FLAGS) -c $<

TQD005_Query_3_Handler.o: transactional_query_driver/transactional_query_handlers/Query_3/TQD005_Query_3_Handler.cpp transactional_query_driver/transactional_query_handlers/Query_3/TQD005_Query_3_Handler.h QDU001_Time.o QDC001_TQD_Config.o QDU002_Random.o SSD000_server_skeleton_driver.o
	g++ $(FLAGS) -c $<

TQD006_Query_4_Handler.o: transactional_query_driver/transactional_query_handlers/Query_4/TQD006_Query_4_Handler.cpp transactional_query_driver/transactional_query_handlers/Query_4/TQD006_Query_4_Handler.h QDU001_Time.o QDC001_TQD_Config.o QDU002_Random.o SSD000_server_skeleton_driver.o
	g++ $(FLAGS) -c $<

TQD007_Query_5_Handler.o: transactional_query_driver/transactional_query_handlers/Query_5/TQD007_Query_5_Handler.cpp transactional_query_driver/transactional_query_handlers/Query_5/TQD007_Query_5_Handler.h QDU001_Time.o QDC001_TQD_Config.o QDU002_Random.o SSD000_server_skeleton_driver.o
	g++ $(FLAGS) -c $<

TQD008_Query_6_Handler.o: transactional_query_driver/transactional_query_handlers/Query_6/TQD008_Query_6_Handler.cpp transactional_query_driver/transactional_query_handlers/Query_6/TQD008_Query_6_Handler.h QDU001_Time.o QDC001_TQD_Config.o QDU002_Random.o SSD000_server_skeleton_driver.o
	g++ $(FLAGS) -c $<

TQD003_Query_1_B_Handler.o: transactional_query_driver/transactional_query_handlers/Query_1_B/TQD003_Query_1_B_Handler.cpp transactional_query_driver/transactional_query_handlers/Query_1_B/TQD003_Query_1_B_Handler.h QDU001_Time.o QDC001_TQD_Config.o QDU002_Random.o TQD005_Query_3_Handler.o TQD008_Query_6_Handler.o SSD000_server_skeleton_driver.o
	g++ $(FLAGS) -c $<

TQD009_Query_7_Handler.o: transactional_query_driver/transactional_query_handlers/Query_7/TQD009_Query_7_Handler.cpp transactional_query_driver/transactional_query_handlers/Query_7/TQD009_Query_7_Handler.h QDU001_Time.o QDC001_TQD_Config.o QDU002_Random.o SSD000_server_skeleton_driver.o
	g++ $(FLAGS) -c $<

TQD010_Query_8_Handler.o: transactional_query_driver/transactional_query_handlers/Query_8/TQD010_Query_8_Handler.cpp transactional_query_driver/transactional_query_handlers/Query_8/TQD010_Query_8_Handler.h QDU001_Time.o QDC001_TQD_Config.o QDU002_Random.o SSD000_server_skeleton_driver.o
	g++ $(FLAGS) -c $<

#TRANSACTIONAL DRIVER

TQD001_Transactional_Query_Driver.o: transactional_query_driver/TQD001_Transactional_Query_Driver.cpp transactional_query_driver/TQD001_Transactional_Query_Driver.h QDC001_TQD_Config.o QDU001_Time.o QDU002_Random.o TQD002_Query_1_A_Handler.o TQD003_Query_1_B_Handler.o TQD004_Query_2_Handler.o TQD005_Query_3_Handler.o TQD006_Query_4_Handler.o TQD007_Query_5_Handler.o TQD008_Query_6_Handler.o TQD009_Query_7_Handler.o TQD010_Query_8_Handler.o
	g++ $(FLAGS) -c $< -lpthread

#ANALYTICAL QUERY HANDLERS

AQD002_Query_1_Handler.o: analytical_query_driver/analytical_query_handlers/Query_1/AQD002_Query_1_Handler.cpp analytical_query_driver/analytical_query_handlers/Query_1/AQD002_Query_1_Handler.h QDC002_AQD_Config.o QDU001_Time.o QDU002_Random.o SSD000_server_skeleton_driver.o
	g++ $(FLAGS) -c $<

AQD003_Query_2_Handler.o: analytical_query_driver/analytical_query_handlers/Query_2/AQD003_Query_2_Handler.cpp analytical_query_driver/analytical_query_handlers/Query_2/AQD003_Query_2_Handler.h QDC002_AQD_Config.o QDU001_Time.o SSD000_server_skeleton_driver.o
	g++ $(FLAGS) -c $<

AQD004_Query_3_Handler.o: analytical_query_driver/analytical_query_handlers/Query_3/AQD004_Query_3_Handler.cpp analytical_query_driver/analytical_query_handlers/Query_3/AQD004_Query_3_Handler.h QDC002_AQD_Config.o QDU001_Time.o SSD000_server_skeleton_driver.o
	g++ $(FLAGS) -c $<

AQD005_Query_4_Handler.o: analytical_query_driver/analytical_query_handlers/Query_4/AQD005_Query_4_Handler.cpp analytical_query_driver/analytical_query_handlers/Query_4/AQD005_Query_4_Handler.h QDC002_AQD_Config.o QDU001_Time.o SSD000_server_skeleton_driver.o
	g++ $(FLAGS) -c $<

AQD006_Query_5_Handler.o: analytical_query_driver/analytical_query_handlers/Query_5/AQD006_Query_5_Handler.cpp analytical_query_driver/analytical_query_handlers/Query_5/AQD006_Query_5_Handler.h QDC002_AQD_Config.o QDU001_Time.o SSD000_server_skeleton_driver.o
	g++ $(FLAGS) -c $<

AQD007_Query_6_Handler.o: analytical_query_driver/analytical_query_handlers/Query_6/AQD007_Query_6_Handler.cpp analytical_query_driver/analytical_query_handlers/Query_6/AQD007_Query_6_Handler.h QDC002_AQD_Config.o QDU001_Time.o QDU002_Random.o SSD000_server_skeleton_driver.o
	g++ $(FLAGS) -c $<

AQD001_Analytical_Query_Driver.o: analytical_query_driver/AQD001_Analytical_Query_Driver.cpp analytical_query_driver/AQD001_Analytical_Query_Driver.h QDC002_AQD_Config.o QDU001_Time.o QDU002_Random.o AQD002_Query_1_Handler.o AQD003_Query_2_Handler.o AQD004_Query_3_Handler.o AQD005_Query_4_Handler.o AQD006_Query_5_Handler.o AQD007_Query_6_Handler.o
	g++ $(FLAGS) -c $< -lpthread

MQD000_Main_Query_Driver.o: MQD000_Main_Query_Driver.cpp MQD000_Main_Query_Driver.h QDU001_Time.o QDU002_Random.o QDC000_HQD_Config.o QDC001_TQD_Config.o QDC002_AQD_Config.o TQD002_Query_1_A_Handler.o TQD004_Query_2_Handler.o TQD005_Query_3_Handler.o TQD006_Query_4_Handler.o TQD007_Query_5_Handler.o TQD008_Query_6_Handler.o TQD003_Query_1_B_Handler.o TQD009_Query_7_Handler.o TQD010_Query_8_Handler.o TQD001_Transactional_Query_Driver.o AQD002_Query_1_Handler.o AQD003_Query_2_Handler.o AQD004_Query_3_Handler.o AQD005_Query_4_Handler.o AQD006_Query_5_Handler.o AQD007_Query_6_Handler.o AQD001_Analytical_Query_Driver.o SSD000_server_skeleton_driver.o
	g++ $(FLAGS) -c $< -lpthread

main_driver: MQD000_Main_Query_Driver.o QDU001_Time.o QDU002_Random.o QDC000_HQD_Config.o QDC001_TQD_Config.o QDC002_AQD_Config.o TQD002_Query_1_A_Handler.o TQD004_Query_2_Handler.o TQD005_Query_3_Handler.o TQD006_Query_4_Handler.o TQD007_Query_5_Handler.o TQD008_Query_6_Handler.o TQD003_Query_1_B_Handler.o TQD009_Query_7_Handler.o TQD010_Query_8_Handler.o TQD001_Transactional_Query_Driver.o AQD002_Query_1_Handler.o AQD003_Query_2_Handler.o AQD004_Query_3_Handler.o AQD005_Query_4_Handler.o AQD006_Query_5_Handler.o AQD007_Query_6_Handler.o AQD001_Analytical_Query_Driver.o SSD000_server_skeleton_driver.o
	g++ $(FLAGS) $^ -o $@ -lpthread

clean_o:
	rm -f *.o

clean:
	rm main_driver && make clean_o

.PHONY: clean_o, clean
