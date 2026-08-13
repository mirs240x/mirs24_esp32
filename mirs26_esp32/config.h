//エンコーダ用
#define PIN_ENC_A_L 4
#define PIN_ENC_B_L 5
#define PIN_ENC_A_R 13
#define PIN_ENC_B_R 14

//足回り用
#define PIN_DIR_R   25
#define PIN_PWM_R   26
#define PIN_DIR_L   32
#define PIN_PWM_L   33

//ROS用設定
#define ROS_DOMAIN_ID 90
#define WATCHDOG_TIMEOUT 1000

//プロポ用
// #define MR8_A 21
// #define MR8_B 22
// #define MR8_C 23

// volatile uint16_t rc_a_pwm = 1496;
// volatile uint16_t rc_b_pwm = 1496;
// volatile uint16_t rc_c_pwm = 1496;

#define MAX_MANUAL_VEL 1.0 // プロポ操作時の最大速度(m/s)

//足回り速度制御用
double RKP = 80.0;
double RKI = 30.0;
double RKD = 8.0;
double LKP = 80.0;
double LKI = 30.0;
double LKD = 8.0;

//車体パラメータ
#define COUNTS_PER_REV    4096.0
double WHEEL_RADIUS = 0.04;  //ホイール径
double WHEEL_BASE = 0.38;  //車輪間幅

// PWM設定 (ESP32 core v3.x: チャンネルは自動管理のため不要)
const int32_t pwmFrequency = 5000; // PWM周波数 (5kHz)
const int32_t pwmResolution = 8;   // PWM分解能 (8ビット = 0-255)
