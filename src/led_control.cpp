/**
 * @file led_control.cpp
 * @brief LED 控制模块实现文件
 */

#include "led_control.h"
#include "config.h"
#include <STM32FreeRTOS.h>

// ==================== 全局变量定义 ====================

FlowDirection g_flowDirection = FLOW_STOP;
BlinkState g_blinkState = BLINK_OFF;
uint32_t g_flowDelay = DEFAULT_FLOW_DELAY;
uint32_t g_blinkDelay = DEFAULT_BLINK_DELAY;

// ==================== LED 初始化函数 ====================

void initLEDs() {
    // 初始化led引脚为输出模式
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);
    pinMode(LED3_PIN, OUTPUT);
    pinMode(LED4_PIN, OUTPUT);
    pinMode(LED5_PIN, OUTPUT);
    pinMode(LED6_PIN, OUTPUT);
    pinMode(LED7_PIN, OUTPUT);
    pinMode(LED8_PIN, OUTPUT);
    
    // 初始化时关闭所有LED
    turnOffAllLEDs();
}

// ==================== LED 流水灯控制函数 ====================

void setFlowDirection(FlowDirection direction) {
    // TODO: 设置流水灯方向
    g_flowDirection = direction;
    
    // 如果停止流水,关闭流水灯
    if (direction == FLOW_STOP) {
        turnOffFlowLEDs();
    }
}

void setFlowDelay(uint32_t delay_ms) {
    // TODO: 设置流水灯延时时间
    g_flowDelay = delay_ms;
}

void taskFlowLED(void *pvParameters) {
    // 实现流水灯任务逻辑
    (void)pvParameters;// 这玩意儿没啥用，当放屁好了
    
    for (;;) {
        // 检查流水灯方向并执行相应动作
        if (g_flowDirection == FLOW_FORWARD) {
            flowForward();
        } else if (g_flowDirection == FLOW_BACKWARD) {
            flowBackward();
        } else {
            // 如果是停止状态,短延时避免占用CPU
            vTaskDelay(pdMS_TO_TICKS(50));
        }
    }
}

void flowForward() {
    // 实现从 LED1 到 LED4 的流水效果
    digitalWrite(LED1_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(g_flowDelay));
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(g_flowDelay));
    digitalWrite(LED2_PIN, LOW);
    digitalWrite(LED3_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(g_flowDelay));
    digitalWrite(LED3_PIN, LOW);
    digitalWrite(LED4_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(g_flowDelay));
    digitalWrite(LED4_PIN, LOW);
}

void flowBackward() {
    // 实现从 LED4 到 LED1 的流水效果
    digitalWrite(LED4_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(g_flowDelay));
    digitalWrite(LED4_PIN, LOW);
    digitalWrite(LED3_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(g_flowDelay));
    digitalWrite(LED3_PIN, LOW);
    digitalWrite(LED2_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(g_flowDelay));
    digitalWrite(LED2_PIN, LOW);
    digitalWrite(LED1_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(g_flowDelay));
    digitalWrite(LED1_PIN, LOW);
    
}

void turnOffFlowLEDs() {
    // 关闭 LED1-LED4
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, LOW);
    digitalWrite(LED3_PIN, LOW);
    digitalWrite(LED4_PIN, LOW);
}

// ==================== LED 闪烁灯控制函数 ====================

void setBlinkState(BlinkState state) {
    // TODO: 设置闪烁灯状态
    g_blinkState = state;
    
    // 如果关闭闪烁,关闭闪烁灯
    if (state == BLINK_OFF) {
        turnOffBlinkLEDs();
    }
}

void setBlinkDelay(uint32_t delay_ms) {
    // TODO: 设置闪烁灯延时时间
    g_blinkDelay = delay_ms;
}

void taskBlinkLED(void *pvParameters) {
    // 实现闪烁灯任务逻辑
    (void)pvParameters;
    
    for (;;) {
        // 检查闪烁灯状态
        if (g_blinkState == BLINK_ON) {
            toggleBlinkLEDs();
            vTaskDelay(pdMS_TO_TICKS(g_blinkDelay));
        } else {
            // 如果关闭状态,短延时避免占用CPU
            vTaskDelay(pdMS_TO_TICKS(50));
        }
    }
}

void toggleBlinkLEDs() {
    // 切换 LED5-LED8 的状态
    static bool ledState = false;
    
    ledState = !ledState;
    
    // 同时切换所有闪烁灯
    digitalWrite(LED5_PIN, ledState ? HIGH : LOW);
    digitalWrite(LED6_PIN, ledState ? HIGH : LOW);
    digitalWrite(LED7_PIN, ledState ? HIGH : LOW);
    digitalWrite(LED8_PIN, ledState ? HIGH : LOW);
}

void turnOffBlinkLEDs() {
    // 关闭 LED5-LED8
    digitalWrite(LED5_PIN, LOW);
    digitalWrite(LED6_PIN, LOW);
    digitalWrite(LED7_PIN, LOW);
    digitalWrite(LED8_PIN, LOW);
}

// ==================== 通用控制函数 ====================

void turnOffAllLEDs() {
    // 关闭所有 LED
    turnOffFlowLEDs();
    turnOffBlinkLEDs();
}
