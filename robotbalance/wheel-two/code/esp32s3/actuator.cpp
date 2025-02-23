#include "config.h"
#include <Arduino.h>




#if MOTORTYPE_SELECT==MOTORTYPE_DRV8833
#define PWM_FREQ 1000
#define PWM_RESOLUTION 8
void motor_init()
{
  ledcAttach(PIN_LEFT_P, PWM_FREQ, PWM_RESOLUTION);
  ledcAttach(PIN_LEFT_N, PWM_FREQ, PWM_RESOLUTION);
  pinMode(PIN_LEFT_EN, OUTPUT);

  ledcAttach(PIN_RIGHT_P, PWM_FREQ, PWM_RESOLUTION);
  ledcAttach(PIN_RIGHT_N, PWM_FREQ, PWM_RESOLUTION);
  pinMode(PIN_RIGHT_EN, OUTPUT);
}
void motor_output(float fl, float fr)
{
  if(abs(fl)<0.001){
    digitalWrite(PIN_LEFT_EN, 0);
  }
  else{
    int il_p = 0;
    int il_n = 0;
    if(fl<0){
      il_p = 255;
      il_n = 255 + (int)(fl*255/1000);
      if(il_n < 0)il_n = 0;
    }
    else{
      il_p = 255 - (int)(fl*255/1000);
      il_n = 255;
      if(il_p < 0)il_p = 0;
    }
    ledcWrite(PIN_LEFT_P, il_p);
    ledcWrite(PIN_LEFT_N, il_n);
    digitalWrite(PIN_LEFT_EN, 1);
  }

  if(abs(fr)<0.001){
    digitalWrite(PIN_RIGHT_EN, 0);
  }
  else{
    int ir_p = 0;
    int ir_n = 0;
    if(fr<0){
      ir_p = 255;
      ir_n = 255 + (int)(fr*255/1000);
      if(ir_n < 0)ir_n = 0;
    }
    else{
      ir_p = 255 - (int)(fr*255/1000);
      ir_n = 255;
      if(ir_p < 0)ir_p = 0;
    }
    ledcWrite(PIN_RIGHT_P, ir_p);
    ledcWrite(PIN_RIGHT_N, ir_n);
    digitalWrite(PIN_RIGHT_EN, 1);
  }
}
#endif




#if MOTORTYPE_SELECT==MOTORTYPE_DRV8825
#define PWM_ACCEL_LIMIT 1000
int pwm_want_l = 0;
int pwm_want_r = 0;
int pwm_curr_l = 0;
int pwm_curr_r = 0;
static void ontimer_compute(){
  int err;

  err = pwm_want_l-pwm_curr_l;
  if(err < -PWM_ACCEL_LIMIT)pwm_curr_l -= PWM_ACCEL_LIMIT;
  else if(err > PWM_ACCEL_LIMIT)pwm_curr_l += PWM_ACCEL_LIMIT;
  else pwm_curr_l = pwm_want_l;

  err = pwm_want_r-pwm_curr_r;
  if(err < -PWM_ACCEL_LIMIT)pwm_curr_r -= PWM_ACCEL_LIMIT;
  else if(err > PWM_ACCEL_LIMIT)pwm_curr_r += PWM_ACCEL_LIMIT;
  else pwm_curr_r = pwm_want_r;
}
static void ontimer_output(){
  if(abs(pwm_curr_l)<160){   //0.001){
    digitalWrite(PIN_LEFT_EN, 1);
  }
  else{
    ledcChangeFrequency(PIN_LEFT_STEP, abs(pwm_curr_l), 8); //resolution=2^8=256
    ledcWrite(PIN_LEFT_STEP, 128);    //duty=50%
    //
    digitalWrite(PIN_LEFT_DIR, (pwm_curr_l>0)?1:0);
    digitalWrite(PIN_LEFT_EN, 0);
  }

  if(abs(pwm_curr_r)<160){   //0.001){
    digitalWrite(PIN_RIGHT_EN, 1);
    pwm_curr_r = 0;
  }
  else{
    ledcChangeFrequency(PIN_RIGHT_STEP, abs(pwm_curr_r), 8);
    ledcWrite(PIN_RIGHT_STEP, 128);
    //
    digitalWrite(PIN_RIGHT_DIR, (pwm_curr_r>0)?1:0);
    digitalWrite(PIN_RIGHT_EN, 0);
  }
}
int pingpong = 0;
static void ontimer(void *){
  if(pingpong&1)ontimer_output();
  else ontimer_compute();

  pingpong = (pingpong+1)&0xff;
}
#define PWM_FREQ 1024
#define PWM_RESOLUTION 8
hw_timer_t* timer = 0;
void motor_init()
{
  pinMode(PIN_LEFT_EN, OUTPUT);
  pinMode(PIN_LEFT_M0, OUTPUT);
  pinMode(PIN_LEFT_M1, OUTPUT);
  pinMode(PIN_LEFT_M2, OUTPUT);
  pinMode(PIN_LEFT_RST, OUTPUT);
  pinMode(PIN_LEFT_SLP, OUTPUT);
  ledcAttach(PIN_LEFT_STEP, PWM_FREQ, PWM_RESOLUTION);
  pinMode(PIN_LEFT_DIR, OUTPUT);
  digitalWrite(PIN_LEFT_EN, 1);   //0=on
  digitalWrite(PIN_LEFT_M0, 1);   //1,1,1 = 32 step
  digitalWrite(PIN_LEFT_M1, 1);
  digitalWrite(PIN_LEFT_M2, 1);
  digitalWrite(PIN_LEFT_RST, 1);   //1=on
  digitalWrite(PIN_LEFT_SLP, 1);   //1=on

  pinMode(PIN_RIGHT_EN, OUTPUT);
  pinMode(PIN_RIGHT_M0, OUTPUT);
  pinMode(PIN_RIGHT_M1, OUTPUT);
  pinMode(PIN_RIGHT_M2, OUTPUT);
  pinMode(PIN_RIGHT_RST, OUTPUT);
  pinMode(PIN_RIGHT_SLP, OUTPUT);
  ledcAttach(PIN_RIGHT_STEP, PWM_FREQ, PWM_RESOLUTION);
  pinMode(PIN_RIGHT_DIR, OUTPUT);
  digitalWrite(PIN_RIGHT_EN, 1);   //0=on
  digitalWrite(PIN_RIGHT_M0, 1);   //1,1,1 = 32 step
  digitalWrite(PIN_RIGHT_M1, 1);
  digitalWrite(PIN_RIGHT_M2, 1);
  digitalWrite(PIN_RIGHT_RST, 1);   //1=on
  digitalWrite(PIN_RIGHT_SLP, 1);   //1=on

  //timer
  timer = timerBegin(1000);   //freq=1000
  timerAlarm(timer, 10, true, 0);   //timer, 20ms, isreload, reloadvalue
  timerAttachInterruptArg(timer, ontimer, 0);  //timer, func, arg
}
void motor_output(float fl, float fr)
{
  //Serial.printf("l=%f,r=%f\n", fl, fr);

  pwm_want_l =-(int)fl;
  pwm_want_r = (int)fr;
}
void motor_getpwm(float* l, float* r)
{
  *l = (float)pwm_curr_l;
  *r = -(float)pwm_curr_r;
}
#endif
