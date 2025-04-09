#ifndef OBF_H
#define OBF_H

#import <Foundation/Foundation.h>

#ifdef __cplusplus
extern "C" {
#endif

// Public API: Các hàm runtime obfuscation
FOUNDATION_EXPORT NSString *NemG_obfuscate(const char *input);
FOUNDATION_EXPORT NSString *NemG_deobfuscate(const char *input);

#ifdef __cplusplus
}
#endif

// --- Compile-time Obfuscation Macro ---
// Nếu được biên dịch với Objective‑C++ (.mm), dùng compile‑time obfuscation.
// Nếu không (file .m), chỉ trả về chuỗi gốc.
#ifdef __cplusplus

#if defined(_MSC_VER)
#define ALWAYS_INLINE __forceinline
#else
#define ALWAYS_INLINE __attribute__((always_inline))
#endif

// (Các định nghĩa C++ compile-time ở đây: seedToInt, vxCplConstantify, vxCplRandom, vxRANDOM, vxCplTolower, vxCplHash, vxCplIndexList, vxCplEncryptedString, v.v...)
// --- BEGIN C++ OBFS CODE ---
constexpr int seedToInt(char c) { return c - '0'; }
const int seed = seedToInt(__TIME__[7]) +
                 seedToInt(__TIME__[6]) * 10 +
                 seedToInt(__TIME__[4]) * 60 +
                 seedToInt(__TIME__[3]) * 600 +
                 seedToInt(__TIME__[1]) * 3600 +
                 seedToInt(__TIME__[0]) * 36000;

template <uintptr_t Const>
struct vxCplConstantify { enum { Value = Const }; };

constexpr uintptr_t vxCplRandom(uintptr_t Id) {
    return (1013904223u + 1664525u * ((Id > 0) ? vxCplRandom(Id - 1) : seed)) & 0xFFFFFFFFu;
}

#define vxRAND() (vxCplConstantify<vxCplRandom(__COUNTER__ + 1)>::Value)
#define vxRANDOM(Min, Max) (Min + (vxRAND() % (Max - Min + 1)))

constexpr char vxCplTolower(char Ch) {
    return (Ch >= 'A' && Ch <= 'Z') ? (Ch - 'A' + 'a') : Ch;
}

constexpr uintptr_t vxCplHashPart3(char Ch, uintptr_t Hash) {
    return ((Hash << 4) + vxCplTolower(Ch));
}
constexpr uintptr_t vxCplHashPart2(char Ch, uintptr_t Hash) {
    return (vxCplHashPart3(Ch, Hash) ^ ((vxCplHashPart3(Ch, Hash) & 0xF0000000u) >> 23));
}
constexpr uintptr_t vxCplHashPart1(char Ch, uintptr_t Hash) {
    return (vxCplHashPart2(Ch, Hash) & 0x0FFFFFFFu);
}
constexpr uintptr_t vxCplHash(const char* Str) {
    return (*Str) ? vxCplHashPart1(*Str, vxCplHash(Str + 1)) : 0;
}

#define HASH(Str) (uintptr_t)(vxCplConstantify<vxCplHash(Str)>::Value ^ vxCplConstantify<vxCplRandom(1)>::Value)

template <uintptr_t...>
struct vxCplIndexList {};

template <typename IndexList, uintptr_t Right>
struct vxCplAppend;
template <uintptr_t... Left, uintptr_t Right>
struct vxCplAppend<vxCplIndexList<Left...>, Right> {
    typedef vxCplIndexList<Left..., Right> Result;
};
template <uintptr_t N>
struct vxCplIndexes {
    typedef typename vxCplAppend<typename vxCplIndexes<N - 1>::Result, N - 1>::Result Result;
};
template <>
struct vxCplIndexes<0> {
    typedef vxCplIndexList<> Result;
};

constexpr char vxCplEncryptCharKey = (const char)vxRANDOM(0, HASH("ObfuscationKey"));

constexpr char ALWAYS_INLINE vxCplEncryptChar(const char Ch, uintptr_t Idx) {
    return Ch ^ (vxCplEncryptCharKey + Idx);
}

template <typename IndexList>
struct vxCplEncryptedString;
template <uintptr_t... Idx>
struct vxCplEncryptedString<vxCplIndexList<Idx...> > {
    char Value[sizeof...(Idx) + 1];
    constexpr ALWAYS_INLINE vxCplEncryptedString(const char* const Str)
        : Value{ vxCplEncryptChar(Str[Idx], Idx)... } {}
    inline const char* decrypt() {
        for (uintptr_t t = 0; t < sizeof...(Idx); t++) {
            Value[t] = Value[t] ^ (vxCplEncryptCharKey + t);
        }
        Value[sizeof...(Idx)] = '\0';
        return Value;
    }
};
// --- END C++ OBFS CODE ---

#define NamK3CR(Str) (vxCplEncryptedString<vxCplIndexes<sizeof(Str) - 1>::Result>(Str).decrypt())
#define FBEncrypt(Str) (@(NamK3CR(Str)))

#else

// Fallback nếu không biên dịch với Objective‑C++: chỉ trả về chuỗi gốc dưới dạng NSString.
#define NamK3CR(Str) ([NSString stringWithUTF8String:(Str)])
#define FBEncrypt(Str) NamK3CR(Str)

#endif  // __cplusplus

#endif // OBF_H