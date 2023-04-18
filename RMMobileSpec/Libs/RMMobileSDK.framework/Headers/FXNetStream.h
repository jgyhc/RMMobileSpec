//
//  FXNetStream.h
//  cqfxplus
//
//  Created by 许 飞 on 14-5-15.
//  Copyright (c) 2014年 frank xu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "FXDefine.h"

@protocol FXNetStreamDelegate;

#define FXNetStreamParamsChangeNotif  @"FXNetStreamParamsChangeNotif"
typedef void(^completionBlock)(ERROR_CODE errorCode);
typedef void(^imageBlock)(UIImage *image) ;

@class FXNetDevice;
@interface FXNetStream : NSObject
{
@public
    int frameWidth;
    int frameHeight;
    BOOL bPause; // AHD设置打开后必须再调用暂停才能播放
}

@property(nonatomic,strong)FXNetDevice* netDevice;
@property(nonatomic,strong)NSNumber* channel;
@property(nonatomic,weak)id<FXNetStreamDelegate> delegate;
@property(nonatomic,assign)BOOL isOpenNetStream;
@property(nonatomic,assign)BOOL openNetStreamWithOutKey;
@property(nonatomic,strong)UIImageView* videoView;
@property (nonatomic, assign) BOOL isStartPlay;

/// 镜像、安装角度参数
@property (nonatomic, assign) int mirroredFlipAngleParam;

-(id)initWithNetDevice:(FXNetDevice*)device;

-(ERROR_CODE)openNetStream:(NSNumber*)channel
                     Image:(UIImageView*)imageview
                StreamType:(STREAM_TYPE)streamtype;

-(void)openNetStream:(NSNumber*)channel
               Image:(UIImageView*)imageview
          StreamType:(STREAM_TYPE)streamtype
          completion:(completionBlock)completion;

-(ERROR_CODE)openNetStream:(NSNumber*)channel
                     Image:(UIImageView*)imageview
                StreamType:(STREAM_TYPE)streamtype
                 FrameMode:(NSInteger)frameMode;//for 04.68 project

-(ERROR_CODE)streamPause:(BOOL)pause;
-(void)streamPause:(BOOL)pause completion:(completionBlock)completion;

-(ERROR_CODE)switchStream:(STREAM_TYPE)streamType;
-(void)switchStream:(STREAM_TYPE)streamType completion:(completionBlock)completion;

-(ERROR_CODE)closeNetStream;
-(void)closeNetStreamCompletion:(completionBlock)completion;

-(ERROR_CODE)openSound;
-(void)openSoundCompletion:(completionBlock)completion;

-(ERROR_CODE)closeSound;
-(void)closeSoundCompletion:(completionBlock)completion;

- (void)openOrPauseStreamIsopen:(BOOL)isOpen  channel:(NSNumber*)channel Image:(UIImageView*)imageview StreamType:(STREAM_TYPE)streamtype completion:(void (^)(ERROR_CODE errorCode))completion;

-(ERROR_CODE)startRecord:(NSString*)recordPath;
-(ERROR_CODE)stopRecord;

-(UIImage*)captureImage:(NSString*)imagePath;

-(void)captureImageBlock:(imageBlock)block;
-(ERROR_CODE)streamThrow:(NSInteger)nValue;

- (void)clearVideoImage;
-(void)setImageView:(UIImageView*)videoView;
- (void)setImgOrientationWithParam:(int)param;
/// 清空存储旋转、镜像参数的字典
+ (void)clearParamDict;
//No useful for custom
-(void)inputStreamData:(NSInteger)dataType Buffer:(char *)pBUffer Size:(int)size isH265:(BOOL)isH265;
-(void)processErrorCode:(NSInteger)errorcode;
-(void)analysisFileHeader:(char*)pBuffer size:(int)size;
-(void)inputStreamSourceData:(char*)pBuffer size:(int)size;
//获取文件中的帧信息
- (UIImage *)getFrameInfoWithType:(NSInteger)filetype Withfilpath:(NSString *)filePath;
- (ERROR_CODE)recordStartWithFileName:(NSString *)filename;
- (ERROR_CODE)recordeStop;
///设置图片方向，用于图片旋转、镜像翻转等
@property (atomic, assign) UIImageOrientation imageOrientation;
@end

@protocol FXNetStreamDelegate <NSObject>
typedef enum
{
    enum_StopPLay = 0,
    enum_Playing,
    enum_StartPlay,
    enum_PlayFail
}REALPLAYSTAUS;
@optional
-(void)netStream:(FXNetStream*)netstream ErrorCode:(NSInteger)errorcode;
-(void)netStream:(FXNetStream*)netStream mirroredFlipAngleParam:(int)param;
//播放状态协议回调
-(void)netStreamPlayWithStatus:(REALPLAYSTAUS)playStatus Withchannel:(int)channel;

@end
