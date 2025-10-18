/**
 * @file serial_command.cpp
 * @brief 串口命令处理模块实现文件
 */

#include "serial_command.h"
#include "led_control.h"
#include "config.h"
#include <STM32FreeRTOS.h>

// ==================== 串口初始化函数 ====================

void initSerial() {
    // 初始化串口
    Serial.begin(SERIAL_BAUDRATE);
    while (!Serial) {
        ; // 等待串口连接
    }
    Serial.println("System Started!");
    Serial.println("Available Commands:");
    Serial.println("  OFF - Turn off all LEDs");
    Serial.println("  flow - Start flow LEDs (LED1-4)");
    Serial.println("  blink - Start blink LEDs (LED5-8)");
    Serial.println("  flow XXX - Set flow delay to XXX ms");
    Serial.println("  blink XXX - Set blink delay to XXX ms");
    Serial.println("  meanwhile blink flow - Start both flow and blink");
}

// ==================== 串口任务函数 ====================

void taskSerialCommand(void *pvParameters) {
    // 实现串口命令接收和处理
    (void)pvParameters;
    
    for (;;) {
        // 检查是否有串口数据可读
        if (Serial.available() > 0) {
            // 读取一行命令
            String command = Serial.readStringUntil('\n');
            
            // 处理命令
            if (command.length() > 0) {
                Serial.print("Received: ");
                Serial.println(command);
                processCommand(command);
            }
        }
        
        vTaskDelay(pdMS_TO_TICKS(100)); // 100ms 检查周期
    }
}

// ==================== 命令处理函数 ====================

void processCommand(String command) {
    // 解析并执行命令
    command = trimString(command);
    command.toLowerCase(); // 转换为小写便于比较
    
    // 处理 OFF 命令
    if (command == "off") {
        handleCommandOff();
    }
    // 处理 flow 命令 (可能带参数)
    else if (command.startsWith("flow")) {
        // 检查是否有参数
        int spaceIndex = command.indexOf(' ');
        if (spaceIndex > 0) {
            // 有参数,提取延时时间
            String delayStr = command.substring(spaceIndex + 1);
            uint32_t delay_ms = delayStr.toInt();
            if (delay_ms > 0) {
                handleCommandFlowDelay(delay_ms);
            } else {
                sendResponse("Error: Invalid flow delay value");
            }
        } else {
            // 无参数,启动流水灯
            handleCommandFlow();
        }
    }
    // 处理 blink 命令 (可能带参数)
    else if (command.startsWith("blink")) {
        // 检查是否有参数
        int spaceIndex = command.indexOf(' ');
        if (spaceIndex > 0) {
            // 有参数,提取延时时间
            String delayStr = command.substring(spaceIndex + 1);
            uint32_t delay_ms = delayStr.toInt();
            if (delay_ms > 0) {
                handleCommandBlinkDelay(delay_ms);
            } else {
                sendResponse("Error: Invalid blink delay value");
            }
        } else {
            // 无参数,启动闪烁灯
            handleCommandBlink();
        }
    }
    // 处理 meanwhile 命令
    else if (command.indexOf("meanwhile") >= 0) {
        handleCommandMeanwhile();
    }
    // 未知命令
    else {
        sendResponse("Error: Unknown command");
    }
}

void handleCommandOff() {
    // 关闭所有LED
    setFlowDirection(FLOW_STOP);
    setBlinkState(BLINK_OFF);
    turnOffAllLEDs();
    sendResponse("All LEDs turned OFF");
}

void handleCommandFlow() {
    // 启动流水灯
    setFlowDirection(FLOW_FORWARD);
    sendResponse("flow ok");
}

void handleCommandBlink() {
    // 启动闪烁灯
    setBlinkState(BLINK_ON);
    sendResponse("blink ok");
}

void handleCommandFlowDelay(uint32_t delay_ms) {
    // 修改流水灯频率
    setFlowDelay(delay_ms);
    sendResponse("Order ok");
}

void handleCommandBlinkDelay(uint32_t delay_ms) {
    // 修改闪烁灯频率
    setBlinkDelay(delay_ms);
    sendResponse("Order ok");
}

void handleCommandMeanwhile() {
    // 同时启动流水和闪烁
    setFlowDirection(FLOW_FORWARD);
    setBlinkState(BLINK_ON);
    sendResponse("meanwhile ok");
}

// ==================== 辅助函数 ====================

void sendResponse(const char* response) {
    // 发送串口响应
    Serial.println(response);
}

String trimString(String str) {
    // 去除首尾空格
    str.trim();
    return str;
}
