Pod::Spec.new do |s|
  s.name         = 'RBarcode'
  s.version      = '0.1.3'
  s.author       = 'Rakuten'
  s.summary      = 'A super-lightweight library for generating and drawing barcodes'
  s.homepage     = 'https://github.com/rakutentech/barcode'
  s.description  = <<-DESC
                     A small, memory-efficient and fast library for generating barcodes
                     and rendering them. It uses CoreGraphics for drawing, so advanced
                     effects are possible (round line joints, colors, gradients, …).

                     Code 128B/C support is built-in, but new types of 1D or 2D codes
                     can be added without changing the library's high-level interface.

                     Pull requests are welcome, especially those adding support for new
                     barcode types!

                     This version targets iOS ≥ 8.0 or watchOS ≥ 2.0.
                   DESC
  s.license      = { :type => 'Apache License, Version 2.0',
                     :text => <<-LICENSE
                       Copyright (c) 2017 Rakuten Inc.

                       Licensed under the Apache License, Version 2.0 (the "License");
                       you may not use this file except in compliance with the License.
                       You may obtain a copy of the License at

                         http://www.apache.org/licenses/LICENSE-2.0
                       
                       Unless required by applicable law or agreed to in writing, software
                       distributed under the License is distributed on an "AS IS" BASIS,
                       WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
                       See the License for the specific language governing permissions and
                       limitations under the License.
                     LICENSE
                   }
  s.source       = { :git => 'https://github.com/rakutentech/barcode.git',
                     :tag => s.version.to_s
                   }
  s.platforms    = { :ios => '8.0', :watchos => '2.0' }
  s.requires_arc = true
  s.xcconfig     = {
    'GCC_C_LANGUAGE_STANDARD'                               => 'gnu99',
    'CLANG_ALLOW_NON_MODULAR_INCLUDES_IN_FRAMEWORK_MODULES' => 'YES',
  }
  s.weak_frameworks = [
    'Foundation',
    'CoreGraphics',
    'UIKit',
  ]

  s.subspec 'Common' do |ss|
    ss.source_files = ["ios/RBarcode/*.{h,m}"]
  end

  s.subspec 'Code128' do |ss|
    ss.dependency 'RBarcode/Common'
    ss.source_files = [
      "ios/RBarcode/Code128/*.{h,m}",
      "src/code128/*.{h,c}",
    ]
    ss.private_header_files = ["src/code128/*.h"]
  end

  s.default_subspec = 'Common'
  s.module_map = 'ios/RBarcode/RBarcode.modulemap'
end

# vim:syntax=ruby:et:sts=2:sw=2:ts=2:ff=unix:
