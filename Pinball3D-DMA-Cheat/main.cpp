#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "DMALibrary/Memory/Memory.h"

uint64_t ReadChainAddy(Memory& m, uint64_t base, const std::vector<uint64_t>& offsets)
{
	uint64_t result = m.Read<uint64_t>(base + offsets.at(0));
	for (int i = 1; i < offsets.size() - 1; i++) {
		result = m.Read<uint64_t>(result + offsets.at(i));
	}
	return result;
}

int main()
{
	if (!mem.Init("SpaceCadetPinball.exe", true, false))
	{
		printf("Failed to initilize DMA\n");
		return 1;
	}

	printf("DMA initilized\n");

	/*
	auto moduleList = mem.GetModuleList("SpaceCadetPinball.exe");

	for (auto item : moduleList)
	{
		std::cout << "[+] module: " << item << std::endl;
	}
	*/

	uintptr_t base = mem.GetBaseDaddy("SpaceCadetPinball.exe");
	printf("SpaceCadetPinball.exe base: 0x%llX\n", base);

	std::vector<uint64_t> offsets = { 0xF0BC0, 0x28, 0x4E0, 0xB8, 0x8, 0x30, 0x84 };

	auto score = mem.ReadChain(base, offsets);
	printf("current score: %d\n", (DWORD)score);
	printf("score addy: 0x%p\n", reinterpret_cast<void*>(ReadChainAddy(mem, base, offsets)));


	return 0;
}