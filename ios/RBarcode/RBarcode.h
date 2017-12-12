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
 * @defgroup Common Common
 * APIs provided by the default subspec.
 */
#import <RBarcode/RBCDefines.h>
#import <RBarcode/RBCBarcode.h>

#if DOXYGEN || __has_include(<RBarcode/RBCCode128Barcode.h>)
/**
 * @defgroup Code128 Code128
 * APIs provided by the `Code128` subspec.
 *
 * For this to become available, you MUST request the `Code128` subspec of the library by adding this to your Podfile:
 * @code{.rb}
 * pod 'RBarcode', :subspecs => ['Code128']
 * @endcode
 */
#import <RBarcode/RBCCode128Barcode.h>
#endif
