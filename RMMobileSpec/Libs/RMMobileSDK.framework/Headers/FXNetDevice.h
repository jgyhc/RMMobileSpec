//
//  FXNetDevice.h
//  cqfxplus
//
//  Created by 许 飞 on 14-5-15.
//  Copyright (c) 2014年 frank xu. All rights reserved.
//

/* description:

 any dvr/mdvr/808/nvr/ipc is a netdevice.
 
*/

#import <Foundation/Foundation.h>
#import "FXDefine.h"
#import "NetDeviceInfo.h"
#import "FXFileHeaderInfo.h"
//#define BSD_CUSTOMER_NAME @"CUSTOMER_04.1302"

#define BSD_CUSTOMER_NAME @"CUSTOMER_04.1206"

@protocol FXNetDeviceDelegate;
@protocol FXNetDeviceRecordeDelegate;

@interface FXNetDevice : NSObject

+ (void)setLogLevel:(RMLogLevel)logLevel;

@property(nonatomic,assign)NSUInteger hDevice;
//被更换设备deviceStreamArr
@property(nonatomic,strong)NetDeviceInfo* netDeviceinfo;
@property(nonatomic,strong)FXFileHeaderInfo *fileHeaderInfo;
@property(nonatomic, weak)id<FXNetDeviceDelegate> delegate;
@property(nonatomic, weak)id<FXNetDeviceRecordeDelegate> recordeDelegate;

- (NSString *)getTimeZoneDic:(NSString *)timeEx;

//打开对讲提示音
@property (nonatomic,assign) BOOL isTalkReminder;
+ (FXNetDevice *)sharedInstanceWithDeviceinfo:(NetDeviceInfo *)deviceinfo;
-(id)initWithDeviceinfo:(NetDeviceInfo*)info;
+ (void)setMosaicOn:(BOOL)on;
-(ERROR_CODE)loginServer;
-(ERROR_CODE)loginDevice;
-(void)loginDeviceBlock:(void (^)(ERROR_CODE errorCode))completion;
-(ERROR_CODE)logoutDevice;

-(ERROR_CODE)requestInfo:(NETREQUEST_ATTRIBUTE)rquest Return:(DataBlock)callback;
-(ERROR_CODE)sendDataToDevice:(NSString*)data;
-(ERROR_CODE)getDataFromDevice:(NSString*)data Return:(DataBlock)callback;
-(ERROR_CODE)openTalk;
-(ERROR_CODE)closeTalk;
-(ERROR_CODE)openTalkWithReminderData:(NSData *)fileData;
-(ERROR_CODE)restartDevice;
-(ERROR_CODE)adjustSixAxis;

-(ERROR_CODE)adjustSixAxisWithExtern:(EXTERNDEV_TYPE)type;
-(ERROR_CODE)setGeneralDevCtrlWithChannel:(NSInteger)channel Signal:(NSInteger)signal;
-(ERROR_CODE)getGeneralDevCtrl:(DataBlock)block;
-(ERROR_CODE)netSnapshot:(NSInteger)channel savePath:(NSString*)picPath;

-(ERROR_CODE)netSnapAVMshotsavePath:(NSString *)picPath is4K:(NSInteger)is4K;
-(NSString*)getDeviceNameInfo;

/*nsdictionary format
 4Key：           Value:
 BRIGHT    亮度    NSNumber
 CHORMA    色度    NSNumber
 CONTRAST  对比度  NSNumber
 SATURA    饱和度  NSNumber
 */

-(void)setNetStreamParamChannel:(NSInteger)channel Value:(NSDictionary*)values;
-(ERROR_CODE)getNetStreamParam:(DataBlock)block;
/*
 重置ipc
channelarr: <Nstring*> 频道
 maindevice: 0：主机设备 1:从机设备
*/
-(ERROR_CODE)setIPCResetDataWithChannel:(NSArray *)channelarr WithMainDevice:(NSInteger)maindevice withCallBack:(DataBlock)callback;
-(ERROR_CODE)getPortConfigInfo:(DataBlock)block;
-(ERROR_CODE)getPortConfigInfo;
-(ERROR_CODE)setDefaultConfig:(DataBlock)block;
- (void)getAlarmAdudioWithChannelBit:(NSInteger)channelBit WithSLavArrBit:(NSArray *)slavpostionArr;
//diskinde : hard disk index number ,like :0 1 2
//formattype:hdd default
//           sd udisk can selecte format type
-(ERROR_CODE)formatDisk:(NSInteger)diskIndex formatType:(FORMAT_TYPE)formatType Return:(DataBlock)callback;
-(ERROR_CODE)getDeviceStorageInfo:(DataBlock)callback;
-(NSDictionary*)getDeviceStorageInfo;
-(ERROR_CODE)selectFileReturn:(DataBlock)callback;
- (ERROR_CODE)setPrintLevelArray:(NSArray *)levelarr Return:(DataBlock)callback;
-(ERROR_CODE)getServerStateAndInfo:(DataBlock)callback;
-(ERROR_CODE)getIOStatus:(DataBlock)callback;
- (NSDictionary*)getIOStatus;
//获取串口信息
-(ERROR_CODE)getDEVgenalStatus:(DataBlock)callback;
-(NSDictionary*)getIOStateInfo;


-(ERROR_CODE)upgradeFile:(UPGRADE_TYPE)versionType Return:(DataBlock)callback;
-(ERROR_CODE)getUpgradeProcess:(UPGRADE_TYPE)versionType Return:(ProcessBlock)callback;

-(ERROR_CODE)setMotionAreaInfo:(NSDictionary *)motionAreaInfo;
-(ERROR_CODE)upgradeFile:(UPGRADE_TYPE)versionType IPCCHN:(NSInteger)channel Return:(DataBlock)callback;
-(ERROR_CODE)getUpgradeProcess:(UPGRADE_TYPE)versionType IPCCHN:(NSInteger)channel Return:(ProcessBlock)callback;
- (ERROR_CODE)controlPassengersNumWithDoorNum:(NSInteger)doorNum WithCMD:(NSInteger)CMD  withcallBack:(DataBlock)callback;

- (ERROR_CODE)requrstDoorMessagewirhDoorNum:(NSInteger)doorNum withcallBack:(DataBlock)callback;
/**
 升级P2 客流统计仪固件以及客流统计仪单片机

 @param versionType 升级类型，详细见枚举参数
 @param p2Type P2安装位置0-前门  1-中门  2-后门
 @param callback 回调信息
 @return 错误码
 */
-(ERROR_CODE)upgradeFile:(UPGRADE_TYPE)versionType P2Type:(NSInteger)p2Type Return:(DataBlock)callback;
-(ERROR_CODE)getUpgradeProcess:(UPGRADE_TYPE)versionType P2Type:(NSInteger)p2Type Return:(ProcessBlock)callback;

//Time 格式:20110928090109 依次表示年月日时分秒
-(ERROR_CODE)exportFile:(EXPORTFILE_TYPE)fileType STTime:(NSString*)stTime ENDTime:(NSString*)endTime isAllTime:(BOOL)isalltime  isEncryption:(BOOL)encryption Return:(DataBlock)callback;
-(ERROR_CODE)getExportFileProcess:(EXPORTFILE_TYPE)fileType Return:(ProcessBlock)callback;

-(ERROR_CODE)importFile:(IMPORTFILE_TYPE)fileType Return:(DataBlock)callback;

- (ERROR_CODE)ctrlFileforCMD2:(NSInteger)fileType Return:(DataBlock)callback;
-(ERROR_CODE)acceptanceModeWithcome:(NSInteger)comeinMode Return:(DataBlock)callback;
-(ERROR_CODE)getImportFileProcess:(IMPORTFILE_TYPE)fileType Return:(ProcessBlock)callback;
-(ERROR_CODE)backupEvidenceRecordFileSTTime:(NSString*)stTime ENDTime:(NSString*)endTime Return:(DataBlock)callback;
-(ERROR_CODE)backupRecordFile:(BACKUP_TYPE)recordType STTime:(NSString*)stTime ENDTime:(NSString*)endTime Channel:(NSInteger)channelbit Return:(DataBlock)callback;
-(ERROR_CODE)backupRecordFile:(BACKUP_TYPE)recordType STTime:(NSString*)stTime ENDTime:(NSString*)endTime Channel:(NSInteger)channelbit StreamType:(STREAM_TYPE)streamtype Return:(DataBlock)callback;
-(ERROR_CODE)backupRecordFile:(BACKUP_TYPE)recordType STTime:(NSString*)stTime ENDTime:(NSString*)endTime Channel:(NSInteger)channelbit StreamType:(STREAM_TYPE)streamtype diskType:(DISK_TYPE)disktype Return:(DataBlock)callback;
- (ERROR_CODE)getTemperaturePanel:(DataBlock)callback;
- (ERROR_CODE)modifyEvidenceInfoEid:(NSString*)recordid WithType:(NSInteger)type videoInfo:(NSDictionary *)info withcallBack:(DataBlock)callback;

- (ERROR_CODE)requestEvidenceListwithcallBack:(DataBlock)callback;
- (ERROR_CODE)getPicListwithcallBack:(DataBlock)callback;
-(ERROR_CODE)getBackupRecordFileProcess:(BACKUP_TYPE)recordType Return:(ProcessBlock)callback;

-(ERROR_CODE)stopTask:(int)taskType Return:(ProcessBlock)callback;
- (ERROR_CODE)driverRegisterWithDriverName:(NSString *)driverName
                          WithDriverNumber:(NSString *)driverNumber WithPicUUId:(NSString *)picuuid WithPicTIme:(NSString *)pictime;

-(ERROR_CODE)getFileTotalSize:(STREAM_TYPE)streamType STTime:(NSString*)stTime ENDTime:(NSString*)endTime Channel:(NSInteger)channelBit Return:(DataBlock)callback;
-(NSDictionary*)getFileTotalSize:(STREAM_TYPE)streamType STTime:(NSString*)stTime ENDTime:(NSString*)endTime Channel:(NSInteger)channelBit;

-(NSDictionary*)getFileTotalSize:(STREAM_TYPE)streamType STTime:(NSString*)stTime ENDTime:(NSString*)endTime diskType:(DISK_TYPE)disktype Channel:(NSInteger)channelBit;

-(ERROR_CODE)verifyStorageWithIndex:(NSArray *)indexArr block:(DataBlock)block;
-(ERROR_CODE)getBlackBoxTotalSize:(STREAM_TYPE)streamType STTime:(NSString*)stTime ENDTime:(NSString*)endTime Channel:(NSInteger)channelBit Return:(DataBlock)callback;
-(NSDictionary*)getBlackBoxTotalSize:(STREAM_TYPE)streamType STTime:(NSString*)stTime ENDTime:(NSString*)endTime diskType:(DISK_TYPE)disktype Channel:(NSInteger)channelBit;
//获取从机版本号
-(ERROR_CODE)getDeviceAllVersionInfo:(DataBlock)callback;
- (void)getERUIDicWithCHN:(NSNumber *)chn With:(NSNumber *)DT;
- (void)setTemparePanelWithPTmask:(NSNumber *)door;
-(ERROR_CODE)getDeviceVersionInfo:(DataBlock)callback;
-(NSDictionary*)getDeviceVersionInfo;
-(ERROR_CODE)requestOperationStatus:(DataBlock)block;

//indexchannel = -1 return all ipc versions
//normal : indexchannel 0-255
-(ERROR_CODE)getIPCVersionsIndex:(NSInteger)indexChannel Return:(DataBlock)callback;
-(ERROR_CODE)getRemoteDeviceInfo:(DataBlock)callback;
-(ERROR_CODE)getDeviceStateConnectServer:(DataBlock)callback;
//just support cp4
-(ERROR_CODE)getUpgradefileInfo:(UPGRADE_TYPE)type Return:(DataBlock)callback;
-(ERROR_CODE)getUpgradefileSwInfo:(DataBlock)callback;


- (ERROR_CODE)openPublicAPIWithType:(NSInteger)type ;
- (ERROR_CODE)closePublicAPIWithType:(NSInteger)type ;

-(ERROR_CODE)setDevParamInfo:(NSDictionary *)dict;
-(ERROR_CODE)getDevParamInfo:(NSInteger)type Return:(DataBlock)callback;
- (NSDictionary *)getDevParamInfoWithDic:(NSDictionary *)dic;
- (ERROR_CODE)getDevParamInfoWithDic:(NSDictionary *)dic Return:(DataBlock)callback;
- (ERROR_CODE)getDevDefaultParamInfoWithDic:(NSDictionary *)dic Return:(DataBlock)callback;
-(ERROR_CODE)getDevDefaultParamInfo:(NSInteger)type Return:(DataBlock)callback;
-(ERROR_CODE)setUploadGPSInfo:(BOOL)bOpen Return:(DataBlock)callback;
-(ERROR_CODE)setUploadAUTest:(BOOL)bOpen Return:(DataBlock)callback;
- (ERROR_CODE)setGPSOSDHidden:(BOOL)ishidden Return:(DataBlock)callback;
-(ERROR_CODE)setUploadDriverReturn:(DataBlock)callback;
-(ERROR_CODE)sendSMSWithContent:(NSString *)content Flag:(NSInteger)flag Time:(NSInteger)time Return:(DataBlock)callback;
- (ERROR_CODE)controlcloudTableWithChannel:(NSInteger)channel WithPtzcmd:(NSInteger)ptzcmd WithSpeed:(NSInteger)speed  WithPSP:(NSInteger)PSP datacallback:(DataBlock)callback;
-(NSArray *)getUserRight;

/**
 @description:获取当前通道设备状态信息（含REI的使能状态信息bit2），
              由于先增加的REI功能，函数名为兼容保持原有名称
 
 @param statusbit bit0-编码状态 bit1-时移状态 bit2-预览回放使能状态 bit3-通道属性状态，bit4-P2状态 bit5-BWC状态
 @param callback
 @return 错误码
 */
-(ERROR_CODE)getCHNEnableAndLiveStatusInfo:(NSInteger)statusbit Return:(DataBlock)callback;


/**
 @description:AHD摄像机参数控制操作，通过AHD自身弹出的菜单实现
 
 @param channe:通道号
 @param operattype:遥控器菜单操作类型
 @param taskid:任务号码，为了避免快速多次操作返回值统一
 @return 错误码
 */
-(ERROR_CODE)controlAHDCameraChannel:(NSInteger)channel OperaType:(AHD_OPR_TYPE)operatype TaskID:(NSInteger)taskid;



/**
 获取设备通用状态接口，可自己定义获取哪些部分参数

 @param statusBit bit0-通信模块 bit1-wifi模块  bit2-gps  bit3-蓝牙  bit4-通道信息 bit5-存储设备 
                  bit6-车钥匙   bit7-IO状态    bit8-服务器状态
 @return 
 */
-(ERROR_CODE)getDeviceGenralStatus:(int)statusBit Return:(DataBlock)callback;
- (NSDictionary *)getDeviceGenralStatus:(int)statusBit;
/**
 获取设备当前的UTC时间

 @return UTC时间信息+时区信息 ,解析见 3.4.5.11章节
 */
-(NSDictionary*)getDeviceUTCTime;


/**
 获取温度单位信息

 @return 温度单位信息 0 是摄氏度  1 是华氏度
 
 华氏度(℉)=32+摄氏度(℃)×1.8，
 摄氏度(℃)=（华氏度(℉)-32）÷1.8
 */
-(NSDictionary*)getTEMPUnit;


-(ERROR_CODE)getOSDChannelInfo:(DataBlock)callback;

-(ERROR_CODE)remoteImportParamFile:(REMOTE_PARAMFILE_TYPE)fileType Filepath:(NSString*)filepath;
-(ERROR_CODE)remoteExportParamFile:(REMOTE_PARAMFILE_TYPE)fileType Filepath:(NSString*)filepath;

-(ERROR_CODE)remoteUpgradeDevice:(NSString *)strFilepath FileType:(REMOTE_UPGRADE_TYPE)filetype TaskID:(NSInteger)taskid Param:(NSInteger)param;
-(ERROR_CODE)getRemoteUpgradeProcess:(NSString **)process TaskID:(NSInteger)taskid;
-(ERROR_CODE)stopRemoteUpgrade:(NSInteger)taskid;


-(ERROR_CODE)sendFileToDevice:(NSString*)strFilepath FileType:(SENDFILE_TYPE)filetype Location:(LOCATION_TYPE)locationType TaskID:(NSInteger)taskid;
-(ERROR_CODE)getSendFileProcess:(NSString **)process TaskID:(NSInteger)taskid;
-(ERROR_CODE)stopSendFile:(NSInteger)taskid;

-(ERROR_CODE)remoteFace:(NSInteger)channel savePath:(NSString *)picPath  Return:(DataBlock)callback;
-(ERROR_CODE)setRecordLock:(BOOL)bLock channelBit:(NSInteger)channelbit streamType:(STREAM_TYPE)streamtype startTime:(NSString*)starttime endTime:(NSString*)endtime;//time format "20170503200000"
-(ERROR_CODE*)getYunweiCheckInfoWithStartTime:(NSString*)starttime endTime:(NSString*)endtime  Return:(DataBlock)callback;//time format "20170503200000"
-(ERROR_CODE)getHWConfigTableInfo:(DataBlock)callback;
-(ERROR_CODE)controlHWConfigTableInfo:(int)controlType userName:(NSString*)username oldPassword:(NSString*)oldpassword newPassword:(NSString*)newpassword;
-(ERROR_CODE)upgradeFilebyMain:(UPGRADE_TYPE)versionType IPCCHN:(NSInteger)channel Return:(DataBlock)callback;
-(ERROR_CODE)remoteControlButton:(NSInteger)buttonType PID:(NSString*)pid;

//一件锁存录像，已设备当前时间和 当前前后配置时间决定
-(ERROR_CODE)driveLockRecordByDevChannelbit:(NSInteger)channelbit streamtype:(STREAM_TYPE)streamtype;

//一件锁存录像，用户自己定义当前时间 和 前后时间，如果 beforetime aftermet 同时为0 已设备配置前后时间为准
-(ERROR_CODE)driveLockRecordByUserTime:(NSString*)lockcurrenttime beforeTime:(NSInteger)beforetime afterTime:(NSInteger)aftertime channelbit:(NSInteger)channelbit streamtype:(STREAM_TYPE)streamtype;



//private function
-(void)processsRecodeState:(DEV_STATE)state Type:(NSInteger)type PARAM:(NSDictionary *)param;
-(void)processsDeviceState:(DEV_STATE)state Type:(NSInteger)type PARAM:(NSDictionary*)param;
- (void)productDriverInfo:(DEV_STATE)state Type:(NSInteger)type PARAM:(NSDictionary *)param;
-(void)processTalkData:(char*)talkData size:(int)size;

//get alarm
-(ERROR_CODE)getAlarmStatusInfo:(DataBlock)block;

//获取CAN图片信息是否存在
- (ERROR_CODE)getCanPicWithcallBack:(DataBlock)callback;

//上传CAN图片文件信息
- (ERROR_CODE)uploadCanPicWithServeraddr:(NSString *)serveraddr user:(NSString *)user password:(NSString *)password callBack:(DataBlock)callback;

//查询上传图片文件进度
- (ERROR_CODE)uploadCanpicStatusWithCallBack:(DataBlock)callback;
- (NSDate *)calculateFutureAndPastTimeWithStartDate:(NSDate *)date;
- (NSString *)calculateFutureAndPastTimeWithDate:(NSDate *)date formateStr:(NSString *)formateStr;


@end


@protocol FXNetDeviceDelegate <NSObject>

-(void)FXNetDevice:(FXNetDevice*)device MSG:(NETREQUEST_ATTRIBUTE)message PARAM:(NSDictionary*)param;
-(void)FXNetDevice:(FXNetDevice *)device STATE:(DEV_STATE)message Type:(NSInteger)type PARAM:(NSDictionary *)param;
//司机注册回调
-(void)FXNetDevice:(FXNetDevice *)device withDriverResult:(NSDictionary *)driverparam;

@end
@protocol FXNetDeviceRecordeDelegate <NSObject>
- (void)recordeFXNetDevice:(FXNetDevice *)device STATE:(DEV_STATE)message Type:(NSInteger)type PARAM:(NSDictionary *)param;

- (ERROR_CODE)controlcloudTable:(DataBlock)callback ;
@end
