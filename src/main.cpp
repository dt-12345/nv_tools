#include "Maxwell.hpp"
#include "MaxwellAccessor.hpp"

#include <fstream>
#include <format>
#include <iostream>
#include <vector>

static constexpr std::uint32_t cNVNGpuCodeHeaderMagic = 0x12345678;

int main() {
    std::ifstream infile("samples/shader1.bin", std::ios::binary | std::ios::ate);
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

    bool shouldBreak = false;
    for (size_t i = start; i < size / 4; ++i) {
        const std::uint64_t schedFlags = data[i * 4];
        for (size_t j = 0; j < 3; ++j) {
            const std::uint64_t inst = data[i * 4 + j + 1];
            const std::uint64_t sched = schedFlags >> j * 21 & 0x1fffffull;
            const auto decoded = Maxwell::Decode(inst, sched);
            const std::uint64_t pc = i * 0x20 + j * 8 + 8 - start * 0x20;
            if (decoded.has_value()) {
                std::cout << std::format("{:#010x}: {}\n", pc, decoded->opcode);
                if (decoded->opclass == Maxwell::OpClass::EXIT) {
                    shouldBreak = true;
                    break;
                } else if (decoded->opclass == Maxwell::OpClass::TXQ) {
                    const auto accessor = Maxwell::Accessor<Maxwell::OpClass::TXQ>(inst, sched, pc);
                    std::cout << "Opcode: " << accessor.Opcode() << ", TexPhase: " << static_cast<std::uint32_t>(accessor.phase()) << "\n";
                    std::cout << "TextureID: " << accessor.tid() << ", Query: " << static_cast<int>(accessor.query()) << "\n";
                }
            } else {
                std::cout << std::format("Failed to decode instruction at {:#010x} ({:#010x} {:#010x})\n", pc, inst, sched);
            }
        }
        if (shouldBreak) {
            break;
        }
    }

    return 0;
}