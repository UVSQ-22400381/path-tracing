#!/bin/sh

BUILD_DIR="${1:-build}"

cmake --build "$BUILD_DIR" --target run_test
