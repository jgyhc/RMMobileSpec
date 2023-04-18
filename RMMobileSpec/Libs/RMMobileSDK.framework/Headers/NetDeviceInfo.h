//
//  NetDeviceInfo.h
//  cqfxplus
//
//  Created by 许 飞 on 14-5-15.
//  Copyright (c) 2014年 frank xu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FXDefine.h"

@class FXDriverInfo;

@interface NetDeviceInfo : NSObject


@property(nonatomic,strong)NSString* deviceName;
@property(nonatomic,strong)NSString* deviceID;///请求均衡服务
@property(nonatomic,strong)NSString* deviceWanIP;
@property(nonatomic,strong)NSString* deviceLanIP;
@property(nonatomic,strong)NSNumber* deviceMediaPort;
@property(nonatomic,strong)NSNumber* deviceWEBPort;
@property(nonatomic,strong)NSString* deviceSerialNo;
@property(nonatomic,assign)DEV_TYPE  deviceType;
@property(nonatomic,assign)BOOL  is808_19;///2019版 808 协议改动（粤标项目），App影响文本下发
@property(nonatomic,strong)NSString* deviceTypeName;
@property(nonatomic,strong)NSNumber* deviceChannel;
//判读设备，用来判断司机界面
@property(nonatomic,strong)NSString* deviceUsername;
@property(nonatomic,strong)NSString* devicePassword;
@property(nonatomic,assign)NSInteger deviceMainType;
@property(nonatomic,assign)NSInteger deviceSubType;
@property(nonatomic,assign)NSInteger loginType;
@property (nonatomic, assign) NSInteger loginObject;
@property (nonatomic,assign)NSInteger carModelFileId;
@property (nonatomic,assign)NSInteger montionSensorID;
@property(nonatomic,strong)NSString* gtServerIP;
@property(nonatomic,strong)NSNumber* gtServerPort;


/*  连接不同服务器时区分协议
    RMRemoteServerProtocolUnknown       为默认值，非服务器模式下 或 不清楚协议时
    RMRemoteServerProtocolGT            GT协议  S17服务器
    RMRemoteServerProtocolCeiba264      Ceiba264更新
 */
@property (nonatomic, assign) RMRemoteServerProtocol protocol;

//校车，PL ET角色区分
@property(nonatomic,assign)NSInteger roleLeve;



@property(nonatomic,assign)USER_LEVEL userLeve;
/// 只使用于1409版本
@property(nonatomic,assign)USER_LEVEL userLeve_1409;
/// 只使用于190版本（警用）
@property(nonatomic,assign)USER_LEVEL190 userLeve_190;
@property(nonatomic,strong)NSString* reservedString;
@property(nonatomic,strong)NSNumber* reservedNumber;

//mvsp information
@property(nonatomic,strong)NSNumber* plateColorID;
//add by frank 1.11
@property(nonatomic,strong)NSString* vehicleNum;
@property(nonatomic,strong)NSString* companyName;

//add by frank 16.3.23 clientname:like 04.862 04.19...
@property(nonatomic,strong)NSString* clientName;
@property(nonatomic,assign)ENCRYPT_TYPE encryptType;
//add by frank 17.5.21 for 2.3.2.判断是否支持时移功能。
@property(nonatomic,assign)BOOL      isSupportTSE;
@property (nonatomic, assign, getter=isShowYunWei232) BOOL showYunWei232;
@property(nonatomic,strong)FXDriverInfo *DRINFO;//司机信息

/// 设备是否支持UTC
@property (nonatomic, assign,getter=isUTC) BOOL UTC;
//平台版本0 表示 N9M 1.0 平台1 表示 N9M 2.0 平台 当没有该字段时默认属于 1.0 平台
@property (nonatomic, assign) NSInteger PV;

//叠瓦式
@property (nonatomic,assign) NSInteger FSV;
/// 是否是长运机型（长运普通用户也有权限格式化存储器，配置页加载长运的URL）
@property (nonatomic, assign,readonly) BOOL isChangYun;
///S17负载均衡
@property (nonatomic, assign) BOOL isEV;
///S17负载均衡 是否用 HTTPS
@property (nonatomic, assign) BOOL s17_usesecure;
//服务器回放设备ID
@property (nonatomic,strong) NSString *playDevID;
//DSM摄像头通道
@property (nonatomic, assign) int DSMChannel;
//C129摄像头通道
@property (nonatomic, assign) int CL29Channel;

//ADAS摄像头通道
@property (nonatomic, assign) int ADASChannel;
@property (nonatomic, copy) NSString *p3Channel;

//DSM标定完成
@property (nonatomic, assign) BOOL DSMCalibration;
//ADAS标定完成
@property (nonatomic, assign) BOOL ADASCalibration;
//客户代码
@property (nonatomic, copy) NSString *customerName;
//双路BSD通道Arr
@property (nonatomic, strong) NSMutableArray *BSDCHArr;

@property(nonatomic,assign)BOOL      isST300;
//导出报警事件是否转化成txt
@property (nonatomic,assign) BOOL isSwitchTxt;
//设备支持的语言
@property (nonatomic,assign) NSInteger language;
//S17 服务器凭证
@property(nonatomic,copy) NSString* S17ACCESSSESSION;

@property (nonatomic, strong) NSDictionary *wifiDic;

@property (nonatomic,assign) NSInteger motionSensorPos;
@property (nonatomic, copy) NSString *carModelStr;

@property (nonatomic, copy) NSString *timeZex;
@property (nonatomic, assign) NSInteger timeZexHour;
@property (nonatomic, assign) NSInteger timeZexMin;

@end
