#!/usr/bin/env python3
"""Host-side raw HID probe for the Keychron V10 Max custom firmware (dump_a.bin).

NOT executed by the analysis agent (rule: never touch USB/HID). Run it yourself:
    uv run --with hidapi python3 tools/rawhid_probe.py

Background (custom_code/rawhid_misc.md): the firmware's raw_hid_receive (0x0800C908) only
forwards data[0] in {0xAA, 0xAB}. 0xA0..0xA3 and VIA 0x01.. are dropped silently, so a
0xAB factory-test command is the only thing the board will ever answer. If these probes
answer, the earlier 0xA0/0xA1/0x01 timeouts are explained by the firmware, not the host.
"""
import sys
import time

try:
    import hid  # hidapi
except ImportError:
    sys.exit("pip/uv install hidapi (module name 'hid')")

VID, PID = 0x3434, 0x09A0
USAGE_PAGE, USAGE = 0xFF60, 0x61
RAW_EPSIZE = 32


def factory_test_packet(sub, payload=b""):
    buf = bytearray(RAW_EPSIZE)
    buf[0] = 0xAB
    buf[1] = sub
    buf[2:2 + len(payload)] = payload
    s = sum(buf[1:RAW_EPSIZE - 3]) & 0xFFFF  # bytes 1..28, as factory_test_rx does
    buf[RAW_EPSIZE - 2] = s & 0xFF
    buf[RAW_EPSIZE - 1] = s >> 8
    return bytes(buf)


def open_raw_interface():
    for d in hid.enumerate(VID, PID):
        if d.get("usage_page") == USAGE_PAGE and d.get("usage") == USAGE:
            h = hid.device()
            h.open_path(d["path"])
            return h, d["path"]
    sys.exit("RAW interface (usage page 0xFF60 / usage 0x61) not found; is the switch on Cable?")


def xfer(h, pkt, label):
    # hidapi wants a leading report-id byte (0x00 = no report id) -> 33 bytes on macOS/Windows.
    n = h.write(b"\x00" + pkt)
    print(f"[{label}] wrote {n} bytes: {pkt.hex(' ')}")
    rsp = h.read(RAW_EPSIZE, timeout_ms=1000)
    if not rsp:
        print(f"[{label}] no reply within 1 s")
        return None
    rsp = bytes(rsp)
    printable = "".join(chr(b) if 32 <= b < 127 else "." for b in rsp)
    print(f"[{label}] reply {len(rsp)} bytes: {rsp.hex(' ')}\n         ascii: {printable}")
    return rsp


def main():
    h, path = open_raw_interface()
    print("opened", path)
    h.set_nonblocking(0)
    try:
        # These must answer on this firmware:
        xfer(h, factory_test_packet(0x08), "0xAB 0x08 GET_BUILD_TIME  (expect 'v1.0.0 2024-07-09-13:57:36')")
        time.sleep(0.1)
        xfer(h, factory_test_packet(0x09), "0xAB 0x09 GET_DEVICE_ID   (expect 0xAB 0x09 0x0C + 12 UID bytes)")
        time.sleep(0.1)
        xfer(h, factory_test_packet(0x05), "0xAB 0x05 GET_TRANSPORT   (expect 0xAB 0x05 <transport> <B0>)")
        time.sleep(0.1)
        # These are expected to time out on this firmware (dropped by raw_hid_receive):
        pkt = bytes([0xA0]) + bytes(RAW_EPSIZE - 1)
        xfer(h, pkt, "0xA0 kc_get_protocol_version (expect NO reply on this build)")
        pkt = bytes([0x01]) + bytes(RAW_EPSIZE - 1)
        xfer(h, pkt, "0x01 VIA get_protocol_version (expect NO reply on this build)")
    finally:
        h.close()


if __name__ == "__main__":
    main()
