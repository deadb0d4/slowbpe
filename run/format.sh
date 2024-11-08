set -ex

find . -type f | \
    grep -e "\.cpp$" -e "\.h$" | \
    grep -v "./cmake-deps" | \
    grep -v "./build" | \
    xargs -L 1 clang-format -i --verbose
