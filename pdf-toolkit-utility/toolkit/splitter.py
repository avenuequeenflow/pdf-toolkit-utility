"""Split a PDF into individual page files."""

import os
import fitz
from tqdm import tqdm


def split_pdf(input_file, output_dir):
    """Split a PDF into one file per page."""
    os.makedirs(output_dir, exist_ok=True)
    with fitz.open(input_file) as doc:
        for i in tqdm(range(len(doc)), desc="Splitting PDF"):
            page_doc = fitz.open()
            page_doc.insert_pdf(doc, from_page=i, to_page=i)
            page_path = os.path.join(output_dir, f"page_{i+1:04d}.pdf")
            page_doc.save(page_path)
            page_doc.close()
    print(f"Split {len(doc)} pages into {output_dir}")