"""Unit tests for the PDF Toolkit."""

import os
import tempfile
import pytest
import fitz

from toolkit.merger import merge_pdfs
from toolkit.splitter import split_pdf
from toolkit.extractor import extract_text


def create_sample_pdf(path, text="Hello World"):
    """Create a simple PDF for testing."""
    doc = fitz.open()
    page = doc.new_page()
    page.insert_text((50, 50), text)
    doc.save(path)
    doc.close()


class TestPdfToolkit:
    def test_merge(self):
        with tempfile.TemporaryDirectory() as tmpdir:
            f1 = os.path.join(tmpdir, "a.pdf")
            f2 = os.path.join(tmpdir, "b.pdf")
            out = os.path.join(tmpdir, "merged.pdf")
            create_sample_pdf(f1, "Page 1")
            create_sample_pdf(f2, "Page 2")
            merge_pdfs([f1, f2], out)
            assert os.path.exists(out)
            doc = fitz.open(out)
            assert len(doc) == 2
            doc.close()

    def test_split(self):
        with tempfile.TemporaryDirectory() as tmpdir:
            src = os.path.join(tmpdir, "src.pdf")
            out_dir = os.path.join(tmpdir, "pages")
            create_sample_pdf(src, "Two\nPages")
            split_pdf(src, out_dir)
            files = os.listdir(out_dir)
            assert len(files) == 1  # only one page in sample

    def test_extract(self):
        with tempfile.TemporaryDirectory() as tmpdir:
            src = os.path.join(tmpdir, "src.pdf")
            out = os.path.join(tmpdir, "out.txt")
            create_sample_pdf(src, "Extract me")
            extract_text(src, out)
            with open(out, "r") as f:
                text = f.read()
            assert "Extract me" in text