/*
 * mainpp.h
 *
 *  Created on: 2018/01/17
 *      Author: yoneken
 */

#ifndef MAINPP_H_
#define MAINPP_H_

#include "std_msgs/Int32.h"


#ifdef __cplusplus
 extern "C" {
#endif


void setup(void);
void loop(void);
//void command_cb(const std_msgs::Int16&);
void read_position_cb(const std_msgs::Int32&);
void PID_position_control_cb(void);


#ifdef __cplusplus
}
#endif


#endif /* MAINPP_H_ */
