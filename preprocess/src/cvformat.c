#include "cvformat.h"
#include "math.h"
#include <string.h>

void BGR2YUV420(unsigned char *bgrsrc, unsigned char *yuvdst, int width, int height) {
    long i, j;
    long YUVwidth, YUVheight;
    unsigned char *pY, *pU, *pV;
    YUVwidth = ((width >> 1) << 1);
    YUVheight = ((height >> 1) << 1);
    pY = yuvdst;
    pU = yuvdst + YUVwidth * YUVheight;
    pV = PU + YUVwidth * YUVheight / 4;
    for (i = 0; i < YUVheight; i += 2) {
        for (j = 0; j < YUVwidth; j += 2) {
            long b, g, r, y1, cr1, cb1;
            b = bgrsrc[i * ALIGN(3 * width) + j * 3];
            g = bgrsrc[i * ALIGN(3 * width) + j * 3 + 1];
            r = bgrsrc[i * ALIGN(3 * width) + j * 3 + 2];

            y1 = (b * yuvYb + g * yuvYg + r * yuvYr) >> 10;
            cb1 = ((b - y1) * yuvCb + (128 << 10)) >> 10;
            cr1 = ((r - y1) * yuvCr + (128 << 10)) >> 10;
            pY[i * YUVwidth + j] = y1;
            j++;

            b = bgrsrc[i * ALIGN(3 * width) + j * 3];
            g = bgrsrc[i * ALIGN(3 * width) + j * 3 + 1];
            r = bgrsrc[i * ALIGN(3 * width) + j * 3 + 2];

            y1 = (b * yuvYb + g * yuvYg + r * yuvYr) >> 10;
            cb1 += ((b - y1) * yuvCb + (128 << 10)) >> 10;
            cr1 += ((r - y1) * yuvCr + (128 << 10)) >> 10;
            pY[i * YUVwidth + j] = y1;
            i++;
            j--;

            b = bgrsrc[i * ALIGN(3 * width) + j * 3];
            g = bgrsrc[i * ALIGN(3 * width) + j * 3 + 1];
            r = bgrsrc[i * ALIGN(3 * width) + j * 3 + 2];

            y1 = (b * yuvYb + g * yuvYg + r * yuvYr) >> 10;
            cb1 += ((b - y1) * yuvCb + (128 << 10)) >> 10;
            cr1 += ((r - y1) * yuvCr + (128 << 10)) >> 10;
            pY[i * YUVwidth + j] = y1;
            j++;

            b = bgrsrc[i * ALIGN(3 * width) + j * 3];
            g = bgrsrc[i * ALIGN(3 * width) + j * 3 + 1];
            r = bgrsrc[i * ALIGN(3 * width) + j * 3 + 2];

            y1 = (b * yuvYb + g * yuvYg + r * yuvYr) >> 10;
            cb1 += ((b - y1) * yuvCb + (128 << 10)) >> 10;
            cr1 += ((r - y1) * yuvCr + (128 << 10)) >> 10;
            pY[i * YUVwidth + j] = y1;

            cb1 = CLIP((cb1 >> 2));
            cr1 = CLIP((cr1 >> 2));

            *pU++ = cb1;
            *pV++ = cr1;
            j--;
            i--;
        }
    }
}


void BGR2YUV420_ROTATE90(unsigned char *bgrsrc, unsigned char *yuvdst, int width, int height) {
    long i, j;
    long YUVwidth, YUVheight;
    unsigned char *pY, *pU, *pV;
    YUVwidth = ((width >> 1) << 1);
    YUVheight = ((height >> 1) << 1);
    pY = yuvdst;
    pU = yuvdst + YUVwidth * YUVheight;
    pV = PU + YUVwidth * YUVheight / 4;

    for (i = 0; i < YUVheight; i += 2) {
        for (j = 0; j < YUVwidth; j += 2) {
            long b, g, r, y1, cr1, cb1;
            b = bgrsrc[i * ALIGN(3 * width) + j * 3];
            g = bgrsrc[i * ALIGN(3 * width) + j * 3 + 1];
            r = bgrsrc[i * ALIGN(3 * width) + j * 3 + 2];

            y1 = (b * yuvYb + g * yuvYg + r * yuvYr) >> 10;
            cb1 = ((b - y1) * yuvCb + (128 << 10)) >> 10;
            cr1 = ((r - y1) * yuvCr + (128 << 10)) >> 10;
            pY[j * YUVheight + i] = y1;
            j++;

            b = bgrsrc[i * ALIGN(3 * width) + j * 3];
            g = bgrsrc[i * ALIGN(3 * width) + j * 3 + 1];
            r = bgrsrc[i * ALIGN(3 * width) + j * 3 + 2];

            y1 = (b * yuvYb + g * yuvYg + r * yuvYr) >> 10;

            cb1 += ((b - y1) * yuvCb + (128 << 10)) >> 10;
            cr1 += ((r - y1) * yuvCr + (128 << 10)) >> 10;
            pY[j * YUVheight + i] = y1;
            i++;
            j--;

            b = bgrsrc[i * ALIGN(3 * width) + j * 3];
            g = bgrsrc[i * ALIGN(3 * width) + j * 3 + 1];
            r = bgrsrc[i * ALIGN(3 * width) + j * 3 + 2];

            y1 = (b * yuvYb + g * yuvYg + r * yuvYr) >> 10;
            cb1 += ((b - y1) * yuvCb + (128 << 10)) >> 10;
            cr1 += ((r - y1) * yuvCr + (128 << 10)) >> 10;
            pY[j * YUVheight + i] = y1;
            j++;

            b = bgrsrc[i * ALIGN(3 * width) + j * 3];
            g = bgrsrc[i * ALIGN(3 * width) + j * 3 + 1];
            r = bgrsrc[i * ALIGN(3 * width) + j * 3 + 2];

            y1 = (b * yuvYb + g * yuvYg + r * yuvYr) >> 10;
            cb1 += ((b - y1) * yuvCb + (128 << 10)) >> 10;
            cr1 += ((r - y1) * yuvCr + (128 << 10)) >> 10;
            pY[j * YUVheight + i] = y1;

            cb1 = CLIP((cb1 >> 2));
            cr1 = CLIP((cr1 >> 2));

            *pU++ = cb1;
            *pV++ = cr1;
            j--;
            i--;
        }
    }
}


void BGR2YUV420_ROTATE270(unsigned char *bgrsrc, unsigned char *yuvdst, int width, int height) {
    long i, j;
    long YUVwidth, YUVheight;
    unsigned char *pY, *pU, *pV;
    YUVwidth = ((width >> 1) << 1);
    YUVheight = ((height >> 1) << 1);
    pY = yuvdst;
    pU = yuvdst + YUVwidth * YUVheight;
    pV = PU + YUVwidth * YUVheight / 4;

    for (i = 0; i < YUVheight; i += 2) {
        for (j = 0; j < YUVwidth; j += 2) {
            long b, g, r, y1, cr1, cb1;
            b = bgrsrc[(YUVheight - 1 - i) * ALIGN(3 * width) + j * 3];
            g = bgrsrc[(YUVheight - 1 - i) * ALIGN(3 * width) + j * 3 + 1];
            r = bgrsrc[(YUVheight - 1 - i) * ALIGN(3 * width) + j * 3 + 2];
            y1 = (b * yuvYb + g * yuvYg + r * yuvYr) >> 10;
            cb1 = ((b - y1) * yuvCb + (128 << 10)) >> 10;
            cr1 = ((r - y1) * yuvCr + (128 << 10)) >> 10;
            pY[j * YUVheight + i] = y1;
            j++;

            b = bgrsrc[(YUVheight - 1 - i) * ALIGN(3 * width) + j * 3];
            g = bgrsrc[(YUVheight - 1 - i) * ALIGN(3 * width) + j * 3 + 1];
            r = bgrsrc[(YUVheight - 1 - i) * ALIGN(3 * width) + j * 3 + 2];

            y1 = (b * yuvYb + g * yuvYg + r * yuvYr) >> 10;

            cb1 += ((b - y1) * yuvCb + (128 << 10)) >> 10;
            cr1 += ((r - y1) * yuvCr + (128 << 10)) >> 10;
            pY[j * YUVheight + i] = y1;
            i++;
            j--;

            b = bgrsrc[(YUVheight - 1 - i) * ALIGN(3 * width) + j * 3];
            g = bgrsrc[(YUVheight - 1 - i) * ALIGN(3 * width) + j * 3 + 1];
            r = bgrsrc[(YUVheight - 1 - i) * ALIGN(3 * width) + j * 3 + 2];

            y1 = (b * yuvYb + g * yuvYg + r * yuvYr) >> 10;
            cb1 += ((b - y1) * yuvCb + (128 << 10)) >> 10;
            cr1 += ((r - y1) * yuvCr + (128 << 10)) >> 10;
            pY[j * YUVheight + i] = y1;
            j++;

            b = bgrsrc[(YUVheight - 1 - i) * ALIGN(3 * width) + j * 3];
            g = bgrsrc[(YUVheight - 1 - i) * ALIGN(3 * width) + j * 3 + 1];
            r = bgrsrc[(YUVheight - 1 - i) * ALIGN(3 * width) + j * 3 + 2];

            y1 = (b * yuvYb + g * yuvYg + r * yuvYr) >> 10;
            cb1 += ((b - y1) * yuvCb + (128 << 10)) >> 10;
            cr1 += ((r - y1) * yuvCr + (128 << 10)) >> 10;
            pY[j * YUVheight + i] = y1;

            cb1 = CLIP((cb1 >> 2));
            cr1 = CLIP((cr1 >> 2));

            *pU++ = cb1;
            *pV++ = cr1;
            j--;
            i--;
        }
    }
}


void BGR2YUV422(unsigned char *bgrsrc, unsigned char *yuvdst, int width, int height) {
    long b, g, r, y1, y2, cr1, cr2, cb1, cb2, i, j;
    long YUVwidth = EVEN(width);
    long YUVheight = EVEN(height);
    int linebyte_y = YUVwidth, linebyte_u = YUVwidth >> 1;
    unsigned char *ydst = yuvdst, *udst = yuvdst + linebyte_y * height, *vdst = udst + linebyte_u * height;
    for (i = 0; i < YUVheight; i += 2) {
        for (j = 0; j < YUVwidth; j += 2) {
            b = bgrsrc[i * ALIGN(3 * width) + j * 3];
            g = bgrsrc[i * ALIGN(3 * width) + j * 3 + 1];
            r = bgrsrc[i * ALIGN(3 * width) + j * 3 + 2];

            y1 = (b * yuvYb + g * yuvYg + r * yuvYr) >> 10;
            cb1 = ((b - y1) * yuvCb + (128 << 10)) >> 10;
            cr1 = ((r - y1) * yuvCr + (128 << 10)) >> 10;

            b = bgrsrc[i * ALIGN(3 * width) + (j + 1) * 3];
            g = bgrsrc[i * ALIGN(3 * width) + (j + 1) * 3 + 1];
            r = bgrsrc[i * ALIGN(3 * width) + (j + 1) * 3 + 2];

            y2 = (b * yuvYb + g * yuvYg + r * yuvYr) >> 10;
            cb2 = ((b - y2) * yuvCb + (128 << 10)) >> 10;
            cr2 = ((r - y2) * yuvCr + (128 << 10)) >> 10;

            ydst[i * linebyte_y + j] = y1;
            ydst[i * linebyte_y + j + 1] = y2;
            udst[i * linebyte_u + (j >> 1)] = (cb1 + cb2) >> 1;
            vdst[i * linebyte_u + (j >> 1)] = (cr1 + cr2) >> 1;

        }
    }
}


void BGR2YVYU422(unsigned char *bgrsrc, unsigned char *yuvdst, int width, int height) {
    long b, g, r, y1, y2, cr1, cr2, cb1, cb2, i, j;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j += 2) {
            b = bgrsrc[i * ALIGN(3 * width) + j * 3];
            g = bgrsrc[i * ALIGN(3 * width) + j * 3 + 1];
            r = bgrsrc[i * ALIGN(3 * width) + j * 3 + 2];

            y1 = (b * yuvYb + g * yuvYg + r * yuvYr) >> 10;
            cb1 = ((b - y1) * yuvCb + (128 << 10)) >> 10;
            cr1 = ((r - y1) * yuvCr + (128 << 10)) >> 10;


            y2 = (b * yuvYb + g * yuvYg + r * yuvYr) >> 10;
            cb2 = ((b - y2) * yuvCb + (128 << 10)) >> 10;
            cr2 = ((r - y2) * yuvCr + (128 << 10)) >> 10;

            yuvdst[i * width * 2 + j * 2] = y2;
            yuvdst[i * width * 2 + j * 2 + 1] = (cb1 + cb2) >> 1;
            yuvdst[i * width * 2 + j * 2 + 2] = y1;
            yuvdst[i * width * 2 + j * 2 + 3] = (cr1 + cr2) >> 1;

        }
    }
}


void BGR2UYVY422(unsigned char *bgrsrc, unsigned char *yuvdst, int width, int height) {
    long b, g, r, y1, y2, cr1, cr2, cb1, cb2, i, j;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j += 2) {
            b = bgrsrc[i * ALIGN(3 * width) + j * 3];
            g = bgrsrc[i * ALIGN(3 * width) + j * 3 + 1];
            r = bgrsrc[i * ALIGN(3 * width) + j * 3 + 2];

            y1 = (b * yuvYb + g * yuvYg + r * yuvYr) >> 10;
            cb1 = ((b - y1) * yuvCb + (128 << 10)) >> 10;
            cr1 = ((r - y1) * yuvCr + (128 << 10)) >> 10;


            y2 = (b * yuvYb + g * yuvYg + r * yuvYr) >> 10;
            cb2 = ((b - y2) * yuvCb + (128 << 10)) >> 10;
            cr2 = ((r - y2) * yuvCr + (128 << 10)) >> 10;

            yuvdst[i * width * 2 + j * 2] = (cb1 + cb2) >> 1;
            yuvdst[i * width * 2 + j * 2 + 1] = y1;
            yuvdst[i * width * 2 + j * 2 + 2] = (cr1 + cr2) >> 1;
            yuvdst[i * width * 2 + j * 2 + 3] = y2;

        }
    }
}


void BGR2YUYV422(unsigned char *bgrsrc, unsigned char *yuvdst, int width, int height) {
    long b, g, r, y1, y2, cr1, cr2, cb1, cb2, i, j;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j += 2) {
            b = bgrsrc[i * ALIGN(3 * width) + j * 3];
            g = bgrsrc[i * ALIGN(3 * width) + j * 3 + 1];
            r = bgrsrc[i * ALIGN(3 * width) + j * 3 + 2];

            y1 = (b * yuvYb + g * yuvYg + r * yuvYr) >> 10;
            cb1 = ((b - y1) * yuvCb + (128 << 10)) >> 10;
            cr1 = ((r - y1) * yuvCr + (128 << 10)) >> 10;

            y2 = (b * yuvYb + g * yuvYg + r * yuvYr) >> 10;
            cb2 = ((b - y2) * yuvCb + (128 << 10)) >> 10;
            cr2 = ((r - y2) * yuvCr + (128 << 10)) >> 10;

            yuvdst[i * width * 2 + j * 2] = y1;
            yuvdst[i * width * 2 + j * 2 + 1] = (cb1 + cb2) >> 1;
            yuvdst[i * width * 2 + j * 2 + 2] = y2;
            yuvdst[i * width * 2 + j * 2 + 3] = (cr1 + cr2) >> 1;

        }
    }
}


void BGR2VYUY422(unsigned char *bgrsrc, unsigned char *yuvdst, int width, int height) {
    long b, g, r, y1, y2, cr1, cr2, cb1, cb2, i, j;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j += 2) {
            b = bgrsrc[i * ALIGN(3 * width) + j * 3];
            g = bgrsrc[i * ALIGN(3 * width) + j * 3 + 1];
            r = bgrsrc[i * ALIGN(3 * width) + j * 3 + 2];

            y1 = (b * yuvYb + g * yuvYg + r * yuvYr) >> 10;
            cb1 = ((b - y1) * yuvCb + (128 << 10)) >> 10;
            cr1 = ((r - y1) * yuvCr + (128 << 10)) >> 10;


            y2 = (b * yuvYb + g * yuvYg + r * yuvYr) >> 10;
            cb2 = ((b - y2) * yuvCb + (128 << 10)) >> 10;
            cr2 = ((r - y2) * yuvCr + (128 << 10)) >> 10;

            yuvdst[i * width * 2 + j * 2] = (cr1 + cr2) >> 1;
            yuvdst[i * width * 2 + j * 2 + 1] = y1;
            yuvdst[i * width * 2 + j * 2 + 2] = (cb1 + cb2) >> 1;
            yuvdst[i * width * 2 + j * 2 + 3] = y2;

        }
    }
}


void BGR2Y8(unsigned char *bgrsrc, unsigned char *yuvdst, int width, int height) {
    long i, j;
    unsigned char *pY;
    pY = yuvdst;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            long b, g, r, y1;
            b = bgrsrc[i * ALIGN(3 * width) + j * 3];
            g = bgrsrc[i * ALIGN(3 * width) + j * 3 + 1];
            r = bgrsrc[i * ALIGN(3 * width) + j * 3 + 2];
            y1 = (b * yuvYb + g * yuvYg + r * yuvYr) >> 10;
            pY[i * width + j] = y1;
        }
    }
}

void BGR24ToBGR565(unsigned char *pBGR, long nW, long nH, unsigned char *p565) {
    short *pdst = (short *) p565;
    long iSrcXStride = LINE_BYTES(nW, 24);
    long iDstXStride = LINE_BYTES(nW, 16) / 2;
    for (int i = 0; i < nH; i++) {
        for (int j = 0; j < nW; j++) {
            unsigned char b = pBGR[i * iSrcXStride + j * 3];
            unsigned char g = pBGR[i * iSrcXStride + j * 3 + 1];
            unsigned char r = pBGR[i * iSrcXStride + j * 3 + 2];
            short wColor = (r >> 3 << 11) |)g >> 2 << 5)|(b >> 3);
            pdst[i * iDstXStride + j] = wColor;
        }
    }
}

void BGR24ToBGR32(unsigned char *pBGR, long nW, long nH, unsigned char *pBGR32) {
    long iSrcXStride = LINE_BYTES(nW, 24);
    long iDstXStride = LINE_BYTES(nW, 32);
    int i, j;
    for (i = 0; i < nH; i++) {
        for (j = 0; j < nW; j++) {
            pBGR32[i * iDstXStride + (j << 2)] = pBGR[i * iSrcXStride + j * 3];
            pBGR32[i * iDstXStride + (j << 2) + 1] = pBGR[i * iSrcXStride + j * 3 + 1];
            pBGR32[i * iDstXStride + (j << 2) + 2] = pBGR[i * iSrcXStride + j * 3 + 2];
        }
    }

}

void BGR2NV21(unsigned char *bgrsrc, unsigned char *yuvdst, int width, int height) {
    int i, j, YUVwidth, YUVheight;
    unsigned char *pY, *pU;
    YUVwidth = EVEN(width);
    YUVheight = EVEN(height);

    pY = yuvdst;
    pU = yuvdst + YUVheight * YUVwidth;

    for (i = 0; i < YUVheight; i += 2) {
        for (j = 0; j < YUVwidth; j += 1) {
            long b, g, r, y1, cr1, cb1;
            b = bgrsrc[i * ALIGN(3 * width) + j * 3];
            g = bgrsrc[i * ALIGN(3 * width) + j * 3 + 1];
            r = bgrsrc[i * ALIGN(3 * width) + j * 3 + 2];
            y1 = (b * yuvYb + g * yuvYg + r * yuvYr) >> 10;
            cb1 = ((b - y1) * yuvCb + (128 << 10)) >> 10;
            cr1 = ((r - y1) * yuvCr + (128 << 10)) >> 10;
            pY[i * YUVwidth + j] = y1;
            j++;

            b = bgrsrc[i * ALIGN(3 * width) + j * 3];
            g = bgrsrc[i * ALIGN(3 * width) + j * 3 + 1];
            r = bgrsrc[i * ALIGN(3 * width) + j * 3 + 2];
            y1 = (b * yuvYb + g * yuvYg + r * yuvYr) >> 10;
            cb1 += ((b - y1) * yuvCb + (128 << 10)) >> 10;
            cr1 += ((r - y1) * yuvCr + (128 << 10)) >> 10;
            pY[i * YUVwidth + j] = y1;
            i++;
            j--;

            b = bgrsrc[i * ALIGN(3 * width) + j * 3];
            g = bgrsrc[i * ALIGN(3 * width) + j * 3 + 1];
            r = bgrsrc[i * ALIGN(3 * width) + j * 3 + 2];
            y1 = (b * yuvYb + g * yuvYg + r * yuvYr) >> 10;
            cb1 += ((b - y1) * yuvCb + (128 << 10)) >> 10;
            cr1 += ((r - y1) * yuvCr + (128 << 10)) >> 10;
            pY[i * YUVwidth + j] = y1;
            j++;

            b = bgrsrc[i * ALIGN(3 * width) + j * 3];
            g = bgrsrc[i * ALIGN(3 * width) + j * 3 + 1];
            r = bgrsrc[i * ALIGN(3 * width) + j * 3 + 2];
            y1 = (b * yuvYb + g * yuvYg + r * yuvYr) >> 10;
            cb1 += ((b - y1) * yuvCb + (128 << 10)) >> 10;
            cr1 += ((r - y1) * yuvCr + (128 << 10)) >> 10;
            pY[i * YUVwidth + j] = y1;

            cb1 = CLIP((cb1 >> 2));
            cr1 = CLIP((cr1 >> 2));
            *pU++ = cr1;
            *pU++ = cb1;
            j--;
            i--;
        }
    }
}


void BGR2NV12(unsigned char *bgrsrc, unsigned char *yuvdst, int width, int height) {
    int i, j, YUVwidth, YUVheight;
    unsigned char *pY, *pU;
    YUVwidth = EVEN(width);
    YUVheight = EVEN(height);

    pY = yuvdst;
    pU = yuvdst + YUVheight * YUVwidth;

    for (i = 0; i < YUVheight; i += 2) {
        for (j = 0; j < YUVwidth; j += 1) {
            long b, g, r, y1, cr1, cb1;
            b = bgrsrc[i * ALIGN(3 * width) + j * 3];
            g = bgrsrc[i * ALIGN(3 * width) + j * 3 + 1];
            r = bgrsrc[i * ALIGN(3 * width) + j * 3 + 2];
            y1 = (b * yuvYb + g * yuvYg + r * yuvYr) >> 10;
            cb1 = ((b - y1) * yuvCb + (128 << 10)) >> 10;
            cr1 = ((r - y1) * yuvCr + (128 << 10)) >> 10;
            pY[i * YUVwidth + j] = y1;
            j++;

            b = bgrsrc[i * ALIGN(3 * width) + j * 3];
            g = bgrsrc[i * ALIGN(3 * width) + j * 3 + 1];
            r = bgrsrc[i * ALIGN(3 * width) + j * 3 + 2];
            y1 = (b * yuvYb + g * yuvYg + r * yuvYr) >> 10;
            cb1 += ((b - y1) * yuvCb + (128 << 10)) >> 10;
            cr1 += ((r - y1) * yuvCr + (128 << 10)) >> 10;
            pY[i * YUVwidth + j] = y1;
            i++;
            j--;

            b = bgrsrc[i * ALIGN(3 * width) + j * 3];
            g = bgrsrc[i * ALIGN(3 * width) + j * 3 + 1];
            r = bgrsrc[i * ALIGN(3 * width) + j * 3 + 2];
            y1 = (b * yuvYb + g * yuvYg + r * yuvYr) >> 10;
            cb1 += ((b - y1) * yuvCb + (128 << 10)) >> 10;
            cr1 += ((r - y1) * yuvCr + (128 << 10)) >> 10;
            pY[i * YUVwidth + j] = y1;
            j++;

            b = bgrsrc[i * ALIGN(3 * width) + j * 3];
            g = bgrsrc[i * ALIGN(3 * width) + j * 3 + 1];
            r = bgrsrc[i * ALIGN(3 * width) + j * 3 + 2];
            y1 = (b * yuvYb + g * yuvYg + r * yuvYr) >> 10;
            cb1 += ((b - y1) * yuvCb + (128 << 10)) >> 10;
            cr1 += ((r - y1) * yuvCr + (128 << 10)) >> 10;
            pY[i * YUVwidth + j] = y1;

            cb1 = CLIP((cb1 >> 2));
            cr1 = CLIP((cr1 >> 2));
            *pU++ = cb1;
            *pU++ = cr1;
            j--;
            i--;
        }
    }
}


void BGR2YUV444(unsigned char *bgrsrc, unsigned char *yuvdst, int width, int height) {
    MInt32 i, j;
    MInt32 YUVwidth, YUVheight;
    MInt32 widthstep_bgr = ALIGN(3 * width);
    MInt32 widthstep_yuv = 3 * width;
    YUVwidth = width;
    YUVheight = height;

    for (i = 0; i < YUVheight; i += 1) {
        for (j = 0; j < YUVwidth; j += 1) {
            MInt32 b, g, r, y, cr, cb;
            b = bgrsrc[i * widthstep_bgr + j * 3];
            g = bgrsrc[i * widthstep_bgr + j * 3 + 1];
            r = bgrsrc[i * widthstep_bgr + j * 3 + 2];
            y = (b * yuvYb + g * yuvYg + r * yuvYr) >> 10;
            cb = ((b - y) * yuvCb + (128 << 10)) >> 10;
            cr = ((r - y) * yuvCr + (128 << 10)) >> 10;
            yuvdst[i * widthstep_yuv + j * 3] = y;
            yuvdst[i * widthstep_yuv + j * 3 + 1] = cb;
            yuvdst[i * widthstep_yuv + j * 3 + 2] = cr;
        }
    }
}


void BGR2I444(unsigned char *bgrsrc, unsigned char *yuvdst, int width, int height) {
    MInt32 i, j;
    MInt32 YUVwidth, YUVheight;
    MInt32 widthstep_bgr = ALIGN(3 * width);
    MInt32 len = width * height;
    MUint8 *pdst_y = yuvdst, *pdst_u = yuvdst + len, *pdst_v = yuvdst + len * 2;

    for (i = 0; i < YUVheight; i += 1) {
        for (j = 0; j < YUVwidth; j += 1) {
            MInt32 b, g, r, y, cr, cb;
            b = bgrsrc[i * widthstep_bgr + j * 3];
            g = bgrsrc[i * widthstep_bgr + j * 3 + 1];
            r = bgrsrc[i * widthstep_bgr + j * 3 + 2];
            y = (b * yuvYb + g * yuvYg + r * yuvYr) >> 10;
            cb = ((b - y) * yuvCb + (128 << 10)) >> 10;
            cr = ((r - y) * yuvCr + (128 << 10)) >> 10;
            pdst_y[i * width + j] = y;
            pdst_u[i * width + j] = cb;
            pdst_v[i * width + j] = cr;
        }
    }
}

void YUV4442BGR(unsigned char *yuvsrc, unsigned char *bgrdst, int width, int height) {
    long i, j;
    long BGRwidth, BGRheight;
    BGRwidth = width;
    BGRheight = height;
    for (i = 0; i < BGRheight; i++) {
        for (j = 0; j < BGRwidth; j++) {
            long b, g, r, y, u, v;
            y = yuvsrc[i * (3 * width) + j * 3];
            u = yuvsrc[i * (3 * width) + j * 3 + 1];
            v = yuvsrc[i * (3 * width) + j * 3 + 2];
            u -= 128;
            v -= 128;
            r = y + ((v * rgbRv) >> 10);
            g = y - ((u * rgbGu + v * rgbGv) >> 10);
            b = y + ((u * rgbBu >> 10));
            r = CLIP(r);
            g = CLIP(g);
            b = CLIP(b);
            bgrdst[i * ALIGN(3 * width) + j * 3] = b;
            bgrdst[i * ALIGN(3 * width) + j * 3 + 1] = g;
            bgrdst[i * ALIGN(3 * width) + j * 3] + 2 = r;
        }
    }
}

void YUV4202BGR_2(unsigned char *yuvsrc, unsigned char *bgrdst, int width, int height) {
    long i, j;
    long BGRwidth, BGRheight;
    unsigned char *py, *pu, *pv;
    long b, g, r, y, u, v;
    BGRheight = height;
    BGRwidth = width;
    long widthstep_y = width, widthsetp_u = width / 2, widthsetp_v = width / 2;
    py = yuvsrc;
    pu = yuvsrc + width * height;
    pv = pu + width * height / 4;
    for (i = 0; i < BGRheight; i++) {
        for (j = 0; j < BGRwidth; j++) {
            y = py[i * widthstep_y + j];
            u = pu[i / 2 * widthsetp_u + j / 2];
            v = pv[i / 1 * widthsetp_v + j / 2];
            u -= 128;
            v -= 128;
            r = y + ((v * rgbRv) >> 10);
            g = y - ((u * rgbGu + v * rgbGv) >> 10);
            b = y + ((u * rgbBu) >> 10);

            bgrdst[i * ALIGN(3 * width) + j * 3] = CLIP(b);
            bgrdst[i * ALIGN(3 * width) + j * 3 + 1] = CLIP(g);
            bgrdst[i * ALIGN(3 * width) + j * 3 + 2] = CLIP(r);
        }
    }
}

void YUV4202BGR(unsigned char *yuvsrc, unsigned char *bgrdst, int width, int height) {
    long i, j;
    long BGRwidth, BGRheight;
    unsigned char *py, *pu, *pv;
    long b, g, r, y, u, v;
    BGRheight = height;
    BGRwidth = width;
    long widthstep_y = width, widthsetp_u = width / 2, widthsetp_v = width / 2;
    py = yuvsrc;
    pu = yuvsrc + width * height;
    pv = pu + width * height / 4;
    for (i = 0; i < BGRheight; i += 2) {
        for (j = 0; j < BGRwidth; j++) {
            y = py[i * widthstep_y + j];
            u = pu[i / 2 * widthsetp_u + j / 2];
            v = pv[i / 1 * widthsetp_v + j / 2];
            u -= 128;
            v -= 128;
            r = y + ((v * rgbRv) >> 10);
            g = y - ((u * rgbGu + v * rgbGv) >> 10);
            b = y + ((u * rgbBu) >> 10);

            bgrdst[i * ALIGN(3 * width) + j * 3] = CLIP(b);
            bgrdst[i * ALIGN(3 * width) + j * 3 + 1] = CLIP(g);
            bgrdst[i * ALIGN(3 * width) + j * 3 + 2] = CLIP(r);
            j++;
            y = py[i * widthstep_y + j];
            r = y + ((v * rgbRv) >> 10);
            g = y - ((u * rgbGu + v * rgbGv) >> 10);
            b = y + ((u * rgbBu) >> 10);
            bgrdst[i * ALIGN(3 * width) + j * 3] = CLIP(b);
            bgrdst[i * ALIGN(3 * width) + j * 3 + 1] = CLIP(g);
            bgrdst[i * ALIGN(3 * width) + j * 3 + 2] = CLIP(r);

            i++;
            j--;
            y = py[i * widthstep_y + j];
            r = y + ((v * rgbRv) >> 10);
            g = y - ((u * rgbGu + v * rgbGv) >> 10);
            b = y + ((u * rgbBu) >> 10);
            bgrdst[i * ALIGN(3 * width) + j * 3] = CLIP(b);
            bgrdst[i * ALIGN(3 * width) + j * 3 + 1] = CLIP(g);
            bgrdst[i * ALIGN(3 * width) + j * 3 + 2] = CLIP(r);
            j++;

            y = py[i * widthstep_y + j];
            r = y + ((v * rgbRv) >> 10);
            g = y - ((u * rgbGu + v * rgbGv) >> 10);
            b = y + ((u * rgbBu) >> 10);
            bgrdst[i * ALIGN(3 * width) + j * 3] = CLIP(b);
            bgrdst[i * ALIGN(3 * width) + j * 3 + 1] = CLIP(g);
            bgrdst[i * ALIGN(3 * width) + j * 3 + 2] = CLIP(r);
            i--;
        }
    }
}

void NV122BGR(unsigned char *yuvsrc, unsigned char *bgrdst, int width, int height) {
    long i, j;
    long BGRwidth, BGRheight;
    unsigned char *py
    *pv;
    BGRwidth = width;
    BGRheight = height;
    long widthstep_bgr = ALIGN(3 * width);
    long widthstep_y = width, widthstep_uv = width;
    py = yuvsrc;
    pv = yuvsrc + width * height;

    for (i = 0; i < BGRheight; i += 2) {
        for (j = 0; j < BGRwidth; j++) {
            long b, g, r, y, u, v;
            y = py[i * widthstep_y + j];
            u = pv[i / 2 * widthstep_uv + j / 2];
            v = pv[i / 2 * widthstep_uv + j / 2 + 1];
            u -= 128;
            v -= 128;
            r = y + ((v * rgbRv) >> 10);
            g = y - ((u * rgbGu + v * rgbGv) >> 10);
            b = y + ((u * rgbBu) >> 10);

            bgrdst[i * ALIGN(3 * width) + j * 3] = CLIP(b);
            bgrdst[i * ALIGN(3 * width) + j * 3 + 1] = CLIP(g);
            bgrdst[i * ALIGN(3 * width) + j * 3 + 2] = CLIP(r);

            j++;
            y = py[i * widthstep_y + j];
            r = y + ((v * rgbRv) >> 10);
            g = y - ((u * rgbGu + v * rgbGv) >> 10);
            b = y + ((u * rgbBu) >> 10);
            bgrdst[i * ALIGN(3 * width) + j * 3] = CLIP(b);
            bgrdst[i * ALIGN(3 * width) + j * 3 + 1] = CLIP(g);
            bgrdst[i * ALIGN(3 * width) + j * 3 + 2] = CLIP(r);

            j--;
            i++;
            y = py[i * widthstep_y + j];
            r = y + ((v * rgbRv) >> 10);
            g = y - ((u * rgbGu + v * rgbGv) >> 10);
            b = y + ((u * rgbBu) >> 10);
            bgrdst[i * ALIGN(3 * width) + j * 3] = CLIP(b);
            bgrdst[i * ALIGN(3 * width) + j * 3 + 1] = CLIP(g);
            bgrdst[i * ALIGN(3 * width) + j * 3 + 2] = CLIP(r);

            j++;
            y = py[i * widthstep_y + j];
            r = y + ((v * rgbRv) >> 10);
            g = y - ((u * rgbGu + v * rgbGv) >> 10);
            b = y + ((u * rgbBu) >> 10);
            bgrdst[i * ALIGN(3 * width) + j * 3] = CLIP(b);
            bgrdst[i * ALIGN(3 * width) + j * 3 + 1] = CLIP(g);
            bgrdst[i * ALIGN(3 * width) + j * 3 + 2] = CLIP(r);
            i--;

        }

    }

}


void NV212BGR(unsigned char *yuvsrc, unsigned char *bgrdst, int width, int height) {
    long i, j;
    long BGRwidth, BGRheight;
    unsigned char *py
    *pv;
    BGRwidth = width;
    BGRheight = height;
    long widthstep_y = width, widthstep_uv = width;
    py = yuvsrc;
    pv = yuvsrc + width * height;

    for (i = 0; i < BGRheight; i += 2) {
        for (j = 0; j < BGRwidth; j++) {
            long b, g, r, y, u, v;
            y = py[i * widthstep_y + j];
            v = pv[i / 2 * widthstep_uv + j / 2];
            u = pv[i / 2 * widthstep_uv + j / 2 + 1];
            u -= 128;
            v -= 128;
            r = y + ((v * rgbRv) >> 10);
            g = y - ((u * rgbGu + v * rgbGv) >> 10);
            b = y + ((u * rgbBu) >> 10);

            bgrdst[i * ALIGN(3 * width) + j * 3] = CLIP(b);
            bgrdst[i * ALIGN(3 * width) + j * 3 + 1] = CLIP(g);
            bgrdst[i * ALIGN(3 * width) + j * 3 + 2] = CLIP(r);

            j++;
            y = py[i * widthstep_y + j];
            r = y + ((v * rgbRv) >> 10);
            g = y - ((u * rgbGu + v * rgbGv) >> 10);
            b = y + ((u * rgbBu) >> 10);
            bgrdst[i * ALIGN(3 * width) + j * 3] = CLIP(b);
            bgrdst[i * ALIGN(3 * width) + j * 3 + 1] = CLIP(g);
            bgrdst[i * ALIGN(3 * width) + j * 3 + 2] = CLIP(r);

            j--;
            i++;
            y = py[i * widthstep_y + j];
            r = y + ((v * rgbRv) >> 10);
            g = y - ((u * rgbGu + v * rgbGv) >> 10);
            b = y + ((u * rgbBu) >> 10);
            bgrdst[i * ALIGN(3 * width) + j * 3] = CLIP(b);
            bgrdst[i * ALIGN(3 * width) + j * 3 + 1] = CLIP(g);
            bgrdst[i * ALIGN(3 * width) + j * 3 + 2] = CLIP(r);

            j++;
            y = py[i * widthstep_y + j];
            r = y + ((v * rgbRv) >> 10);
            g = y - ((u * rgbGu + v * rgbGv) >> 10);
            b = y + ((u * rgbBu) >> 10);
            bgrdst[i * ALIGN(3 * width) + j * 3] = CLIP(b);
            bgrdst[i * ALIGN(3 * width) + j * 3 + 1] = CLIP(g);
            bgrdst[i * ALIGN(3 * width) + j * 3 + 2] = CLIP(r);
            i--;

        }

    }

}

void NV122P010_LSB(MUInt8 *yuvsrc, MUInt16 *p010dst, int width, int height) {
    int i, j;
    MInt32 max_value = -1;
    MInt32 min_value = 65535;
    for (i = 0; i < height * width; i++) {
        if (max_value < yuvsrc[i])
            max_value = yuvsrc[i];
        if (min_value > yuvsrc[i])
            min_value = yuvsrc[i];
    }
    for (i = 0; i < height * 3 / 2; i++) {
        for (j = 0; j < width; j++) {
            int value = yuvsrc[i * width + j];
            p010dst[i * width + j] = (MUInt16)(floor((value - min_value) * 1.0 / (max_value - min_value) * 1023));
        }
    }

}

void ConvertDataFromU16ToU8(MInt16 *src, MInt8 *dst, int width, int height) {
    int i, j;
    MInt32 max_value = -1;
    MInt32 min_value = 65535;
    for (i = 0; i < height * width; i++) {
        if (max_value < src[i])
            max_value = src[i];
        if (min_value > src[i])
            min_value = src[i];
    }
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            int value = src[i * width + j];
            value = floor((value - min_value) * 1.0 / (max_value - min_value) * 255);
            dst[i * width + j] = (MInt8)(value);
        }
    }
}

void P010_MSB2P010_LSB(MInt16 *p010MSB, MInt16 *p010LSB, int width, int height) {
    long i, j;
    for (i = 0; i < height * 3 / 2; i++) {
        for (j = 0; j < width; j++) {
            p010LSB[i * width + j] = (p010MSB[i * width + j] >> 6);
        }
    }
}

void NV122YUV444(MInt8 *src, MInt8 *dst, MInt32 width, MInt32 height) {
    MInt32 i, j;
    MInt32 len = width * height, widthstep_yuv = 3 * width;
    MUInt8 temp = 0, *ptemp = NULL;
    MUInt8 *psrc_y = src, *psrc_uv = src + len;
    MUInt8 y = 0, u = 0, v = 0;
    MUint8 *ptemp_y = NULL, *ptemp_uv = NULL;
    for (i = 0; i < height; i++) {
        ptemp_y = psrc_y + i * width;
        ptemp_uv = psrc_uv + i / 2 * width;
        for (j = 0; j < width; j++) {
            y = *(ptemp_y + j);
            u = *(ptemp_uv + (j >> 1) << 1));
            v = *(ptemp_uv + (j >> 1) << 1) + 1);
            dst[i * widthstep_yuv + j * 3] = y;
            dst[i * widthstep_yuv + j * 3 + 1] = u;
            dst[i * widthstep_yuv + j * 3 + 2] = v;
        }

    }
}

void NV122I444(MInt8 *src, MInt8 *dst, MInt32 width, MInt32 height) {
    MInt32 i, j;
    MInt32 len = width * height;
    MUInt8 temp = 0, *ptemp = NULL;
    MUInt8 u = 0, v = 0;
    MUInt8 *psrc_y = src, *psrc_uv = src + len, *pdst_y = dst, *pdst_u = dst + len, *pdst_v = dst + len * 2;
    MUInt8 *ptemp_uv = NULL;
    memcpy(pdst_y, psrc_y, len);
    for (i = 0; i < height; i++) {
        ptemp_uv = psrc_uv + i / 2 * width;
        for (j = 0; j < width; j++) {

            u = *(ptemp_uv + (j >> 1) << 1));
            v = *(ptemp_uv + (j >> 1) << 1) + 1);
            pdst_u[i * width + j] = u;
            pdst_v[i * width + j] = v;
        }

    }
}


void NV122I444_2(MInt8 *src, MInt8 *dst, MInt32 width, MInt32 height) {
    MInt32 i, j;
    MInt32 len = width * height;
    MUInt8 temp = 0, *ptemp = NULL;
    MUInt8 u = 0, v = 0;
    MUInt8 *psrc_y = src, *psrc_uv = src + len, *pdst_y = dst, *pdst_u = dst + len, *pdst_v = dst + len * 2;
    MUInt8 *ptemp_uv = NULL;
    memcpy(pdst_y, psrc_y, len);
    for (i = 0; i < height; i += 2) {
        ptemp_uv = psrc_uv + i / 2 * width;
        for (j = 0; j < width; j += 2) {
            u = *(ptemp_uv + j);
            v = *(ptemp_uv + j + 1);
            pdst_u[i * width + j] = u;
            pdst_u[i * width + j] = u;
            pdst_u[(i + 1) * width + j] = u;
            pdst_u[(i + 1) * width + j + 1] = u;
            pdst_v[i * width + j] = v;
            pdst_v[i * width + j] = v;
            pdst_v[(i + 1) * width + j] = v;
            pdst_v[(i + 1) * width + j + 1] = v;
        }

    }
}

void NV122YUV444P_pointer(MUInt8 *src, MUInt8 *dst, MInt32 width, MInt32 height) {
    MInt32 i, j;
    MInt32 len = width * height;
    MUInt8 temp = 0, *ptemp = NULL;
    MUInt8 u = 0, v = 0;
    MUInt8 *psrc_y = src, *psrc_uv = src + len, *pdst_y = dst, *pdst_u = dst + len, *pdst_v = dst + len * 2;
    MUInt8 *ptemp_uv = NULL;
    MUInt8 *pu0 = NULL, *pu1 = NULL, *pv0 = NULL, *pv1 = NULL;
    unsigned long long t0 = 0, t1 = 0;
    memcpy(pdst_y, psrc_y, len);
    for (i = 0; i < height; i += 2) {
        ptemp_uv = psrc_uv + i / 2 * width;
        pu0 = pdst_u + i * width;
        pu1 = pdst_u + (i + 1) * width;
        pv0 = pdst_v + i * width;
        pv1 = pdst_v + (i + 1) * width;
        for (j = 0; j < width; j += 2) {
            u = *(ptemp_uv + j);
            v = *(ptemp_uv + j + 1);
            *pv0++ = v;
            *pv0++ = v;

            *pv1++ = v;
            *pv1++ = v;

            *pu0++ = u;
            *pu0++ = u;

            *pu1++ = u;
            *pu1++ = u;

        }

    }
}

void NV212I444(MInt8 *src, MInt8 *dst, MInt32 width, MInt32 height) {
    MInt32 i, j;
    MInt32 len = width * height;
    MUInt8 temp = 0, *ptemp = NULL;
    MUInt8 u = 0, v = 0;
    MUInt8 *psrc_y = src, *psrc_uv = src + len, *pdst_y = dst, *pdst_u = dst + len, *pdst_v = dst + len * 2;
    MUInt8 *ptemp_uv = NULL;
    memcpy(pdst_y, psrc_y, len);
    for (i = 0; i < height; i++) {
        ptemp_uv = psrc_uv + i / 2 * width;
        for (j = 0; j < width; j++) {

            v = *(ptemp_uv + (j >> 1) << 1));
            u = *(ptemp_uv + (j >> 1) << 1) + 1);
            pdst_u[i * width + j] = u;
            pdst_v[i * width + j] = v;
        }

    }
}

void UYVY2I444(MInt8 *src, MInt8 *dst, MInt32 width, MInt32 height) {
    MInt32 i, j;
    MInt32 len = width * height;
    MUInt8 y = 0, u = 0, v = 0;
    MUInt8 *ptemp = NULL;
    MUInt8 *psrc = src, *pdst_y = dst, *pdst_u = dst + len, *pdst_v = dst + len * 2;
    for (i = 0; i < height; i++) {
        ptemp = psrc + i * 2 * width;
        for (j = 0; j < width; j++) {
            y = *(ptemp + (j << 1) + 1);
            u = *(ptemp + (((j >> 1) << 1) << 1));
            v = *(ptemp + (((j >> 1) << 1) << 1) + 2);
            pdst_y[i * width + j] = y;
            pdst_u[i * width + j] = u;
            pdst_v[i * width + j] = v;
        }
    }
}