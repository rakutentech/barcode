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

#import <RBarcode/RBarcode.h>
#include "bar128encode.h"

static const unsigned int kBufferSize = 1024;

@interface RBCCode128Barcode() {
    char _encoded[kBufferSize];
}
@end

@implementation RBCCode128Barcode
- (instancetype)initWithPayload:(NSString *)payload
{
    // NSISOLatin1StringEncoding is required because of FNC 1...4
    unsigned int dotWidth = bar128encode([payload cStringUsingEncoding:NSISOLatin1StringEncoding], _encoded, kBufferSize);
    if (!dotWidth)
    {
        return nil;
    }

    if ((self = [super initWithMinimumSize:CGSizeMake(dotWidth, 2)]))
    {
        _payload = payload.copy;
    }
    return self;
}

#pragma mark RBCBarcode
- (instancetype)initWithMinimumSize:(CGSize __unused)minimumSize
{
    return self = [self initWithPayload:@""];
}

- (void)drawInRect:(CGRect)rect context:(CGContextRef)context
{
    CGFloat x = rect.origin.x,
    y = rect.origin.y,
    w = rect.size.width,
    h = rect.size.height;

    CGSize min = self.minimumSize;
    if (w < min.width || h < min.height) return;

    CGFloat dot2px = w / min.width;

    BOOL positive = NO;
    char *ptr = _encoded;
    char dots;

    CGContextSaveGState(context);
    while ((dots = *ptr++))
    {
        CGFloat barWidth = dot2px * dots;
        if ((positive = !positive))
        {
            /*
             * We draw a path instead of filling a rect, so that application
             * developers can setup fancy effects such as round line joints,
             * stroke colors etc.
             */
            CGContextBeginPath(context);
            CGContextAddRect(context, CGRectMake(x, y, barWidth, h));
            CGContextClosePath(context);
            CGContextDrawPath(context, kCGPathFillStroke);
        }
        x += barWidth;
    }
    CGContextRestoreGState(context);
}

#pragma mark <NSCopying>
- (instancetype)copyWithZone:(NSZone *)zone
{
    typeof(self) __strong copy = [[self.class allocWithZone:zone] initWithPayload:_payload];
    return copy;
}

#pragma mark <NSSecureCoding>
+ (BOOL)supportsSecureCoding
{
    return YES;
}

#pragma mark <NSCoding>
- (instancetype)initWithCoder:(NSCoder *)coder
{
    return self = [self initWithPayload:(id)[coder decodeObjectOfClass:NSString.class forKey:NSStringFromSelector(@selector(payload))]];
}

- (void)encodeWithCoder:(NSCoder *)coder
{
    [coder encodeObject:_payload forKey:NSStringFromSelector(@selector(payload))];
}

#pragma mark <NSObject>
- (NSUInteger)hash
{
    return _payload.hash;
}

- (BOOL)isEqual:(RBCCode128Barcode *)other
{
    if (other == self) return YES;
    if (![other isMemberOfClass:RBCCode128Barcode.class]) return NO;
    return [_payload isEqualToString:other.payload];
}
@end
