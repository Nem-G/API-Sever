# NemG Library

**NemG Library** là một thư viện tĩnh (static library) iOS được phát triển bởi **Nem'G**. Thư viện này cung cấp một bộ các API để xác thực key, truy xuất thông tin đăng nhập (login info), và các tiện ích hữu ích như:  
- Tự động hiển thị loading  
- Gửi tin nhắn qua Telegram/Discord  
- Fake trạng thái mạng và thiết bị  
- Kiểm tra VPN  
- Tính toán thời gian còn hiệu lực của key

Các API quan trọng bao gồm:
- **Khởi tạo & Xác Thực Key:**  
  + `+ (NemG *)listen:(NSString *)key;`  
    Khởi tạo đối tượng NemG với chìa khóa đã được mã hóa.
  
  + `- (void)version:(NSString *)version paid:(void (^)(void))execute;`  
    Kiểm tra version và xác thực key; nếu thành công, gọi block để tiếp tục xử lý (ví dụ: hiển thị Menu ứng dụng).

- **Các Getter cho info_login:**  
  + `- (NSString *)loginIP;`  
  + `- (NSString *)loginCity;`  
  + `- (NSString *)loginRegion;`  
  + `- (NSString *)loginCountry;`  
  + `- (NSString *)loginLocation;`  
  + `- (NSString *)loginOrg;`  
  + `- (NSString *)loginPostal;`  
  + `- (NSString *)loginTimezone;`

- **Các Getter cho key_info:**  
  + `- (NSString *)loginUsername;`  
  + `- (NSString *)loginKey;`  
  + `- (NSString *)loginType;`  
  + `- (NSString *)loginEndTime;`  
  + `- (NSString *)loginTimeReal;`  
  + `- (NSString *)loginUUID;`  
  + `- (NSString *)loginTextServer;`

- **Tiện ích khác:**  
  + `- (void)cleardata:(NSString *)title displayTime:(NSTimeInterval)displayDuration;`  
    Hiển thị cảnh báo và xoá toàn bộ dữ liệu ứng dụng.

  + `- (void)fakedevice:(BOOL)enable device:(NSString *)deviceName;`  
    Fake thông tin thiết bị.

  + `- (void)FakeNetwork:(int)state;`  
    Fake trạng thái mạng (WiFi/4G/Không có mạng).

  + `- (void)tele:(NSString *)text andCaption:(NSString *)caption token:(NSString *)providedToken chatID:(NSString *)providedChatID;`  
    Gửi ảnh hay text phản hồi qua Telegram.

  + `- (void)loadingg:(NSTimeInterval)duration execute:(void (^)(void))execute;`  
    Hiển thị màn hình loading giả (GIF) trong thời gian cho trước.

  + `- (void)FPS:(NSString *)text color:(UIColor *)color font:(UIFont *)font active:(BOOL)status;`  
    Hiển thị FPS (frame per second) của ứng dụng khi cần.

  + `- (BOOL)isVPNConnected;`  
    Kiểm tra trạng thái VPN.

  + `- (void)callDiscord:(NSString *)contentString webhookURL:(NSString *)webhookURL;`  
    Gửi thông báo đến Discord qua webhook.

  + `- (void)sendTelegram:(NSString *)contentString botToken:(NSString *)botToken chatID:(NSString *)chatID;`  
    Gửi thông báo đến Telegram qua bot.

---

## Yêu Cầu

- iOS 9.0 trở lên  
- Xcode 11+  
- [Theos](https://github.com/theos/theos) (nếu bạn phát triển ứng dụng jailbreak hoặc dùng Theos để build static library)

> **Lưu ý:** Static library NemG không tự liên kết các framework hệ thống. Khi tích hợp NemG vào dự án của bạn, bạn cần liên kết các framework sau:
> - WebKit.framework  
> - Security.framework  
> - SystemConfiguration.framework

---

## Cài Đặt Theos

1. **Cài đặt Theos**:  
   Bạn có thể cài đặt Theos theo hướng dẫn chính thức trên [Theos GitHub repository](https://github.com/theos/theos). Tóm lại:
   - Clone Theos vào thư mục bạn muốn (ví dụ: `/var/mobile/theos`)
   - Cài đặt các tool cần thiết (dpkg, clang, ldid, …) theo hướng dẫn của Theos.

2. **Thiết lập biến môi trường**:  
   Đảm bảo rằng biến môi trường `THEOS` được đặt đúng:
   ```bash
   export THEOS=/var/mobile/theos
