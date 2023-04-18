//
//  FXRecordDateInfo.h
//  cqfxplus
//
//  Created by 许 飞 on 14/8/12.
//  Copyright (c) 2014年 frank xu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FXDefine.h"

@interface FXRecordDateInfo : NSObject

@property(nonatomic,assign)NSInteger year;
@property(nonatomic,assign)NSInteger month;
@property(nonatomic,assign)NSInteger day;
@property(nonatomic,assign)NSInteger hour;
@property(nonatomic,assign)NSInteger minute;
@property(nonatomic,assign)NSInteger second;
@property(nonatomic,assign)RECORD_TYPE recordType;
@property(nonatomic,assign)STREAM_TYPE streamType;
@property(nonatomic,copy)NSString *dateStr;

@property(nonatomic,assign)NSInteger property;
@property(nonatomic,strong)NSMutableDictionary* chnDict;

@end
