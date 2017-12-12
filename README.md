This is a small, memory-efficient and fast library for generating and rendering
1D/2D barcodes on Android and iOS/watchOS, with built-in support for
one-dimensional Code 128B/C barcodes.

New types of 1D/2D barcodes can be added without changing the library's high-level
interface.

The iOS/watchOS version uses CoreGraphics for drawing on a user-supplied CGContext,
while the Android version gives access to the shape's Paint object. This allows
client code to implement advanced effects such as masks, round line joints,
gradients, etc.

Pull requests are welcome, especially those adding support for new
barcode types!
