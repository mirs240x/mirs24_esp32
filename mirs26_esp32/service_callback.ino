// 　updateサーバーのコールバック
void update_service_callback(const void * req, void * res){
  mirs_msgs__srv__ParameterUpdate_Request * req_in = (mirs_msgs__srv__ParameterUpdate_Request *) req;
  mirs_msgs__srv__ParameterUpdate_Response * res_in = (mirs_msgs__srv__ParameterUpdate_Response *) res;

  //  パラメーター更新
  WHEEL_RADIUS = req_in->wheel_radius;
  WHEEL_BASE = req_in->wheel_base;
  RKP = req_in->rkp;
  RKI = req_in->rki;
  RKD = req_in->rkd;
  LKP = req_in->lkp;
  LKI = req_in->lki;
  LKD = req_in->lkd;
  
  res_in->success = true;
}
/*
//  rebootサーバーのコールバック
void reboot_service_callback(const void * req, void * res){
  mirs_msgs__srv__SimpleCommand_Request * req_in = (mirs_msgs__srv__SimpleCommand_Request *) req;
  mirs_msgs__srv__SimpleCommand_Response * res_in = (mirs_msgs__srv__SimpleCommand_Response *) res;

  res_in->success = true;
  ESP.restart();
}
*/
//  resetサーバーのコールバック
void reset_service_callback(const void * req, void * res){
  mirs_msgs__srv__SimpleCommand_Request * req_in = (mirs_msgs__srv__SimpleCommand_Request *) req;
  mirs_msgs__srv__SimpleCommand_Response * res_in = (mirs_msgs__srv__SimpleCommand_Response *) res;

  encoder_reset();

  res_in->success = true;
}

