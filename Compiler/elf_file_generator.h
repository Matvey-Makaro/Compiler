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
    void write_header(FILE* file);

private:
    Elf64_Ehdr header;
};