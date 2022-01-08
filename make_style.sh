#!/bin/bash
STYLE=file

OPTIONS="-i"
clang-format-12 $OPTIONS inc/*.hpp -style=$STYLE
clang-format-12 $OPTIONS src/*.cpp -style=$STYLE
clang-format-12 $OPTIONS tests/*.cpp -style=$STYLE
