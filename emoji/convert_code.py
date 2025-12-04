import cv2
from pathlib import Path

current_dir = Path(__file__).parent
images = current_dir.glob("*.png")

EMOJI_WIDTH = 160
EMOJI_HEIGHT = 160

points_table = {
    "surprise": [(56, 62), (104, 62), (80, 134)],
    "happy": [(56, 62), (104, 62), (80, 134)],
    "neutral": [(56, 62), (104, 62), (80, 134)],
    "angry": [(56, 62), (104, 62), (80, 134)],
}

with open("emoji.h", "w") as f:
    f.write("#ifndef EMOJI_H\n")
    f.write("#define EMOJI_H\n\n")

    f.write("#include \"geometry.h\"\n")

    f.write("namespace emoji {\n")

    for image in images:
        image_bgr = cv2.imread(str(image), cv2.IMREAD_UNCHANGED)
        if image_bgr.shape[2] == 4:
            image_rgba = cv2.cvtColor(image_bgr, cv2.COLOR_BGRA2RGBA)
        else:
            image_rgba = cv2.cvtColor(image_bgr, cv2.COLOR_BGR2RGBA)

        image_rgba = cv2.resize(image_rgba, (EMOJI_WIDTH, EMOJI_HEIGHT))
        pixels = image_rgba.flatten()

        pxiel_array = "{\n" + ", ".join([f"0x{pixel:02x}" for pixel in pixels]) + "}"    
        f.write(f"const unsigned char {image.stem.upper()}_EMOJI[] = {pxiel_array};\n")

        points_array = "{\n" + ", ".join([f"geo::Point{{{x}.f, {y}.f}}" for x, y in points_table[image.stem.lower()]]) + "\n}"
        f.write(f"const std::vector<geo::Point> {image.stem.upper()}_POINTS = {points_array};\n")

    f.write(f"const int EMOJI_WIDTH = {EMOJI_WIDTH};\n")
    f.write(f"const int EMOJI_HEIGHT = {EMOJI_HEIGHT};\n")
    f.write("}\n")
    f.write("\n#endif // EMOJI_H\n")
