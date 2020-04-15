#!/bin/bash

# https://developer.apple.com/documentation/metal/libraries/building_a_library_with_metal_s_command-line_tools

mkdir -p Resource-Intermediate-iOS

xcrun -sdk iphoneos metal -c Shaders.metal -g -MO -o Resource-Intermediate-iOS/Shaders.air
xcrun -sdk iphoneos metallib Resource-Intermediate-iOS/Shaders.air -o Resource-Intermediate-iOS/Shaders.metallib
ThirdParty/include-bin/bin64/include-bin Resource-Intermediate-iOS/Shaders.metallib > Resource-Intermediate-iOS/Shaders.metallib.h

ThirdParty/include-bin/bin64/include-bin ThirdParty/Assets/Lenna/l_hires-ASTC.pvr > Resource-Intermediate-iOS/l_hires.h