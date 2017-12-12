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

#import <RBarcode/RBCDefines.h>
#import <RBarcode/RBCBarcode.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * A concrete subclass of RBCBarcode that can draw [Code 128 B/C](https://en.wikipedia.org/wiki/Code_128) barcodes.
 * @attention This class is opt-in. For it to become available, you MUST request the `Code128` subspec
 *            of the library by adding this to your `Podfile`:
 *            @code{.rb}
 *            pod 'RBarcode', :subspecs => ['Code128']
 *            @endcode
 *
 * @class RBCCode128Barcode RBCCode128Barcode.h <RBarcode/RBarcode.h>
 * @ingroup Code128
 */
@interface RBCCode128Barcode : RBCBarcode
/**
 * The original payload used to create this barcode.
 */
@property (nonatomic, readonly, copy) NSString *payload;

/**
 * Designated initializer.
 *
 * @param payload A string to encode. Only code points in the `[32…126]` range (ASCII minus control characters)
 *                can be encoded, along with special characters in the `[241…244]` range (FNC 1-4).
 * @return An initialized instance.
 */
- (instancetype)initWithPayload:(NSString *)payload NS_DESIGNATED_INITIALIZER;
@end

NS_ASSUME_NONNULL_END
