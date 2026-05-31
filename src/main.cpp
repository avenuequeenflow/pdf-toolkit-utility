#include <iostream>
#include <string>
#include "pdf_utils.h"

void print_usage() {
    std::cout << "PDF Toolkit Utility\n";
    std::cout << "Usage:\n";
    std::cout << "  pdf-toolkit-utility merge <output.pdf> <input1.pdf> <input2.pdf> ...\n";
    std::cout << "  pdf-toolkit-utility extract <input.pdf> <output_prefix> <start_page> <end_page>\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_usage();
        return 1;
    }

    std::string command = argv[1];

    if (command == "merge") {
        if (argc < 4) {
            std::cerr << "Error: Not enough arguments for merge\n";
            print_usage();
            return 1;
        }
        std::string output = argv[2];
        std::vector<std::string> inputs(argv + 3, argv + argc);
        if (merge_pdfs(output, inputs)) {
            std::cout << "Successfully merged PDFs to " << output << "\n";
        } else {
            std::cerr << "Failed to merge PDFs\n";
            return 1;
        }
    }
    else if (command == "extract") {
        if (argc != 6) {
            std::cerr << "Error: Incorrect number of arguments for extract\n";
            print_usage();
            return 1;
        }
        std::string input = argv[2];
        std::string output_prefix = argv[3];
        int start_page = std::stoi(argv[4]);
        int end_page = std::stoi(argv[5]);

        if (extract_pages(input, output_prefix, start_page, end_page)) {
            std::cout << "Successfully extracted pages " << start_page << "-" << end_page
                      << " to " << output_prefix << "_extracted.pdf\n";
        } else {
            std::cerr << "Failed to extract pages\n";
            return 1;
        }
    }
    else {
        std::cerr << "Error: Unknown command '" << command << "'\n";
        print_usage();
        return 1;
    }

    return 0;
}