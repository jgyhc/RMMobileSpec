//
//  FXDefine.h
//  cqfxplus
//
//  Created by 许 飞 on 14-5-15.
//  Copyright (c) 2014年 frank xu. All rights reserved.
//

#ifndef cqfxplus_FXDefine_h
#define cqfxplus_FXDefine_h

#ifdef DEBUG
    #define FXLOG(xx, ...)  NSLog(@"%s(%d): " xx, __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
    #define FXLOG(xx, ...)  ((void)0)
#endif


static NSString * const kSearchStartTime = @"RECORDSTARTTIME";
static NSString * const kSearchEndTime = @"RECORDENDTIME";
static NSString * const kSearchChanel = @"RECORDCHANNEL";
static NSString * const kSearchRecordType = @"RECORDTYPE";

#define PLAY_PROCESS 0x2000
#define PLAY_END     0x2001


typedef enum : NSUInteger {
    DEV_N9,
    DEV_N9M,
    DEV_808,
    DEV_CMS,
    DEV_MVSP,
    DEV_1078,
} DEV_TYPE;

typedef enum : NSUInteger {
    Tripod_UP = 1,
    Tripod_Down,
    Tripod_Left,
    Tripod_Right,
    Tripod_IRISOPEN,//光圈大
    Tripod_IRISCLOSE,//光圈小
    Tripod_ZOOMin,//调焦缩
    Tripod_ZOOMOUT,//调焦伸
    Tripod_FOCUSNEAR,//聚焦近
    Tripod_FOCUSFAR,//聚焦远
    Tripod_AUTOSCAN,//自动水平转动
    Tripod_BRUSHON,//雨刷启
    Tripod_BRUSHOFF, //雨刷停
    Tripod_RESET,//设置预置点
    Tripod_RECALL,//启用预置点
    Tripod_CRUISE,//启动巡航
    Tripod_CLEARPRESET,//清除预置点
    Tripod_SPEED,//速度
    Tripod_STOPCRUISE,//停止巡航
    Tripod_STOP,//停止
    Tripod_CLEAR_ALLPRESET,//清除全部预置点
    Tripod_LeftUP,//左上
    Tripod_RightUP,//右上
    Tripod_LeftDown,//左下
    Tripod_RightDown,//右下
    Tripod_LightOpen,//灯光打开
    Tripod_LightClose,//灯光关闭

}Enum_Tripod_head;
typedef enum : NSInteger {
    ERROR_SUCCESS,
    ERROR_TIMEOUT,
    ERROR_PARAM,
    ERROR_NETWROK,
    ERROR_USERORPASSWORD,
    ERROR_NORIGHT,
    ERROR_FAILED,
    ERROR_NOFILE,
    ERROR_ERRORCODE,
    ERROR_TASKCOMPLETE,
    ERROR_TOOMANYUSERONLINE,
    ERROR_DEVICEOFFLINE,
    ERROR_USEREXPIRED
} ERROR_CODE;

typedef enum : NSUInteger {
    NETREQUEST_ALARM,
    NETREQUEST_GPS,
    NETREQUEST_STATUS,
    NETREQUEST_FAULTREPORT,
    NETREQUEST_SETDEFAULT,
    NETREQUEST_FORMATDISK,
    NETREQUEST_FAULTERPORTHISTORY
} NETREQUEST_ATTRIBUTE;

typedef enum : NSUInteger {
    STREAM_SUB,//子码流
    STREAM_MAIN,//主码流
    STREAM_IMAGE,//镜像码流
    STREAM_SUBANDMAIN,//主码流+子码流
} STREAM_TYPE;

typedef enum : NSUInteger {
    PROTOCOL_TCP,
    PROTOCOL_UDP,
} NET_PROTOOL;

typedef enum : NSUInteger {
    FRAME_VIDEO_I=0,
    FRAME_VIDEO_P=2,
    FRAME_AUDIO=1,
    FRAME_YUV422=5
}FRAME_TYPE;

typedef enum : NSUInteger {
    DEV_ONLINE,
    DEV_OFFLINE,
    DEV_ALARM_TOTAL,
    DEV_ALARM_SPEED,
    DEV_ALARM_IO,
    DEV_ALARM_FENCE,
    DEV_ALARM_VIDEOLOSS,
    DEV_ALARM_EMOTION,
    DEV_TASK_COMPLTED,
    DEV_TASK_FAILED,
    DEV_STATUS_NOTIFY,
	DEV_TALK_START,
    DEV_DRIVER_REGISTER,
    DEV_TASK_UPEVENTSTATUS,
    DEV_TASK_PROXY,
    DEV_STATUS_UPDATE
} DEV_STATE;

typedef enum : NSUInteger {
    VEHICLE_REPORT_SPEED,
    VEHICLE_REPORT_ONLIE,
    VEHICLE_REPORT_ALARM
} VEHICLE_REPORT_TYPE;

typedef enum : NSUInteger {
    GROUP_REPORT_ONLINEPERCENT,
    GROUP_REPORT_SERVERSTATE,
    GROUP_REPORT_REPAIR,
} GROUP_REPORT_TYPE;


/*
bright    亮度
chorma    色度
contrast  对比度
satura    饱和度
*/
typedef enum : NSUInteger {
    STREAM_BRIGHT,
    STREAM_CHORMA,
    STREAM_CONTRAST,
    STREAM_SATURA
} STREAMPARAM_TYPE;

typedef enum : NSUInteger {
    PLAYBACK_PLAYING,
    PLAYBACK_BUFFERING,
    PLAYBACK_FRAMEINFO,
    PLAYBACK_END,
    PLAYBACK_DEVERRORCODE
} PLAYBACK_MSG_TYPE;

typedef enum : NSUInteger {
    RECORD_NORMAL,
    RECORD_ALARM,
    RECORD_LOCK,
	RECORD_NONE
} RECORD_TYPE;

typedef enum : NSUInteger {
    UPGRADE_FIREWARE=1000,
    UPGRADE_MCU,
    UPGRADE_CP4,
    UPGRADE_IPC=1010,
    UPGRADE_4G=1020,
    UPGRADE_GDS=1030,
    UPGRADE_P2=1040,//p2固件
    UPGRADE_P2TOF=1050,//p2单片机
    UPGRADE_OBD = 1060,//OBD升级
    UPGRADE_RWATCH = 1070,//RWatch升级
    UPGRADE_PRINTER = 1080,//打印机升级
	UPGRADE_CANBOX = 1090,//Canbox升级
	UPGRADE_AudibleVisual = 1100,//声光报警
    UPGRADE_GPSVisual = 1110,//GPS
    UPGRADE_DoubleAudibleVisual = 1120,//双声光报警
    UPGRADE_ControlBox = 1130,//控制盒
    UPGRADE_TemperaturePanel = 1140, //测温面板
    UPGRADE_doubleRwatch = 1150, //Rwatch
    UPGRADE_NewAudibleVisual = 1160,//新版声光报警,
    UPGRADE_mostRwatch = 1170, //Rwatch
    UPGRADE_PowerBox = 1180,
    UPGRADE_CP7AI = 1190, //CP7AI
    UPGRADE_CARMODEL = 1200,//车型文件
    UPGRADE_CARMODEL_FILE = 1201,//车型文件包含文件id
    UPGRADE_TPZ = 1210,//TPZ
    UPGRADE_SERIALHUB = 1220,//扩展盒
    UPGRADE_MOTIONSENSOR = 1300,//motionsensor
    CLEAR_CAR_MODEL = 1310,
    GET_CAR_MODEL = 1320,
    SET_CAR_MODEL = 1330,
} UPGRADE_TYPE;

typedef enum : NSUInteger {
    DELETE_AImp3File = 1700,
    DELETE_SchoolBusmp3File,
    DELETE_CHECKFILE,
    IMPORTFILE_CAN,
    EXPORTFILE_CAN,
    EXPORT_ELECTRON_PARAM,
    IMPORT_ELECTRON_PARAM,
    EXPORT_NETWORK_PARAM,
    IMPORT_NETWORK_PARAM,
    EXPORT_PARTHOST_PARAM,
    IMPORT_PARTHOST_PARAM,
    CLEAR_KEY,
    IMPORT_KEY,
    EXPORTFILE_USERLOG_1062_2,
    START_AVM_CALIBRATE,
    QUERY_AVM_RESULT,
    EXPORT_AVM_CONFIG,
    IMPORT_AVM_CONFIG,
    IMPORTFILE_WATER_FILE,
    RESTORE_ANDRIODINIT//安卓初始化
    




}DELETEFILE_TYPE;
//importtype
typedef enum : NSUInteger {
    IMPORTFILE_IMPOER_STARTTAG = 1299,
    IMPORTFILE_CONFIG,
    IMPORTFILE_GDSCONFIG_FILE,
    IMPORTFILE_EFENCE_FILE,
    IMPORTFILE_HWTABLE_FILE,
    IMPORTFILE_EVIDENCE_FILE,
    IMPORTFILE_DSM_ALARM,
    IMPORTFILE_DSM_CONFIG,
    IMPORTFILE_SERVER_CONFIG,
    IMPORTFILE_IPC_CONFIG,
    DRIVER_RESP_SURE,
    IMPORT_CAMERA_CONFIG,
    IMPORT_PASSENGER_PARAM_FILE,
    IMPORT_C34CAMERA_CONFIG,
    IMPORT_MOTIONSENSOR_CONFIG,
    DEVICE_RESTART,
    Comback_defaultSetting,
    SELECT_LOG_PRINTLEVEL,
    IMPORT_mp3File,
    IMPORT_AImp3File,
    IMPORT_PANEL_CONFIG,
      EXPORT_PANEL_CONFIG,
      UPDATE_PANEL_CONFIG,
      RESET_PANEL_CONFIG,
  

} IMPORTFILE_TYPE;
typedef enum : NSUInteger {
    EXPORTFILE_CONFIG=1100,
    EXPORTFILE_ALARM,
    EXPORTFILE_BLACKBOX,
    EXPORTFILE_USER,
    EXPORTFILE_IMAGE,
    EXPROTFILE_ROUTERLOG,
    EXPROTFILE_MEATDATA,
    EXPORTFILE_PRINTBACKUPFILE,
    EXPORTFILE_GDSCONFIG_FILE,
    EXPORTFILE_EFENCE_FILE,
    EXPORTFILE_HWTABLE_FILE,
    EXPORTFILE_EVIDENCE_FILE,
    EXPORT_PASSENGER_FLOW_FILE,
	EXPORTFILE_PASSENGER_STATISTICS_FILE,
	EXPORTFILE_PASSENGER_PARAM_FILE,
	EXPORTFILE_DSM_ALARM,
    EXPORTFILE_CAMERA_CONFIG,
    EXPORTFILE_EVIDENCE_CONFIG,
    EXPORTFILE_EVIDENCE_BLACKANDPIC,
    EXPORTFILE_GPS_RESOURCE,
   EXPORTFILE_FACE_RESOURCE,
    EXPORTFILE_LOG_PRINTLEVEL,
    EXPORTFILE_MOTIONSENSOR_CONFIG,
    EXPORTFILE_MOTIONSENSOR5_CONFIG,
    EXPORTFILE_C34CAMERA_CONFIG,
    EXPORTFILE_DSM_CONFIG,
    EXPORTFILE_LICENSE_MATTING,
    RESET_IPC_CONFIG,
    EXPORTFILE_USERLOG_1062
  
} EXPORTFILE_TYPE;

typedef enum : NSUInteger {
    BACKUP_RECORDFILE=1200,
    BACKUP_BLACKBOX,
    BACKUP_AVI,
    BACKUP_ALL,
    BACKUP_MP4
} BACKUP_TYPE;


typedef enum : NSUInteger {
    FORMAT_N9M=0,
    FORMAT_FAT32=1,
    FORMAT_DEFAULT,
    
} FORMAT_TYPE;

typedef enum:NSInteger {
    USER_Role_Super=0,
    USER_Role_PL=1,
    USER_Role_ET
} USER_Role;
typedef enum : NSUInteger {
    USER_SUPER=1,
    USER_MANAGER,
    USER_NORMAL,
    USER_SECONDMANAGER,
    USER_EXTENSIONMANAGER,//C6D2.0网阔项目屏蔽导入
    USER_SCHOOL,
    USER_POLICE,

} USER_LEVEL;

// 190版本专用
typedef enum : NSUInteger {
    USER_NOTHING190=0, // 没有任何权限，直接提示登录失败
    USER_NORMAL190,
    USER_MANAGER190,
    USER_SUPER190,
} USER_LEVEL190;

typedef enum : NSInteger {
    DISK_NONE = -1,
    DISK_HDD=0,
    DISK_SD,
    DISK_PROTECTED
} DISK_TYPE;


typedef enum :NSUInteger {
    ENCRYPT_MD5_NORMAL,
    ENCRYPT_MD5_SV
}ENCRYPT_TYPE;


typedef enum :NSUInteger {
    EXTERNDEV_GDS = 0,
    
}EXTERNDEV_TYPE;

typedef enum : NSUInteger {
    REMOTE_PARAMFILE_MDVR = 0,
    REMOTE_PARAMFILE_GDS = 1,
} REMOTE_PARAMFILE_TYPE;

typedef enum : NSUInteger {
    REMOTE_UPGRADE_MDVR = 0,
    REMOTE_UPGRADE_GDS = 1,
    REMOTE_UPGRADE_OBD = 2,
} REMOTE_UPGRADE_TYPE;

typedef enum : NSUInteger {
    SENDFILE_MAINTAIN = 0,//运维记录文件，多个文件打包zip后生成，文件名称格式2222222222.ML(22222,为10为时间戳)
} SENDFILE_TYPE;


typedef enum : NSUInteger {
    LOCATION_SERVER = 0,//运维文件保存到服务器
    LOCATION_SDCARDORUDISK = 1,//运维文件保存到sd卡或U盘
} LOCATION_TYPE;



//AHD 摄像机，遥控器操作类型，分别为： 菜单/OK  ,上 ， 下 ，左， 右
typedef enum : NSUInteger {
    AHD_OPR_MENU_OK,
    AHD_OPR_UP,
    AHD_OPR_DOWN,
    AHD_OPR_LEFT,
    AHD_OPR_RIGHT
} AHD_OPR_TYPE;

typedef NS_OPTIONS(NSUInteger, RMLogLevel) {
    RMLogLevelNone =         0,
    RMLogLevelNormal =       1,
    RMLogLevelDebug =   1 << 2,
    RMLogLevelTrace =   1 << 3,
    RMLogLevelVideo =   1 << 8,
    RMLogLevelTmp =     1 << 9,
    RMLogLevelAll = RMLogLevelNormal | RMLogLevelDebug | RMLogLevelTrace | RMLogLevelVideo | RMLogLevelTmp,
};

typedef NS_ENUM(NSUInteger, RMRemoteServerProtocol) {
    RMRemoteServerProtocolUnknown = 0,
    RMRemoteServerProtocolGT,
    RMRemoteServerProtocolCeiba264,
};

typedef void(^DataBlock)(ERROR_CODE nReturn,NSDictionary* callbackdata) ;
typedef void(^ProcessBlock)(ERROR_CODE nReturn,NSMutableDictionary* callbackdata);

#endif
