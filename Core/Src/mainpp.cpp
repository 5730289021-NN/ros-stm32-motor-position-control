/*
 * mainpp.cpp
 *
 *  Created on: May 1, 2020
 *      Author: carls
 */

#include <mainpp.h>
#include <ros.h>
#include <std_msgs/Int32.h>
//#include <std_msgs/Int16.h>

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim16;
extern TIM_HandleTypeDef htim6;

ros::NodeHandle nh;

//uint16_t pwm_cmd = 0;
//bool direction = false;
int32_t error_angle = 0;
int32_t error_angle_sum = 0;

int32_t desired_position = 0;
float Kp = 500;//240 Overdamped, 500 Underdamped
float Ki = 0;
float Kd = 0;

//std_msgs::Int32 encoder_msg;
//ros::Publisher encoder_publisher("encoder", &encoder_msg);
//ros::Subscriber<std_msgs::Int16> cmd_subscriber("command", &command_cb);
ros::Subscriber<std_msgs::Int32> position_subscriber("position", &read_position_cb);
std_msgs::Int32 error_msg;
ros::Publisher error_publisher("error", &error_msg);

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
  nh.getHardware()->flush();
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
  nh.getHardware()->reset_rbuf();
}

void read_position_cb(const std_msgs::Int32& desired_position_msg){
	desired_position = desired_position_msg.data;
}

//void command_cb(const std_msgs::Int16& cmd_msg){
//	direction = cmd_msg.data >= 0;
//	pwm_cmd = abs(cmd_msg.data);
//	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
//}

void PID_position_control_cb() {
	int32_t error_angle_diff = desired_position - TIM2->CNT - error_angle;
	error_angle = desired_position - TIM2->CNT;
	error_angle_sum += error_angle;

	int32_t effort_voltage = Kp * error_angle + Ki * error_angle_sum * Kd * error_angle_diff;
	GPIOA->ODR = effort_voltage >= 0 ? 0x20:0x10; //Control Direction
	effort_voltage = abs(effort_voltage) > 3200 ? 3200:abs(effort_voltage); //Limit Pulse not beyond than 3200(ARR + 1)
	TIM16->CCR1 = effort_voltage;
}

void setup(void)
{
	nh.initNode();
	//nh.advertise(encoder_publisher);
	//nh.subscribe(cmd_subscriber);
	nh.advertise(error_publisher);
	nh.subscribe(position_subscriber);

	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
	HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);
	HAL_TIM_Base_Start_IT(&htim6);
}

void loop(void)
{
	/*
	GPIOA->ODR = direction ? 0x10:0x20;
	TIM16->CCR1 = pwm_cmd;
	encoder_msg.data = TIM2->CNT;
	encoder_publisher.publish(&encoder_msg);
	*/
	error_msg.data = error_angle;
	error_publisher.publish(&error_msg);

	nh.spinOnce();
	HAL_Delay(100); //
}
