//
//  FXLocalPlayback.h
//  cqfxplus
//
//  Created by 许 飞 on 14-5-15.
//  Copyright (c) 2014年 frank xu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "FXDefine.h"

@protocol FXLocalPlaybackDelegate;

@interface FXLocalPlayback : NSObject

@property(nonatomic,assign)id<FXLocalPlaybackDelegate> delegate;

-(ERROR_CODE)openPlayLocalfile:(NSString*)filepath imageView:(UIImageView*)imageview;
-(ERROR_CODE)closePlay;

-(ERROR_CODE)pausePlay:(BOOL)pause;
-(ERROR_CODE)setSpeed:(NSInteger)speed;
-(ERROR_CODE)seekTime:(NSInteger)timepos;

-(ERROR_CODE)openSound;
-(ERROR_CODE)closeSound;
-(UIImage*)captureImage;


-(void)inputStreamData:(NSInteger)dataType Buffer:(char *)pBUffer Size:(int)size;
-(void)processjson:(NSInteger)type json:(char*)pbuffer;

@end

@protocol FXLocalPlaybackDelegate <NSObject>

-(void)DecoderStatus:(NSInteger)type totalTime:(NSInteger)totalTime currentTime:(NSInteger)curTime;
-(void)FXLocalPlayback:(FXLocalPlayback *)playback Width:(CGFloat) nWidth Height:(CGFloat)nHeight;

@end
