#pragma once

#include <elf.h>
#include <cstdio>

class ElfFileGenerator
{
public:
    ElfFileGenerator();
    void generate(FILE* file);

private:
    void init_header();
    void fill_program_header();

private:
    Elf64_Ehdr elf_header;
    Elf64_Phdr program_header;
    Elf64_Shdr segment_header;
};