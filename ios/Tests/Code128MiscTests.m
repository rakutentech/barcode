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

@interface Code128MiscTests : XCTestCase
@end

@implementation Code128MiscTests

- (void)testDefaultBarcodeIsInvalid
{
    RBCBarcode *barcode = RBCCode128Barcode.new;
    XCTAssertNil(barcode);
}

- (void)testBarcodeWithNoPayloadIsInvalid
{
    RBCBarcode *barcode = [RBCCode128Barcode.alloc initWithMinimumSize:CGSizeMake(40, 30)];
    XCTAssertNil(barcode);
}

- (void)testBarcodeWithEmptyPayloadIsInvalid
{
    RBCBarcode *barcode = [RBCCode128Barcode.alloc initWithPayload:@""];
    XCTAssertNil(barcode);
}

- (void)testCopyWorks
{
    RBCBarcode *barcode = [RBCCode128Barcode.alloc initWithPayload:@"Rakuten"];
    XCTAssertNotNil(barcode);

    RBCBarcode *copy = barcode.copy;
    XCTAssertNotNil(copy);
    XCTAssertNotEqual(copy, barcode);
    XCTAssertEqualObjects(copy, barcode);
}

- (void)testArchiveWorks
{
    NSString *payload = @"Rakuten";
    RBCCode128Barcode *barcode = [RBCCode128Barcode.alloc initWithPayload:payload];
    XCTAssertNotNil(barcode);

    NSData *archive = [NSKeyedArchiver archivedDataWithRootObject:barcode];
    XCTAssertNotNil(archive);

    barcode = [NSKeyedUnarchiver unarchiveObjectWithData:archive];
    XCTAssertNotNil(barcode);
    XCTAssertEqualObjects(barcode.payload, payload);
}

@end

