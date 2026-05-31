# PDF Toolkit Utility

A lightweight command-line toolkit for merging, splitting, and extracting text from PDF files.

## Features

- Merge multiple PDFs into one
- Split a PDF into individual pages
- Extract text from PDF

## Requirements

- Python 3.7+
- PyMuPDF (fitz)
- tqdm

## Installation

```bash
pip install -r requirements.txt
```

## Usage

```bash
# Merge PDFs
python main.py merge input1.pdf input2.pdf -o output.pdf

# Split PDF into pages
python main.py split input.pdf -o output_dir/

# Extract text from PDF
python main.py extract input.pdf -o output.txt
```

## Testing

```bash
pytest tests/
```