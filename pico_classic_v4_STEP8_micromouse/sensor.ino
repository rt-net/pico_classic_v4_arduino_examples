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

#include "sensor.h"

SENSOR g_sensor;

void sensorInterrupt(void) {
  g_sensor.interrupt();
}

void SENSOR::interrupt(void) 
{
  static char cnt = 0;
  static char bled_cnt = 0;

  switch (cnt) {
    case 0:
      sen_fr.p_value = sen_fr.value;
      sen_fr.value = sensorGetFR();
      if (sen_fr.value > sen_fr.th_wall) {
        sen_fr.is_wall = true;
      } else {
        sen_fr.is_wall = false;
      }
      break;
    case 1:
      sen_fl.p_value = sen_fl.value;
      sen_fl.value = sensorGetFL();
      if (sen_fl.value > sen_fl.th_wall) {
        sen_fl.is_wall = true;
      } else {
        sen_fl.is_wall = false;
      }
      break;
    case 2:
      sen_r.p_value = sen_r.value;
      sen_r.value = sensorGetR();
      if (sen_r.value > sen_r.th_wall) {
        sen_r.is_wall = true;
      } else {
        sen_r.is_wall = false;
      }
      if (sen_r.value > sen_r.th_control) {
        sen_r.error = sen_r.value - sen_r.ref;
        sen_r.is_control = true;
      } else {
        sen_r.error = 0;
        sen_r.is_control = false;
      }
      break;
    case 3:
      sen_l.p_value = sen_l.value;
      sen_l.value = sensorGetL();
      if (sen_l.value > sen_l.th_wall) {
        sen_l.is_wall = true;
      } else {
        sen_l.is_wall = false;
      }
      if (sen_l.value > sen_l.th_control) {
        sen_l.error = sen_l.value - sen_l.ref;
        sen_l.is_control = true;
      } else {
        sen_l.error = 0;
        sen_l.is_control = false;
      }
      bled_cnt++;
      if (bled_cnt > 10) {
        bled_cnt = 0;
      }
      battery_value = batteryVoltGet();
      if (((battery_value - BATT_MIN) * 10 / (BATT_MAX - BATT_MIN)) > bled_cnt) {
        bledSet(1);
      } else {
        bledSet(2);
      }
      if(battery_value < BATT_MIN){
        buzzerEnable(400);
        ledSet(0);
      }
      break;
    default:
      Serial.printf("sensor state error\n\r");
      break;
  }
  cnt++;
  if (cnt >= 4) cnt = 0;
}
