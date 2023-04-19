//
//  RMViewController.m
//  RMMobileSpec
//
//  Created by 16422230 on 04/18/2023.
//  Copyright (c) 2023 16422230. All rights reserved.
//

#import "RMViewController.h"
#import <RMMobileSDK/RMMobileSDK.h>
#import "RMWifiTool.h"
#define dispatch_global_queue_priority_default dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0)

@interface RMViewController ()

@property (nonatomic, copy) NSString *deviceIP;
@property (nonatomic, assign) NSInteger port;
@property (nonatomic, strong) FXNetDevice *netDevice;
@end

@implementation RMViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.deviceIP = [RMWifiTool getRouterIP];
    self.port = 9006;
    NSLog(@"ip:%@", self.deviceIP);
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
- (IBAction)loginEvent:(id)sender {
    [self loginDevice];
}

- (IBAction)logoutEvent:(id)sender {
    [self logoutDevice];
}


- (void)loginDevice {
    NetDeviceInfo* deviceInfo = [[NetDeviceInfo alloc]init];
    deviceInfo.deviceWanIP =  self.deviceIP;
    deviceInfo.deviceMediaPort = [NSNumber numberWithInteger:self.port];
    deviceInfo.deviceUsername = @"admin";
    deviceInfo.devicePassword = @"";
    deviceInfo.deviceType = DEV_N9M;
    __weak __typeof(self)wself = self;
    dispatch_async(dispatch_global_queue_priority_default, ^{

        self.netDevice = [[FXNetDevice alloc]initWithDeviceinfo:deviceInfo];
        
        ERROR_CODE ec = [wself.netDevice loginDevice];
        
        if (ec == ERROR_SUCCESS) {
            dispatch_async(dispatch_get_main_queue(), ^{
                NSLog(@"登录成功");
            });
        }
        else {
            dispatch_async(dispatch_get_main_queue(), ^{
                NSLog(@"登录失败");
                
            });
            
        }
        
    });
}

- (void)logoutDevice {
    __weak __typeof(self)wself = self;
    dispatch_async(dispatch_global_queue_priority_default, ^{

        ERROR_CODE ec = [wself.netDevice logoutDevice];
        
        if (ec == ERROR_SUCCESS) {
            dispatch_async(dispatch_get_main_queue(), ^{
                NSLog(@"退出登录成功");
            });
        }
        else {
            dispatch_async(dispatch_get_main_queue(), ^{
                NSLog(@"退出登录失败");
                
            });
            
        }
        
    });
}

@end
