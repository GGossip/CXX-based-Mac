#!/bin/bash

# https://developer.apple.com/documentation/metal/libraries/building_a_library_with_metal_s_command-line_tools

xcrun -sdk macosx metal -c Shaders.metal -g -MO -o /Users/aduzha01/Library/Containers/AdunZhang.CXXBasedMac/Data/Library/Caches/Shaders_MacOS.air
xcrun -sdk macosx metallib /Users/aduzha01/Library/Containers/AdunZhang.CXXBasedMac/Data/Library/Caches/Shaders_MacOS.air -o /Users/aduzha01/Library/Containers/AdunZhang.CXXBasedMac/Data/Library/Caches/Shaders_MacOS.metallib

xcrun -sdk iphoneos metal -c Shaders.metal -g -MO -o Resource-Intermediate/Shaders.air
xcrun -sdk iphoneos metallib /Users/aduzha01/Library/Containers/AdunZhang.CXXBasedMac/Data/Library/Caches/Shaders_IOS.air -o /Users/aduzha01/Library/Containers/AdunZhang.CXXBasedMac/Data/Library/Caches/Shaders_IOS.metallib

ThirdParty/include-bin/bin64/include-bin 