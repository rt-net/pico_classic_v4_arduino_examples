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

#include "SPI.h"
#include "TMC5240.h"
#include "run.h"

#define LED0 13
#define LED1 14
#define LED2 47
#define LED3 48

#define SW_L 16
#define SW_R 18
#define SW_C 15

#define MOTOR_EN 17

#define SPI_CLK 39
#define SPI_MOSI 42
#define SPI_MISO 41
#define SPI_CS_L 40  //左モータ
#define SPI_CS_R 3   //右モータ
#define SPI_CS_J 46  //ジャイロ

#define TIRE_DIAMETER (48.00)
#define PULSE TMC5240_PULSE

#define MIN_SPEED 30

hw_timer_t * g_timer0 = NULL;

portMUX_TYPE g_timer_mux = portMUX_INITIALIZER_UNLOCKED;

//割り込み
//目標値の更新周期1kHz
void IRAM_ATTR onTimer0(void)
{
  portENTER_CRITICAL_ISR(&g_timer_mux);  //割り込み禁止
  controlInterrupt();
  portEXIT_CRITICAL_ISR(&g_timer_mux);  //割り込み許可
}

void setup()
{
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

  g_timer0 = timerBegin(1000000);  //1MHz(1us)
  timerAttachInterrupt(g_timer0, &onTimer0);
  timerAlarm(g_timer0, 1000, true, 0);  //1000 * 1us =1000us(1kHz)
  timerStart(g_timer0);

  digitalWrite(MOTOR_EN, LOW);
  delay(1);
  g_tmc5240.init();
  digitalWrite(MOTOR_EN, HIGH);
}

void loop()
{
  // put your main code here, to run repeatedly:
  while (digitalRead(SW_L) & digitalRead(SW_C) & digitalRead(SW_R)) {
    continue;
  }
  digitalWrite(MOTOR_EN, LOW);
  delay(1000);
  digitalWrite(LED0, HIGH);
  g_run.accelerate(90, 350);
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  g_run.oneStep(180, 350);
  digitalWrite(LED3, HIGH);
  g_run.decelerate(90, 350);
  digitalWrite(LED0, LOW);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  delay(1000);
  digitalWrite(MOTOR_EN, HIGH);
}
