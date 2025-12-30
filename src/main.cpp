#include "Maxwell.hpp"
#include "MaxwellAccessor.hpp"
#include "MaxwellPrint.hpp"

#include <fstream>
#include <format>
#include <iostream>
#include <vector>

static constexpr std::uint32_t cNVNGpuCodeHeaderMagic = 0x12345678;

int main(int argc, const char* argv[]) {
    const char* path = "samples/output_code_only.bin";
    if (argc > 1) {
        path = argv[1];
    }
    std::ifstream infile(path, std::ios::binary | std::ios::ate);
    std::size_t size = infile.tellg() >> 3;
    std::vector<std::uint64_t> data(size);
    infile.seekg(0);
    infile.read(reinterpret_cast<char*>(data.data()), size << 3);

    if (size < 1) {
        std::cout << "Empty shader!\n";
        return 1;
    }

    size_t start = 0;
    if ((data[0] & 0xffffffffu) == cNVNGpuCodeHeaderMagic) {
        if (size < 0x11) {
            std::cout << "File is too small to be a valid shader!\n";
            return 1;
        }
        start = 4;
    }

    for (size_t i = start; i < size / 4; ++i) {
        const std::uint64_t schedFlags = data[i * 4];
        for (size_t j = 0; j < 3; ++j) {
            const std::uint64_t inst = data[i * 4 + j + 1];
            const std::uint64_t sched = schedFlags >> j * 21 & 0x1fffffull;
            const auto decoded = Maxwell::Decode(inst, sched);
            const std::uint64_t pc = i * 0x20 + j * 8 + 8 - start * 0x20;
            if (decoded.has_value()) {
                std::cout << std::format("{:#010x} [{:#018x}, {:#010x}]: {}\n", pc, inst, sched, Maxwell::Print(decoded->opclass, decoded->opcode, inst, sched, pc));
            } else {
                std::cout << std::format("{:#010x} [{:#018x}, {:#010x}]: Failed to decode instruction\n", pc, inst, sched);
            }
        }
    }

    return 0;
}