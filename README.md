# NemG Library

**NemG Library** là một thư viện tĩnh (static library) dành cho iOS, được phát triển bởi **Nem'G**. Thư viện này cung cấp một bộ API toàn diện để xác thực key, truy xuất thông tin đăng nhập (login info) và các tiện ích hữu ích như:
- Hiển thị màn hình loading (GIF)
- Gửi tin nhắn qua Telegram/Discord
- Fake thông tin thiết bị và trạng thái mạng
- Kiểm tra trạng thái VPN
- Tính số ngày còn hiệu lực của key

Các API của thư viện bao gồm:

## Tính Năng Chính

### 1. Xác Thực Key & Lấy Thông Tin Đăng Nhập
- **Khởi tạo & Xác thực Key**
  - `+ (NemG *)listen:(NSString *)key;`  
    Khởi tạo đối tượng NemG với chìa khóa đã được mã hóa (sử dụng hàm FBEncrypt nếu cần).

  - `- (void)version:(NSString *)version paid:(void (^)(void))execute;`  
    Kiểm tra phiên bản (version) và xác thực key, sau đó gọi block `execute` nếu thành công.

- **Các Getter cho info_login:**
  - `- (NSString *)loginIP;`  
  - `- (NSString *)loginCity;`  
  - `- (NSString *)loginRegion;`  
  - `- (NSString *)loginCountry;`  
  - `- (NSString *)loginLocation;`  
  - `- (NSString *)loginOrg;`  
  - `- (NSString *)loginPostal;`  
  - `- (NSString *)loginTimezone;`

- **Các Getter cho key_info:**
  - `- (NSString *)loginUsername;`  
  - `- (NSString *)loginKey;`  
  - `- (NSString *)loginType;`  
  - `- (NSString *)loginEndTime;`  
  - `- (NSString *)loginTimeReal;`  
  - `- (NSString *)loginUUID;`  
  - `- (NSString *)loginTextServer;`

### 2. Tiện Ích Khác
- **Xoá Dữ Liệu Ứng Dụng**  
  `- (void)cleardata:(NSString *)title displayTime:(NSTimeInterval)displayDuration;`  
  Hiển thị cảnh báo và xoá toàn bộ dữ liệu.

- **Fake Thông Tin Thiết Bị & Trạng Thái Mạng**  
  `- (void)fakedevice:(BOOL)enable device:(NSString *)deviceName;`  
  `- (void)FakeNetwork:(int)state;`  

- **Gửi Thông Báo Qua Telegram & Discord**  
  `- (void)tele:(NSString *)text andCaption:(NSString *)caption token:(NSString *)providedToken chatID:(NSString *)providedChatID;`  
  `- (void)callDiscord:(NSString *)contentString webhookURL:(NSString *)webhookURL;`  
  `- (void)sendTelegram:(NSString *)contentString botToken:(NSString *)botToken chatID:(NSString *)chatID;`

- **Hiển Thị Loading Giả**  
  `- (void)loadingg:(NSTimeInterval)duration execute:(void (^)(void))execute;`  

- **Hiển Thị FPS**  
  `- (void)FPS:(NSString *)text color:(UIColor *)color font:(UIFont *)font active:(BOOL)status;`  

- **Kiểm Tra VPN**  
  `- (BOOL)isVPNConnected;`  

---

## Yêu Cầu

- iOS 9.0 trở lên  
- Xcode 11+  
- [Theos](https://github.com/theos/theos) (nếu dùng để phát triển tweak/jailbreak)

> **Chú ý:** Khi tích hợp NemG Library vào dự án của bạn, hãy đảm bảo liên kết các framework sau:
> - WebKit.framework  
> - Security.framework  
> - SystemConfiguration.framework

---

## Cài Đặt Theos

1. **Cài đặt Theos:**  
   - Clone Theos từ [Theos GitHub](https://github.com/theos/theos) vào thư mục (ví dụ: `/var/mobile/theos`).  
   - Thiết lập biến môi trường:
     ```bash
     export THEOS=/var/mobile/theos
     ```
   - Cài đặt các tool cần thiết (dpkg, clang, ldid, …) theo hướng dẫn trong README của Theos.

2. **Build dự án Theos:**  
   Sau khi cấu hình Makefile, bạn chỉ cần chạy `make`.

---

## Tích Hợp NemG vào Dự Án Theos

Thêm các dòng sau vào Makefile của bạn:

```makefile
# NemG Makefile Template

TARGET = iphone:latest:9.0
ARCHS = arm64
export THEOS_PROJECT_DIR = $(CURDIR)

include $(THEOS)/makefiles/common.mk

TWEAK_NAME = YourTweakName
YourTweakName_FILES = Tweak.x
YourTweakName_FRAMEWORKS = UIKit
YourTweakName_CFLAGS += -I$(THEOS_PROJECT_DIR)/API
YourTweakName_LDFLAGS += $(THEOS_PROJECT_DIR)/API/NemGVn.a

include $(THEOS)/makefiles/tweak.mk
