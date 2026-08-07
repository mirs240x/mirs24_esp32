volatile unsigned long rc_a_start = 0;
volatile unsigned long rc_b_start = 0;
volatile unsigned long rc_c_start = 0;

void IRAM_ATTR rc_a_isr() {
  if (digitalRead(PIN_RC_A) == HIGH) {
    rc_a_start = micros();
  } else {
    rc_a_pwm = micros() - rc_a_start;
  }
}

void IRAM_ATTR rc_b_isr() {
  if (digitalRead(PIN_RC_B) == HIGH) {
    rc_b_start = micros();
  } else {
    rc_b_pwm = micros() - rc_b_start;
  }
}

void IRAM_ATTR rc_c_isr() {
  if (digitalRead(PIN_RC_C) == HIGH) {
    rc_c_start = micros();
  } else {
    rc_c_pwm = micros() - rc_c_start;
  }
}

void rc_setup() {
  pinMode(PIN_RC_A, INPUT_PULLDOWN);
  pinMode(PIN_RC_B, INPUT_PULLDOWN);
  pinMode(PIN_RC_C, INPUT_PULLDOWN);
  attachInterrupt(PIN_RC_A, rc_a_isr, CHANGE);
  attachInterrupt(PIN_RC_B, rc_b_isr, CHANGE);
  attachInterrupt(PIN_RC_C, rc_c_isr, CHANGE);
  ledcAttach(PIN_PWM_R, pwmFrequency, pwmResolution);
  ledcAttach(PIN_PWM_L, pwmFrequency, pwmResolution);
}
