#include "elf_file_generator.h"
#include "listing_generate_helper.h"

ElfFileGenerator::ElfFileGenerator() :
        header{0}
{
    init_header();
}

void ElfFileGenerator::init_header()
{
    auto* const e_ident = header.e_ident;
    e_ident[EI_MAG0] = 0x7f;
    e_ident[EI_MAG1] = 'E';
    e_ident[EI_MAG2] = 'L';
    e_ident[EI_MAG3] = 'F';
    e_ident[EI_CLASS] = ELFCLASS64;
    e_ident[EI_DATA] = ELFDATA2LSB;
    e_ident[EI_VERSION] = EV_CURRENT;
    e_ident[EI_OSABI] = ELFOSABI_NONE;  // TODO: Here maybe a problem.
    e_ident[EI_ABIVERSION] = 0;
    e_ident[EI_PAD] = 0;
    e_ident[10] = 0;
    e_ident[11] = 0;
    e_ident[12] = 0;
    e_ident[13] = 0;
    e_ident[14] = 0;
    e_ident[15] = 0;

    header.e_type = ET_EXEC;
    header.e_machine = EM_X86_64;
    header.e_version = EV_CURRENT;
    // header.e_entry is filled later.
    // header.e_phoff is filled later.
    // header.e_shoff is filled later.
    header.e_flags = 0;
    header.e_ehsize = sizeof(Elf64_Ehdr);
    // header.e_phentsize is filled later.
    // header.e_phnum is filled later.
    // header.e_shentsize is filled later.
    // header.e_shnum is filled later.
    header.e_shstrndx = 0;

    // TODO: For test:
#if 1
    header.e_entry = 0x400078;
    header.e_phoff = 64;
    header.e_shoff = 0;
    header.e_phentsize = 56;
    header.e_phnum = 1;
    header.e_shentsize = 0;
    header.e_shnum = 0;
#endif
}

void ElfFileGenerator::generate(FILE* file)
{
    write_header(file);
}

void ElfFileGenerator::write_header(FILE *file)
{
    fwrite(header.e_ident, sizeof(header.e_ident[0]), 16, file);

    auto le_e_type = header.e_type;
    fwrite(reinterpret_cast<void*>(&le_e_type), sizeof(le_e_type), 1, file);

    auto le_e_machine = header.e_machine;
    fwrite(reinterpret_cast<void*>(&le_e_machine), sizeof(le_e_machine), 1, file);

    auto le_e_version = header.e_version;
    fwrite(reinterpret_cast<void*>(&le_e_version), sizeof(le_e_version), 1, file);

    auto le_e_entry = header.e_entry;
    fwrite(reinterpret_cast<void*>(&le_e_entry), sizeof(le_e_entry), 1, file);

    auto le_e_phoff = header.e_phoff;
    fwrite(reinterpret_cast<void*>(&le_e_phoff), sizeof(le_e_phoff), 1, file);

    auto le_e_shoff = header.e_shoff;
    fwrite(reinterpret_cast<void*>(&le_e_shoff), sizeof(le_e_shoff), 1, file);

    auto le_e_flags = header.e_flags;
    fwrite(reinterpret_cast<void*>(&le_e_flags), sizeof(le_e_flags), 1, file);

    auto le_e_ehsize = header.e_ehsize;
    fwrite(reinterpret_cast<void*>(&le_e_ehsize), sizeof(le_e_ehsize), 1, file);

    auto le_e_phentsize = header.e_phentsize;
    fwrite(reinterpret_cast<void*>(&le_e_phentsize), sizeof(le_e_phentsize), 1, file);

    auto le_e_phnum = header.e_phnum;
    fwrite(reinterpret_cast<void*>(&le_e_phnum), sizeof(le_e_phnum), 1, file);

    auto le_e_shentsize = header.e_shentsize;
    fwrite(reinterpret_cast<void*>(&le_e_shentsize), sizeof(le_e_shentsize), 1, file);

    auto le_e_shnum = header.e_shnum;
    fwrite(reinterpret_cast<void*>(&le_e_shnum), sizeof(le_e_shnum), 1, file);

    auto le_e_shstrndx = header.e_shstrndx;
    fwrite(reinterpret_cast<void*>(&le_e_shstrndx), sizeof(le_e_shstrndx), 1, file);
}
