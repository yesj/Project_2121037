
#ifndef __CHANDLER_H__
#define __CHANDLER_H__

#include <rthw.h>
#include <stdio.h>
#include <string.h>
#include "scan_key_led.h"
#include "bz.h"
#include "ht1650.h"
#include "number_process.h"
#include "pwm_vms.h"
#include "Incline.h"
#include "heart.h"
//=================================
// 把计砞﹚ 
#define ageNumMaxVal					99
#define ageNumMinVal					10
#define ageNumVal							40

#define workOutTimeMinuteNumMaxVal		99
#define workOutTimeMinuteNumMinVal		5
#define workOutTimeMinuteNumVal				15

#define WeightNumMaxVal			350
#define WeightNumMinVal			50
#define WeightNumVal				150

#define LevelNumMaxVal			20		
#define LevelNumMinVal			1
#define LevelNumVal					7
//=================================
enum _uiStatus {
		sysPowerStartVal,
    sysUiStartVal,
    eng1Val,
		engineeringModeVal,
		setUintVal,
		setBzTestVal,
		setLcdTestVal,
		setKeyTestVal,
    setNoramalVal,
    sportManualVal,
    setProfilesVal,
    setProfileChooseVal,
    setRollingHillVal,
    setPeakVal,
    setPlateauVal,
    setClimbVal,
    setInterval_1_Val,
    setInterval_2_Val,
		profileSportVal,
		setProfileManualVal,
		manualSportVal,
		setUsersVal,
		setUsersNoDataVal,
		setUsersDataVal,
		setUsersResetDataVal,
		setUsersSportVal,
		setProfilesHeartRateVal,
		setHeartRateFatBurnVal,
		setHeartRateCardioVal,
		setHeartRateTargetVal,
		setHeartRateSportVal,
		setProfilesFocusVal,
		setProfilesFocusDataVal,
		FocusSportVal,
    eepromErrVal,
    sportErrVal
};

enum _sportNormalEvent {
	StandardViewVal,
	BasicViewVal,
	HeartRateViewVal,
	CalorieVewVal,
	FocusVewVal
};

enum _sportProfileEvent {
	CalHrViewVal,
	RpmDisViewVal
};

enum _sportProfileSportEvent{
	sportProfileSportNormalEvent,
	sportProfileSportStopEvent
};

enum _eng1Event{
	IncAdr1EventVal,
	IncAdr2EventVal,
	IncAdrOkEventVal,
	IncAdrErrEventVal
};

enum _setProfilesEvent{
	setProfileEventVal,
	setManualEventVal,
	setHeartRateEventVal,
	setFocusEventVal,
	setMetsEventVal
};

enum _setProfileChooseEvent{
	setRollingHillEventVal,
	setPeakEventVal,
	setPlateauEventVal,
	setClimbEventVal,
	setInterval_1_EventVal,
	setInterval_2_EventVal
};

enum _setAllProfileLvelAndWorkOutTimeEvent{
	setProfileLevelEventVal,
	setProfileWorkOutTImeEventVal
};

enum _setUsersEvent{
	setUser_1_EventVal,
	setUser_2_EventVal,
	setUser_3_EventVal,
	setUser_4_EventVal,
	setUser_5_EventVal,
	setUser_6_EventVal,
	setUser_7_EventVal,
	setUser_8_EventVal,
	setUser_9_EventVal,
	setUser_10_EventVal
};

enum _setUsersNoDataEvent{
	setUsersNoDataEventVal,
	setUsersName_1_EventVal,
	setUsersName_2_EventVal,
	setUsersName_3_EventVal,
	setUsersName_4_EventVal,
	setUsersName_5_EventVal,
	setUsersName_6_EventVal,
	setUsersName_7_EventVal,
	setUsersName_8_EventVal,
	setUsersName_9_EventVal,
	setSeatPositionEventVal,
	setGenderEventVal,
	setAgeEventVal,
	setWeightEventVal,
	setUserRollingHillEventVal,
	setUserPeakEventVal,
	setUserPlateauEventVal,
	setUserClimbEventVal,
	setUserInterval_1_EventVal,
	setUserInterval_2_EventVal,
	setUserProfileLevelEventVal,
	setUserProfileWorkOutTImeEventVal
};

//enum _setUsersResetDataEvent{
//};

enum _setUsersDataEvent{
	showUserStartEventVal,
	showUserSeetingsEventVal,
	showUserTotalEventVal,
	showUserDataEventVal,
	showUserResetNoEventVal,
	showUserResetYesEventVal
	//showUserNameEventVal,
};

enum _setHeartRateEvent{
	showHeartRateFatBurnEventVal,
	showHeartRateCardicEventVal,
	showHeartRateTargetEventVal
};

enum _setHeartRateDataEvent{
	showHeartRateAgeEventVal,
	showHeartRateSetTargetEventVal,
	showHeartRateWorkoutEventVal
};

enum _setEngineeringModeEvent{
	UnitEventVal,
	VersionEventVal,
	BeeperTestEventVal,
	DisplayTestEventVal,
	KeypadTestEventVal,
	SeatLiftInstallEventVal
};

enum _setUintEvent{
	MetricEventVal,
	EnglishEventVal
};

enum _setBzTestEvent{
	BzTest1EventVal,
	BzTest2EventVal,
	BzTest3EventVal
};

enum _setProfilesFocusEvent{
	FocusTotalBodyEventVal,
	FocusArmsEventVal,
	FocusLegsEventVal
};

enum _setProfilesFocusDataEvent{
	FocusMaximumLevelEventVal,
	FocusWorkoutTimeEventVal
};

enum _uint{
	UintMetricVal,
	UintEnglishVal
};

enum _TemporarySeatPositionEvent{
	TemporarySeatPositionNormalEventVal,
	TemporarySeatPositionMoveEventVal,
	TemporarySeatPositionUnlockEventVal,
	TemporarySeatPositionUnlockYesEventVal,
	TemporarySeatPositionUnlockNoEventVal
};

enum _TemporarySportStopEvent{
	TemporarySportStopNormalEventVal,
	TemporarySportStopEventVal,
	TemporarySportStopSetTimeEventVal
};

//================================
struct	rt_ui_action
{
  rt_uint8_t	Status;
  rt_uint8_t	Event;
	rt_uint8_t	ProfileEventSave;
	rt_uint8_t	UsersEventSave;
	rt_uint8_t	HeartRateEventSave;
	rt_uint8_t	FocusEventSave;
	rt_uint8_t	TemporaryEventTimer;
	rt_uint8_t	TemporarySeatPositionEvent;
	rt_uint8_t	TemporarySportStopEvent;
};
typedef struct	rt_ui_action	rt_ui_action_t;

//================================
struct rt_time_data
{
	rt_uint8_t		timeH;
	rt_uint8_t		timeL;
};
typedef struct rt_time_data rt_time_data_t;
//================================
#define ProgfileDataSizeVal					60
struct	rt_sport_data
{
  uint8_Number_t age;
  uint16_Number_t weight;
  uint8_Number_t seatPosition;
  uint8_Number_t targetHeart;
  uint16_Number_t wheelSize;
	uint8_Number_t	resistance;
	uint8_Number_t	IncNumAdBuf;
	rt_uint8_t	progfileArry[ProgfileDataSizeVal];
	rt_uint8_t	progfileArryBuf[ProgfileDataSizeVal];
	rt_uint8_t	saveSeatPositionHome_1;
	rt_uint8_t	saveSeatPositionHome_2;
  rt_bool_t		UnitFlg;
	uint8_Number_t	sportSetTimer;
	rt_time_data_t	SetWorkoutTime;
};
typedef struct	rt_sport_data		rt_sport_data_t;

struct	rt_set_profile_data
{
  uint8_Number_t roolingHillLevel;
  uint8_Number_t roolingHillWorkoutMinTime;
  uint8_Number_t peakLevel;
  uint8_Number_t peakWorkoutMinTime;
  uint8_Number_t plateauLevel;
  uint8_Number_t plateauWorkoutMinTime;
  uint8_Number_t climbLevel;
  uint8_Number_t climbWorkoutMinTime;
  uint8_Number_t interval_1_Level;
  uint8_Number_t interval_1_WorkoutMinTime;
  uint8_Number_t interval_2_Level;
  uint8_Number_t interval_2_WorkoutMinTime;
	uint8_Number_t menualLevel;
	uint8_Number_t menualWorkoutTime;
};

typedef struct	rt_set_profile_data		rt_set_profile_data_t;
//================================
struct	rt_profile_heartrate_data
{
  uint8_Number_t FatBurnAge;
	rt_uint8_t	FatBurnTarget;
	uint8_Number_t FatBurnWorkoutMinTime;
  uint8_Number_t CardioAge;
	rt_uint8_t	CardioTarget;
	uint8_Number_t CardioWorkoutMinTime;
  uint8_Number_t TargetTarget;
	uint8_Number_t TargetWorkoutMinTime;
};

typedef struct	rt_profile_heartrate_data		rt_profile_heartrate_data_t;
//================================
struct	rt_set_focus_data
{
  uint8_Number_t	FocusLevel;
	uint8_Number_t	FocusWorkoutMinTime;
};

typedef struct	rt_set_focus_data		rt_set_focus_data_t;
//================================
struct rt_incline_eeprom_data
{
	rt_uint8_t		incMaxNum;
	rt_uint8_t		incMaxAd;
	rt_uint8_t		incMinAd;
	rt_bool_t			incUpDownFlg;
};

typedef struct rt_incline_eeprom_data rt_incline_eeprom_data_t;
//================================
struct rt_calor_data
{
	rt_uint8_t	level;
	rt_uint16_t	watt;
	rt_uint32_t calorie;
	rt_uint16_t calorieHr;
};
typedef struct rt_calor_data rt_calor_data_t;
//================================
struct rt_distance_data
{
	rt_uint16_t	WheelSize;
	rt_uint16_t	rpm;
	rt_uint32_t distance_count;
};
typedef struct rt_distance_data rt_distance_data_t;
//================================
struct rt_coordinate
{
	rt_uint8_t	x;
	rt_uint8_t	y;
};
typedef struct rt_coordinate rt_coordinate_t;
//================================
#define UserNaumSizeVal			9
struct rt_user_data
{
	rt_uint8_t	DetectionDataFlg;
	rt_uint8_t	UserNaume[UserNaumSizeVal];
	rt_uint8_t	SetSeatPositionAd;
	rt_uint8_t	Gender;
	uint16_Number_t	Weight;
	uint8_Number_t	age;
	rt_uint8_t	TimeH;
	rt_uint8_t	TimeM;
	rt_uint16_t	calorie;
	rt_uint32_t	SportTimeSec;
	rt_uint32_t	SportCal;
	rt_uint16_t	SportKm;
	rt_uint8_t	UserProfileChoose;
	uint8_Number_t userLevel;
	uint8_Number_t userWorkoutTime;
	
};
typedef struct rt_user_data rt_user_data_t;

struct rt_user_name_detection
{
	rt_bool_t	 User_DetectionFlg;
	rt_uint8_t	UserName[UserNaumSizeVal];
};

typedef struct rt_user_name_detection rt_user_name_detection_t;

struct rt_user_name_data
{
	rt_user_name_detection_t	user_1;
	rt_user_name_detection_t	user_2;
	rt_user_name_detection_t	user_3;
	rt_user_name_detection_t	user_4;
	rt_user_name_detection_t	user_5;
	rt_user_name_detection_t	user_6;
	rt_user_name_detection_t	user_7;
	rt_user_name_detection_t	user_8;
	rt_user_name_detection_t	user_9;
	rt_user_name_detection_t	user_10;
};
typedef struct rt_user_name_data rt_user_name_data_t;

struct rt_fouse_count_data
{
	rt_uint8_t	segment;
	rt_uint8_t	resistanceSetting;
	rt_uint8_t	handlePosistion;
	rt_uint8_t	instruction;
};

typedef struct rt_fouse_count_data	rt_fouse_count_data_t;
//========================================================================
extern rt_ui_action_t	ui_action;

extern rt_time_data_t TimeData;

extern rt_sport_data_t	sport_data;

extern rt_calor_data_t calor_count;

extern rt_distance_data_t	distance_data;

extern rt_set_profile_data_t set_profile_data;

extern rt_user_data_t	set_user_data;

extern rt_profile_heartrate_data_t	profile_heartrate_data;

extern rt_set_focus_data_t	set_focus_data;
//================================

typedef void (*app_err_treadmill_handler_t)(rt_uint8_t message);


// Err

#define SpeedErrNumVal					5
#define InclineAutoErrNumVal		6
#define InclineErrNumVal				7
#define InclineAutoOkNumVal			8
//==================================================================
// 计矪瞶 把计
#define cycleNumberVal          0
#define noCycleNumberVal        1

#define NoComplyVal			0
#define YesComplyVal		1
//===================================================================
#define CommonModeVal			0
#define FlickerModeVal		1


//===================================================================
extern	rt_comply_t	F_NumberUp_8(uint8_Number_t *Number_t,rt_uint8_t upNumber,rt_uint8_t mode);

extern rt_comply_t F_NumberUp_16(uint16_Number_t *Number_t,rt_uint16_t upNumber,rt_uint8_t mode);

extern rt_comply_t	F_NumberDown_8(uint8_Number_t *Number_t,rt_uint8_t upNumber,rt_uint8_t mode);

extern rt_comply_t F_NumberDown_16(uint16_Number_t *Number_t,rt_uint16_t upNumber,rt_uint8_t mode);

extern void	F_timer_process_up(rt_time_data_t *time_data);

extern rt_bool_t	F_timer_process_down(rt_time_data_t *time_data);

extern void	F_calorie_process(rt_calor_data_t *calorie_data);

extern void	F_distance_process(rt_distance_data_t *distance_data_t);

extern void	F_RollingHillLevelCount(rt_uint8_t MaxLevel,rt_uint8_t *LevelData,rt_uint8_t DataSize);

extern void	F_PeakLevelCount(rt_uint8_t MaxLevel,rt_uint8_t *LevelData,rt_uint8_t DataSize);

extern void	F_PlateauLevelCount(rt_uint8_t MaxLevel,rt_uint8_t *LevelData,rt_uint8_t DataSize);

extern void	F_ClimbLevelCount(rt_uint8_t MaxLevel,rt_uint8_t *LevelData,rt_uint8_t DataSize);

extern void	F_Interval_1_LevelCount(rt_uint8_t MaxLevel,rt_uint8_t *LevelData,rt_uint8_t DataSize);

extern void	F_Interval_2_LevelCount(rt_uint8_t MaxLevel,rt_uint8_t *LevelData,rt_uint8_t DataSize);

extern void	F_Menual_LevelCount(rt_uint8_t Level,rt_uint8_t *LevelData,rt_uint8_t DataSize);

extern void	F_ProfileTimeSegments(rt_uint8_t *Segments,rt_time_data_t Time,rt_uint8_t SegmentsData,rt_uint8_t MaxSegments);

extern rt_uint32_t F_ChangeKmToMile(rt_uint32_t Data);

extern rt_uint32_t F_ChangeMileToKm(rt_uint32_t Data);
//==================================================================
// Display
#define blankVal					255
#define ShowHiByeVal			1
#define ShowNoHiByeVal		0
//==================================================================
#define time_10ms_val			0x0001
#define time_20ms_val			0x0002
#define time_40ms_val			0x0004
#define time_100ms_val		0x0008
#define time_500ms_val		0x0010
#define time_1s_val				0x0020
#define CpuTime_1s_val		0x0040

extern struct rt_event			sport_timer_event;

extern void	F_cleartTimer(void);

extern void F_startSportTimerInit(void);

//==================================================================
struct rt_inc_init_data
{
		rt_uint8_t		incNum;
		rt_incline_eeprom_data_t incline_eeprom_data;
		app_err_treadmill_handler_t		err_treadmill_handler;
			//rt_uint8_t		incCarryAd;
};

#define InclineMaxAdrVal			19


typedef struct rt_inc_init_data rt_inc_init_data_t;

extern void		rt_incline_control(rt_uint8_t incNum);

extern void		rt_hw_incline_control_init(rt_inc_init_data_t	inc_data_init);

extern void		F_IncCorrectionEnd(void);

extern void		rt_IncCorrectionAdr_1(void);

extern void		rt_IncCorrectionAdr_2(void);

extern void		rt_incline_auto(void);

extern void		rt_incline_stop(void);

extern void		rt_inc_micro_control(rt_uint8_t IncNumAdBuf);

extern rt_uint8_t	rt_inc_read_ad(void);

extern void		rt_read_incline_eeprom_data(rt_incline_eeprom_data_t *data);

extern void		rt_seat_position_up(void);

extern void		rt_seat_position_down(void);

extern void		rt_seat_position_stop(void);

extern rt_uint8_t	rt_inc_read_adr_number(void);

extern void		rt_inc_control_start(rt_uint8_t set_inc);

extern void		rt_inc_control_auto_init(void);

//=========================================================================
extern void F_SysUiStart(void);

extern void F_setNoramal(void);

extern void F_setNoramalInit(void);

extern void F_SportNoramal(void);

extern void F_SportNoramalInit(void);

extern void F_EngMode1(void);

extern void F_EngMode1_Init(void);

extern void F_EngMode1_AutoOk(void);

extern void F_EngMode1_AutoErr(void);

extern void F_setProfiles(void);

extern void F_setProfileInit(rt_uint8_t Event);

extern void F_setProfileChoose(void);

extern void F_setProfileChooseInit(rt_uint8_t Event);

extern void F_setProfileRollingHill(void);

extern void F_setProfileRollingHillInit(void);

extern void F_setProfilePeak(void);

extern void F_setProfilePeakInit(void);

extern void F_setProfilePlateau(void);

extern void F_setProfilePlateauInit(void);

extern void F_setProfileClimb(void);

extern void F_setProfileClimbInit(void);

extern void F_setProfileInterval_1(void);

extern void F_setProfileInterval_1Init(void);

extern void F_setProfileInterval_2(void);

extern void F_setProfileInterval_2Init(void);

extern void F_ProfileSport(void);

extern void	F_ProfileSportInit(rt_uint8_t Evnet);

extern void F_setUsers(void);

extern void F_setUsersInit(rt_uint8_t UserEvent);

extern void F_setUsersNoData(void);

extern void F_setUsersNoDataInit(void);

extern void F_setUsersDataSetInit(void);

extern void F_setUsersData(void);

extern void F_setUsersDataInit(rt_uint8_t	Event);

extern void F_setUsersResetData(void);

extern void F_setUsersResetDataInit(void);

extern void F_setUsersSport(void);

extern void F_setUsersSportInit(void);

extern void F_setProfilesHeartRate(void);

extern void F_setProfilesHeartRateInit(rt_uint8_t Event);

extern void F_setHeartRateFatBurn(void);
	
extern void F_setHeartRateFatBurnInit(void);

extern void F_setHeartRateCardio(void);

extern void F_setHeartRateCardioInit(void);

extern void F_setHeartRateTarget(void);

extern void F_setHeartRateTargetInit(void);

extern void F_ProfilesHeartRateSport(void);

extern void F_ProfilesHeartRateSportInit(rt_uint8_t WorkOutTimeMin,rt_uint8_t Target,rt_uint8_t HeartRateEvent);

extern void F_EngineeringMode(void);

extern void F_EngineeringModeInit(rt_uint8_t Event);

extern void F_setUint(void);

extern void F_setUintInit(void);

extern void F_setBzTest(void);

extern void F_setBzTestInit(void);

extern void F_setLcdTest(void);

extern void F_setLcdTestInit(void);

extern void F_setKeyTest(void);

extern void F_setKeyTestInit(void);

extern void F_eepromErrMode(void);

extern void F_eepromErrModeInit(void);

extern void F_setProfilesFocus(void);

extern void F_setProfilesFocusInit(rt_uint8_t Event);

extern void F_setProfilesFocusData(void);

extern void F_setProfilesFocusDataInit(void);

extern void F_FocusSport(void);

extern void F_FocusSportInit(void);

extern void F_setProfileManual(void);

extern void F_setProfileManualInit(void);

extern void F_manualSport(void);

extern void F_manualSportInit(void);
//===========================================================================

extern void  F_ShowMatrixLcd(rt_uint8_t	lcdRamAdr,rt_uint32_t data,rt_uint8_t dataLongSize,rt_uint32_t *displayAdr);

extern void		F_ShowMatrixLcdChossDot(rt_coordinate_t	adr,rt_uint8_t x_long,rt_uint8_t y_long,rt_uint32_t *displayAdr);

extern void F_ShowMatrixLcdChossReverse(rt_coordinate_t	adr,rt_uint8_t x_long,rt_uint8_t y_long,rt_uint32_t data,rt_uint32_t *displayAdr);

extern void  F_ShowMatrixNumProcessReverse(rt_coordinate_t	adr3,rt_coordinate_t	adr2,rt_coordinate_t	adr1,rt_bool_t ShowHiByeFlg,rt_uint16_t data,rt_uint32_t *displayAdr);

extern void  F_ShowMatrixNumProcess(rt_coordinate_t	adr3,rt_coordinate_t	adr2,rt_coordinate_t	adr1,rt_bool_t ShowHiByeFlg,rt_uint16_t data,rt_uint32_t *displayAdr);

extern void  F_ShowMatrixStringLcdReverse(rt_coordinate_t adr,const rt_uint8_t *asciiString,rt_uint8_t stringSize,rt_uint32_t *displayAdr);

extern void  F_ShowMatrixFontLcdReverse(rt_coordinate_t adr,rt_uint8_t asciiNum,rt_uint32_t *displayAdr);

extern void  F_ShowMatrixStringLcd(rt_coordinate_t adr,const rt_uint8_t *asciiString,rt_uint8_t stringSize,rt_uint32_t *displayAdr);

extern void  F_ShowMatrixFontLcd(rt_coordinate_t adr,rt_uint8_t asciiNum,rt_uint32_t *displayAdr);

extern void  F_ShowMatrixBigNumFontLcd(rt_coordinate_t adr,rt_uint8_t asciiNum,rt_uint32_t *displayAdr);

extern void  F_ShowMatrixBigNumProcess(rt_coordinate_t	adr3,rt_coordinate_t	adr2,rt_coordinate_t	adr1,rt_bool_t ShowHiByeFlg,rt_uint16_t data,rt_uint32_t *displayAdr);

extern void  F_ShowMatrixBigNumProcessReverse(rt_coordinate_t	adr3,rt_coordinate_t	adr2,rt_coordinate_t	adr1,rt_bool_t ShowHiByeFlg,rt_uint16_t data,rt_uint32_t *displayAdr);

//=======================================

extern void  F_Show_8_LcdDot(rt_uint8_t	lcdRamAdr,rt_uint8_t dataDot,rt_uint32_t *displayAdr);

extern void	F_Show_8_FontLcd(rt_uint8_t	adr,rt_uint8_t	dataNum,rt_uint32_t *displayAdr);

extern void  F_Show_8_Lcd(rt_uint8_t	adr3,rt_uint8_t	adr2,rt_uint8_t	adr1,rt_bool_t ShowHiByeFlg,rt_uint16_t data,rt_uint32_t *displayAdr);
//=======================================
extern void	F_readWatte(rt_uint8_t adr,rt_uint16_t *watt);
//=======================================
extern void IWDG_Config(unsigned char timeout);
//=======================================
extern rt_uint16_t	F_readRpm(void);
//=======================================

extern void	F_showNoramal(void);

extern void	F_showMatrixTime(rt_time_data_t TimeData);

extern void	F_showMatrixProfileWrokOutTime(rt_time_data_t TimeData);

extern void	F_showResistance(rt_uint8_t resistance);

extern void	F_showMaxResistance(rt_uint8_t resistance);

extern void	F_show8HearRate(rt_uint8_t HandHeartRate,rt_uint8_t wHeartRate);

extern void	F_showHearRateGraph(rt_uint8_t HandHeartRate,rt_uint8_t wHeartRate);

extern void	F_show8Time(rt_time_data_t TimeData);

extern void	F_showCal(rt_uint32_t Cal);

extern void	F_showDistance(rt_uint32_t DistanceNum,rt_bool_t Unit);

extern void	F_showMatrixCal(rt_uint32_t Cal,rt_uint32_t CalHour);

extern void	F_showIncAd(rt_uint8_t IncAdNum);

extern void	F_showTargetIncAd(rt_uint8_t IncAdNum);

extern void	F_showEngIncAdr1(void);

extern void	F_showEngIncAdr2(void);
	
extern void	F_showEngIncOk(void);

extern void	F_showEngIncErr(void);

extern void	F_showProfileReverse(void);

extern void	F_showManualReverse(void);

extern void	F_showHeartReverse(void);

extern void	F_showFocusReverse(void);

extern void	F_showMetsReverse(void);

extern void	F_showUsers_1(rt_user_name_detection_t user_1,rt_user_name_detection_t user_2,rt_user_name_detection_t user_3);

extern void	F_showUsers_2(rt_user_name_detection_t user_1,rt_user_name_detection_t user_2,rt_user_name_detection_t user_3);

extern void	F_showUsers_3(rt_user_name_detection_t user_1,rt_user_name_detection_t user_2,rt_user_name_detection_t user_3);

extern void	F_showUsers_4(rt_user_name_detection_t user_2,rt_user_name_detection_t user_3,rt_user_name_detection_t user_4);

extern void	F_showUsers_5(rt_user_name_detection_t user_3,rt_user_name_detection_t user_4,rt_user_name_detection_t user_5);

extern void	F_showUsers_6(rt_user_name_detection_t user_4,rt_user_name_detection_t user_5,rt_user_name_detection_t user_6);

extern void	F_showUsers_7(rt_user_name_detection_t user_5,rt_user_name_detection_t user_6,rt_user_name_detection_t user_7);

extern void	F_showUsers_8(rt_user_name_detection_t user_6,rt_user_name_detection_t user_7,rt_user_name_detection_t user_8);

extern void	F_showUsers_9(rt_user_name_detection_t user_7,rt_user_name_detection_t user_8,rt_user_name_detection_t user_9);

extern void	F_showUsers_10(rt_user_name_detection_t user_8,rt_user_name_detection_t user_9,rt_user_name_detection_t user_10);

extern void	F_showRollingHillGraph(void);

extern void	F_showPeakGraph(void);

extern void	F_showPlateauGraph(void);

extern void	F_showClimbGraph(void);

extern void	F_showInterval_1_Graph(void);

extern void	F_showInterval_2_Graph(void);

extern void	F_showProfileSetLeve(rt_uint8_t Level);

extern void	F_showProfileSetWorkoutTime(rt_time_data_t TimeData);

extern void	F_ShowProgfileGraph(rt_uint8_t *LevelData,rt_uint8_t DataSize,rt_uint8_t Mode,rt_uint8_t SegmentsAdr,rt_bool_t FlickerFlg);

extern void	F_showNoData(void);

extern void	F_showSetUserName(rt_uint8_t adr,rt_uint8_t *data,rt_uint8_t size);

extern void	F_showUserName(rt_uint8_t *data,rt_uint8_t size);

extern void	F_showSetSeatPosition(void);

extern void	F_showSeatPositionStatus(rt_uint8_t event);

extern void	F_showGender(rt_uint8_t Gender);

extern void	F_showSetAge(rt_uint8_t Age);

extern void	F_showSetWeight(rt_uint16_t Weight);

extern void	F_showTimeMilesCal(rt_time_data_t TimeData,rt_uint16_t	KM,rt_uint32_t	Cal,rt_bool_t UnitFlg);

extern void	F_showResetDataYesNo(rt_uint8_t YesNo);

extern void	F_showFatburn(void);

extern void	F_showCardio(void);

extern void	F_showTarget(void);

extern void	F_showSetTargetNum(rt_uint8_t target,rt_uint8_t Dot);

extern void	F_ShowUnit(void);

extern void	F_ShowSoftwareVersion(void);

extern void	F_ShowBeeperTest(void);

extern void	F_ShowDisplayTest(void);

extern void	F_ShowKeypedTest(void);

extern void	F_ShowSeatLiftInstall(void);

extern void	F_ShowChooseMetric(void);

extern void	F_ShowChooseEnglish(void);

extern void	F_ShowChooseBz1(void);

extern void	F_ShowChooseBz2(void);

extern void	F_ShowChooseBz3(void);

extern void	F_ShowKeyNum(rt_uint8_t	Num);

extern void	F_Show_8_DotDisplay(rt_uint8_t	Num);

extern void	F_ShowMatrixDotDisplayTest(rt_uint32_t	Num);

extern void	F_ShowEepromErr(void);

extern void	F_ShowChooseTotalBody(void);

extern void	F_ShowChooseArms(void);

extern void	F_ShowChooseLegs(void);

extern void	F_ShowMaximumResistanceLevel(rt_uint8_t Level);

extern void	F_ShowStartReverse(void);

extern void	F_ShowSettingsReverse(void);

extern void	F_ShowUserTotalReverse(void);

extern void	F_ShowTotalBodyFocus(rt_uint8_t FocusSegment);

extern void	F_ShowArmsFocus(rt_uint8_t FocusSegment);

extern void	F_ShowLegsFocus(rt_uint8_t FocusSegment);

extern void	F_ShowMexLevel(rt_uint8_t MexLevel);

extern void	F_Show8Rpm(rt_uint16_t Rpm);

//=======================================
extern void	F_SwitchingSeatPositionDisplayTimer(void);

extern void	F_SeatPositionControlAllKey(rt_uint8_t *Key,rt_bool_t LongKeyStartFlg);

extern void	F_SetUserKey(rt_uint8_t keyCode);

extern void	F_SetProgramsKey(rt_uint8_t keyCode);

extern void	F_LongRestKey(rt_uint8_t keyCode);

extern void	F_VmsDetection(rt_uint8_t rpm,rt_uint8_t resistance);

extern void	F_setVmsDetectionVal(rt_uint8_t val);

#endif
