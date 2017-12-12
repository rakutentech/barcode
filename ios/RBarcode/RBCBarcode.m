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

@implementation RBCBarcode
- (instancetype)init
{
    return self = [self initWithMinimumSize:CGSizeZero];
}

- (instancetype)initWithMinimumSize:(CGSize)minimumSize
{
    if ((self = [super init]))
    {
        _minimumSize = minimumSize;
    }
    return self;
}

- (void)drawInRect:(CGRect __unused)rect context:(CGContextRef __unused)context
{
    // NO-OP
}

#pragma mark <NSCopying>
- (instancetype)copyWithZone:(NSZone *)zone
{
    typeof(self) __strong copy = [[self.class allocWithZone:zone] initWithMinimumSize:_minimumSize];
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
    return self = [self initWithMinimumSize:[coder decodeCGSizeForKey:NSStringFromSelector(@selector(minimumSize))]];
}

- (void)encodeWithCoder:(NSCoder *)coder
{
    [coder encodeCGSize:_minimumSize forKey:NSStringFromSelector(@selector(minimumSize))];
}

#pragma mark <NSObject>
- (NSUInteger)hash
{
    return @(_minimumSize.width).hash ^ @(_minimumSize.height).hash;
}

- (BOOL)isEqual:(RBCBarcode *)other
{
    if (other == self) return YES;
    if (![other isMemberOfClass:RBCBarcode.class]) return NO;
    return CGSizeEqualToSize(_minimumSize, other.minimumSize);
}
@end
