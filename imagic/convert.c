//
//  convert.c
//  imagic
//
//  Created by Romain on 06/01/2018.
//  Copyright © 2018 Romain Dubreucq. All rights reserved.
//

#include "convert.h"

#define IS_RGB(img) (img->depth == 3)
#define IS_RGBA(img) (img->depth == 4)
#define IS_GRAYSCALE(img) (img->depth == 1)
#define IS_MONO(img) (img->depth == 1)

void rgb82gray8(img_t *src, img_t *dst) {
    unsigned int len = src->width * src->height * src->depth, i = 0, j = dst->width * dst->height * dst->depth - 1;
    
    for (i = len; i--; ) {
        uint8_t r = ELT_DATA(src, uint8_t, i - 2);
        uint8_t g = ELT_DATA(src, uint8_t, i - 1);
        uint8_t b = ELT_DATA(src, uint8_t, i - 0);
        
        float p = (float)(r + g + b) / 3;
        ELT_DATA(dst, uint8_t, j) = (uint8_t)p;
        i -= 2;
        j--;
    }
}

void rgb162gray16(img_t *src, img_t *dst) {
    unsigned int len = src->width * src->height * src->depth, i = 0, j = dst->width * dst->height * dst->depth - 1;
    
    for (i = len; i--; ) {
        uint16_t r = ELT_DATA(src, uint16_t, i - 2);
        uint16_t g = ELT_DATA(src, uint16_t, i - 1);
        uint16_t b = ELT_DATA(src, uint16_t, i - 0);
        
        float p = (float)(r + g + b) / 3;
        ELT_DATA(dst, uint16_t, j) = (uint16_t)p;
        i -= 2;
        j--;
    }
}

void rgb2gray(img_t *src, img_t *dst) {
    if (!IS_RGB(src) || !IS_GRAYSCALE(dst)) {
        return;
    }
    
    void (*_rgb2gray[2]) (img_t *src, img_t *dst) = {rgb82gray8, rgb162gray16};
    _rgb2gray[src->dsize >> 1](src, dst);
}

void gray82rgb8(img_t *src, img_t *dst) {
    unsigned int len = src->width * src->height * src->depth, i = 0, j = dst->width * dst->height * dst->depth - 1;
    
    for (i = len; i--; ) {
        uint8_t p = ELT_DATA(src, uint8_t, i);
        
        ELT_DATA(dst, uint8_t, j) = p;
        ELT_DATA(dst, uint8_t, j - 1) = p;
        ELT_DATA(dst, uint8_t, j - 2) = p;
        
        j -= 3;
    }
}

void gray162rgb16(img_t *src, img_t *dst) {
    unsigned int len = src->width * src->height * src->depth, i = 0, j = dst->width * dst->height * dst->depth - 1;
    
    for (i = len; i--; ) {
        uint16_t p = ELT_DATA(src, uint8_t, i);
        
        ELT_DATA(dst, uint16_t, j) = p;
        ELT_DATA(dst, uint16_t, j - 1) = p;
        ELT_DATA(dst, uint16_t, j - 2) = p;
        
        j -= 3;
    }
}

void gray2rgb(img_t *src, img_t *dst) {
    if (!IS_GRAYSCALE(src) || !IS_RGB(dst)) {
        return;
    }
    
    void (*_gray2rgb[2]) (img_t *src, img_t *dst) = {gray82rgb8, gray162rgb16};
    _gray2rgb[src->dsize >> 1](src, dst);
}

void gray82mono8(img_t *src, img_t *dst, unsigned int threshold) {
    unsigned int len = src->width * src->height * src->depth, i = 0;
    
    for (i = len; i--; ) {
        ELT_DATA(dst, uint8_t, i) = ELT_DATA(src, uint8_t, i) > threshold;
    }
}

void gray162mono16(img_t *src, img_t *dst, unsigned int threshold) {
    unsigned int len = src->width * src->height * src->depth, i = 0;
    
    for (i = len; i--; ) {
        ELT_DATA(dst, uint16_t, i) = ELT_DATA(src, uint16_t, i) > threshold;
    }
}

void gray2mono(img_t *src, img_t *dst, unsigned int threshold) {
    if (!IS_GRAYSCALE(src) || !IS_MONO(dst)) {
        return;
    }
    
    void (*_gray2mono[2]) (img_t *src, img_t *dst, unsigned int threshold) = {gray82mono8, gray162mono16};
    _gray2mono[src->dsize >> 1](src, dst, threshold);
}

void mono82gray8(img_t *src, img_t *dst) {
    unsigned int len = src->width * src->height * src->depth, i = 0;
    
    for (i = len; i--; ) {
        ELT_DATA(dst, uint8_t, i) = (!ELT_DATA(src, uint8_t, i)) * UINT8_MAX;
    }
}

void mono162gray16(img_t *src, img_t *dst) {
    unsigned int len = src->width * src->height * src->depth, i = 0;
    
    for (i = len; i--; ) {
        ELT_DATA(dst, uint16_t, i) = (!ELT_DATA(src, uint16_t, i)) * UINT16_MAX;
    }
}

void mono2gray(img_t *src, img_t *dst) {
    if (!IS_MONO(src) || !IS_GRAYSCALE(dst)) {
        return;
    }
    
    void (*_mono2gray[2]) (img_t *src, img_t *dst) = {mono82gray8, mono162gray16};
    _mono2gray[src->dsize >> 1](src, dst);
}

void rgb82rgba8(img_t *src, img_t *dst, float alpha) {
    
}

void rgb162rgba16(img_t *src, img_t *dst, float alpha) {
    
}