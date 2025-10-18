/**
 * @file config.h
 * @brief 项目配置文件 - 引脚定义和全局配置
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ==================== 引脚定义 ====================

// LED 引脚定义 (LED1-LED8)
#define LED1_PIN    PA0
#define LED2_PIN    PA1
#define LED3_PIN    PA2
#define LED4_PIN    PA3
#define LED5_PIN    PA4
#define LED6_PIN    PA5
#define LED7_PIN    PA6
#define LED8_PIN    PA7

// 按键引脚定义 (B1-B4)
#define BUTTON1_PIN PB0   // 控制流水灯从1流至4
#define BUTTON2_PIN PB1   // 控制流水灯从4流至1
#define BUTTON3_PIN PB2   // LED5-8开始闪烁
#define BUTTON4_PIN PB3   // 关闭LED5-8闪烁

// ==================== 全局配置 ====================

// 串口波特率
#define SERIAL_BAUDRATE 115200

// 默认延时时间 (毫秒)
#define DEFAULT_FLOW_DELAY  300   // 流水灯默认延时
#define DEFAULT_BLINK_DELAY 500   // 闪烁灯默认延时

// 按键防抖延时 (毫秒)
#define BUTTON_DEBOUNCE_DELAY 50

// FreeRTOS 任务优先级
#define TASK_PRIORITY_BUTTON    2
#define TASK_PRIORITY_SERIAL    2
#define TASK_PRIORITY_FLOW      1
#define TASK_PRIORITY_BLINK     1

// FreeRTOS 任务栈大小
#define TASK_STACK_SIZE_BUTTON  256
#define TASK_STACK_SIZE_SERIAL  512
#define TASK_STACK_SIZE_FLOW    256
#define TASK_STACK_SIZE_BLINK   256

#endif