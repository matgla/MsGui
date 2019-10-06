#!/bin/sh -l

COLOR_RED=$'\e[1;31m'
COLOR_GREEN=$'\e[1;32m'
COLOR_BLUE=$'\e[1;34m'
COLOR_WHITE=$'\e[0m'

print_error()
{
  echo "$COLOR_RED ERROR: $@ $COLOR_WHITE"
  return 1
}

print_status()
{
  echo "$COLOR_BLUE STEP: $@ $COLOR_WHITE"
  return 1
}

print_success()
{
  echo "$COLOR_GREEN OK: $@ $COLOR_WHITE"
  return 1
}

print_status "Configuring workspace"
mkdir -p build
[ $? -eq 0 ] || print_error "Configuration of workspace failed!" || exit $?;
cd build
print_status "Configuring project"
cmake .. -DBUILD_TESTS=ON
[ $? -eq 0 ] || print_error "Configuration of project failed!" || exit $?;
print_status "Build project with threads: $(nproc)"
make -j$(nproc)
[ $? -eq 0 ] || print_error "Building of project failed!" || exit $?;
print_status "Running tests"
test/UT/msgui_tests
[ $? -eq 0 ] || print_error "Tests failed!" || exit $?;

print_success "All tests succeeded!"