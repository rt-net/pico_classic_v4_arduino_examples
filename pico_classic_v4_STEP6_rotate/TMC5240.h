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

#ifndef TMC5240_H_
#define TMC5240_H_

#define TMC5240_READ 0x00
#define TMC5240_WRITE 0x80

//General Configuration Register
#define TMC5240_GCONF 0x00
#define TMC5240_GSTAT 0x01
#define TMC5240_IFCNT 0x02  //read only
#define TMC5240_NODECONFIG 0x03
#define TMC5240_IOIN 0x04
#define TMC5240_XCOMPARE 0x05
#define TMC5240_XCOMPARE_REPEAT 0x06
#define TMC5240_DRV_CONF 0x0A
#define TMC5240_GLOBAL_SCALER 0x0B

//Velocity Dependent Configuration Registers
#define TMC5240_IHOLD_IRUN 0x10
#define TMC5240_TPOWERDOWN 0x11
#define TMC5240_TSTEP 0x12
#define TMC5240_TPWMTHRS 0x13
#define TMC5240_TCOOLTHRS 0x14
#define TMC5240_THIGH 0x15

//Ramp Generator Registers
#define TMC5240_RAMPMODE 0x20
#define TMC5240_XACTUAL 0x21
#define TMC5240_VACTUAL 0x22  //Read only
#define TMC5240_VSTART 0x23
#define TMC5240_A1 0x24
#define TMC5240_V1 0x25
#define TMC5240_AMAX 0x26
#define TMC5240_VMAX 0x27
#define TMC5240_DMAX 0x28
#define TMC5240_D1 0x2A
#define TMC5240_VSTOP 0x2B
#define TMC5240_TZEROWAIT 0x2C
#define TMC5240_XTARGET 0x2D
#define TMC5240_V2 0x2E
#define TMC5240_A2 0x2F

//Ramp Generator Driver Feature Control Registers
#define TMC5240_VDCMIN 0x33
#define TMC5240_SW_MODE 0x34
#define TMC5240_RAMP_STAT 0x35
#define TMC5240_XLATCH 0x36

//Encoder Registgers
#define TMC5240_ENCMODE 0x38
#define TMC5240_X_ENC 0x39
#define TMC5240_ENC_CONST 0x3A
#define TMC5240_ENC_STATUS 0x3B
#define TMC5240_ENC_LATCH 0x3C
#define TMC5240_ENC_DEVIATION 0x3D
#define TMC5240_VIRTUAL_STOP_L 0x3E
#define TMC5240_VIRTUAL_STOP_R 0x3F

//ADC Registers
#define TMC5240_ADC_VSUPPLY 0x50
#define TMC5240_ADC_TEMP 0x51
#define TMC5240_OTW_OV_VTH 0x52

//Motor Driver Registers
#define TMC5240_MSLUT_0 0x60
#define TMC5240_MSLUT_1 0x61
#define TMC5240_MSLUT_2 0x62
#define TMC5240_MSLUT_3 0x63
#define TMC5240_MSLUT_4 0x64
#define TMC5240_MSLUT_5 0x65
#define TMC5240_MSLUT_6 0x66
#define TMC5240_MSLUT_7 0x67
#define TMC5240_MSLUTSEL 0x68
#define TMC5240_MSLUTSTART 0x69
#define TMC5240_MSCNT 0x6A
#define TMC5240_MSCURACT 0x6B
#define TMC5240_CHOPCONG 0x6C
#define TMC5240_COOLCONF 0x6D
#define TMC5240_DCCTRL 0x6E
#define TMC5240_DRVSTATUS 0x6F
#define TMC5240_PWMCONF 0x70
#define TMC5240_PWM_SCALE 0x71
#define TMC5240_PWM_AUTO 0x72
#define TMC5240_SG4_THRS 0x74
#define TMC5240_SG4_RESULT 0x75
#define TMC5240_SG4_IND 0x76

#define microstep 16

#define TMC5240_PULSE (TIRE_DIAMETER * PI / (200.0 * microstep))
#define TMC5240_VELOCITY (TMC5240_PULSE * 0.787)  //13200000/2/2^23=0.787 +50c


class TMC5240 {
private:

public:
  unsigned int readXactual(void);
  void write(unsigned char add, unsigned int data_l, unsigned int data_r);
  void init(void);
};


extern TMC5240 g_tmc5240;



#endif  // TMC5240_H_
