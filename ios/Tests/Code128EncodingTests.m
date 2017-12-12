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

#import <XCTest/XCTest.h>
#import <RBarcode/RBarcode.h>
#import "../../src/code128/bar128encode.h"

static const unsigned int kBufferSize = 1024;

@interface Code128EncodingTests : XCTestCase {
    char _buffer[kBufferSize];
}
@end

@implementation Code128EncodingTests

- (void)commonTestEncodingWithPayload:(NSString *)payload
                             patterns:(const char*)patterns
                                count:(NSUInteger)count
{
    unsigned int dotWidth = bar128encode([payload cStringUsingEncoding:NSISOLatin1StringEncoding], _buffer, kBufferSize);
    XCTAssertNotEqual(dotWidth, 0u);

    unsigned int encodedLength = (unsigned int) strlen(_buffer);
    XCTAssertNotEqual(encodedLength, 0u);
    XCTAssertEqual(encodedLength, count);

    unsigned int expectedDotWidth = 0u;
    for (int index = 0; index < (int) count; ++index)
    {
        expectedDotWidth += (unsigned int) patterns[index];
        XCTAssertEqual(_buffer[index], patterns[index]);
    }
    XCTAssertEqual(dotWidth, expectedDotWidth);
}

- (void)testEmptyEncoding
{
    unsigned int dotWidth = bar128encode("", _buffer, kBufferSize);
    XCTAssertEqual(dotWidth, 0u);
}

- (void)testREncoding
{
    const char patterns[] = {2,1,1,2,1,4,2,3,1,1,3,1,2,1,3,1,1,3,2,3,3,1,1,1,2};
    [self commonTestEncodingWithPayload:@"R" patterns:patterns count:sizeof(patterns)];
}

- (void)test20Encoding
{
    const char patterns[] = {2,1,1,2,3,2,2,2,1,2,3,1,2,2,3,1,1,2,2,3,3,1,1,1,2};
    [self commonTestEncodingWithPayload:@"20" patterns:patterns count:sizeof(patterns)];
}

- (void)test20REncoding
{
    const char patterns[] = {2,1,1,2,3,2,2,2,1,2,3,1,1,1,4,1,3,1,2,3,1,1,3,1,1,1,1,2,2,4,2,3,3,1,1,1,2};
    [self commonTestEncodingWithPayload:@"20R" patterns:patterns count:sizeof(patterns)];
}

- (void)testR20Encoding
{
    const char patterns[] = {2,1,1,2,1,4,2,3,1,1,3,1,2,2,3,2,1,1,1,2,3,1,2,2,2,3,2,1,2,1,2,3,3,1,1,1,2};
    [self commonTestEncodingWithPayload:@"R20" patterns:patterns count:sizeof(patterns)];
}

- (void)testSimpleGS1Encoding
{
    // Just a serial shipping container code, [FNC1] 00 12345678 0000000001
    const char patterns[] = {2,1,1,2,3,2,4,1,1,1,3,1,2,1,2,2,2,2,1,1,2,2,3,2,1,3,1,1,2,3,3,3,1,1,2,1,2,4,1,1,1,2,2,1,2,2,2,2,2,1,2,2,2,2,2,1,2,2,2,2,2,1,2,2,2,2,2,2,2,1,2,2,1,3,1,2,2,2,2,3,3,1,1,1,2};
    NSString *fnc1 = [NSString stringWithCString:"\xf1" encoding:NSISOLatin1StringEncoding];
    [self commonTestEncodingWithPayload:[fnc1 stringByAppendingString:@"00123456780000000001"] patterns:patterns count:sizeof(patterns)];
}

- (void)testComplexGS1Encoding
{
    // Serial number, production date and expiration date, [FNC1] 21 12345 [FNC1] 11 090101 17 100101
    const char patterns[] = {2,1,1,2,3,2,4,1,1,1,3,1,2,1,3,2,1,2,1,1,2,2,3,2,1,3,1,1,2,3,1,1,4,1,3,1,2,1,3,2,1,2,4,1,1,1,3,1,1,1,3,1,4,1,2,3,1,2,1,2,2,2,1,2,1,3,2,2,2,1,2,2,2,2,2,1,2,2,1,2,3,2,2,1,2,2,1,3,1,2,2,2,2,1,2,2,2,2,2,1,2,2,1,4,1,1,2,2,2,3,3,1,1,1,2};
    NSString *fnc1 = [NSString stringWithCString:"\xf1" encoding:NSISOLatin1StringEncoding];
    [self commonTestEncodingWithPayload:[NSString stringWithFormat:@"%1$@2112345%1$@1109010117100101", fnc1] patterns:patterns count:sizeof(patterns)];
}

- (void)testComplexGS1CompactEncoding
{
    // Same data as above, but re-ordered to make it more compact: [FNC1] 11 090101 17 100101 21 12345
    const char patterns[] = {2,1,1,2,3,2,4,1,1,1,3,1,2,3,1,2,1,2,2,2,1,2,1,3,2,2,2,1,2,2,2,2,2,1,2,2,1,2,3,2,2,1,2,2,1,3,1,2,2,2,2,1,2,2,2,2,2,1,2,2,2,1,3,2,1,2,1,1,2,2,3,2,1,3,1,1,2,3,1,1,4,1,3,1,2,1,3,2,1,2,1,2,3,2,2,1,2,3,3,1,1,1,2};
    NSString *fnc1 = [NSString stringWithCString:"\xf1" encoding:NSISOLatin1StringEncoding];
    [self commonTestEncodingWithPayload:[fnc1 stringByAppendingString:@"11090101171001012112345"] patterns:patterns count:sizeof(patterns)];
}
@end
