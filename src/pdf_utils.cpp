#include "pdf_utils.h"
#include <poppler/cpp/poppler-document.h>
#include <poppler/cpp/poppler-page.h>
#include <fstream>
#include <iostream>

bool merge_pdfs(const std::string& output_file, const std::vector<std::string>& input_files) {
    poppler::document* output_doc = poppler::document::new_from_file(output_file, "", "");
    if (output_doc) {
        delete output_doc;
        std::cerr << "Output file already exists\n";
        return false;
    }

    std::vector<poppler::document*> docs;
    for (const auto& file : input_files) {
        poppler::document* doc = poppler::document::new_from_file(file, "", "");
        if (!doc) {
            std::cerr << "Failed to open " << file << "\n";
            for (auto d : docs) delete d;
            return false;
        }
        docs.push_back(doc);
    }

    // Simple merge implementation (would need proper page copying in real code)
    std::ofstream out(output_file, std::ios::binary);
    if (!out) {
        std::cerr << "Failed to create output file\n";
        for (auto d : docs) delete d;
        return false;
    }

    // In a real implementation, we would properly merge the PDFs here
    // This is just a placeholder that creates an empty PDF
    out << "%PDF-1.4\n1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
    out << "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
    out << "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] /Contents 4 0 R >>\nendobj\n";
    out << "4 0 obj\n<< /Length 44 >>\nstream\nBT\n/F1 12 Tf\n100 700 Td\n(Placeholder merged PDF) Tj\nET\nendstream\nendobj\n";
    out << "xref\n0 5\n0000000000 65535 f \n0000000009 00000 n \n0000000063 00000 n \n0000000131 00000 n \n0000000224 00000 n \n";
    out << "trailer\n<< /Size 5 /Root 1 0 R >>\nstartxref\n373\n%%EOF\n";

    for (auto d : docs) delete d;
    return true;
}

bool extract_pages(const std::string& input_file, const std::string& output_prefix, int start_page, int end_page) {
    poppler::document* doc = poppler::document::new_from_file(input_file, "", "");
    if (!doc) {
        std::cerr << "Failed to open " << input_file << "\n";
        return false;
    }

    int page_count = doc->pages();
    if (start_page < 1 || end_page > page_count || start_page > end_page) {
        std::cerr << "Invalid page range\n";
        delete doc;
        return false;
    }

    std::string output_file = output_prefix + "_extracted.pdf";
    std::ofstream out(output_file, std::ios::binary);
    if (!out) {
        std::cerr << "Failed to create output file\n";
        delete doc;
        return false;
    }

    // In a real implementation, we would properly extract the pages here
    // This is just a placeholder that creates an empty PDF
    out << "%PDF-1.4\n1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
    out << "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
    out << "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] /Contents 4 0 R >>\nendobj\n";
    out << "4 0 obj\n<< /Length 50 >>\nstream\nBT\n/F1 12 Tf\n100 700 Td\n(Placeholder extracted pages " << start_page << "-" << end_page << ") Tj\nET\nendstream\nendobj\n";
    out << "xref\n0 5\n0000000000 65535 f \n0000000009 00000 n \n0000000063 00000 n \n0000000131 00000 n \n0000000240 00000 n \n";
    out << "trailer\n<< /Size 5 /Root 1 0 R >>\nstartxref\n400\n%%EOF\n";

    delete doc;
    return true;
}