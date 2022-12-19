cmake_minimum_required(VERSION 3.24)
project(Compiler)

set(CMAKE_CXX_STANDARD 17)

add_executable(Compiler main.cpp exceptions/exception_with_line_number.h directives/IDs.h directives/IListingGenerator.h directives/ISyntaxChecker.h aliases.h exceptions/comma_expected_exception.h directives/directive.cpp directives/directive.h exceptions/few_arguments_exception.h lexical_analyzer.cpp lexical_analyzer.h listing_generate_helper.cpp listing_generate_helper.h listing_generator.cpp listing_generator.h directives/mov.cpp directives/mov.h directives/pop.cpp directives/pop.h string_functions.cpp string_functions.h syntax_analyzer.cpp syntax_analyzer.h exceptions/too_many_arguments_exception.h var.h var_table.cpp var_table.h exceptions/wrong_argument_exception.h exceptions/exceptions.h directives/directives.h directives/numeric_values.h elf_file_generator.cpp elf_file_generator.h directives/comma.h directives/registers.h directives/define_variable.h directives/variable.cpp directives/variable.h directives/IDs.cpp directives/add.cpp directives/add.h)
