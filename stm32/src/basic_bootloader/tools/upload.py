import argparse
import struct
import time

import serial


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("firmware")
    parser.add_argument("--port", default="COM4")
    parser.add_argument("--baud", type=int, default=115200)
    args = parser.parse_args()

    with open(args.firmware, "rb") as f:
        firmware = f.read()

    size = len(firmware)

    print(f"Firmware size: {size} bytes")
    print(f"Opening {args.port} at {args.baud} baud...")

    with serial.Serial(args.port, args.baud, timeout=10) as ser:
        time.sleep(0.5)

        print("Sending size...")
        ser.write(struct.pack("<I", size))
        ser.flush()

        print("Waiting for bootloader to erase flash...")

        while True:
            line = ser.readline()

            if not line:
                raise RuntimeError("Timed out waiting for READY")

            text = line.decode(errors="replace").strip()
            print(f"Bootloader: {text}")

            if text == "READY":
                break

        print("Bootloader ready.")
        print("Sending firmware...")

        ser.write(firmware)
        ser.flush()

        print("Firmware sent.")
        print("Waiting for result...")

        while True:
            line = ser.readline()

            if not line:
                raise RuntimeError("Timed out waiting for result")

            text = line.decode(errors="replace").strip()
            print(f"Bootloader: {text}")

            if text == "OK":
                print("Firmware update successful!")
                break

            if "failed" in text.lower():
                raise RuntimeError("Firmware update failed")


if __name__ == "__main__":
    main()