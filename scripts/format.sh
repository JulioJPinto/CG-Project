find . -type f \( -name "*.cpp" -o -name "*.hpp" \) -exec clang-format -style=Google -i {} \;
