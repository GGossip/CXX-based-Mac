#!/bin/bash

# https://developer.apple.com/documentation/metal/libraries/building_a_library_with_metal_s_command-line_tools

mkdir -p Resource-Intermediate-macOS

xcrun -sdk macosx metal -c Shaders.metal -g -MO -o Resource-Intermediate-macOS/Shaders.air
xcrun -sdk macosx metallib Resource-Intermediate-macOS/Shaders.air -o Resource-Intermediate-macOS/Shaders.metallib
ThirdParty/include-bin/bin64/include-bin Resource-Intermediate-macOS/Shaders.metallib > Resource-Intermediate-macOS/Shaders.metallib.h

ThirdParty/include-bin/bin64/include-bin ThirdParty/Assets/Lenna/lena_std-DirectXTex.dds > Resource-Intermediate-macOS/l_hires.h