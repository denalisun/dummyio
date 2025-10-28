import os, shutil

# Build fonts
fonts = ["assets/fonts/bytesized.ttf"]
font_template = """#ifndef FONTS_H\n#define FONTS_H"""
for font in fonts:
    with open(font, 'rb') as f:
        t = f"const unsigned char {os.path.splitext(os.path.basename(font))[0]}[] {{"
        while (byte := f.read(1)):
            t += f"0x{byte.hex()}, "
        t += "}"
        font_template += f"\n{t}"

with open("src/data/fonts.h", 'w') as f:
    f.write(font_template)