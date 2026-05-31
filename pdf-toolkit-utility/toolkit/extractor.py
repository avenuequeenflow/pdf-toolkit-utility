"""Extract text from a PDF file."""

import fitz
from tqdm import tqdm


def extract_text(input_file, output_file):
    """Extract all text from a PDF and save to a text file."""
    text_parts = []
    with fitz.open(input_file) as doc:
        for page in tqdm(doc, desc="Extracting text"):
            text_parts.append(page.get_text())
    full_text = "\n".join(text_parts)
    with open(output_file, "w", encoding="utf-8") as f:
        f.write(full_text)
    print(f"Extracted {len(full_text)} characters to {output_file}")