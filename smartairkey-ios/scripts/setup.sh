#!/usr/bin/env bash
#
# Copies the SmartAirKey binary SDK (xcframeworks) out of the official
# iOS_TestApp bundle into Vendor/SDK/, then generates the Xcode project.
#
# The binaries are intentionally not committed to git (they are large and
# distributed by SmartAirKey). Run this once after cloning.
#
# Usage:
#   scripts/setup.sh /path/to/TestAppX/TestAppX
#
# where the given directory contains the `sdk/` folder with the *.xcframework
# bundles (AirKeySmartDeviceCore, AIKAirKite, BWBluetoothWolf,
# DIDeviceInteractionLion, TCTransportCamel).

set -euo pipefail

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
SRC="${1:-}"

if [[ -z "$SRC" ]]; then
  echo "error: pass the path to the TestApp folder that contains sdk/*.xcframework" >&2
  echo "usage: scripts/setup.sh /path/to/TestAppX/TestAppX" >&2
  exit 1
fi

SDK_SRC="$SRC/sdk"
if [[ ! -d "$SDK_SRC" ]]; then
  echo "error: $SDK_SRC not found" >&2
  exit 1
fi

DEST="$HERE/Vendor/SDK"
mkdir -p "$DEST"

FRAMEWORKS=(
  AirKeySmartDeviceCore.xcframework
  AIKAirKite.xcframework
  BWBluetoothWolf.xcframework
  DIDeviceInteractionLion.xcframework
  TCTransportCamel.xcframework
)

for fw in "${FRAMEWORKS[@]}"; do
  if [[ ! -d "$SDK_SRC/$fw" ]]; then
    echo "error: missing $SDK_SRC/$fw" >&2
    exit 1
  fi
  echo "→ $fw"
  rm -rf "${DEST:?}/$fw"
  cp -R "$SDK_SRC/$fw" "$DEST/$fw"
done

echo "SDK copied to $DEST"

if command -v xcodegen >/dev/null 2>&1; then
  echo "→ xcodegen generate"
  ( cd "$HERE" && xcodegen generate )
else
  echo "note: install xcodegen (brew install xcodegen) then run 'xcodegen generate'"
fi

if command -v pod >/dev/null 2>&1; then
  echo "→ pod install"
  ( cd "$HERE" && pod install )
else
  echo "note: install CocoaPods (sudo gem install cocoapods) then run 'pod install'"
fi

echo "Done. Open SmartAirKey.xcworkspace"
