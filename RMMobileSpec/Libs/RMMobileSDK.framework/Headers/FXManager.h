//
//  FXManager.h
//  cqfxplus
//
//  Created by 许 飞 on 14/6/25.
//  Copyright (c) 2014年 frank xu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FXDefine.h"
#import "NetDeviceInfo.h"
#import "NetServiceInfo.h"

@protocol FXManagerDelegate;

@interface FXManager : NSObject

@property(nonatomic,strong)NetServiceInfo* interfaceServer;

@property(nonatomic,strong)NetServiceInfo* playbackServer;
@property(nonatomic,strong)NetServiceInfo* webServiceServer;
@property(nonatomic,strong)NetServiceInfo* searchServer;
@property(nonatomic,strong)NetServiceInfo* adsServer;
@property(nonatomic,strong)NetServiceInfo* msgServer;
@property(nonatomic,weak)id<FXManagerDelegate> delegate;
@property(nonatomic,assign)NSInteger       lastErrorCode;
@property(nonatomic,assign) bool isMosaicImage;


+(FXManager*)shareFXManager;
+(void)writeLog:(NSString*)strLog;
- (void)setAesinfoWithkeyArr:(NSArray *)keyarr aesType:(int)aesType audioEncrypt:(BOOL)audioEncrypt videoEncrypt:(BOOL)videoEncryp;
-(ERROR_CODE)discoveryLanDevice;
-(ERROR_CODE)stopDiscoveryLanDevice;

-(BOOL)loginInterfaceService:(NSString*)serverIP Port:(NSInteger)port;
-(BOOL)logoutService;

-(BOOL)getOnlieDevicelistWithCallback:(DataBlock)block;

-(DEV_STATE)getVehicleState:(NetDeviceInfo*)devinfo CALLBACK:(DataBlock)block;
-(BOOL)getVehicleBasicInfo:(NetDeviceInfo*)devinfo CALLBACK:(DataBlock)block;
-(BOOL)getVehicleReport:(NetDeviceInfo*)deviceinfo ReportType:(VEHICLE_REPORT_TYPE)type Callback:(DataBlock)block;

-(BOOL)getGroupReport:(GROUP_REPORT_TYPE)type;

-(void)processDiscoveryData:(NSDictionary*)devicedict;

@end

@protocol FXManagerDelegate <NSObject>

-(void)managerdiscoverydevice:(NSMutableArray*)devicearray;

@end
