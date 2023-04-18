//
//  FXNetVideoPlayback.h
//  cqfxplus
//
//  Created by 锐明 on 2018/1/9.
//  Copyright © 2018年 frank xu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "FXDefine.h"
#import "FXNetDevice.h"

@protocol FXNetVideoPlaybackDelegate;

@interface FXNetVideoPlayback : NSObject

@property(nonatomic,strong)FXNetDevice* netDevice;
@property(nonatomic,weak)id<FXNetVideoPlaybackDelegate> delegate;

-(id)initWithNetDevice:(FXNetDevice*)device;

-(ERROR_CODE)startPlaybackTime:(NSDate*)time StreamType:(STREAM_TYPE)streamtype VideoArray:(NSArray*)videoviewArray Channel:(NSArray<NSNumber *>*)chnArray;

///Ceiba3 新增 location 检索位置:0 - 设备回放，1 - 服务器回放，无此字段默认为设备回放
///           fileIDs   FMS 存储的文件 ID，无此字段默认为设备回放
-(ERROR_CODE)startPlaybackTime:(NSDate *)time StreamType:(STREAM_TYPE)streamtype VideoArray:(NSArray *)videoviewArray Channel:(NSArray<NSNumber *> *)chnArray location:(NSInteger)location fileIDs:(NSArray *)fileIDs;
-(ERROR_CODE)startPlaybackTime:(NSDate *)time StreamType:(STREAM_TYPE)streamtype VideoArray:(NSArray *)videoviewArray Channel:(NSArray<NSNumber *> *)chnArray diskType:(DISK_TYPE)diskType location:(NSInteger)location fileIDs:(NSArray *)fileIDs;

-(ERROR_CODE)stopPlayback;
-(ERROR_CODE)pausePlayback:(BOOL)pause;
-(ERROR_CODE)setPlaySpeed:(NSInteger)speed;
-(ERROR_CODE)setPlaybackSpeed:(NSInteger)speed;
-(ERROR_CODE)setNetPlaybackSpeed:(NSInteger)speed;
-(ERROR_CODE)framePlayback:(BOOL)isForward;//yes forward  no back
-(ERROR_CODE)seekPlaybackTime:(NSDate*)time;

-(ERROR_CODE)closeSound;
-(ERROR_CODE)writeFile:(NSString *)fileName;

-(ERROR_CODE)openSound:(NSInteger)channel;
-(ERROR_CODE)closeSound:(NSInteger)channel;


-(ERROR_CODE)addStream:(STREAM_TYPE)streamType imageView:(UIImageView*)videoview time:(NSString*)time chn:(NSInteger)channel;
-(ERROR_CODE)removeStream:(STREAM_TYPE)streamType time:(NSString*)time chn:(NSInteger)channel;


-(void)inputJsonString:(NSString*)strJson;
-(void) inputStreamData:(NSInteger)dataType Buffer:(char *)pBUffer Size:(int)size Chn:(int)channel encodeType:(int)encodeType;

@end

@protocol FXNetVideoPlaybackDelegate <NSObject>

-(void)FXNetVideoPlayback:(FXNetVideoPlayback*)playback MSG:(PLAYBACK_MSG_TYPE)msgtype Data:(NSDictionary*)value;
-(void)FXNetVideoPlayback:(FXNetVideoPlayback*)playback Channel:(NSInteger)channel Width:(CGFloat) nWidth Height:(CGFloat)nHeight;
@end
