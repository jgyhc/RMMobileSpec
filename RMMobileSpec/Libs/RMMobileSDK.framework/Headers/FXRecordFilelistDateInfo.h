//
//  FXRecordFilelistDateInfo.h
//  cqfxplus
//
//  Created by 许 飞 on 14/8/12.
//  Copyright (c) 2014年 frank xu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FXDefine.h"


@interface FXRecordFilelistDateInfo : NSObject

@property(nonatomic,strong)NSString *fileName;
@property(nonatomic,assign)NSInteger year;
@property(nonatomic,assign)NSInteger month;
@property(nonatomic,assign)NSInteger day;
@property(nonatomic,assign)NSInteger startHour;
@property(nonatomic,assign)NSInteger startMinute;
@property(nonatomic,assign)NSInteger startSecond;
@property(nonatomic,assign)NSInteger endHour;
@property(nonatomic,assign)NSInteger endMinute;
@property(nonatomic,assign)NSInteger endSecond;
@property(nonatomic,assign)RECORD_TYPE fileType;
@property(nonatomic,assign)STREAM_TYPE streamType;
@property(nonatomic,assign)NSInteger channel;
@property(nonatomic,strong)NSDate    *startDate;
@property(nonatomic,copy)NSString    *startTime;
@property(nonatomic,strong)NSDate    *endDate;
@property(nonatomic,assign)NSInteger alarmType;
@property(nonatomic,assign)double    filesize;

@end
