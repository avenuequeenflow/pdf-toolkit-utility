"""Merge multiple PDF files into one."""

import fitz
from tqdm import tqdm


def merge_pdfs(input_files, output_file):
    """Merge a list of PDF files into a single PDF."""
    doc_out = fitz.open()
    for pdf_path in tqdm(input_files, desc="Merging PDFs"):
        with fitz.open(pdf_path) as doc_in:
            doc_out.insert_pdf(doc_in)
    doc_out.save(output_file)
    doc_out.close()
    print(f"Merged {len(input_files)} PDFs into {output_file}")