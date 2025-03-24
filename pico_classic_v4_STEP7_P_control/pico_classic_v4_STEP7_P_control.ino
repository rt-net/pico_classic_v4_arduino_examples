// Copyright 2025 RT Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "run.h"
#include "sensor.h"
#include "SPI.h"
#include "TMC5240.h"

#define LED0 13
#define LED1 14
#define LED2 47
#define LED3 48

#define SW_L 16
#define SW_R 18
#define SW_C 15

#define MOTOR_EN 17

#define AD4 7
#define AD3 6
#define AD2 5
#define AD1 4
#define AD0 8

#define SLED_FR 9
#define SLED_FL 10
#define SLED_R 11
#define SLED_L 12

#define SPI_CLK 39
#define SPI_MOSI 42
#define SPI_MISO 41
#define SPI_CS_L 40   //左モータ
#define SPI_CS_R 3   //右モータ
#define SPI_CS_J 46  //ジャイロ

#define TIRE_DIAMETER (48.00)
#define PULSE TMC5240_PULSE
#define TREAD_WIDTH (65.00)

#define MIN_SPEED 30


//環境に合わせて変更する
//ここから
#define REF_SEN_R 352
#define REF_SEN_L 327

#define TH_SEN_R 173
#define TH_SEN_L 169
#define TH_SEN_FR 145
#define TH_SEN_FL 134

#define CONTH_SEN_R TH_SEN_R
#define CONTH_SEN_L TH_SEN_L

#define CON_WALL_KP (0.5)
//ここまで


hw_timer_t * g_timer0 = NULL;
hw_timer_t * g_timer1 = NULL;
portMUX_TYPE g_timer_mux = portMUX_INITIALIZER_UNLOCKED;

//割り込み
//目標値の更新周期1kHz
void IRAM_ATTR onTimer0(void) {
  portENTER_CRITICAL_ISR(&g_timer_mux);  //割り込み禁止
  controlInterrupt();
  portEXIT_CRITICAL_ISR(&g_timer_mux);  //割り込み許可
}

void IRAM_ATTR onTimer1(void)
{
  portENTER_CRITICAL_ISR(&g_timer_mux);  //割り込み禁止
  sensorInterrupt();
  portEXIT_CRITICAL_ISR(&g_timer_mux);  //割り込み許可
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  pinMode(SW_L, INPUT_PULLUP);
  pinMode(SW_C, INPUT_PULLUP);
  pinMode(SW_R, INPUT_PULLUP);

  //motor disable
  pinMode(MOTOR_EN, OUTPUT);
  digitalWrite(MOTOR_EN, HIGH);

  pinMode(SLED_FR, OUTPUT);
  pinMode(SLED_FL, OUTPUT);
  pinMode(SLED_R, OUTPUT);
  pinMode(SLED_L, OUTPUT);
  digitalWrite(SLED_FR, LOW);
  digitalWrite(SLED_FL, LOW);
  digitalWrite(SLED_R, LOW);
  digitalWrite(SLED_L, LOW);

  Serial.begin(115200);

  g_timer0 = timerBegin(1000000);  //1MHz(1us)
  timerAttachInterrupt(g_timer0, &onTimer0);
  timerAlarm(g_timer0, 1000, true, 0);  //1000 * 1us =1000us(1kHz)
  timerStart(g_timer0);

  g_timer1 = timerBegin(1000000);
  timerAttachInterrupt(g_timer1, &onTimer1);
  timerAlarm(g_timer1, 250, true, 0);
  timerStart(g_timer1);

  digitalWrite(MOTOR_EN, LOW);
  delay(1);
  g_tmc5240.init();
  digitalWrite(MOTOR_EN, HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:
  while (digitalRead(SW_L) & digitalRead(SW_C) & digitalRead(SW_R)) {
    continue;
  }
  if (digitalRead(SW_L) == 0) {
    while (1) {
      Serial.printf("r_sen  is %d\n\r", g_sensor.sen_r.value);
      Serial.printf("fr_sen is %d\n\r", g_sensor.sen_fr.value);
      Serial.printf("fl_sen is %d\n\r", g_sensor.sen_fl.value);
      Serial.printf("l_sen  is %d\n\r", g_sensor.sen_l.value);
      Serial.printf("VDD    is %d\n\r", g_sensor.battery_value);
      delay(100);
    }
  }
  digitalWrite(MOTOR_EN, LOW);
  delay(1000);
  g_run.accelerate(90, 350);
  g_run.oneStep(180 * 3, 350);
  g_run.decelerate(90, 350);
  delay(1000);
  digitalWrite(MOTOR_EN, HIGH);
}
