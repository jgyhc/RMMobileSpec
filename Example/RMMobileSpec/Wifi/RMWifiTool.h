//
//  RMWifiTool.h
//  S17MediaDemo
//
//  Created by 刘聪 on 2023/4/19.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface RMWifiTool : NSObject

/// 获取wifi的ip
+ (nullable NSString*)getCurrentLocalIP;

+ (nullable NSString *)getCurreWiFiSsid;

+(NSString*)getRouterIP;
@end

NS_ASSUME_NONNULL_END
