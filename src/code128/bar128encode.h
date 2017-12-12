/*
 * Copyright 2017 Rakuten, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
 /**
 * @file bar128encode.h
 * Code 128 B/C barcode encoder in pure C.
 *
 * This library provides a single function for encoding barcodes: #bar128encode.
 */

#ifdef __cplusplus
    #define CODE128_EXPORT extern "C"
#else
    #define CODE128_EXPORT extern
#endif

/**
 *  Encode a null-terminated ASCII string into a Code-128 one-dimensional barcode.
 *
 *  @param  src       Pointer to the string to encode. While no size limit is enforced, keep in mind that
 *                    barcodes that are too dense or too wide may require a high-resolution, wide-angle scanner
 *                    and not work with common, cheaper hardware. For those, a good limit is probably around 48.
 *
 *                    The source string should only contain bytes in the `[32…126]` range, and optionally in the `[241…244]` range (FNC 1-4).
 *
 *  @param  dst       Pointer to the destination buffer.
 *
 *  @param  dst_size  Size, in bytes, of the destination buffer. A safe, recommended size is 1024 bytes.
 *
 *  @return           Returns code's total visual width in dots. 0 value indicates, that error occurred.
 */
CODE128_EXPORT unsigned int bar128encode(const char *src, char *dst, unsigned int dst_size);
