//
//  FXFileHeaderInfo.h
//  cqfxplus
//
//  Created by xufei on 5/13/16.
//  Copyright © 2016 frank xu. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface FXFileHeaderInfo : NSObject

@property(nonatomic,strong)NSString* companyName;
@property(nonatomic,strong)NSString* vehicleName;
@property(nonatomic,strong)NSString* serialNumber;
@property(nonatomic,strong)NSString* firmwareVersion;
@property(nonatomic,strong)NSString* mcuVersion;
@property(nonatomic,strong)NSMutableDictionary* sensorName;

@end
