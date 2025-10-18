/**
 * @file button_control.h
 * @brief 按键控制模块头文件
 */

#ifndef BUTTON_CONTROL_H
#define BUTTON_CONTROL_H

#include <Arduino.h>

// ==================== 按键初始化函数 ====================

/**
 * @brief 初始化所有按键引脚
 */
void initButtons();

// ==================== 按键任务函数 ====================

/**
 * @brief 按键扫描任务 - 在这里实现按键检测逻辑
 * @param pvParameters FreeRTOS 任务参数
 */
void taskButtonScan(void *pvParameters);

// ==================== 按键处理函数 ====================

/**
 * @brief 处理按键1按下 - 控制流水灯从1流至4
 * TODO: 调用相应的LED控制函数
 */
void handleButton1Press();

/**
 * @brief 处理按键2按下 - 控制流水灯从4流至1
 * TODO: 调用相应的LED控制函数
 */
void handleButton2Press();

/**
 * @brief 处理按键3按下 - LED5-8开始闪烁
 * TODO: 调用相应的LED控制函数
 */
void handleButton3Press();

/**
 * @brief 处理按键4按下 - 关闭LED5-8闪烁
 * TODO: 调用相应的LED控制函数
 */
void handleButton4Press();

// ==================== 按键读取函数 ====================

/**
 * @brief 读取按键状态(带防抖)
 * @param pin 按键引脚
 * @return true 按键按下, false 按键未按下
 * TODO: 实现按键防抖逻辑
 */
bool readButtonWithDebounce(uint8_t pin);

#endif
