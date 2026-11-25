#!/usr/bin/env bash
# Build the network layer for the host and run the tests in a private network
# namespace (no access to any real network). Needs: cmake, gcc, dnsmasq, ping,
# iproute2, python3, and unprivileged user namespaces with /dev/net/tun.
#   scripts/net_host_test/run.sh [build dir]
set -euo pipefail
here="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
build="${1:-$here/build}"
"${CMAKE:-cmake}" -S "$here" -B "$build" -DCMAKE_BUILD_TYPE=Debug > /dev/null
"${CMAKE:-cmake}" --build "$build" -j "$(nproc)"
for unit in test_phy test_pic32mz; do
    echo "--- $unit"
    "$build/$unit" | sed 's/^/   /'
    [ "${PIPESTATUS[0]}" -eq 0 ] || { echo "$unit FAILED"; exit 1; }
done
exec unshare -rn python3 -I "$here/harness.py" "$build/test_net"
