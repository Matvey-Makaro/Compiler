#include "lexical_analyzer.h"
#include "syntax_analyzer.h"
#include "listing_generator.h"
#include "exceptions/exceptions.h"
#include "elf_file_generator.h"

#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

int main(int argc, char* argv[])
{
    if(argc < 3)
    {
        cerr << "Few arguments. The names of the input and output files were expected." << endl;
        return 1;
    }

    const char* const input_file_name = argv[1];
    const char* const output_file_name = argv[2];

    FILE* f = fopen(output_file_name, "wb");
    if(!f)
    {
        cerr << "File \"" << output_file_name <<"\" doesn't open!" << endl;
        return 2;
    }


    ElfFileGenerator elf_file_generator;
    elf_file_generator.generate(f);

    std::fstream fs(input_file_name);
    if (!fs.is_open())
    {
        cerr << "File \"" << input_file_name << "\" doesn't open." << endl;
        return 3;
    }

    LexicalAnalyzer lexical_analyzer;
    lexical_analyzer.split(fs);
    const auto& text = lexical_analyzer.get_text();
#if 0
    cout << "Text: " << endl;
    for (const auto& str : text)
    {
        for (const auto& word : str)
            cout << word << ' ';
        cout << '\n';
    }
#endif

    lexical_analyzer.parse();
    const auto& table = lexical_analyzer.get_lexical_table();
#if 0
    cout << "\nTable:\n";
    for (const auto& line : table)
    {
        for (const auto el : line)
            cout << static_cast<int>(el) << ' ';
        cout << '\n';
    }
#endif
    lexical_analyzer.analyze();

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