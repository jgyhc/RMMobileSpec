//
//  RMDevice.m
//  CeiBaII Demo
//
//  Created by ctctct on 2020/1/15.
//  Copyright © 2020 ctctct. All rights reserved.
//

#import "RMDevice.h"
#import <RMMobileSDK/FXNetDevice.h>
#import <RMMobileSDK/FXNetStream.h>
#import <RMMobileSDK/FXNetVideoPlayback.h>

@interface RMStreamImageView : UIImageView

@end

@implementation RMStreamImageView

- (void)setImage:(UIImage *)image{
    if (self.superview != nil) {
        [super setImage:image];
    }
}

- (BOOL)isHidden{
    if ([NSThread isMainThread]) {
        return [super isHidden];
    }else{
        __block BOOL hidden = NO;
        dispatch_sync(dispatch_get_main_queue(), ^{
           hidden = [super isHidden];
        });
        return hidden;
    }
}

@end

@implementation RMDeviceConfig

- (instancetype)init
{
    self = [super init];
    if (self) {
        self.protocol = RMRemoteServerProtocolGT;
    }
    return self;
}

@end

@interface RMDevice ()<FXNetStreamDelegate,FXNetVideoPlaybackDelegate>

@property (nonatomic, assign, readwrite) BOOL isLogin;
@property (nonatomic, assign, readwrite) BOOL isStreaming;
@property (nonatomic, assign, readwrite) BOOL isTalking;

@property (nonatomic, strong) FXNetDevice *netDevice;

@property (nonatomic, strong) NSMutableDictionary<NSNumber *, FXNetStream *> *streamsDictionary;
@property (nonatomic, strong) NSMutableDictionary<NSNumber *, RMStreamImageView *> *streamImagesDictionary;
@property (nonatomic, strong, readwrite) NSMutableArray<NSNumber *> *streamChannelsMutableArray;

@property (nonatomic, strong) FXNetVideoPlayback *netPlayback;
@property (nonatomic, strong) NSMutableDictionary<NSNumber *, RMStreamImageView *> *playbackImagesDictionary;
@property (nonatomic, strong, readwrite) NSMutableArray<NSNumber *> *playbackChannelsMutableArray;

@property (nonatomic, strong) dispatch_queue_t streams_operation_queue;

@end

@implementation RMDevice

- (void)dealloc{
    NSLog(@"%s",__func__);
}

- (instancetype)initWithConfig:(RMDeviceConfig *)config{
    self = [super init];
    if (self) {
        NSString *queueName = [NSString stringWithFormat:@"com.streamax.media-%@", [[NSUUID UUID] UUIDString]];
        _streams_operation_queue = dispatch_queue_create([queueName cStringUsingEncoding:NSASCIIStringEncoding], DISPATCH_QUEUE_SERIAL);
        _streamImagesDictionary = [NSMutableDictionary dictionary];
        _streamsDictionary = [NSMutableDictionary dictionary];
        _playbackImagesDictionary =  [NSMutableDictionary dictionary];
        
        NetDeviceInfo *deviceInfo = [[NetDeviceInfo alloc] init];
        deviceInfo.protocol = config.protocol;
        deviceInfo.deviceType = (DEV_TYPE)config.deviceType;
        if (config.deviceType == RMDeviceTypeN9M) {
            deviceInfo.deviceWanIP = config.deviceID;
        }else{
            deviceInfo.deviceWanIP = [NSString stringWithFormat:@"%@%02ld+%012ld",config.deviceID,(long)config.plateColorID,(long)[config.simCard integerValue]];
        }
        deviceInfo.gtServerIP = config.serverIP;
        deviceInfo.gtServerPort = config.serverPort;
        deviceInfo.deviceChannel = @1;
        deviceInfo.S17ACCESSSESSION = config.accessSession;
        _netDevice = [[FXNetDevice alloc]initWithDeviceinfo:deviceInfo];
    }
    return self;
}

- (instancetype)init{
    return [self initWithConfig:[RMDeviceConfig new]];
}

- (void)loginDevice:(void (^)(ERROR_CODE))callback{
    dispatch_async(_streams_operation_queue, ^{
        ERROR_CODE result = (ERROR_CODE)[self.netDevice loginDevice];
        if (result == 0) {
            self.isLogin = YES;
        }
        dispatch_async(dispatch_get_main_queue(), ^{
            if (callback) {
                callback(result);
            }
        });
    });
}

- (void)logoutDevice:(void (^)(ERROR_CODE))callback{
    dispatch_async(_streams_operation_queue, ^{
        if (self.isStreaming) {
            [self closeStreams];
        }
        if (self.isTalking) {
            [self closeTalk];
        }
        if (self.isPlaybacking) {
            [self closePlayback];
        }
        NSLog(@"logoutDevice");
        ERROR_CODE result = (ERROR_CODE)[self.netDevice logoutDevice];
        if (result == 0) {
            self.isLogin = NO;
        }
        dispatch_async(dispatch_get_main_queue(), ^{
            if (callback) {
                callback(result);
            }
        });
    });
}


- (void)openTalk:(void(^)(ERROR_CODE))callback{
    dispatch_async(_streams_operation_queue, ^{
        ERROR_CODE result = (ERROR_CODE)[self.netDevice openTalk];
        self.isTalking = result == ERROR_SUCCESS;
        dispatch_async(dispatch_get_main_queue(), ^{
            if (callback) {
                callback(result);
            }
        });
    });
}
- (ERROR_CODE)closeTalk{
    ERROR_CODE result = (ERROR_CODE)[self.netDevice closeTalk];
    if (self.isTalking) {
        self.isTalking = result != ERROR_SUCCESS;
    }
    return result;
}
- (void)closeTalk:(void(^)(ERROR_CODE))callback{
    dispatch_async(_streams_operation_queue, ^{
        ERROR_CODE result = [self closeTalk];
        dispatch_async(dispatch_get_main_queue(), ^{
            if (callback) {
                callback(result);
            }
        });
    });
}

#pragma mark - RealPlay

- (void)openStreams:(NSArray<NSNumber *> *)channels streamType:(STREAM_TYPE)streamType callback:(void(^)(ERROR_CODE result))callback{
    dispatch_async(_streams_operation_queue, ^{
        ERROR_CODE code = ERROR_SUCCESS;
        for (NSNumber *channel in channels) {
            FXNetStream *netStream = [self getNetStreamByChannel:channel];
            if (!netStream.isOpenNetStream) {
                UIImageView *imageView = [self getStreamImageByChannel:channel];
                ERROR_CODE result = (ERROR_CODE)[netStream openNetStream:channel Image:imageView StreamType:streamType];
                if (result != 0) {
                    [self removeStreamAndImageWithChannel:channel];
                    code = ERROR_FAILED;
                }
            }
        }
        dispatch_async(dispatch_get_main_queue(), ^{
            if (callback) {
                callback(code);
            }
        });
    });
}
- (void)openStreamChannel:(NSNumber *)channel streamType:(STREAM_TYPE)streamType callback:(void(^)(ERROR_CODE result))callback{
    dispatch_async(_streams_operation_queue, ^{
        ERROR_CODE code = ERROR_FAILED;
        FXNetStream *netStream = [self getNetStreamByChannel:channel];
        if (!netStream.isOpenNetStream) {
            UIImageView *imageView = [self getStreamImageByChannel:channel];
            code = (ERROR_CODE)[netStream openNetStream:channel Image:imageView StreamType:streamType];
        }
        dispatch_async(dispatch_get_main_queue(), ^{
            if (callback) {
                callback(code);
            }
        });
    });
}
- (ERROR_CODE)closeStreams{
    ERROR_CODE code = ERROR_SUCCESS;
    for (NSNumber *channel in self.streamChannelsMutableArray) {
        FXNetStream *netStream = self.streamsDictionary[channel];
        if (netStream) {
            ERROR_CODE result = (ERROR_CODE)[netStream closeNetStream];
            if (result != 0 && result != code) {
                code = ERROR_FAILED;
            }
        }
    }
    NSLog(@"closeNetStream");
    [self removeAllStreamsAndImages];
    return code;
}
- (void)closeStreams:(void(^)(ERROR_CODE))callback{
    dispatch_async(_streams_operation_queue, ^{
        NSArray *images = [self.streamImagesDictionary allValues];
        ERROR_CODE code = [self closeStreams];
        dispatch_async(dispatch_get_main_queue(), ^{
            for (UIImageView *imageView in images) {
                imageView.image = nil;
                [imageView removeFromSuperview];
            }
            if (callback) {
                callback(code);
            }
        });
    });
}
- (void)closeStreamChannel:(NSNumber *)channel callback:(void(^)(ERROR_CODE))callback{
    dispatch_async(_streams_operation_queue, ^{
        ERROR_CODE code = ERROR_FAILED;
        FXNetStream *netStream = self.streamsDictionary[channel];
        UIImageView *imageView = nil;
        if (netStream) {
            imageView = self.streamImagesDictionary[channel];
            code = (ERROR_CODE)[netStream closeNetStream];
            [self removeStreamAndImageWithChannel:channel];
        }
        dispatch_async(dispatch_get_main_queue(), ^{
            imageView.image = nil;
            [imageView removeFromSuperview];
            if (callback) {
                callback(code);
            }
        });
    });
}

- (void)openStreamSoundChannel:(NSNumber *)channel callback:(void(^)(ERROR_CODE))callback{
    dispatch_async(_streams_operation_queue, ^{
        ERROR_CODE code = ERROR_FAILED;
        FXNetStream *netStream = self.streamsDictionary[channel];
        if (netStream) {
            code = (ERROR_CODE)[netStream openSound];
        }
        dispatch_async(dispatch_get_main_queue(), ^{
            if (callback) {
                callback(code);
            }
        });
    });
}
- (void)closeStreamSoundChannel:(NSNumber *)channel callback:(void(^)(ERROR_CODE))callback{
    dispatch_async(_streams_operation_queue, ^{
        ERROR_CODE code = ERROR_FAILED;
        FXNetStream *netStream = self.streamsDictionary[channel];
        if (netStream) {
            code = (ERROR_CODE)[netStream closeSound];
        }
        dispatch_async(dispatch_get_main_queue(), ^{
            if (callback) {
                callback(code);
            }
        });
    });
}

- (void)screenShotAllChannels:(void(^)(NSArray<UIImage *> *))callback{
    dispatch_async(_streams_operation_queue, ^{
        NSMutableArray *temp = [NSMutableArray new];
        for (NSNumber *channel in self.streamChannelsMutableArray) {
            FXNetStream *netStream = self.streamsDictionary[channel];
            if (netStream) {
                UIImage *result = [netStream captureImage:nil];
                if (result) {
                    [temp addObject:result];
                }
            }
        }
        dispatch_async(dispatch_get_main_queue(), ^{
            if (callback) {
                callback(temp);
            }
        });
    });
}
- (void)screenShotChannel:(NSNumber *)channel callback:(void(^)(UIImage *))callback{
    dispatch_async(_streams_operation_queue, ^{
        FXNetStream *netStream = self.streamsDictionary[channel];
        UIImage *result = nil;
        if (netStream) {
            result = [netStream captureImage:nil];
        }
        dispatch_async(dispatch_get_main_queue(), ^{
            if (callback) {
                callback(result);
            }
        });
    });
}

- (void)switchStream:(STREAM_TYPE)streamType channels:(NSArray<NSNumber *> *)channels callback:(void(^)(ERROR_CODE))callback{
    dispatch_async(_streams_operation_queue, ^{
        ERROR_CODE result = ERROR_SUCCESS;
        for (NSNumber *channel in channels) {
            FXNetStream *netStream = self.streamsDictionary[channel];
            if (netStream) {
                ERROR_CODE tmp = [netStream switchStream:streamType];
                if (tmp != ERROR_SUCCESS) {
                    result = tmp;
                }
            }
        }
        dispatch_async(dispatch_get_main_queue(), ^{
            if (callback) {
                callback(result);
            }
        });
    });
}

- (void)switchStreamAllChannels:(STREAM_TYPE)streamType callback:(void(^)(ERROR_CODE))callback{
    [self switchStream:streamType channels:self.streamChannelsMutableArray callback:callback];
}

- (void)switchStream:(STREAM_TYPE)streamType channel:(NSNumber *)channel callback:(void(^)(ERROR_CODE))callback{
    [self switchStream:streamType channels:@[channel] callback:callback];
}

#pragma mark - Playback

- (void)openPlayback:(NSDate *)playbackDate channels:(NSArray<NSNumber *> *)channels streamType:(STREAM_TYPE)streamType callback:(void (^)(ERROR_CODE))callback{
    if (channels.count < 1) {
        if (callback) {
            callback(ERROR_PARAM);
        }
        return;
    }
    dispatch_async(_streams_operation_queue, ^{
        NSMutableArray *imageViews = [NSMutableArray new];
        for (NSNumber *channel in channels) {
            UIImageView *imageView = [self getPlaybackImageByChannel:channel];
            [imageViews addObject:imageView];
        }
        ERROR_CODE code = [self.netPlayback startPlaybackTime:playbackDate StreamType:streamType VideoArray:imageViews Channel:channels];
        dispatch_async(dispatch_get_main_queue(), ^{
            if (callback) {
                callback(code);
            }
        });
    });
}

- (ERROR_CODE)closePlayback{
    ERROR_CODE code = [self.netPlayback stopPlayback];
    [self.playbackImagesDictionary removeAllObjects];
    return code;
}

- (void)closePlayback:(void(^)(ERROR_CODE))callback{
    dispatch_async(_streams_operation_queue, ^{
        NSArray *images = [self.playbackImagesDictionary allValues];
        ERROR_CODE code = [self closePlayback];
        dispatch_async(dispatch_get_main_queue(), ^{
            for (UIImageView *imageView in images) {
                imageView.image = nil;
                [imageView removeFromSuperview];
            }
            if (callback) {
                callback(code);
            }
        });
    });
}

- (void)pausePlayback:(BOOL)pause callback:(void (^)(ERROR_CODE))callback{
    dispatch_async(_streams_operation_queue, ^{
        ERROR_CODE code = [self.netPlayback pausePlayback:pause];
        dispatch_async(dispatch_get_main_queue(), ^{
            if (callback) {
                callback(code);
            }
        });
    });
}

- (void)openPlaybackSoundChannel:(NSNumber *)channel callback:(void(^)(ERROR_CODE))callback{
    dispatch_async(_streams_operation_queue, ^{
        ERROR_CODE code = [self.netPlayback openSound:[channel integerValue]];
        dispatch_async(dispatch_get_main_queue(), ^{
            if (callback) {
                callback(code);
            }
        });
    });
}

- (void)closePlaybackSoundCallback:(void (^)(ERROR_CODE))callback{
    dispatch_async(_streams_operation_queue, ^{
        ERROR_CODE code = [self.netPlayback closeSound];
        dispatch_async(dispatch_get_main_queue(), ^{
            if (callback) {
                callback(code);
            }
        });
    });
}

- (void)setPlaybackSpeed:(NSInteger)speed{
    if (_netPlayback) {
        [_netPlayback setPlaybackSpeed:speed];
        [_netPlayback setNetPlaybackSpeed:speed];
    }
}
- (void)playbackSeekTo:(NSDate *)date{
    if (_netPlayback) {
        [_netPlayback seekPlaybackTime:date];
    }
}

#pragma mark - Helper
- (void)removeAllStreamsAndImages{
    [self.streamsDictionary removeAllObjects];
    [self.streamImagesDictionary removeAllObjects];
    [self.streamChannelsMutableArray removeAllObjects];
}
- (void)removeStreamAndImageWithChannel:(NSNumber *)channel{
    [self.streamsDictionary removeObjectForKey:channel];
    [self.streamImagesDictionary removeObjectForKey:channel];
    [self.streamChannelsMutableArray removeObject:channel];
}
- (FXNetStream *)getNetStreamByChannel:(NSNumber *)channel{
    FXNetStream *netStream = self.streamsDictionary[channel];
    if (!netStream) {
        netStream = [[FXNetStream alloc]initWithNetDevice:self.netDevice];
        netStream.delegate = self;
        self.streamsDictionary[channel] = netStream;
    }
    return netStream;
}

- (RMStreamImageView *)getStreamImageByChannel:(NSNumber *)channel{
    __block RMStreamImageView *imageView = self.streamImagesDictionary[channel];
    if (!imageView) {
        dispatch_async(dispatch_get_main_queue(), ^{
            imageView = [RMStreamImageView new];
            imageView.contentMode = UIViewContentModeScaleAspectFit;
        });
//        RMMainQueueSyncSafe(^{
//
//        })
        self.streamImagesDictionary[channel] = imageView;
        
        if (![self.streamChannelsMutableArray containsObject:channel]) {
            [self.streamChannelsMutableArray addObject:channel];
        }
    }
    return imageView;
}

- (RMStreamImageView *)getPlaybackImageByChannel:(NSNumber *)channel{
    __block RMStreamImageView *imageView = self.playbackImagesDictionary[channel];
    if (!imageView) {
        dispatch_async(dispatch_get_main_queue(), ^{
            imageView = [RMStreamImageView new];
            imageView.contentMode = UIViewContentModeScaleToFill;
        });
//        RMMainQueueSyncSafe(^{
//            imageView = [RMStreamImageView new];
//            imageView.contentMode = UIViewContentModeScaleToFill;
//        })
        self.playbackImagesDictionary[channel] = imageView;
        
        if (![self.playbackChannelsMutableArray containsObject:channel]) {
            [self.playbackChannelsMutableArray addObject:channel];
        }
    }
    return imageView;
}

#pragma mark -FXNetStreamDelegate
-(void)netStreamPlayWithStatus:(REALPLAYSTAUS)playStatus Withchannel:(int)channel{
    if ([self.delegate respondsToSelector:@selector(realPlayStatus:channel:)]) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [self.delegate realPlayStatus:(RM_REALPLAY_STAUS)playStatus channel:@(channel)];
        });
        if (playStatus == enum_PlayFail) {
            [self closeStreamChannel:@(channel) callback:^(ERROR_CODE result) {
                
            }];
        }
    }
}
- (void)netStream:(FXNetStream *)netStream mirroredFlipAngleParam:(int)param{
    dispatch_async(dispatch_get_main_queue(), ^{
        if ([self.delegate respondsToSelector:@selector(streamsVideoAspectRatioWidth:height:channel:)]) {
            [self.delegate streamsVideoAspectRatioWidth:netStream->frameWidth height:netStream->frameHeight channel:netStream.channel];
        }
    });
}

#pragma mark - FXNetVideoPlaybackDelegate
- (void)FXNetVideoPlayback:(FXNetVideoPlayback*)playback MSG:(PLAYBACK_MSG_TYPE)msgtype Data:(NSDictionary*)value{
    if(msgtype == PLAYBACK_END){
        NSLog(@"PLAYBACK END");
    }else if(msgtype == PLAYBACK_FRAMEINFO){
        NSString *time = value[@"PARAM"][@"TIME"];
        dispatch_async(dispatch_get_main_queue(), ^{
            if (self.delegate && [self.delegate respondsToSelector:@selector(playbackTime:)]) {
                [self.delegate playbackTime:time];
            }
        });
    }else if(msgtype == PLAYBACK_DEVERRORCODE){
        
    }
}
- (void)FXNetVideoPlayback:(FXNetVideoPlayback*)playback Channel:(NSInteger)channel Width:(CGFloat)nWidth Height:(CGFloat)nHeight{
    dispatch_async(dispatch_get_main_queue(), ^{
        if ([self.delegate respondsToSelector:@selector(playbackVideoAspectRatioWidth:height:channel:)]) {
            [self.delegate playbackVideoAspectRatioWidth:nWidth height:nHeight channel:@(channel)];
        }
    });
}

#pragma mark - Getter
- (RMStreamImagesDictionary *)playbackImages{
    return [self.playbackImagesDictionary copy];
}
- (RMStreamImagesDictionary *)streamImages{
    return [self.streamImagesDictionary copy];
}
- (FXNetVideoPlayback *)netPlayback{
    if (_netPlayback) {
        return _netPlayback;
    }
    _netPlayback = [[FXNetVideoPlayback alloc]initWithNetDevice:self.netDevice];
    _netPlayback.delegate = self;
    return _netPlayback;
}

- (BOOL)isStreaming{
    BOOL isStreaming = NO;
    NSArray *streams = [self.streamsDictionary allValues];
    for (FXNetStream *stream in streams) {
        if (stream.isOpenNetStream) {
            isStreaming = YES;
        }
    }
    return isStreaming;
}
- (BOOL)isPlaybacking{
    return self.playbackImagesDictionary.count > 0;
}
- (NSMutableArray<NSNumber *> *)streamChannelsMutableArray{
    if (!_streamChannelsMutableArray) {
        _streamChannelsMutableArray = [NSMutableArray array];
    }
    return _streamChannelsMutableArray;
}
- (NSMutableArray<NSNumber *> *)playbackChannelsMutableArray{
    if (!_playbackChannelsMutableArray) {
        _playbackChannelsMutableArray = [NSMutableArray array];
    }
    return _playbackChannelsMutableArray;
}
- (NSArray<NSNumber *> *)playbackChannels{
    return [self.playbackChannelsMutableArray copy];

}
- (NSArray<NSNumber *> *)streamChannels{
    return [self.streamChannelsMutableArray copy];
}
@end
