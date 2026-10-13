#!/bin/sh

set -eu

cd "$(dirname "$0")"

if ! command -v make >/dev/null 2>&1; then
    echo "Error: make is required. Install Xcode Command Line Tools and try again." >&2
    exit 1
fi

make build
exec ./banking
