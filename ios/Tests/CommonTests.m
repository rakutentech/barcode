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
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKit.h>

@interface CommonTests : XCTestCase
@end

@implementation CommonTests
- (void)testDefaultBarcodeHasEmptySize
{
    RBCBarcode *barcode = RBCBarcode.new;
    XCTAssertNotNil(barcode);
    XCTAssertEqual(barcode.minimumSize.width,  0);
    XCTAssertEqual(barcode.minimumSize.height, 0);
}

- (void)testCopyWorks
{
    RBCBarcode *barcode = [RBCBarcode.alloc initWithMinimumSize:CGSizeMake(4, 3)];
    XCTAssertNotNil(barcode);

    RBCBarcode *copy = barcode.copy;
    XCTAssertNotNil(copy);
    XCTAssertNotEqual(copy, barcode);
    XCTAssertEqualObjects(copy, barcode);
}

- (void)testArchiveWorks
{
    CGSize size = CGSizeMake(4, 3);
    RBCBarcode *barcode = [RBCBarcode.alloc initWithMinimumSize:size];
    XCTAssertNotNil(barcode);

    NSData *archive = [NSKeyedArchiver archivedDataWithRootObject:barcode];
    XCTAssertNotNil(archive);

    barcode = [NSKeyedUnarchiver unarchiveObjectWithData:archive];
    XCTAssertNotNil(barcode);
    XCTAssertEqual(barcode.minimumSize.width,  size.width);
    XCTAssertEqual(barcode.minimumSize.height, size.height);
}
@end
