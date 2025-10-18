/**
 * @file main.cpp
 * @brief 主程序文件 - LED控制系统
 * 
 * 功能说明:
 * 1. 按键控制:
 *    - B1: 流水灯从LED1流至LED4
 *    - B2: 流水灯从LED4流至LED1
 *    - B3: LED5-8开始闪烁
 *    - B4: 关闭LED5-8闪烁
 * 
 * 2. 串口命令:
 *    - OFF: 关闭所有灯
 *    - flow: 启动流水灯,返回"flow ok"
 *    - blink: 启动闪烁灯,返回"blink ok"
 *    - flow XXX: 修改流水频率,返回"Order ok"
 *    - blink XXX: 修改闪烁频率,返回"Order ok"
 *    - meanwhile blink flow: 同时启动流水和闪烁,返回"meanwhile ok"
 */

#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include "config.h"
#include "led_control.h"
#include "button_control.h"
#include "serial_command.h"

// ==================== FreeRTOS 任务句柄 ====================

TaskHandle_t taskHandleButton = NULL;
TaskHandle_t taskHandleSerial = NULL;
TaskHandle_t taskHandleFlow = NULL;
TaskHandle_t taskHandleBlink = NULL;

// ==================== 初始化函数 ====================

void setup() {
    // 初始化串口
    initSerial();
    
    // 初始化LED
    initLEDs();
    
    // 初始化按键
    initButtons();
    
    Serial.println("Initializing FreeRTOS tasks...");
    
    // 创建按键扫描任务
    xTaskCreate(
        taskButtonScan,
        "ButtonTask",
        TASK_STACK_SIZE_BUTTON,
        NULL,
        TASK_PRIORITY_BUTTON,
        &taskHandleButton
    );
    
    // 创建串口命令任务
    xTaskCreate(
        taskSerialCommand,
        "SerialTask",
        TASK_STACK_SIZE_SERIAL,
        NULL,
        TASK_PRIORITY_SERIAL,
        &taskHandleSerial
    );
    
    // 创建流水灯任务
    xTaskCreate(
        taskFlowLED,
        "FlowTask",
        TASK_STACK_SIZE_FLOW,
        NULL,
        TASK_PRIORITY_FLOW,
        &taskHandleFlow
    );
    
    // 创建闪烁灯任务
    xTaskCreate(
        taskBlinkLED,
        "BlinkTask",
        TASK_STACK_SIZE_BLINK,
        NULL,
        TASK_PRIORITY_BLINK,
        &taskHandleBlink
    );
    
    Serial.println("FreeRTOS tasks created successfully!");
    Serial.println("Starting scheduler...");
    
    // 启动调度器
    vTaskStartScheduler();
    
    // 如果调度器启动失败,会执行到这里
    Serial.println("ERROR: Scheduler failed to start!");
    while(1);
}

void loop() {
    //置空
}