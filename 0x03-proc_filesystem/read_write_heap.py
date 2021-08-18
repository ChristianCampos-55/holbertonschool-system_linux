#!/usr/bin/python3
"""Finds and changes a string in mem file"""

from sys import argv


def parse_maps_file(pid):
    """sets /maps file into heap"""
    h_start = None
    h_stop = None
    try:
        with open("/proc/{:d}/maps".format(pid), "r") as f:
            for l in f:
                if l.endswith("[heap]\n"):
                    h_start, h_stop = \
                        [int(x, 16) for x in l.split(" ")[0].split("-")]
    except Exception as a:
        print(a) or exit(1)
    if not h_start or not h_stop:
        print("[ERROR] Heap address not found.") or exit(1)
    print("[*] Heap starts at {:02X}".format(h_start))
    return h_start, h_stop


def update_mem_file(pid, search_string, replace_string, h_start, h_stop):
    """finds string in /mem file changes it"""
    try:
        with open("/proc/{:d}/mem".format(pid), "r+b") as fi:
            fi.seek(h_start)
            data = fi.read(h_stop - h_start)
            print("[*] Read {:d} bytes".format(h_stop - h_start))
            str = data.find(search_string.encode())
            if str > -1:
                print("[*] String found at {:02X}"
                      .format(h_start + str))
                fi.seek(h_start + str)
                w = fi.write(replace_string.encode() + b'\x00')
                print("[*] {:d} bytes written!".format(w))
            else:
                print(
                    "[ERROR] String '{:s}' not found in heap."
                    .format(search_string))
                exit(1)
    except Exception as a:
        print(a) or exit(1)

if __name__ == "__main__":
    if len(argv) < 4 or len(argv[2]) < len(argv[3]):
        exit(1)
    h_start, h_stop = parse_maps_file(int(argv[1]))
    update_mem_file(int(argv[1]), argv[2], argv[3], h_start, h_stop)
