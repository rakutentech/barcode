@tableofcontents
@section barcode-module Introduction
This is a super-lightweight library for drawing barcodes. It currently supports [Code-128 B/C](https://en.wikipedia.org/wiki/Code_128) barcodes only, but can be extended to support other types of 1D/2D barcodes depending on demand.

@note This library requires either **iOS 8.0+** or **watchOS 2.0+**.

@section barcode-installing Installing
To use this library, your `Podfile` should contain:

@code{.rb}
source 'https://github.com/CocoaPods/Specs.git'
source 'https://gitpub.rakuten-it.com/scm/eco/core-ios-specs.git'

target 'MyApp' do
  # Request the 'Code128' subspec of the library so that you can draw Code-128 barcodes
  pod 'RBarcode', :subspecs => ['Code128']
end
@endcode

Run `pod install` to install the library.


@section barcode-tutorial Getting started
@subsection barcode-create-code128 Creating a Code-128 barcode
@attention Code-128 barcodes require the `Code128` subspec. See @ref barcode-installing "Installing" for more information.

A Code-128 barcode can be created using the following code:

@code{.m}
RBCCode128Barcode *barcode = [RBCCode128Barcode.alloc initWithPayload:@"012345678"];
@endcode

@subsection barcode-create-gs1-128 Creating a GS1-128 barcode
@attention [GS1-128](https://en.wikipedia.org/wiki/GS1-128) barcodes require the `Code128` subspec. See @ref barcode-installing "Installing" for more information.

A GS1-128 barcode is a Code-128 barcode with a `FNC 1` prefix, that adheres to a [certain format](https://en.wikipedia.org/wiki/GS1-128).

@code{.m}
/*
 * First, create the FNC-1 mark:
 */
NSString *fnc1 = [NSString stringWithCString:"\xf1" encoding:NSISOLatin1StringEncoding];

/*
 * Then, create our payload:
 *
 * - A `12345` serial number (code `21`),
 * - A `2015-12-23` production date (code `11`),
 * - A `2017-06-23` best-before date (code `15`).
 *
 * That is represented by [FNC-1] <21> <12345> [FNC-1] <11> <151223> <15> <170623>,
 * which we create below:
 */
NSString *payload = [NSString stringWithFormat:@"%1$@2112345%1$@1115122315170623", fnc1];

/*
 * Finally, we create the barcode with:
 */
RBCCode128Barcode *barcode = [RBCCode128Barcode.alloc initWithPayload:payload];
@endcode

#### Optimizing GS1-128 barcodes
Note that because the first field used in the example above has a variable length (serial numbers can have anything between
one and twenty characters), we had to use a second `FNC 1` mark as a separator. We can encode the same information in a
more compact barcode by reordering the fields so that the data becomes `[FNC-1] <11> <151223> <15> <170623> <21> <12345>`, as
shown below:

@code{.m}
NSString *payload = [fnc1 stringByAppendingString:@"11151223151706232112345"];
RBCCode128Barcode *barcode = [RBCCode128Barcode.alloc initWithPayload:payload];
@endcode

@subsection barcode-rendering Rendering a barcode
Barcodes are rendered using RBCBarcode#drawInRect:context:, as shown below:

@code{.m}
/*
 * The library assumes the context has been properly set up. Here, we
 * clear the area we want to draw to with a white backeground, then
 * set the fill color to black so that the barcode's individual bars
 * will use that color.
 */
CGContextSetRGBFillColor(context, 1, 1, 1, 1); // white, opaque
CGContextFillRect(context, rect);

CGContextSetRGBFillColor(context, 0, 0, 0, 1); // black, opaque
[barcode drawInRect:rect context:context];
@endcode

@section barcode-examples Examples
This section shows a few examples barcodes drawn by our library.

@image html 012345678.png "Code-128 type C barcode for '012345678'" width=80%

---

@image html Rakuten.png "Code-128 type B barcode for 'Rakuten'" width=80%

---

@image html GS1_00123456780000000001.png "GS1-128 barcode for a shipping container with serial number '123456780000000001'" width=80%

@section barcode-changelog Changelog

@subsection barcode-0-1-2 0.1.2 (2016-11-11)
* Fixed a rendering bug due to antialiasing being disabled.

@subsection barcode-0-1-0 0.1.0 (2016-11-07)
* Initial version.

