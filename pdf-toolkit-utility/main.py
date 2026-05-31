#!/usr/bin/env python3
"""PDF Toolkit Utility - CLI entry point."""

import argparse
import sys

from toolkit.merger import merge_pdfs
from toolkit.splitter import split_pdf
from toolkit.extractor import extract_text


def main():
    parser = argparse.ArgumentParser(description="PDF Toolkit Utility")
    subparsers = parser.add_subparsers(dest="command", required=True)

    # Merge command
    merge_parser = subparsers.add_parser("merge", help="Merge multiple PDFs")
    merge_parser.add_argument("inputs", nargs="+", help="Input PDF files")
    merge_parser.add_argument("-o", "--output", default="merged.pdf", help="Output PDF file")

    # Split command
    split_parser = subparsers.add_parser("split", help="Split PDF into pages")
    split_parser.add_argument("input", help="Input PDF file")
    split_parser.add_argument("-o", "--output", default=".", help="Output directory")

    # Extract command
    extract_parser = subparsers.add_parser("extract", help="Extract text from PDF")
    extract_parser.add_argument("input", help="Input PDF file")
    extract_parser.add_argument("-o", "--output", default="output.txt", help="Output text file")

    args = parser.parse_args()

    try:
        if args.command == "merge":
            merge_pdfs(args.inputs, args.output)
        elif args.command == "split":
            split_pdf(args.input, args.output)
        elif args.command == "extract":
            extract_text(args.input, args.output)
    except Exception as e:
        print(f"Error: {e}", file=sys.stderr)
        sys.exit(1)


if __name__ == "__main__":
    main()