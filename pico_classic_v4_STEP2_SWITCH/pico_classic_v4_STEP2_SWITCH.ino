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

#define LED0 13
#define LED1 14
#define LED2 47
#define LED3 48

#define SW_L 16
#define SW_C 15
#define SW_R 18

int g_state_r, g_state_c, g_state_l;

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

  g_state_r = g_state_c = g_state_l = 0;
}

void loop()
{
  // put your main code here, to run repeatedly:
  while (digitalRead(SW_L) && digitalRead(SW_C) && digitalRead(SW_R)) {
    continue;
  }
  if (digitalRead(SW_R) == 0) {
    digitalWrite(LED0, (++g_state_r) & 0x01);
  }
  if (digitalRead(SW_C) == 0) {
    digitalWrite(LED1, (++g_state_c) & 0x01);
    digitalWrite(LED2, (g_state_c) & 0x01);
  }
  if (digitalRead(SW_L) == 0) {
    digitalWrite(LED3, (++g_state_l) & 0x01);
  }
  delay(30);
  while (!(digitalRead(SW_L) && digitalRead(SW_C) && digitalRead(SW_R))) {
    continue;
  }
  delay(30);
}