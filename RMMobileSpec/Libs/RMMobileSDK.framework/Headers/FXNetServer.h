//
//  FXNetServer.h
//  cqfxplus
//
//  Created by 许 飞 on 14-5-15.
//  Copyright (c) 2014年 frank xu. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol FXNetServerDelegate;

@interface FXNetServer : NSObject

@property(nonatomic,strong)NSMutableArray* serverArray;
@property(nonatomic,assign)id<FXNetServerDelegate> delegate;


-(id)initWithServerList:(NSMutableArray*)servers;//Netserverinfo array.
-(void)ConnectServer;
-(void)DisconnectServer;
-(void)ConnectMSGServer:(NSString *)serverIP Port:(NSInteger)port;

-(void)DisconnectMSGServer;

+ (void)setOnTLS:(BOOL)on;

/// 设置视频加密RSA key
/// @param keyString nil == 关闭
+ (void)setVideoEncryptionKey:(NSString *)keyString;

//DATA: 被加密的公钥结构体原始数据数组。说明：调用公共库接口对公钥和模数（私钥为空）加密后再Base64编码后的字符串
//DATALEN: 被加密的公钥结构体原始数据长度
//INDEX: 密钥索引，生成规则：模数【char[516]】+公钥指数【char[516]】的MD5值，char数组长度不足516的，用0填充
+ (void)setMultiVideoEncryptionKeys:(NSArray *)multiKeysInfo;

@end

@protocol FXNetServerDelegate <NSObject>

-(void)FXNetServer:(FXNetServer*)server MSG:(NSInteger)message PARAM:(NSString*)param;

@end
