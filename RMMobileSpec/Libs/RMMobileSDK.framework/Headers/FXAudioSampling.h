//
//  RMCQRecord.h
//  RMCQAudioQueue
//
//  Created by frank on 16-8-17.
//  Copyright (c) 2016年 frank. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AudioToolbox/AudioToolbox.h>
#import <AudioToolbox/AudioFile.h>

#define kNumberBuffers 3
#define t_sample SInt16
#define kSamplingRate 8000
#define kNumberChannels 1
#define kBitsPerChannels (sizeof(t_sample) * 8)
//#define kBytesPerFrame (640)
#define kFrameSize (640)

#define kBytesPerFrame (kNumberChannels * sizeof(t_sample))
//#define kFrameSize (kSamplingRate * sizeof(t_sample))
//#define kFrameSize 1000

typedef struct AQCallbackStruct
{
	AudioStreamBasicDescription mDataFormat;
	AudioQueueRef queue;
	AudioQueueBufferRef mBuffers[kNumberBuffers];
	AudioFileID outputFile;
	
	unsigned long frameSize;
	long long recPtr;
	int run;
} AQCallbackStruct;

@protocol FXAudioSamplingDelegate;

@interface FXAudioSampling : NSObject{
	AQCallbackStruct aqc;
	AudioFileTypeID fileFormat;
	long audioDataLength;
    Byte audioByte[999999];
    long audioDataIndex;
    char sendBuf[kFrameSize];
    BOOL bNeedCopy;
    int  nSendSize;
    
    char remainBuf[kFrameSize];
    int  nRemainSize;
    BOOL bPause;
}

@property(nonatomic,assign)id<FXAudioSamplingDelegate> delegate;

- (void) start;
- (void) stop;
- (void) pause;
- (Byte*) getBytes;
- (void) processAudioBuffer:(AudioQueueBufferRef) buffer withQueue:(AudioQueueRef) queue;

@property (nonatomic, assign) AQCallbackStruct aqc;
@property (nonatomic, assign) long audioDataLength;

@end

@protocol FXAudioSamplingDelegate <NSObject>

-(void)audioSampling:(FXAudioSampling*)audiosample data:(char*)pData size:(int)nsize;

@end
