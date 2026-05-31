#ifndef PDF_UTILS_H
#define PDF_UTILS_H

#include <string>
#include <vector>

bool merge_pdfs(const std::string& output_file, const std::vector<std::string>& input_files);
bool extract_pages(const std::string& input_file, const std::string& output_prefix, int start_page, int end_page);

#endif // PDF_UTILS_H