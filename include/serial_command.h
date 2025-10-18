/**
 * @file serial_command.h
 * @brief 串口命令处理模块头文件
 */

#ifndef SERIAL_COMMAND_H
#define SERIAL_COMMAND_H

#include <Arduino.h>

// ==================== 串口初始化函数 ====================

/**
 * @brief 初始化串口
 */
void initSerial();

// ==================== 串口任务函数 ====================

/**
 * @brief 串口命令处理任务
 * @param pvParameters FreeRTOS 任务参数
 */
void taskSerialCommand(void *pvParameters);

// ==================== 命令处理函数 ====================

/**
 * @brief 处理接收到的串口命令
 * @param command 命令字符串
 * TODO: 解析并执行命令
 */
void processCommand(String command);

/**
 * @brief 处理 "OFF" 命令 - 关闭所有灯
 * TODO: 调用关闭所有LED的函数,返回确认信息
 */
void handleCommandOff();

/**
 * @brief 处理 "flow" 命令 - 启动流水灯
 * TODO: 启动LED1-4流水灯,返回 "flow ok"
 */
void handleCommandFlow();

/**
 * @brief 处理 "blink" 命令 - 启动闪烁灯
 * TODO: 启动LED5-8闪烁,返回 "blink ok"
 */
void handleCommandBlink();

/**
 * @brief 处理 "flow XXX" 命令 - 修改流水频率
 * @param delay_ms 延时时间(毫秒)
 * TODO: 设置流水灯延时,返回 "Order ok"
 */
void handleCommandFlowDelay(uint32_t delay_ms);

/**
 * @brief 处理 "blink XXX" 命令 - 修改闪烁频率
 * @param delay_ms 延时时间(毫秒)
 * TODO: 设置闪烁灯延时,返回 "Order ok"
 */
void handleCommandBlinkDelay(uint32_t delay_ms);

/**
 * @brief 处理 "meanwhile blink flow" 命令 - 同时启动流水和闪烁
 * TODO: 同时启动流水灯和闪烁灯,返回 "meanwhile ok"
 */
void handleCommandMeanwhile();

// ==================== 辅助函数 ====================

/**
 * @brief 发送串口响应
 * @param response 响应字符串
 */
void sendResponse(const char* response);

/**
 * @brief 去除字符串首尾空格
 * @param str 输入字符串
 * @return 去除空格后的字符串
 */
String trimString(String str);

#endif
