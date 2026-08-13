void calculate_vel(){
  //エンコーダーの変化量を計算
  int32_t delta_left = count_l - prev_count_l;
  int32_t delta_right = count_r - prev_count_r;

  prev_count_l = count_l;
  prev_count_r = count_r;

  // 車輪の回転角度（ラジアン）を計算
  double delta_left_rad = (delta_left / COUNTS_PER_REV) * 2.0 * PI;
  double delta_right_rad = (delta_right / COUNTS_PER_REV) * 2.0 * PI;

  // それぞれの車輪の移動距離を計算
  double left_distance = delta_left_rad * WHEEL_RADIUS;
  double right_distance = delta_right_rad * WHEEL_RADIUS;

  // 現在の速度を計算 (15ms間隔)
  l_vel = left_distance / 0.015;
  r_vel = right_distance / 0.015;
}

void PID_control(){
  calculate_vel();

  float r_err = r_vel_cmd - r_vel;
  float l_err = l_vel_cmd - l_vel;

  r_err_sum += r_err;
  l_err_sum += l_err;

  // PID計算を実行
  double r_pwm = RKP * r_err + RKI * r_err_sum + RKD *  (r_err - prev_r_err);
  double l_pwm = LKP * l_err + LKI * l_err_sum + LKD *  (l_err - prev_l_err);

  prev_r_err = r_err;
  prev_l_err = l_err;

  if(r_pwm > 255){
    r_pwm = 255;
  }else if(r_pwm < -255){
    r_pwm = -255;
  }
  if(l_pwm > 255){
    l_pwm = 255;
  }else if(l_pwm < -255){
    l_pwm = -255;
  }

  //  出力値の前処理
  if(r_pwm >= 0){
    digitalWrite(PIN_DIR_R, LOW);
  }else{
    r_pwm *= -1;
    digitalWrite(PIN_DIR_R,HIGH);
  }
  if(l_pwm >= 0){
    digitalWrite(PIN_DIR_L, HIGH);
  }else{
    l_pwm *= -1;
    digitalWrite(PIN_DIR_L,LOW);
  }

  //  確実な停止
  if(r_vel_cmd == 0){
    r_pwm = 0;
  }
  if(l_vel_cmd == 0){
    l_pwm = 0; 
  }

  //  pwm出力 (ESP32 core v3.x: 第1引数はピン番号)
  ledcWrite(PIN_PWM_R, uint8_t(r_pwm));
  ledcWrite(PIN_PWM_L, uint8_t(l_pwm));
}

void vel_ctrl_set() {
  // ledcのPWM設定 (ESP32 core v3.x: ledcAttach に統合)
  pinMode(PIN_DIR_R, OUTPUT);
  pinMode(PIN_DIR_L, OUTPUT);
  ledcAttach(PIN_PWM_R, pwmFrequency, pwmResolution);
  ledcAttach(PIN_PWM_L, pwmFrequency, pwmResolution);

  curr_vel_msg.data.capacity = 2;
  curr_vel_msg.data.size = 2;
  curr_vel_msg.data.data = (double *)malloc(curr_vel_msg.data.capacity * sizeof(double)); // 配列のメモリを確保
  curr_vel_msg.data.data[0] = 0;
  curr_vel_msg.data.data[1] = 0;
}
