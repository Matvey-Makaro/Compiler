#include "lexical_analyzer.h"
#include "syntax_analyzer.h"
#include "listing_generator.h"
#include "exceptions/exceptions.h"
#include "elf_file_generator.h"

#include <iostream>
#include <fstream>
#include <cstdio>

#include <elf.h>    // TODO: For debug, delete later.

using namespace std;

int main()
{
    FILE* f = fopen("elf_file", "wb");
    if(!f)
    {
        cerr << "Elf file doesn't open!" << endl;
        return -1;
    }

#if 0
    out << static_cast<unsigned char>(0x7f);
    out << static_cast<unsigned char>('E');
    out << static_cast<unsigned char>('L');
    out << static_cast<unsigned char>('F');
    out << 512U;
#else
    ElfFileGenerator elf_file_generator;
    elf_file_generator.generate(f);
#endif

    std::string fName = "test";
    std::fstream fs(fName);
    if (!fs.is_open())
    {
        cerr << "File \"" << fName << "\" doesn't open." << endl;
        return -1;
    }

    LexicalAnalyzer lexical_analyzer;
    lexical_analyzer.split(fs);
    const auto& text = lexical_analyzer.get_text();
    cout << "Text: " << endl;
    for (const auto& str : text)
    {
        for (const auto& word : str)
            cout << word << ' ';
        cout << '\n';
    }

    cout << "\nTable:\n";
    lexical_analyzer.parse();
    const auto& table = lexical_analyzer.get_lexical_table();
    for (const auto& line : table)
    {
        for (const auto el : line)
            cout << static_cast<int>(el) << ' ';
        cout << '\n';
    }

    SyntaxAnalyzer syntax_analyzer(table);
    try
    {
        syntax_analyzer.analyze();
    }
    catch (const std::exception& ex)
    {
        cerr << ex.what() << endl;
        return -1;
    }

    cout << "Generated text:" << endl;
    const auto& var_table = lexical_analyzer.get_var_table();
    ListingGenerator listing_generator(table, var_table, text);
    listing_generator.generate(cout);

    return 0;
}