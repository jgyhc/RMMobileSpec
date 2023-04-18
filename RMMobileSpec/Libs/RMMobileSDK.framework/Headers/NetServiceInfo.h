//
//  NetServiceInfo.h
//  cqfxplus
//
//  Created by 许 飞 on 14-5-20.
//  Copyright (c) 2014年 frank xu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FXDefine.h"

@interface NetServiceInfo : NSObject

@property(nonatomic,strong)NSString* serverName;
@property(nonatomic,strong)NSString* serverIP;
@property(nonatomic,assign)NSInteger serverPort;
@property(nonatomic,assign)NET_PROTOOL netType;

@end
