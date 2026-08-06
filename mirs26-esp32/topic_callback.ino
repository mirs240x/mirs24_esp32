//ノードのタイマーコールバック関数
void timer_callback(rcl_timer_t * timer, int64_t last_call_time)
{  
  RCLC_UNUSED(last_call_time);
  if (timer != NULL) {
    if (rc_b_pwm > 1700) {
      if (rc_a_pwm > 1520 && rc_a_pwm <= 2200) {
        l_vel_cmd = (rc_a_pwm - 1520) * MAX_MANUAL_VEL / (2100 - 1520);
      } else if (rc_a_pwm < 1470 && rc_a_pwm >= 800) {
        l_vel_cmd = (rc_a_pwm - 1470) * MAX_MANUAL_VEL / (1470 - 890);
      } else {
        l_vel_cmd = 0.0;
      }
      
      if (rc_c_pwm > 1520 && rc_c_pwm <= 2200) {
        r_vel_cmd = (rc_c_pwm - 1520) * MAX_MANUAL_VEL / (2100 - 1520);
      } else if (rc_c_pwm < 1470 && rc_c_pwm >= 800) {
        r_vel_cmd = (rc_c_pwm - 1470) * MAX_MANUAL_VEL / (1470 - 890);
      } else {
        r_vel_cmd = 0.0;
      }
    } else {
      // watchdog (ROS2 mode)
      if( (millis() - lastCalledAt) > WATCHDOG_TIMEOUT){
        r_vel_cmd = 0;
        l_vel_cmd = 0;
      }
    }

    //PID計算
    PID_control();
    
    //エンコーダーデータを格納
    enc_msg.data.data[0] = count_l;
    enc_msg.data.data[1] = count_r;

    curr_vel_msg.data.data[0] = l_vel;
    curr_vel_msg.data.data[1] = r_vel;
    rcl_publish(&enc_pub, &enc_msg, NULL);
    rcl_publish(&curr_vel_pub, &curr_vel_msg, NULL);
  }
}

// cmd_velメッセージのコールバック関数
void cmd_vel_Callback(const void * msgin) {
  const geometry_msgs__msg__Twist * vel_msg = (const geometry_msgs__msg__Twist *)msgin;

  // linear.x と angular.z のデータを取得
  linear_x = vel_msg->linear.x;
  angular_z = vel_msg->angular.z;

  //  目標速度計算
  r_vel_cmd = linear_x + WHEEL_BASE / 2 * angular_z;
  l_vel_cmd = linear_x - WHEEL_BASE / 2 * angular_z;

  // WatchDog用 最後に呼び出された時間を格納
  lastCalledAt = millis();
}

//TODO: 消してサービスに移行
//パラメーター更新のコールバック関数
void param_Callback(const void * msgin){
  const mirs_msgs__msg__BasicParam * param_msg = (const mirs_msgs__msg__BasicParam *)msgin;

  // linear.x と angular.z のデータを取得
  WHEEL_RADIUS = param_msg->wheel_radius;
  WHEEL_BASE = param_msg->wheel_base;
  RKP = param_msg->rkp;
  RKI = param_msg->rki;
  RKD = param_msg->rkd;
  LKP = param_msg->lkp;
  LKI = param_msg->lki;
  LKD = param_msg->lkd;
}
