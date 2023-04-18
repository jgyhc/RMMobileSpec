//
//  FXNetSearchFile.h
//  cqfxplus
//
//  Created by 许 飞 on 14-5-15.
//  Copyright (c) 2014年 frank xu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FXNetDevice.h"
#import "FXDefine.h"

@interface FXNetSearchFile : NSObject

@property(nonatomic,strong)FXNetDevice* netDevice;


-(id)initWithNetDevice:(FXNetDevice*)device;

-(ERROR_CODE)SearchCalendarWithYear:(NSInteger)year Month:(NSInteger)month StreamType:(STREAM_TYPE)streamtype DiskType:(DISK_TYPE)disktype Block:(DataBlock)block;
-(ERROR_CODE)SearchCalendarAllWithStreamType:(STREAM_TYPE)streamtype diskType:(DISK_TYPE)disktype Block:(DataBlock)block;
-(ERROR_CODE)SearchCalendarAllWithStreamType:(STREAM_TYPE)streamtype Block:(DataBlock)block;
-(ERROR_CODE)SearchFilelistWithStart:(NSDate *)start End:(NSDate *)end StreamType:(STREAM_TYPE)streamtype Block:(DataBlock)block;
-(ERROR_CODE)SearchFilelistWithDay:(NSDate *)time StreamType:(STREAM_TYPE)streamtype DiskType:(DISK_TYPE)disktype Block:(DataBlock)block;
-(ERROR_CODE)SearchFilelistSynWithDay:(NSDate *)time StreamType:(STREAM_TYPE)streamtype DiskType:(DISK_TYPE)disktype Block:(DataBlock)block;
-(ERROR_CODE)SearchAlarmFilelistWithDay:(NSDate *)time StreamType:(STREAM_TYPE)streamtype diskType:(DISK_TYPE)diskType Block:(DataBlock)block;

-(ERROR_CODE)SearchFilelistEXWithStart:(NSDate *)start End:(NSDate *)end StreamType:(STREAM_TYPE)streamtype DiskType:(DISK_TYPE)disktype Block:(DataBlock)block;
//isAllUser  如果要检索所有司机的一键锁仓录像YES 如果当前登录的司机则为 NO
-(ERROR_CODE)SearchOneKeyLockFilelist:(BOOL)isAllUser Block:(DataBlock)block;

-(ERROR_CODE)SearchAuthorizationFilelistBlock:(DataBlock)block;


@end
