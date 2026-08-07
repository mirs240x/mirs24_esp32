// volatile unsigned long rc_a_start = 0;
// volatile unsigned long rc_b_start = 0;
// volatile unsigned long rc_c_start = 0;
//
// void IRAM_ATTR rc_a_isr() {
//   if (digitalRead(MR8_A) == HIGH) {
//     rc_a_start = micros();
//   } else {
//     rc_a_pwm = micros() - rc_a_start;
//   }
// }
//
// void IRAM_ATTR rc_b_isr() {
//   if (digitalRead(MR8_B) == HIGH) {
//     rc_b_start = micros();
//   } else {
//     rc_b_pwm = micros() - rc_b_start;
//   }
// }
//
// void IRAM_ATTR rc_c_isr() {
//   if (digitalRead(MR8_C) == HIGH) {
//     rc_c_start = micros();
//   } else {
//     rc_c_pwm = micros() - rc_c_start;
//   }
// }
//
// void rc_setup() {
//   pinMode(MR8_A, INPUT_PULLDOWN);
//   pinMode(MR8_B, INPUT_PULLDOWN);
//   pinMode(MR8_C, INPUT_PULLDOWN);
//   attachInterrupt(MR8_A, rc_a_isr, CHANGE);
//   attachInterrupt(MR8_B, rc_b_isr, CHANGE);
//   attachInterrupt(MR8_C, rc_c_isr, CHANGE);
//   ledcAttach(PIN_PWM_R, pwmFrequency, pwmResolution);
//   ledcAttach(PIN_PWM_L, pwmFrequency, pwmResolution);
// }
