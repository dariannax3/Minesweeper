#!/bin/bash
STYLE=file

OPTIONS="-i"
clang-format-11 $OPTIONS inc/*.hpp -style=$STYLE
clang-format-11 $OPTIONS src/*.cpp -style=$STYLE
clang-format-11 $OPTIONS tests/*.cpp -style=$STYLE

