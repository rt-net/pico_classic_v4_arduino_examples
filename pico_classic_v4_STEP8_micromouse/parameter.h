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
#ifndef PARAMETER_H_
#define PARAMETER_H_

//初期パラメータ
#define TIRE_DIAMETER_INIT (48.21)
#define TREAD_WIDTH_INIT (69.5)

#define REF_SEN_R_INIT 409
#define REF_SEN_L_INIT 585

#define TH_SEN_R_INIT 120
#define TH_SEN_L_INIT 120
#define TH_SEN_FR_INIT 99
#define TH_SEN_FL_INIT 67

#define GOAL_X_INIT 3
#define GOAL_Y_INIT 3

#define WAITLOOP_SLED 300

#define CON_WALL_KP_INIT 0.3
#define SEARCH_ACCEL_INIT 1.5
#define TURN_ACCEL_INIT 0.3

#define SEARCH_SPEED_INIT 350
#define MAX_SPEED_INIT 1000
#define MIN_SPEED 30

#define INC_FREQ 3000
#define DEC_FREQ 2000

#define BATT_MAX 12000
#define BATT_MIN 10000

#define HALF_SECTION 90
#define SECTION 180

#endif  // PARAMETER_H_