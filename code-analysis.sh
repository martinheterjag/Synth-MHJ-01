#! /bin/bash

# Check style
find Source/ -name '*.h' -o -name '*.cpp' | xargs clang-format --style=file:.clang-format --dry-run
if [[ ! $(find Source/ -name '*.h' -o -name '*.cpp' | xargs clang-format --style=file:.clang-format --dry-run 2>&1) ]]; then
	echo "PASS stylecheck"
else
	echo "FAIL stylecheck"
fi

# Run cppcheck
cppcheck --std=c++14 --enable=all --inline-suppr --suppress=unusedFunction:Source/Plugin* --suppress=missingIncludeSystem ./Source 2> err.txt
cat err.txt
if [ ! -s err.txt ]; then
	echo "PASS cppcheck"
else
	echo "FAIL cppcheck"
fi

