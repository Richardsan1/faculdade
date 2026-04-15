from __future__ import annotations

import re
from pathlib import Path

from reportlab.lib import colors
from reportlab.lib.pagesizes import A4
from reportlab.lib.styles import ParagraphStyle, getSampleStyleSheet
from reportlab.lib.units import cm
from reportlab.platypus import Image, Paragraph, SimpleDocTemplate, Spacer


def build_pdf(md_path: Path, pdf_path: Path) -> None:
    text = md_path.read_text(encoding="utf-8")
    lines = text.splitlines()

    doc = SimpleDocTemplate(
        str(pdf_path),
        pagesize=A4,
        leftMargin=1.6 * cm,
        rightMargin=1.6 * cm,
        topMargin=1.6 * cm,
        bottomMargin=1.6 * cm,
        title="Modelo Conceitual - VR Memory",
    )

    base_styles = getSampleStyleSheet()
    styles = {
        "h1": ParagraphStyle(
            "H1", parent=base_styles["Heading1"], fontSize=16, leading=19, spaceAfter=8
        ),
        "h2": ParagraphStyle(
            "H2", parent=base_styles["Heading2"], fontSize=13, leading=16, spaceAfter=6
        ),
        "h3": ParagraphStyle(
            "H3", parent=base_styles["Heading3"], fontSize=11, leading=14, spaceAfter=5
        ),
        "normal": ParagraphStyle(
            "NormalText", parent=base_styles["BodyText"], fontSize=9.6, leading=13
        ),
        "bullet": ParagraphStyle(
            "BulletText",
            parent=base_styles["BodyText"],
            fontSize=9.6,
            leading=13,
            leftIndent=14,
        ),
        "caption": ParagraphStyle(
            "Caption",
            parent=base_styles["Italic"],
            fontSize=8.2,
            leading=10,
            textColor=colors.HexColor("#444444"),
            spaceBefore=3,
            spaceAfter=8,
        ),
        "code": ParagraphStyle(
            "Code", parent=base_styles["BodyText"], fontName="Courier", fontSize=8.8, leading=12
        ),
    }

    story = []
    in_code = False

    for line in lines:
        raw = line.rstrip()

        if raw.strip().startswith("```"):
            in_code = not in_code
            continue

        if in_code:
            if raw.strip():
                escaped = raw.replace("&", "&amp;").replace("<", "&lt;").replace(">", "&gt;")
                story.append(Paragraph(escaped, styles["code"]))
            else:
                story.append(Spacer(1, 5))
            continue

        if not raw.strip():
            story.append(Spacer(1, 6))
            continue

        img_match = re.match(r"!\[(.*?)\]\((.*?)\)", raw.strip())
        if img_match:
            alt, rel_path = img_match.groups()
            img_path = (md_path.parent / rel_path).resolve()
            if img_path.exists():
                img = Image(str(img_path))
                max_w = doc.width
                max_h = 14 * cm
                ratio = img.imageWidth / img.imageHeight if img.imageHeight else 1
                width = min(max_w, img.imageWidth)
                height = width / ratio if ratio else 6 * cm
                if height > max_h:
                    height = max_h
                    width = height * ratio
                img.drawWidth = width
                img.drawHeight = height
                story.append(img)
                if alt:
                    caption = alt.replace("&", "&amp;").replace("<", "&lt;").replace(">", "&gt;")
                    story.append(Paragraph(caption, styles["caption"]))
                else:
                    story.append(Spacer(1, 6))
            else:
                msg = f"[Imagem nao encontrada: {rel_path}]"
                story.append(Paragraph(msg, styles["caption"]))
            continue

        if raw.startswith("# "):
            content = raw[2:].strip()
            story.append(Paragraph(escape_md(content), styles["h1"]))
            continue
        if raw.startswith("## "):
            content = raw[3:].strip()
            story.append(Paragraph(escape_md(content), styles["h2"]))
            continue
        if raw.startswith("### "):
            content = raw[4:].strip()
            story.append(Paragraph(escape_md(content), styles["h3"]))
            continue
        if raw.startswith("#### "):
            content = raw[5:].strip()
            story.append(Paragraph("<b>" + escape_md(content) + "</b>", styles["normal"]))
            continue

        if re.match(r"^\d+\.\s+", raw.strip()):
            content = re.sub(r"^\d+\.\s+", "", raw.strip())
            story.append(Paragraph("&#8226; " + escape_md(content), styles["bullet"]))
            continue
        if raw.strip().startswith("- "):
            content = raw.strip()[2:]
            story.append(Paragraph("&#8226; " + escape_md(content), styles["bullet"]))
            continue

        if raw.strip().startswith("|") and raw.strip().endswith("|"):
            story.append(Paragraph(escape_md(raw), styles["code"]))
            continue

        story.append(Paragraph(escape_md(raw), styles["normal"]))

    doc.build(story)


def escape_md(text: str) -> str:
    text = text.replace("&", "&amp;").replace("<", "&lt;").replace(">", "&gt;")
    text = re.sub(r"\*\*(.+?)\*\*", r"<b>\1</b>", text)
    text = re.sub(r"\*(.+?)\*", r"<i>\1</i>", text)
    text = re.sub(r"`(.+?)`", r"<font name='Courier'>\1</font>", text)
    return text


if __name__ == "__main__":
    root = Path(__file__).resolve().parent
    # md_file = root / "modelo_conceitual.md"
    # pdf_file = root / "modelo_conceitual.pdf"
    md_file = root / "prototipo_baixa.md"
    pdf_file = root / "prototipo_baixa.pdf"
    build_pdf(md_file, pdf_file)
    print(f"PDF gerado: {pdf_file}")
