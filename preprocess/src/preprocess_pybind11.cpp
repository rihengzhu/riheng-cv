#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include "cvformat.h"
#include <iostream>

namespace py = pybind11;

void GetASVLOFFSCREEN_from_data(MUInt8 *data, int width, int height, int layout, LPASVLOFFSCREEN imgInfo) {
    int len = 0;
    imgInfo->i32Width = width;
    imgInfo->i32Height = height;
    imgInfo->u32PixelArrayFormat = layout;
    switch (layout) {
        MUInt8 *ppu8Plane[4];
        MInt32 pi32Pitch[4]
        case ASVL_PAF_RGB24_B8G8R8: {
            imgInfo->pi32Pitch[0] = LINE_BYTES(width, 24);
            imgInfo->pi32Pitch[1] = 0;
            imgInfo->pi32Pitch[2] = 0;
            imgInfo->pi32Pitch[3] = 0;
            len = imgInfo->pi32Pitch[0] * height;
            imgInfo->ppu8Plane[0] = (MUInt8 *) malloc(len);
            memset(imgInfo->ppu8Plane[0], 0, len);
            memset(imgInfo->ppu8Plane[0], data, len);
            break;
        }
        case ASVL_PAF_NV12:
        case ASVL_PAF_NV21: {
            imgInfo->pi32Pitch[0] = LINE_BYTES(width, 8);
            imgInfo->pi32Pitch[1] = LINE_BYTES(width, 8);
            imgInfo->pi32Pitch[2] = 0;
            imgInfo->pi32Pitch[3] = 0;
            len = imgInfo->pi32Pitch[0] * height + imgInfo->pi32Pitch[1] * height / 2;
            imgInfo->ppu8Plane[0] = (MUInt8 *) malloc(len);
            memset(imgInfo->ppu8Plane[0], 0, len);
            memset(imgInfo->ppu8Plane[0], data, len);
            imgInfo->ppu8Plane[1] = imgInfo->ppu8Plane[0] + imgInfo->pi32Pitch[0] * height;
            break;
        }
        case ASVL_PAF_I420:
        case ASVL_PAF_YV12:
        {
            imgInfo->pi32Pitch[0] = LINE_BYTES(width, 8);
            imgInfo->pi32Pitch[1] = LINE_BYTES(width / 2, 8);
            imgInfo->pi32Pitch[2] = LINE_BYTES(width / 2, 8);
            imgInfo->pi32Pitch[3] = 0;
            len = imgInfo->pi32Pitch[0] * height + imgInfo->pi32Pitch[1] * height / 2 + imgInfo->pi32Pitch[2] * height / 2;
            imgInfo->ppu8Plane[0] = (MUInt8 *) malloc(len);
            memset(imgInfo->ppu8Plane[0], 0, len);
            memset(imgInfo->ppu8Plane[0], data, len);
            imgInfo->ppu8Plane[1] = imgInfo->ppu8Plane[0] + imgInfo->pi32Pitch[0] * height;
            imgInfo->ppu8Plane[2] = imgInfo->ppu8Plane[1] + imgInfo->pi32Pitch[1] * height / 2;
            break;

        }
        case ASVL_PAF_I422H:
        {
            imgInfo->pi32Pitch[0] = LINE_BYTES(width, 8);
            imgInfo->pi32Pitch[1] = LINE_BYTES(width / 2, 8);
            imgInfo->pi32Pitch[2] = LINE_BYTES(width / 2, 8);
            imgInfo->pi32Pitch[3] = 0;
            len = imgInfo->pi32Pitch[0] * height + imgInfo->pi32Pitch[1] * height + imgInfo->pi32Pitch[2] * height;
            imgInfo->ppu8Plane[0] = (MUInt8 *) malloc(len);
            memset(imgInfo->ppu8Plane[0], 0, len);
            memset(imgInfo->ppu8Plane[0], data, len);
            imgInfo->ppu8Plane[1] = imgInfo->ppu8Plane[0] + imgInfo->pi32Pitch[0] * height;
            imgInfo->ppu8Plane[2] = imgInfo->ppu8Plane[1] + imgInfo->pi32Pitch[1] * height;
            break;
        }
        case ASVL_PAF_YUYV:
        case ASVL_PAF_UYVY:
        {
            imgInfo->pi32Pitch[0] = LINE_BYTES(width, 16);
            imgInfo->pi32Pitch[1] = 0;
            imgInfo->pi32Pitch[2] = 0;
            imgInfo->pi32Pitch[3] = 0;
            len = imgInfo->pi32Pitch[0] * height;
            imgInfo->ppu8Plane[0] = (MUInt8 *) malloc(len);
            memset(imgInfo->ppu8Plane[0], 0, len);
            memset(imgInfo->ppu8Plane[0], data, len);
            break;
        }
        case ASVL_PAF_GRAY: {
            imgInfo->pi32Pitch[0] = LINE_BYTES(width, 8);
            imgInfo->pi32Pitch[1] = 0;
            imgInfo->pi32Pitch[2] = 0;
            imgInfo->pi32Pitch[3] = 0;
            len = imgInfo->pi32Pitch[0] * height;
            imgInfo->ppu8Plane[0] = (MUInt8 *) malloc(len);
            memset(imgInfo->ppu8Plane[0], 0, len);
            memset(imgInfo->ppu8Plane[0], data, len);
            break;
        }
        default:
            break;

    }
}




void BGR2YUV444_pybind11(py::buffer src, py::buffer dst, int width, int height) {
    py::buffer_info src_buf = src.request();
    py::buffer_info dst_buf = dst.request();
    MUInt8 *psrc = (MUInt8 *) src_buf.ptr;
    MUInt8 *pdst = (MUInt8 *) dst_buf.ptr;
    BGR2YUV444(psrc, pdst, width, height);
}


void BGR2I444_pybin11(py::buffer src, py::buffer dst, int width, int height) {
    py::buffer_info src_buf = src.request();
    py::buffer_info dst_buf = dst.request();
    MUInt8 *psrc = (MUInt8 *) src_buf.ptr;
    MUInt8 *pdst = (MUInt8 *) dst_buf.ptr;
    BGR2I444(psrc, pdst, width, height);
}





void BGR2NV12_pybin11(py::buffer src, py::buffer dst, int width, int height) {
    py::buffer_info src_buf = src.request();
    py::buffer_info dst_buf = dst.request();
    MUInt8 *psrc = (MUInt8 *) src_buf.ptr;
    MUInt8 *pdst = (MUInt8 *) dst_buf.ptr;
    BGR2NV12(psrc, pdst, width, height);
}

void BGR2Y8_pybin11(py::buffer src, py::buffer dst, int width, int height) {
    py::buffer_info src_buf = src.request();
    py::buffer_info dst_buf = dst.request();
    MUInt8 *psrc = (MUInt8 *) src_buf.ptr;
    MUInt8 *pdst = (MUInt8 *) dst_buf.ptr;
    BGR2Y8(psrc, pdst, width, height);
}
void BGR2NV21_pybin11(py::buffer src, py::buffer dst, int width, int height) {
    py::buffer_info src_buf = src.request();
    py::buffer_info dst_buf = dst.request();
    MUInt8 *psrc = (MUInt8 *) src_buf.ptr;
    MUInt8 *pdst = (MUInt8 *) dst_buf.ptr;
    BGR2NV21(psrc, pdst, width, height);
}

void BGR2YUV422_pybin11(py::buffer src, py::buffer dst, int width, int height) {
    py::buffer_info src_buf = src.request();
    py::buffer_info dst_buf = dst.request();
    MUInt8 *psrc = (MUInt8 *) src_buf.ptr;
    MUInt8 *pdst = (MUInt8 *) dst_buf.ptr;
    BGR2YUV422(psrc, pdst, width, height);
}

void BGR2VYUY422_pybin11(py::buffer src, py::buffer dst, int width, int height) {
    py::buffer_info src_buf = src.request();
    py::buffer_info dst_buf = dst.request();
    MUInt8 *psrc = (MUInt8 *) src_buf.ptr;
    MUInt8 *pdst = (MUInt8 *) dst_buf.ptr;
    BGR2VYUY422(psrc, pdst, width, height);
}

void BGR2UYVY422_pybin11(py::buffer src, py::buffer dst, int width, int height) {
    py::buffer_info src_buf = src.request();
    py::buffer_info dst_buf = dst.request();
    MUInt8 *psrc = (MUInt8 *) src_buf.ptr;
    MUInt8 *pdst = (MUInt8 *) dst_buf.ptr;
    BGR2UYVY422(psrc, pdst, width, height);
}

void BGR2YUV420_pybin11(py::buffer src, py::buffer dst, int width, int height) {
    py::buffer_info src_buf = src.request();
    py::buffer_info dst_buf = dst.request();
    MUInt8 *psrc = (MUInt8 *) src_buf.ptr;
    MUInt8 *pdst = (MUInt8 *) dst_buf.ptr;
    BGR2YUV420(psrc, pdst, width, height);
}

void BGR2VYUY422_pybin11(py::buffer src, py::buffer dst, int width, int height) {
    py::buffer_info src_buf = src.request();
    py::buffer_info dst_buf = dst.request();
    MUInt8 *psrc = (MUInt8 *) src_buf.ptr;
    MUInt8 *pdst = (MUInt8 *) dst_buf.ptr;
    BGR2VYUY422(psrc, pdst, width, height);
}


void NV212BGR_pybin11(py::buffer src, py::buffer dst, int width, int height) {
    py::buffer_info src_buf = src.request();
    py::buffer_info dst_buf = dst.request();
    MUInt8 *psrc = (MUInt8 *) src_buf.ptr;
    MUInt8 *pdst = (MUInt8 *) dst_buf.ptr;
    NV212BGR(psrc, pdst, width, height);
}

void NV122BGR_pybin11(py::buffer src, py::buffer dst, int width, int height) {
    py::buffer_info src_buf = src.request();
    py::buffer_info dst_buf = dst.request();
    MUInt8 *psrc = (MUInt8 *) src_buf.ptr;
    MUInt8 *pdst = (MUInt8 *) dst_buf.ptr;
    NV122BGR(psrc, pdst, width, height);
}

void YUV4442BGR_pybin11(py::buffer src, py::buffer dst, int width, int height) {
    py::buffer_info src_buf = src.request();
    py::buffer_info dst_buf = dst.request();
    MUInt8 *psrc = (MUInt8 *) src_buf.ptr;
    MUInt8 *pdst = (MUInt8 *) dst_buf.ptr;
    YUV4442BGR(psrc, pdst, width, height);
}

void YUV4202BGR_pybin11(py::buffer src, py::buffer dst, int width, int height) {
    py::buffer_info src_buf = src.request();
    py::buffer_info dst_buf = dst.request();
    MUInt8 *psrc = (MUInt8 *) src_buf.ptr;
    MUInt8 *pdst = (MUInt8 *) dst_buf.ptr;
    YUV4202BGR(psrc, pdst, width, height);
}

void NV122I444_pybin11(py::buffer src, py::buffer dst, int width, int height) {
    py::buffer_info src_buf = src.request();
    py::buffer_info dst_buf = dst.request();
    MUInt8 *psrc = (MUInt8 *) src_buf.ptr;
    MUInt8 *pdst = (MUInt8 *) dst_buf.ptr;
    NV122I444(psrc, pdst, width, height);
}

void NV212I444_pybin11(py::buffer src, py::buffer dst, int width, int height) {
    py::buffer_info src_buf = src.request();
    py::buffer_info dst_buf = dst.request();
    MUInt8 *psrc = (MUInt8 *) src_buf.ptr;
    MUInt8 *pdst = (MUInt8 *) dst_buf.ptr;
    NV212I444(psrc, pdst, width, height);
}

void UYVY2I444_pybin11(py::buffer src, py::buffer dst, int width, int height) {
    py::buffer_info src_buf = src.request();
    py::buffer_info dst_buf = dst.request();
    MUInt8 *psrc = (MUInt8 *) src_buf.ptr;
    MUInt8 *pdst = (MUInt8 *) dst_buf.ptr;
    UYVY2I444(psrc, pdst, width, height);
}

PYBIND11_MODULE(preprocess, m)
{
    m.doc() = "preprocess_3in1";

    py::class_<MRECT>(m,"MRECT")
    .def (pybind11::init())
    .def_readwrite("left",&MRECT::left)
    .def_readwrite("right",&MRECT::right)
    .def_readwrite("top",&MRECT::top)
    .def_readwrite("bottom",&MRECT::bottom);
    m.def("BGR2YUV444",&BGR2YUV444_pybin11,"BGR2YUV444");
    m.def("BGR2I444",&BGR2I444_pybin11,"BGR2I444");
    m.def("BGR2YUV422",&BGR2YUV422_pybin11,"BGR2YUV422");
    m.def("BGR2VYUY422",&BGR2VYUY422_pybin11,"BGR2VYUY422");
    m.def("BGR2UYVY422",&BGR2UYVY422_pybin11,"BGR2UYVY422");
    m.def("BGR2YUYV422",&BGR2YUYV422_pybin11,"BGR2I444");
    m.def("BGR2YUV420",&BGR2YUV420pybin11,"BGR2YUV420");
    m.def("BGR2NV21",&BGR2NV21_pybin11,"BGR2NV21");
    m.def("BGR2NV12",&BGR2NV12_pybin11,"BGR2NV12");
    m.def("BGR2Y8",&BGR2Y8_pybin11,"BGR2Y8");

    m.def("NV212BGR",&NV212BGR_pybin11,"NV212BGR");
    m.def("NV122BGR",&NV122BGR_pybin11,"NV122BGR");
    m.def("YUV4442BGR",&YUV4442BGR_pybin11,"YUV4442BGR");
    m.def("YUV4202BGR",&YUV4202BGR_pybin11,"YUV4202BGR");
    m.def("NV122I444",&NV122I444_pybin11,"NV122I444");
    m.def("NV212I444",&NV212I444_pybin11,"NV212I444");
    m.def("UYVY2I444",&UYVY2I444_pybin11,"UYVY2I444");
}
