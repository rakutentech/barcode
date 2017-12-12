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

NS_ASSUME_NONNULL_BEGIN

/**
 * Base class for all supported barcodes.
 * @class RBCBarcode RBCBarcode.h <RBarcode/RBarcode.h>
 * @ingroup Common
 */
RBC_EXPORT @interface RBCBarcode : NSObject<NSCopying, NSSecureCoding>

/**
 * Minimum size required to render the barcode, in pixels.
 */
@property (nonatomic, readonly) CGSize minimumSize;

/**
 * Designated initializer.
 *
 * @param minimumSize The minimum size required to render the barcode, in pixels. See #minimumSize.
 * @return An initialized instance.
 */
- (instancetype)initWithMinimumSize:(CGSize)minimumSize NS_DESIGNATED_INITIALIZER;

/**
 * Draw the barcode in the given rect. This method does nothing in RBCBarcode, and must
 * be implemented by its concrete subclasses.
 *
 * @attention It is up to the caller to setup the context. An example setup is show below:
 * @code{.m}
 * // Clear the context using white color
 * CGContextSetRGBFillColor(context, 1, 1, 1, 1);
 * CGContextFillRect(context, rect);
 *
 * // Set the fill color to black, and draw the barcode
 * CGContextSetRGBFillColor(context, 0, 0, 0, 1);
 * [barcode drawInRect:rect context:context];
 * @endcode
 *
 * @param rect    The rectangle in which to draw the barcode.
 * @param context The graphic context.
 */
- (void)drawInRect:(CGRect)rect context:(CGContextRef)context;
@end

NS_ASSUME_NONNULL_END
