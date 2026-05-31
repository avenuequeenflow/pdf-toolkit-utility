#include <gtest/gtest.h>
#include "../src/pdf_utils.h"
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

class PdfUtilsTest : public ::testing::Test {
protected:
    void SetUp() override {
        test_dir = "test_output";
        fs::create_directory(test_dir);
    }

    void TearDown() override {
        fs::remove_all(test_dir);
    }

    std::string test_dir;
};

TEST_F(PdfUtilsTest, MergePdfs) {
    std::vector<std::string> inputs = {test_dir + "/input1.pdf", test_dir + "/input2.pdf"};
    std::ofstream out1(inputs[0]);
    out1 << "%PDF-1.4\n1 0 obj\n<< /Type /Catalog >>\nendobj\n%%EOF\n";
    out1.close();

    std::ofstream out2(inputs[1]);
    out2 << "%PDF-1.4\n1 0 obj\n<< /Type /Catalog >>\nendobj\n%%EOF\n";
    out2.close();

    std::string output = test_dir + "/merged.pdf";
    EXPECT_TRUE(merge_pdfs(output, inputs));
    EXPECT_TRUE(fs::exists(output));
}

TEST_F(PdfUtilsTest, ExtractPages) {
    std::string input = test_dir + "/input.pdf";
    std::ofstream out(input);
    out << "%PDF-1.4\n1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
    out << "2 0 obj\n<< /Type /Pages /Kids [3 0 R 4 0 R] /Count 2 >>\nendobj\n%%EOF\n";
    out.close();

    std::string output_prefix = test_dir + "/extracted";
    EXPECT_TRUE(extract_pages(input, output_prefix, 1, 1));
    EXPECT_TRUE(fs::exists(output_prefix + "_extracted.pdf"));
}