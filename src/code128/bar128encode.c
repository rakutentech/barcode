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
 
 #include "bar128encode.h"

static const unsigned int BAR128_PATTERNS[][7] = {
        {2, 1, 2, 2, 2, 2}, {2, 2, 2, 1, 2, 2}, {2, 2, 2, 2, 2, 1}, {1, 2, 1, 2, 2, 3},
        {1, 2, 1, 3, 2, 2}, {1, 3, 1, 2, 2, 2}, {1, 2, 2, 2, 1, 3}, {1, 2, 2, 3, 1, 2},
        {1, 3, 2, 2, 1, 2}, {2, 2, 1, 2, 1, 3}, {2, 2, 1, 3, 1, 2}, {2, 3, 1, 2, 1, 2},
        {1, 1, 2, 2, 3, 2}, {1, 2, 2, 1, 3, 2}, {1, 2, 2, 2, 3, 1}, {1, 1, 3, 2, 2, 2},
        {1, 2, 3, 1, 2, 2}, {1, 2, 3, 2, 2, 1}, {2, 2, 3, 2, 1, 1}, {2, 2, 1, 1, 3, 2},
        {2, 2, 1, 2, 3, 1}, {2, 1, 3, 2, 1, 2}, {2, 2, 3, 1, 1, 2}, {3, 1, 2, 1, 3, 1},
        {3, 1, 1, 2, 2, 2}, {3, 2, 1, 1, 2, 2}, {3, 2, 1, 2, 2, 1}, {3, 1, 2, 2, 1, 2},
        {3, 2, 2, 1, 1, 2}, {3, 2, 2, 2, 1, 1}, {2, 1, 2, 1, 2, 3}, {2, 1, 2, 3, 2, 1},
        {2, 3, 2, 1, 2, 1}, {1, 1, 1, 3, 2, 3}, {1, 3, 1, 1, 2, 3}, {1, 3, 1, 3, 2, 1},
        {1, 1, 2, 3, 1, 3}, {1, 3, 2, 1, 1, 3}, {1, 3, 2, 3, 1, 1}, {2, 1, 1, 3, 1, 3},
        {2, 3, 1, 1, 1, 3}, {2, 3, 1, 3, 1, 1}, {1, 1, 2, 1, 3, 3}, {1, 1, 2, 3, 3, 1},
        {1, 3, 2, 1, 3, 1}, {1, 1, 3, 1, 2, 3}, {1, 1, 3, 3, 2, 1}, {1, 3, 3, 1, 2, 1},
        {3, 1, 3, 1, 2, 1}, {2, 1, 1, 3, 3, 1}, {2, 3, 1, 1, 3, 1}, {2, 1, 3, 1, 1, 3},
        {2, 1, 3, 3, 1, 1}, {2, 1, 3, 1, 3, 1}, {3, 1, 1, 1, 2, 3}, {3, 1, 1, 3, 2, 1},
        {3, 3, 1, 1, 2, 1}, {3, 1, 2, 1, 1, 3}, {3, 1, 2, 3, 1, 1}, {3, 3, 2, 1, 1, 1},
        {3, 1, 4, 1, 1, 1}, {2, 2, 1, 4, 1, 1}, {4, 3, 1, 1, 1, 1}, {1, 1, 1, 2, 2, 4},
        {1, 1, 1, 4, 2, 2}, {1, 2, 1, 1, 2, 4}, {1, 2, 1, 4, 2, 1}, {1, 4, 1, 1, 2, 2},
        {1, 4, 1, 2, 2, 1}, {1, 1, 2, 2, 1, 4}, {1, 1, 2, 4, 1, 2}, {1, 2, 2, 1, 1, 4},
        {1, 2, 2, 4, 1, 1}, {1, 4, 2, 1, 1, 2}, {1, 4, 2, 2, 1, 1}, {2, 4, 1, 2, 1, 1},
        {2, 2, 1, 1, 1, 4}, {4, 1, 3, 1, 1, 1}, {2, 4, 1, 1, 1, 2}, {1, 3, 4, 1, 1, 1},
        {1, 1, 1, 2, 4, 2}, {1, 2, 1, 1, 4, 2}, {1, 2, 1, 2, 4, 1}, {1, 1, 4, 2, 1, 2},
        {1, 2, 4, 1, 1, 2}, {1, 2, 4, 2, 1, 1}, {4, 1, 1, 2, 1, 2}, {4, 2, 1, 1, 1, 2},
        {4, 2, 1, 2, 1, 1}, {2, 1, 2, 1, 4, 1}, {2, 1, 4, 1, 2, 1}, {4, 1, 2, 1, 2, 1},
        {1, 1, 1, 1, 4, 3}, {1, 1, 1, 3, 4, 1}, {1, 3, 1, 1, 4, 1}, {1, 1, 4, 1, 1, 3},
        {1, 1, 4, 3, 1, 1}, {4, 1, 1, 1, 1, 3}, {4, 1, 1, 3, 1, 1}, {1, 1, 3, 1, 4, 1},
        {1, 1, 4, 1, 3, 1}, {3, 1, 1, 1, 4, 1}, {4, 1, 1, 1, 3, 1}, {2, 1, 1, 4, 1, 2},
        {2, 1, 1, 2, 1, 4}, {2, 1, 1, 2, 3, 2}, {2, 3, 3, 1, 1, 1, 2}
};

static const unsigned int BAR128_PATTERN_FNC_1     = 102; // Code B
static const unsigned int BAR128_PATTERN_FNC_3     = 96;  // Code B
static const unsigned int BAR128_PATTERN_FNC_2     = 97;  // Code B
static const unsigned int BAR128_PATTERN_FNC_4     = 100; // Code B
static const unsigned int BAR128_PATTERN_START_B   = 104;
static const unsigned int BAR128_PATTERN_START_C   = 105;
static const unsigned int BAR128_PATTERN_SWITCH_B  = 100; // Switch from Code C to Code B
static const unsigned int BAR128_PATTERN_SWITCH_C  = 99;  // Switch from Code B to Code C
static const unsigned int BAR128_PATTERN_STOP      = 106;

static const char BAR128_CHAR_FNC_1 = '\xf1';
static const char BAR128_CHAR_FNC_2 = '\xf2';
static const char BAR128_CHAR_FNC_3 = '\xf3';
static const char BAR128_CHAR_FNC_4 = '\xf4';
static const char BAR128_CHAR_SPACE = '\x20';
static const char BAR128_CHAR_ZERO  = '\x30';
static const char BAR128_CHAR_NINE  = '\x39';
static const char BAR128_CHAR_TILDE = '\x7e';

static inline int findCType(const char *ptr) {
    char c = ptr[0];

    if (c == BAR128_CHAR_FNC_1) return 0;
    else if (c < BAR128_CHAR_ZERO || c > BAR128_CHAR_NINE) return -1;

    c = ptr[1];
    return (c < BAR128_CHAR_ZERO || c > BAR128_CHAR_NINE) ? 1 : 2;
}

static inline unsigned int chooseCode(const char *ptr, unsigned int oldCode) {
    int lookahead = findCType(ptr);
    if (lookahead == -1 || lookahead == 1) return BAR128_PATTERN_SWITCH_B;
    if (oldCode == BAR128_PATTERN_SWITCH_C) return oldCode;
    if (oldCode == BAR128_PATTERN_SWITCH_B) {
        if (lookahead == 0) return oldCode;

        lookahead = findCType(ptr + 2);
        if (lookahead == -1 || lookahead == 1) return oldCode;
        if (lookahead == 0) return findCType(ptr + 3) == 2 ? BAR128_PATTERN_SWITCH_C : BAR128_PATTERN_SWITCH_B;

        unsigned int index = 4;
        while ((lookahead = findCType(ptr + index)) == 2) index += 2;

        return lookahead == 1 ? BAR128_PATTERN_SWITCH_B : BAR128_PATTERN_SWITCH_C;
    }
    if (lookahead == 0) lookahead = findCType(ptr + 1);
    return lookahead == 2 ? BAR128_PATTERN_SWITCH_C : BAR128_PATTERN_SWITCH_B;
}

static inline unsigned int write(unsigned int pattern, char *dst, unsigned int dst_offset, unsigned int dst_size) {
    unsigned int patternSize = pattern == BAR128_PATTERN_STOP ? 7 : 6;
    if (dst_offset + patternSize < dst_size) {
        for (unsigned int i = 0; i < patternSize; ++i) {
            dst[dst_offset + i] = (char) BAR128_PATTERNS[pattern][i];
        }
        return patternSize;
    }
    return 0;
}

/**
 *  Encode a null-terminated ASCII string into a Code 128 one-dimensional barcode.
 *
 *  @param  src       Pointer to the string to encode. While no size limit is enforced, keep in mind that
 *                    barcodes that are too dense or too wide may require a high-resolution, wide-angle scanner
 *                    and not work with common, cheaper hardware. For those, a good limit is probably around 48.
 *
 *  @param  dst       Pointer to the destination buffer.
 *
 *  @param  dst_size  Size, in bytes, of the destination buffer. A safe, recommended size is 1024 bytes.
 *
 *  @return           Returns code's total visual width in dots. `0` indicates that an error occurred.
 */
unsigned int bar128encode(const char *src, char *dst, unsigned int dst_size) {
    if (!src || !dst) return 0;

    const char *start = src;
    while (*src) {
        char c = *src++;
        if ((c < BAR128_CHAR_SPACE || c > BAR128_CHAR_TILDE) && (c < BAR128_CHAR_FNC_1 || c > BAR128_CHAR_FNC_4))
            return 0;
    }
    if (src == start) return 0; // empty src

    src = start;

    unsigned int dst_offset = 0, written;

    unsigned int checkSum = 0, checkWeight = 1, codeSet = 0;
    while (*src) {
        unsigned int patternIndex, newCodeSet = chooseCode(src, codeSet);

        if (newCodeSet == codeSet) {
            char c = *src;

            switch (c) {
                case BAR128_CHAR_FNC_1: patternIndex = BAR128_PATTERN_FNC_1; break;
                case BAR128_CHAR_FNC_2: patternIndex = BAR128_PATTERN_FNC_2; break;
                case BAR128_CHAR_FNC_3: patternIndex = BAR128_PATTERN_FNC_3; break;
                case BAR128_CHAR_FNC_4: patternIndex = BAR128_PATTERN_FNC_4; break;
                default:
                    if (codeSet == BAR128_PATTERN_SWITCH_B) patternIndex = (unsigned int)(c - BAR128_CHAR_SPACE);
                    else {
                        patternIndex = (unsigned int)((src[0] - BAR128_CHAR_ZERO) * 10 + (src[1] - BAR128_CHAR_ZERO));
                        ++src;
                    }
            }
            ++src;
        } else {
            patternIndex = codeSet ? newCodeSet : (newCodeSet == BAR128_PATTERN_SWITCH_B ? BAR128_PATTERN_START_B : BAR128_PATTERN_START_C);
            codeSet = newCodeSet;
        }

        // Copy the pattern into place
        written = write(patternIndex, dst, dst_offset, dst_size);
        if (!written) return 0;
        dst_offset += written;

        // Compute checksum
        checkSum += patternIndex * checkWeight;
        if (src != start) ++checkWeight;
    }

    checkSum %= 103;

    written = write(checkSum, dst, dst_offset, dst_size);
    if (!written) return 0;
    dst_offset += written;

    written = write(BAR128_PATTERN_STOP, dst, dst_offset, dst_size);
    if (!written) return 0;
    dst_offset += written;

    dst[dst_offset] = 0;

    /* -7 and +13 means we are excluding the last pattern from equation and then adding it
     * since it contains 7 values with sum of 13
     */
    return ((dst_offset - 7) * 11) / 6 + 13;
}
