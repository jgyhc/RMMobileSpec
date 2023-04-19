//
//  RMDevice.h
//  CeiBaII Demo
//
//  Created by ctctct on 2020/1/15.
//  Copyright © 2020 ctctct. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RMMobileSDK/FXDefine.h>

typedef NS_ENUM(NSInteger, RM_REALPLAY_STAUS){
    RM_REALPLAY_STOP = 0,
    RM_REALPLAY_PLAYING,
    RM_REALPLAY_START,
    RM_REALPLAY_FAIL,
};

typedef NS_ENUM(NSUInteger, RMDeviceType){
    RMDeviceTypeN9M = 1,
    RMDeviceType808 = 2,
    RMDeviceType1078 = 5,
};


typedef NSDictionary<NSNumber *, UIImageView *> RMStreamImagesDictionary;

NS_ASSUME_NONNULL_BEGIN

@protocol RMDeviceDelegate <NSObject>

@optional
- (void)realPlayStatus:(RM_REALPLAY_STAUS)playStatus channel:(NSNumber *)channel;
- (void)streamsVideoAspectRatioWidth:(CGFloat)width height:(CGFloat)height channel:(NSNumber *)channel;

- (void)playbackTime:(NSString *)time;
- (void)playbackVideoAspectRatioWidth:(CGFloat)width height:(CGFloat)height channel:(NSNumber *)channel;

@end


@interface RMDeviceConfig : NSObject

@property(nonatomic, assign) RMRemoteServerProtocol protocol;///默认  RMRemoteServerProtocolGT
@property(nonatomic, assign) RMDeviceType deviceType;
@property(nonatomic, strong) NSString *deviceID;///N9M  为设备序列号， 808 和 1078 为车牌号
@property(nonatomic, strong) NSString *simCard;/// SIM 卡号， N9M  设备可不填
@property(nonatomic, assign) NSInteger plateColorID;///车牌颜色  两位整数。例： 01  。 N9M 设备可不填

@property(nonatomic, strong) NSString *accessSession;///S17 3.0 用到

@property(nonatomic, strong) NSString *serverIP;
@property(nonatomic, strong) NSNumber *serverPort;

@end


@interface RMDevice : NSObject

@property (nonatomic, assign, readonly) BOOL isLogin;
@property (nonatomic, assign, readonly) BOOL isStreaming;
@property (nonatomic, assign, readonly) BOOL isTalking;
@property (nonatomic, assign, readonly) BOOL isPlaybacking;
@property (nonatomic, weak) id<RMDeviceDelegate> delegate;

- (instancetype)initWithConfig:(RMDeviceConfig *)config NS_DESIGNATED_INITIALIZER;

//使用Device其他接口时 必须登录
- (void)loginDevice:(nullable void(^)(ERROR_CODE result))callback;

//不再使用Device时 必须登出
- (void)logoutDevice:(nullable void(^)(ERROR_CODE result))callback;


- (void)openTalk:(nullable void(^)(ERROR_CODE result))callback;
- (void)closeTalk:(nullable void(^)(ERROR_CODE result))callback;

@end

@interface RMDevice (RMDeviceRealPlay)

@property (nonatomic, strong, readonly) NSArray<NSNumber *> *streamChannels;
@property (nonatomic, strong, readonly) RMStreamImagesDictionary *streamImages;

//打开流
- (void)openStreams:(NSArray<NSNumber *> *)channels streamType:(STREAM_TYPE)streamType callback:(nullable void(^)(ERROR_CODE result))callback;
- (void)openStreamChannel:(NSNumber *)channel streamType:(STREAM_TYPE)streamType callback:(nullable void(^)(ERROR_CODE result))callback;

//关闭流
- (void)closeStreams:(nullable void(^)(ERROR_CODE result))callback;
- (void)closeStreamChannel:(NSNumber *)channel callback:(nullable void(^)(ERROR_CODE result))callback;

//打开声音
- (void)openStreamSoundChannel:(NSNumber *)channel callback:(nullable void(^)(ERROR_CODE result))callback;
- (void)closeStreamSoundChannel:(NSNumber *)channel callback:(nullable void(^)(ERROR_CODE result))callback;

//抓拍
- (void)screenShotAllChannels:(nullable void(^)(NSArray<UIImage *> *imagesArray))callback;
- (void)screenShotChannel:(NSNumber *)channel callback:(nullable void(^)(UIImage *image))callback;

//切换码流
- (void)switchStreamAllChannels:(STREAM_TYPE)streamType callback:(nullable void(^)(ERROR_CODE result))callback;
- (void)switchStream:(STREAM_TYPE)streamType channel:(NSNumber *)channel callback:(nullable void(^)(ERROR_CODE result))callback;

@end

@interface RMDevice (RMDevicePlayback)

@property (nonatomic, strong, readonly) NSArray<NSNumber *> *playbackChannels;
@property (nonatomic, strong, readonly) RMStreamImagesDictionary *playbackImages;

- (void)openPlayback:(NSDate *)playbackDate channels:(NSArray<NSNumber *> *)channels streamType:(STREAM_TYPE)streamType callback:(nullable void(^)(ERROR_CODE result))callback;

- (void)closePlayback:(nullable void(^)(ERROR_CODE result))callback;

- (void)pausePlayback:(BOOL)pause callback:(nullable void(^)(ERROR_CODE result))callback;

- (void)openPlaybackSoundChannel:(NSNumber *)channel callback:(nullable void(^)(ERROR_CODE result))callback;
- (void)closePlaybackSoundCallback:(nullable void(^)(ERROR_CODE result))callback;

- (void)setPlaybackSpeed:(NSInteger)speed;
- (void)playbackSeekTo:(NSDate *)date;

@end

NS_ASSUME_NONNULL_END
