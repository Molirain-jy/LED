/**
 * @file button_control.cpp
 * @brief 按键控制模块实现文件
 */

#include "button_control.h"
#include "led_control.h"
#include "config.h"
#include <STM32FreeRTOS.h>

// ==================== 按键初始化函数 ====================

void initButtons() {
    // TODO: 初始化所有按键引脚为输入上拉模式
    pinMode(BUTTON1_PIN, INPUT_PULLUP);
    pinMode(BUTTON2_PIN, INPUT_PULLUP);
    pinMode(BUTTON3_PIN, INPUT_PULLUP);
    pinMode(BUTTON4_PIN, INPUT_PULLUP);
}

// ==================== 按键任务函数 ====================

void taskButtonScan(void *pvParameters) {
    // 实现按键扫描任务
    (void)pvParameters;
    
    for (;;) {
        // 依次检查每个按键
        if (readButtonWithDebounce(BUTTON1_PIN)) {
            handleButton1Press();
        }
        
        if (readButtonWithDebounce(BUTTON2_PIN)) {
            handleButton2Press();
        }
        
        if (readButtonWithDebounce(BUTTON3_PIN)) {
            handleButton3Press();
        }
        
        if (readButtonWithDebounce(BUTTON4_PIN)) {
            handleButton4Press();
        }
        
        vTaskDelay(pdMS_TO_TICKS(50)); // 50ms 扫描周期
    }
}

// ==================== 按键处理函数 ====================

void handleButton1Press() {
    // 处理按键1 - 控制流水灯从1流至4
    setFlowDirection(FLOW_FORWARD);
    Serial.println("[Button] Flow Forward (LED1->LED4)");
}

void handleButton2Press() {
    // 处理按键2 - 控制流水灯从4流至1
    setFlowDirection(FLOW_BACKWARD);
    Serial.println("[Button] Flow Backward (LED4->LED1)");
}

void handleButton3Press() {
    // 处理按键3 - LED5-8开始闪烁
    setBlinkState(BLINK_ON);
    Serial.println("[Button] Blink ON (LED5-8)");
}

void handleButton4Press() {
    // 处理按键4 - 关闭LED5-8闪烁
    setBlinkState(BLINK_OFF);
    Serial.println("[Button] Blink OFF (LED5-8)");
}

// ==================== 按键读取函数 ====================

bool readButtonWithDebounce(uint8_t pin) {
    // 实现带防抖的按键读取
    static bool lastState[4] = {false, false, false, false};
    static uint32_t lastPressTime[4] = {0, 0, 0, 0};
    
    // 确定按键索引
    uint8_t buttonIndex = 0;
    if (pin == BUTTON1_PIN) buttonIndex = 0;
    else if (pin == BUTTON2_PIN) buttonIndex = 1;
    else if (pin == BUTTON3_PIN) buttonIndex = 2;
    else if (pin == BUTTON4_PIN) buttonIndex = 3;
    
    // 读取按键状态 (INPUT_PULLUP 模式下,按下为 LOW)
    bool currentState = (digitalRead(pin) == LOW);
    
    // 检测按键按下(从未按下到按下的跳变)
    if (currentState && !lastState[buttonIndex]) {
        // 防抖延时
        uint32_t currentTime = millis();
        if (currentTime - lastPressTime[buttonIndex] > BUTTON_DEBOUNCE_DELAY) {
            lastPressTime[buttonIndex] = currentTime;
            lastState[buttonIndex] = true;
            return true;
        }
    } else if (!currentState) {
        // 按键释放,更新状态
        lastState[buttonIndex] = false;
    }
    
    return false;
}
