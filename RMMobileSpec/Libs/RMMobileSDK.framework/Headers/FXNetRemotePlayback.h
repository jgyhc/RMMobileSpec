//
//  FXNetRemotePlayback.h
//  cqfxplus
//
//  Created by 许 飞 on 14-5-15.
//  Copyright (c) 2014年 frank xu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "FXDefine.h"
#import "FXNetDevice.h"


@protocol FXNetRemotePlaybackDelegate;


@interface FXNetRemotePlayback : NSObject
{
@public
    int frameWidth;
    int frameHeight;
}
@property(nonatomic,strong)FXNetDevice* netDevice;
@property(nonatomic,assign)id<FXNetRemotePlaybackDelegate> delegate;
@property(nonatomic,assign)NSInteger   channelBit;
///设置图片方向，用于图片旋转、镜像翻转等
@property (atomic, assign) UIImageOrientation imageOrientation;


-(id)initWithNetDevice:(FXNetDevice*)device;

-(ERROR_CODE)startPlaybackTime:(NSDate*)time StreamType:(STREAM_TYPE)streamtype VideoImageView:(UIImageView*)videoview Channel:(NSInteger)channel;
-(ERROR_CODE)startPlaybackTime:(NSDate *)time StreamType:(STREAM_TYPE)streamtype VideoImageView:(UIImageView *)videoview Channel:(NSInteger)channel DiskType:(DISK_TYPE)disktype;

-(ERROR_CODE)stopPlayback;
-(ERROR_CODE)pausePlayback:(BOOL)pause;
-(ERROR_CODE)setPlaybackSpeed:(NSInteger)speed;
-(ERROR_CODE)setNetPlaybackSpeed:(NSInteger)speed;
-(ERROR_CODE)framePlayback:(BOOL)isForward;//yes forward  no back
-(ERROR_CODE)seekPlaybackTime:(NSDate*)time;

-(ERROR_CODE)openSound;
-(ERROR_CODE)closeSound;


-(ERROR_CODE)uninitDecoder;
//time format:20151202010202
-(ERROR_CODE)switchStream:(STREAM_TYPE)streamType time:(NSString*)time chn:(NSInteger)channelbit;
-(ERROR_CODE)addStream:(STREAM_TYPE)streamType imageView:(UIImageView*)videoview time:(NSString*)time chn:(NSInteger)channel;
-(ERROR_CODE)removeStream:(STREAM_TYPE)streamType time:(NSString*)time chn:(NSInteger)channel;


-(void)inputStreamData:(NSInteger)dataType Buffer:(char *)pBUffer Size:(int)size Chn:(int)channel isH265:(BOOL)isH265;
-(void)inputJsonString:(NSString*)strJson;

@end

@protocol FXNetRemotePlaybackDelegate <NSObject>

-(void)FXNetRemotePlayback:(FXNetRemotePlayback*)playback MSG:(PLAYBACK_MSG_TYPE)msgtype Data:(NSDictionary*)value;
-(void)FXNetRemotePlayback:(FXNetRemotePlayback*)playback Width:(float)width Height:(float)height Channel:(int)channel;

@end
