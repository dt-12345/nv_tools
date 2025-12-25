"""
A simple script to decode + decompress file data embedded inside of nvdisasm
Extraction of the data from nvdisasm is not handled here (I extracted them with a Ghidra script but whatever works)
The values in this script are derived from CUDA Toolkit 12.9 (so no Fermi/Kepler unfortunately)
"""

import os

from pathlib import Path
from typing import Dict, List, Tuple

import lz4.block

# from nvdisasm
DECODING_TABLE = b"\x64\x80\x0d\x1e\xe2\xf6\xef\x16\x98\xff\x29\x3a\x5e\xcf\x28\xad\x84\x45\xfc\xce\x65\xab\xe3\xac\xeb\x97\x49\x92\xc3\x13\xa8\xf7\xdd\x7c\xd0\xde\xf8\x78\x72\xec\xa5\x12\x94\x2b\x39\x53\x9a\x90\x04\x3f\xae\x99\x32\x75\xbf\xc1\x02\x91\xdb\xfe\x7d\xd6\xb5\xf0\x3d\x3c\xb3\xb6\x00\xbc\x76\xa2\x9c\xe1\x50\x85\x09\x4a\x66\x2d\xb7\x6a\xd5\x79\xea\x3e\x1b\xd1\xa3\x7b\x71\x95\x59\xb2\x87\x8b\x5c\x9f\x81\x18\x27\xcb\x4b\x93\x11\x2a\x6b\xbd\xa0\xc8\xf5\x19\xf2\x1f\xc2\x40\x6c\xdf\x03\xda\x21\x55\xb1\x82\x63\x89\x77\xe6\xa9\xc9\x73\x24\xc6\xd9\xe4\x37\x17\x4f\xf4\x68\xc7\x07\x86\xaf\xfa\xa6\xb8\xdc\x88\x0a\x47\x8e\xe7\x14\x1a\x83\x74\x9e\x35\x7f\xfd\x52\xe0\xa1\x41\x4c\x0b\x33\x44\x8f\xf3\xbb\x08\x58\x7a\x0c\xf1\x3b\xe5\x9b\x26\xd4\x5d\xc0\xf9\x7e\xa7\x60\xe8\x51\x25\x34\xd7\x0f\x4d\x5a\xd3\x36\x1d\xc4\x8a\x2f\x20\x62\xb0\xaa\x61\x8d\x8c\x69\x01\x48\x38\xed\xd8\x6e\x42\xcc\x05\x2e\x22\x10\x5b\x06\x4e\x23\x46\x0e\xba\xe9\x5f\xee\xb9\xb4\x30\xa4\x54\xbe\x1c\x57\xcd\xfb\x96\x9d\x31\x67\xc5\x70\x15\x43\x6d\x56\x2c\xd2\x6f\xca"

FILE_TYPES: List[Tuple[str, str]] = [
    ( "machine_description", "md"        ),
    ( "latencies"          , "latencies" ),
    ( "patterns"           , "patterns"  )
]

ARCHITECTURES: Dict[str, int] = {
    # the architecture/processor ID values listed in the files seem to not line up with what the internet says
    "SM5"   : 0x1648,   # Maxwell
    "SM52"  : 0x6c9e,   # Maxwell
    "SM55"  : 0xc401,   # Maxwell
    "SM57"  : 0x0e44,   # Maxwell
    "SM70"  : 0x0b4a,   # Volta
    "SM72"  : 0x0b4a,   # Volta
    "SM75"  : 0x0b4a,   # Volta
    "SM80"  : 0x8416,   # Volta
    "SM86"  : 0x8416,   # Volta
    "SM89"  : 0x1684,   # Volta
    "SM90"  : 0x3927,   # Volta
    "SM100" : 0x9327,   # Volta
    "SM101" : 0x9327,   # Volta
    "SM103" : 0x9327,   # Volta
    "SM120" : 0x9327    # Volta
}


ARCHITECTURE_REMAP: Dict[int, str] = {
    # based on what the internet says
    # Maxwell
    50  : "SM5",
    52  : "SM52",
    53  : "SM52",
    # Pascal
    60  : "SM55",
    61  : "SM57",
    62  : "SM57",
    # Volta
    70  : "SM70",
    72  : "SM72",
    # Turing
    75  : "SM75",
    # Ampere
    80  : "SM80",
    86  : "SM86",
    87  : "SM86",
    # Ada
    89  : "SM89",
    # Hopper
    90  : "SM90",
    # Blackwell
    100 : "SM100",
    101 : "SM101",
    103 : "SM103",
    120 : "SM120",
    # is this also Blackwell? or maybe Ruben?
    121 : "SM120"
}

class Context:
    def __init__(self, init_state: int) -> "Context":
        self.base_state: int = init_state
        self.curr_state: int = 0
        self.curr_index: int = 1
        self.last_byte : int = ~(init_state & 0xff)

    def decode(self, data: bytes, size: int = -1) -> bytearray:
        if size == -1:
            size = len(data)
        out: bytearray = bytearray(size)
        self.curr_state &= 0xffffffff
        for i in range(size):
            self.curr_index -= 1
            if self.curr_index == 0:
                self.curr_index = 4
                self.curr_state = self.base_state * 0x41c64e6d + 0x3039
                self.base_state = self.curr_state
            else:
                self.curr_state >>= 8
            out[i] = (self.curr_state & 0xff) ^ DECODING_TABLE[data[i] ^ self.last_byte]
            self.last_byte = data[i]
        return out
    
def decode_files(arch: str, out_path: str) -> None:
    if not arch.startswith("SM") and not arch.startswith("sm"):
        print(f"Unrecognized architecture: {arch}")
        return
    if os.path.dirname(out_path) != "":
        os.makedirs(os.path.dirname(out_path), exist_ok=True)
    if arch not in ARCHITECTURES:
        ver: int
        if not arch.endswith("a"): # accelerated doesn't change the actual data files
            ver = int(arch[2:])
        else:
            ver = int(arch[2:-1])
        if ARCHITECTURE_REMAP.get(ver, "") == "":
            print(f"Unrecognized architecture: {arch}")
        else:
            arch = ARCHITECTURE_REMAP.get(ver, "")
    init_state: int = ARCHITECTURES[arch]
    for file_type in FILE_TYPES:
        print("Decoding %s for %s" % (file_type[0], arch))
        ctx: Context = Context(init_state)
        decoded: bytearray = ctx.decode(Path(os.path.join(os.path.dirname(os.path.realpath(__file__)), f"raw/{arch}/{file_type[0]}.bin")).read_bytes())
        if file_type[0] == "machine_description":
            Path(os.path.join(out_path, f"{arch}.{file_type[1]}")).write_bytes(lz4.block.decompress(decoded, uncompressed_size = 0x1000000))
        else:
            Path(os.path.join(out_path, f"{arch}.{file_type[1]}")).write_bytes(decoded)

if __name__ == "__main__":
    import sys

    out_path: str = "data"
    if len(sys.argv) > 1:
        out_path = sys.argv[1]

    # nvidia seems to have added a ton of additional whitespace to the files, maybe for obsfuscation purposes?
    for arch in ARCHITECTURES:
        decode_files(arch, out_path)