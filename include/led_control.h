/**
 * @file led_control.h
 * @brief LED 控制模块头文件
 */

#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include <Arduino.h>

// ==================== LED 控制枚举 ====================

// 流水灯方向
enum FlowDirection {
    FLOW_FORWARD,   // 从LED1到LED4
    FLOW_BACKWARD,  // 从LED4到LED1
    FLOW_STOP       // 停止流水
};

// 闪烁灯状态
enum BlinkState {
    BLINK_ON,       // 闪烁开启
    BLINK_OFF       // 闪烁关闭
};

// ==================== 全局变量声明 ====================

extern FlowDirection g_flowDirection;
extern BlinkState g_blinkState;
extern uint32_t g_flowDelay;
extern uint32_t g_blinkDelay;

// ==================== LED 初始化函数 ====================

/**
 * @brief 初始化所有 LED 引脚
 */
void initLEDs();

// ==================== LED 流水灯控制函数 ====================

/**
 * @brief 设置流水灯方向
 * @param direction 流水方向 (FLOW_FORWARD/FLOW_BACKWARD/FLOW_STOP)
 */
void setFlowDirection(FlowDirection direction);

/**
 * @brief 设置流水灯延时
 * @param delay_ms 延时时间(毫秒)
 */
void setFlowDelay(uint32_t delay_ms);

/**
 * @brief 流水灯任务函数 - 在这里实现流水灯逻辑
 * @param pvParameters FreeRTOS 任务参数
 */
void taskFlowLED(void *pvParameters);

/**
 * @brief 执行一次流水灯向前流动
 * TODO: 实现 LED1->LED2->LED3->LED4 的流水效果
 */
void flowForward();

/**
 * @brief 执行一次流水灯向后流动
 * TODO: 实现 LED4->LED3->LED2->LED1 的流水效果
 */
void flowBackward();

/**
 * @brief 关闭所有流水灯 (LED1-LED4)
 */
void turnOffFlowLEDs();

// ==================== LED 闪烁灯控制函数 ====================

/**
 * @brief 设置闪烁灯状态
 * @param state 闪烁状态 (BLINK_ON/BLINK_OFF)
 */
void setBlinkState(BlinkState state);

/**
 * @brief 设置闪烁灯延时
 * @param delay_ms 延时时间(毫秒)
 */
void setBlinkDelay(uint32_t delay_ms);

/**
 * @brief 闪烁灯任务函数 - 在这里实现闪烁灯逻辑
 * @param pvParameters FreeRTOS 任务参数
 */
void taskBlinkLED(void *pvParameters);

/**
 * @brief 切换闪烁灯状态
 * TODO: 实现 LED5-LED8 同时开/关切换
 */
void toggleBlinkLEDs();

/**
 * @brief 关闭所有闪烁灯 (LED5-LED8)
 */
void turnOffBlinkLEDs();

// ==================== 通用控制函数 ====================

/**
 * @brief 关闭所有 LED (LED1-LED8)
 */
void turnOffAllLEDs();

#endif
