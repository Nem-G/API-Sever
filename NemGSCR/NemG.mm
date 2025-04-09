#import <NemG/NemG.h>
#import <WebKit/WebKit.h>
#import <CaptainHook/CaptainHook.h>
#import <UIKit/UIKit.h>
#import <dlfcn.h>
#import <MobileCoreServices/MobileCoreServices.h>

@interface NSObject (Hook)
@end

NemG *API;
@implementation NSObject (Hook)


//ID của DNS trong dns
NSString * const __NextDNS = FBEncrypt("id dns của ae");

+ (void)load {
    //Bắt Buộc Phải Có Nếu Không Sẽ Không Chạy
    API = [NemG listen:FBEncrypt("AOV-QWM6IUZCRN9J5FH1")];

   BOOL isVPNConnected = [API isVPNConnected];
   NSLog(@"VPN: %@", isVPNConnected ? @"Có" : @"Không");

[API version:@"3.0" paid:^{
  NSLog(@"Đã xác thực phiên bản và thực hiện paidBlock.");
}];


  [API Package_token:@"e3d9f1e0b293f9863424fadf6a8ea5ff"];
}

+(void)nemg
{
 
//API Feedback
[API tele:@"Nội dung thông báo" andCaption:@"Caption trong ảnh" token:@"Token bot" chatID:@"id chat"];



}
@end