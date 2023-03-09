#ifndef _CVT_FORMAT_HEADER_
#define _CVT_FORMAT_HEADER_

#include "asvloffscreen.hpp"
#include "amcomdef.hpp"

//#ifdef __cplusplus
//extern "C"{
//#endif

#define fix(x,n) (long long)((x)*((long long)(1)<<(n)) + 0.5)
#define yuvYr fix(0.299,10)
#define yuvYg fix(0.587,10)
#define yuvYb fix(0.114,10)
#define yuvCr fix(0.713,10)
#define yuvCb fix(0.564,10)

#define rgbRv fix(1.402,10)
#define rgbGu fix(0.34414,10)
#define rgbGv fix(0.71414,10)
#define rgbBu fix(1.772,10)

#define rgbRv_16 fix(1.402,16)
#define rgbGu_16 fix(0.34414,16)
#define rgbGv_16 fix(0.71414,16)
#define rgbBu_16 fix(1.772,16)

#define ALIGN(size) (((size)+3)& -4)
#define EVEN(x) (x&0xfffffffe)
#define CLIP(x) (unsigned char)((x)&(~255)?((-x)>>31):(x))
#define LINE_BYTES(Width, BitCt)  (((long)(Width)*(BitCt)+31)/32 * 4)


void BGR2YUV444(unsigned char* bgrsrc, unsigned char* yuvdst, int width, int height);
void BGR2I444(unsigned char* bgrsrc, unsigned char* yuvdst, int width, int height);
void BGR2YUV422(unsigned char* bgrsrc, unsigned char* yuvdst, int width, int height);
void BGR2VYUY422(unsigned char* bgrsrc, unsigned char* yuvdst, int width, int height);
void BGR2UYVY422(unsigned char* bgrsrc, unsigned char* yuvdst, int width, int height);
void BGR2YUYV422(unsigned char* bgrsrc, unsigned char* yuvdst, int width, int height);
void BGR2Y8(unsigned char* bgrsrc, unsigned char* yuvdst, int width, int height);
void BGR22ToBGR565(unsigned char* bgrsrc, unsigned char* yuvdst, int width, int height);
void BGR2YUV420(unsigned char* bgrsrc, unsigned char* yuvdst, int width, int height);
void BGR2YUV420_ROTATE90(unsigned char* bgrsrc, unsigned char* yuvdst, int width, int height);
void BGR2YUV420_ROTATE270(unsigned char* bgrsrc, unsigned char* yuvdst, int width, int height);
void BGR22ToBGR32(unsigned char* bgrsrc, unsigned char* yuvdst, int width, int height);
void BGR2NV21(unsigned char* bgrsrc, unsigned char* yuvdst, int width, int height);
void BGR2NV12(unsigned char* bgrsrc, unsigned char* yuvdst, int width, int height);

void NV212BGR(unsigned char* yuvsrc, unsigned char* bgrdst, int width, int height);
void NV122BGR(unsigned char* yuvsrc, unsigned char* bgrdst, int width, int height);
void YUV4442BGR(unsigned char* yuvsrc, unsigned char* bgrdst, int width, int height);
void YUV4202BGR(unsigned char* yuvsrc, unsigned char* bgrdst, int width, int height);
void YUV4202BGR_2(unsigned char* yuvsrc, unsigned char* bgrdst, int width, int height);

void NV122P010_LSB(MUInt8* yuvsrc, MUInt16* p010dst, int width, int height);
void P010_LSB2NV12(MUInt16 p010src, MUInt8* yuvdst, int width, int height);
void P010_MSB2P010_MSB(MUInt16* p010MSB, MUInt16* p010LSB, int width, int height);

void ConvertDataFromU16ToU8(MUInt16* src, MUInt8* dst, int width, int height);
void NV122YUV444(MUInt8* src, MUInt8* dst, MInt32 width, MInt32 height);
void NV122I444(MUInt8* src, MUInt8* dst, MInt32 width, MInt32 height);
void NV122I444_2(MUInt8* src, MUInt8* dst, MInt32 width, MInt32 height);
void NV212I444(MUInt8* src, MUInt8* dst, MInt32 width, MInt32 height);
void UYVY2I444(MUInt8* src, MUInt8* dst, MInt32 width, MInt32 height);
//#ifdef __cplusplus
//}
//#endif
#endif

