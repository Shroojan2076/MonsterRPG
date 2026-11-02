import os
import shutil
from PIL import Image, ImageDraw, ImageFont

def ensure_dir(path):
    os.makedirs(path, exist_ok=True)

# 1. Setup website directories
WEBSITE_ASSETS = os.path.abspath("website/public/assets")
SCREENSHOTS_DIR = os.path.join(WEBSITE_ASSETS, "screenshots")
MONSTERS_DIR = os.path.join(WEBSITE_ASSETS, "monsters")
CHARACTERS_DIR = os.path.join(WEBSITE_ASSETS, "characters")
WORLD_DIR = os.path.join(WEBSITE_ASSETS, "world")
LOGO_DIR = os.path.join(WEBSITE_ASSETS, "logo")

for d in [SCREENSHOTS_DIR, MONSTERS_DIR, CHARACTERS_DIR, WORLD_DIR, LOGO_DIR]:
    ensure_dir(d)

print("Created website asset directories.")

# 2. Copy Game Assets
# Tileset
shutil.copy2("assets/world_tileset.png", os.path.join(WORLD_DIR, "world_tileset.png"))

# Characters
for char_file in ["HGSS_boy.png", "HGSS_boy_run.png", "npc_prof.png", "npc_nurse.png", "npc_villager.png"]:
    src = os.path.join("assets", char_file)
    if os.path.exists(src):
        shutil.copy2(src, os.path.join(CHARACTERS_DIR, char_file))

# Monsters
monsters = [
    "001_BULBASAUR.png", "004_CHARMANDER.png", "007_SQUIRTLE.png",
    "016_PIDGEY.png", "025_PIKACHU.png", "035_CLEFAIRY.png",
    "039_JIGGLYPUFF.png", "052_MEOWTH.png", "054_PSYDUCK.png",
    "060_POLIWAG.png", "127_PINSIR.png", "133_EEVEE.png",
    "143_SNORLAX.png", "150_MEWTWO.png"
]

ensure_dir(os.path.join(MONSTERS_DIR, "front"))
ensure_dir(os.path.join(MONSTERS_DIR, "back"))
ensure_dir(os.path.join(MONSTERS_DIR, "overworld"))

for m in monsters:
    f_src = os.path.join("assets/pokemon/front", m)
    b_src = os.path.join("assets/pokemon/back", m)
    if os.path.exists(f_src):
        shutil.copy2(f_src, os.path.join(MONSTERS_DIR, "front", m))
    if os.path.exists(b_src):
        shutil.copy2(b_src, os.path.join(MONSTERS_DIR, "back", m))

# Overworld icons
ow_files = [
    "ow_127.png", "ow_128.png", "ow_129.png", "ow_130.png", "ow_131.png",
    "ow_132.png", "ow_133.png", "ow_134.png", "ow_135.png", "ow_136.png",
    "ow_137.png", "ow_138.png", "ow_139.png", "ow_140.png", "ow_141.png",
    "ow_142.png", "ow_143.png", "ow_144.png", "ow_145.png", "ow_146.png",
    "ow_147.png", "ow_148.png", "ow_149.png"
]
for ow in ow_files:
    ow_src = os.path.join("assets/overworld", ow)
    if os.path.exists(ow_src):
        shutil.copy2(ow_src, os.path.join(MONSTERS_DIR, "overworld", ow))

print("Copied core assets to website directory.")

# 3. Screenshot Generator
tileset_img = Image.open("assets/world_tileset.png").convert("RGBA")

def get_tile(tile_id):
    src_x = (tile_id % 8) * 32
    src_y = (tile_id // 8) * 32
    return tileset_img.crop((src_x, src_y, src_x + 32, src_y + 32))

def get_char_frame(char_path, row, col, frame_size=64):
    img = Image.open(char_path).convert("RGBA")
    x = col * frame_size
    y = row * frame_size
    return img.crop((x, y, x + frame_size, y + frame_size))

# Font for HUD rendering
try:
    hud_font = ImageFont.truetype("assets/font.ttf", 20)
    hud_font_sm = ImageFont.truetype("assets/font.ttf", 14)
    hud_font_lg = ImageFont.truetype("assets/font.ttf", 26)
    hud_font_battle = ImageFont.truetype("assets/font.ttf", 22)
except:
    hud_font = ImageFont.load_default()
    hud_font_sm = hud_font
    hud_font_lg = hud_font
    hud_font_battle = hud_font

# ==========================================
# SCENE 1: Oakdale Town Square (Overworld)
# ==========================================
def render_town_square():
    # View window: 15 cols x 10 rows (240x160 world units) centered around col 10, row 13
    # In world units: 16px per tile.
    # At 32px native tile resolution: viewport is 15 * 32 = 480w, 10 * 32 = 320h
    # Then upscaled 2x to 960x640!
    view_x = 3
    view_y = 8
    cols = 15
    rows = 10
    
    # Build tile grid (from TileMap::initializeOverworld)
    grid = [[0 for _ in range(44)] for _ in range(28)]
    # Town cobblestone: 2..19, 3..24
    for y in range(3, 25):
        for x in range(2, 20):
            grid[y][x] = 1
    # Town square path
    for y in range(3, 25):
        grid[y][10] = 3
        grid[y][11] = 3
    for x in range(2, 20):
        grid[13][x] = 3
        grid[14][x] = 3
    # Street lamps
    for lx, ly in [(9, 10), (9, 16), (15, 10), (15, 16)]:
        grid[ly][lx] = 16
    # Flower beds
    for fx in [11, 12, 13]:
        grid[7][fx] = 14
        grid[19][fx] = 13
    grid[7][15] = 15
    # Town sign
    grid[11][14] = 17
    # Oak Lab exterior (cols 4..8, rows 3..7 -> IDs 24..48)
    for r in range(5):
        for c in range(5):
            grid[3 + r][4 + c] = 24 + (r * 5 + c)
    # Pokemon Center exterior (cols 4..8, rows 14..18 -> IDs 49..73)
    for r in range(5):
        for c in range(5):
            grid[14 + r][4 + c] = 49 + (r * 5 + c)
            
    # Render tiles
    canvas = Image.new("RGBA", (cols * 32, rows * 32), (0, 0, 0, 255))
    for r in range(rows):
        for c in range(cols):
            gx = view_x + c
            gy = view_y + r
            tid = grid[gy][gx] if (0 <= gy < 28 and 0 <= gx < 44) else 0
            tile = get_tile(tid)
            canvas.paste(tile, (c * 32, r * 32), tile)

    # Entities
    # Draw Cedric at (13, 11) -> relative: (13 - 3, 11 - 8) = (10, 3)
    cedric_frame = get_char_frame("assets/npc_villager.png", 2, 0) # Right facing
    # Native tile is 32x32, character is 64x64 (anchored bottom center)
    cedric_frame = cedric_frame.resize((32, 32), Image.NEAREST)
    canvas.paste(cedric_frame, (10 * 32, 3 * 32), cedric_frame)
    
    # Cedric's Meowth at (12, 11) -> (9, 3)
    meowth_img = Image.open("assets/overworld/ow_145.png").convert("RGBA")
    meowth_img = meowth_img.resize((32, 32), Image.NEAREST)
    canvas.paste(meowth_img, (9 * 32, 3 * 32), meowth_img)
    
    # Player at (10, 13) -> (7, 5)
    player_frame = get_char_frame("assets/HGSS_boy.png", 0, 0) # Down facing
    player_frame = player_frame.resize((32, 32), Image.NEAREST)
    canvas.paste(player_frame, (7 * 32, 5 * 32), player_frame)
    
    # Partner Charmander at (10, 14) -> (7, 6)
    charmander_img = Image.open("assets/overworld/ow_149.png").convert("RGBA")
    charmander_img = charmander_img.resize((32, 32), Image.NEAREST)
    canvas.paste(charmander_img, (7 * 32, 6 * 32), charmander_img)

    # Upscale 2x to 960x640
    final_img = canvas.resize((960, 640), Image.NEAREST)
    
    # Add retro HUD overlay
    draw = ImageDraw.Draw(final_img)
    draw.rectangle([0, 0, 960, 40], fill=(10, 15, 25, 220))
    draw.text((20, 10), "[WASD] Move   |   [Shift] Run   |   [E / Space] Interact   |   Oakdale Town Square", fill=(240, 240, 245), font=hud_font_sm)
    
    # Dialogue box at bottom showing interaction with Cedric's Meowth
    draw.rectangle([40, 480, 920, 610], fill=(15, 20, 35, 245), outline=(234, 179, 8), width=3)
    draw.text((65, 495), "Meowth", fill=(234, 179, 8), font=hud_font)
    draw.text((65, 530), "Meowth: 'Nya-ha-ha! Purrr!'", fill=(255, 255, 255), font=hud_font)
    draw.text((65, 565), "Cedric's friendly Meowth playfully taps its shiny gold coin.", fill=(200, 210, 225), font=hud_font_sm)
    
    final_img.save(os.path.join(SCREENSHOTS_DIR, "town_square.png"))
    print("Rendered town_square.png")

# ==========================================
# SCENE 2: Prof. Oak's Research Lab Interior
# ==========================================
def render_oak_lab():
    # 14 cols x 11 rows
    layout = [
        [80, 80,  80,  80,  80,  80,  80,  80,  80,  80,  80,  80,  80, 80],
        [80, 84,  84,  84,  84,  84,  84,  84,  84,  84,  84,  84,  80, 80],
        [80, 85,  89, 110,  89,  91,  91,  85,  89, 110,  89,  85,  80, 80],
        [80, 74,  81,  81,  92,  81,  81,  81, 111,  81,  81,  75,  80, 80],
        [80, 74,  81,  81,  81,  94,  93,  96,  81,  81,  81,  75,  80, 80],
        [80, 74,  81,  81,  81,  81,  81,  81,  81,  81,  81,  75,  80, 80],
        [80, 74,  88, 109,  81,  81,  81,  81,  81,  88, 109,  75,  80, 80],
        [80, 74,  89, 110,  81,  81,  81,  81,  81,  89, 110,  75,  80, 80],
        [80, 74, 106,  81,  81,  81,  81,  81,  81,  81, 106,  75,  80, 80],
        [80, 78,  78,  78,  78,  78,  97,  78,  78,  78,  78,  78,  80, 80],
        [80, 80,  80,  80,  80,  80,  80,  80,  80,  80,  80,  80,  80, 80]
    ]
    canvas = Image.new("RGBA", (14 * 32, 11 * 32), (10, 15, 25, 255))
    for r in range(11):
        for c in range(14):
            tid = layout[r][c]
            tile = get_tile(tid)
            canvas.paste(tile, (c * 32, r * 32), tile)

    # Entities:
    # Prof Oak at (6, 3)
    prof_frame = get_char_frame("assets/npc_prof.png", 0, 0).resize((32, 32), Image.NEAREST)
    canvas.paste(prof_frame, (6 * 32, 3 * 32), prof_frame)

    # Eevee at (9, 3)
    eevee_img = Image.open("assets/overworld/ow_135.png").convert("RGBA").resize((32, 32), Image.NEAREST)
    canvas.paste(eevee_img, (9 * 32, 3 * 32), eevee_img)

    # Squirtle at (3, 5)
    squirtle_img = Image.open("assets/overworld/ow_133.png").convert("RGBA").resize((32, 32), Image.NEAREST)
    canvas.paste(squirtle_img, (3 * 32, 5 * 32), squirtle_img)

    # Player at (6, 5) facing UP
    player_frame = get_char_frame("assets/HGSS_boy.png", 3, 0).resize((32, 32), Image.NEAREST)
    canvas.paste(player_frame, (6 * 32, 5 * 32), player_frame)

    # Charmander follower at (6, 6)
    charmander_img = Image.open("assets/overworld/ow_149.png").convert("RGBA").resize((32, 32), Image.NEAREST)
    canvas.paste(charmander_img, (6 * 32, 6 * 32), charmander_img)

    # Scale to 960x640 with letterbox centering
    scaled = canvas.resize((int(14 * 32 * 1.8), int(11 * 32 * 1.8)), Image.NEAREST)
    final_img = Image.new("RGBA", (960, 640), (11, 17, 23, 255))
    offset_x = (960 - scaled.width) // 2
    offset_y = (640 - scaled.height) // 2
    final_img.paste(scaled, (offset_x, offset_y), scaled)

    draw = ImageDraw.Draw(final_img)
    draw.rectangle([0, 0, 960, 40], fill=(10, 15, 25, 220))
    draw.text((20, 10), "[WASD] Move   |   [E / Space] Interact   |   Prof. Oak's Research Lab", fill=(240, 240, 245), font=hud_font_sm)

    # Dialogue box
    draw.rectangle([40, 480, 920, 610], fill=(15, 20, 35, 245), outline=(56, 189, 248), width=3)
    draw.text((65, 495), "Prof. Oak", fill=(56, 189, 248), font=hud_font)
    draw.text((65, 530), "Hello young adventurer! Welcome to Oakdale Town.", fill=(255, 255, 255), font=hud_font)
    draw.text((65, 565), "I have entrusted you with a brave Charmander (Fire-type)! Go explore Whispering Woods!", fill=(200, 210, 225), font=hud_font_sm)

    final_img.save(os.path.join(SCREENSHOTS_DIR, "oak_lab.png"))
    print("Rendered oak_lab.png")

# ==========================================
# SCENE 3: Pokémon Center Interior
# ==========================================
def render_pokemon_center():
    layout = [
        [80, 80,  80,  80,  80,  80,  80,  80,  80,  80,  80,  80,  80, 80],
        [80, 86,  86,  86,  86,  86,  86,  86,  86,  86,  86,  86,  80, 80],
        [80, 87, 107,  87,  87,  87, 101,  87,  87,  87, 102,  87,  80, 80],
        [80, 76,  82,  82,  82,  82,  82,  82,  82,  82,  82,  77,  80, 80],
        [80, 76, 103,  82,  82,  98, 100,  99,  82,  82,  82,  77,  80, 80],
        [80, 76,  82,  82,  82,  82,  83,  82,  82,  82,  82,  77,  80, 80],
        [80, 76, 104, 105,  82,  82,  83,  82,  82,  82,  82,  77,  80, 80],
        [80, 76,  82,  82,  82,  82,  83,  82,  82,  82,  82,  77,  80, 80],
        [80, 76, 107,  82,  82,  82,  83,  82,  82,  82, 107,  77,  80, 80],
        [80, 79,  79,  79,  79,  79, 108,  79,  79,  79,  79,  79,  80, 80],
        [80, 80,  80,  80,  80,  80,  80,  80,  80,  80,  80,  80,  80, 80]
    ]
    canvas = Image.new("RGBA", (14 * 32, 11 * 32), (10, 15, 25, 255))
    for r in range(11):
        for c in range(14):
            tid = layout[r][c]
            tile = get_tile(tid)
            canvas.paste(tile, (c * 32, r * 32), tile)

    # Nurse Joy at (6, 3)
    nurse_frame = get_char_frame("assets/npc_nurse.png", 0, 0).resize((32, 32), Image.NEAREST)
    canvas.paste(nurse_frame, (6 * 32, 3 * 32), nurse_frame)

    # Clefairy at (7, 3)
    clefairy_img = Image.open("assets/overworld/ow_146.png").convert("RGBA").resize((32, 32), Image.NEAREST)
    canvas.paste(clefairy_img, (7 * 32, 3 * 32), clefairy_img)

    # Jigglypuff at (4, 6)
    jiggly_img = Image.open("assets/overworld/ow_148.png").convert("RGBA").resize((32, 32), Image.NEAREST)
    canvas.paste(jiggly_img, (4 * 32, 6 * 32), jiggly_img)

    # Player at (6, 5) facing UP
    player_frame = get_char_frame("assets/HGSS_boy.png", 3, 0).resize((32, 32), Image.NEAREST)
    canvas.paste(player_frame, (6 * 32, 5 * 32), player_frame)

    # Charmander at (6, 6)
    charmander_img = Image.open("assets/overworld/ow_149.png").convert("RGBA").resize((32, 32), Image.NEAREST)
    canvas.paste(charmander_img, (6 * 32, 6 * 32), charmander_img)

    scaled = canvas.resize((int(14 * 32 * 1.8), int(11 * 32 * 1.8)), Image.NEAREST)
    final_img = Image.new("RGBA", (960, 640), (11, 17, 23, 255))
    offset_x = (960 - scaled.width) // 2
    offset_y = (640 - scaled.height) // 2
    final_img.paste(scaled, (offset_x, offset_y), scaled)

    draw = ImageDraw.Draw(final_img)
    draw.rectangle([0, 0, 960, 40], fill=(10, 15, 25, 220))
    draw.text((20, 10), "[WASD] Move   |   [E / Space] Interact   |   Oakdale Pokemon Center", fill=(240, 240, 245), font=hud_font_sm)

    # Dialogue box
    draw.rectangle([40, 480, 920, 610], fill=(15, 20, 35, 245), outline=(244, 63, 94), width=3)
    draw.text((65, 495), "Nurse Joy", fill=(244, 63, 94), font=hud_font)
    draw.text((65, 530), "Welcome to the Pokemon Center! Your monsters look exhausted...", fill=(255, 255, 255), font=hud_font)
    draw.text((65, 565), "Your monster party has been completely restored to full health! Stay safe out there!", fill=(200, 210, 225), font=hud_font_sm)

    final_img.save(os.path.join(SCREENSHOTS_DIR, "pokemon_center.png"))
    print("Rendered pokemon_center.png")

# ==========================================
# SCENE 4: Whispering Woods Wilderness
# ==========================================
def render_whispering_woods():
    # View around (26, 17) -> cols 20..34, rows 12..21
    cols = 15
    rows = 10
    view_x = 20
    view_y = 12

    grid = [[0 for _ in range(44)] for _ in range(28)]
    # Main dirt trail: rows 12..13, cols 21..34
    for y in range(12, 14):
        for x in range(21, 35):
            grid[y][x] = 2
    # South trail
    for y in range(13, 23):
        grid[y][27] = 2
        grid[y][28] = 2
    for x in range(28, 39):
        grid[22][x] = 2
    # Tall grass patches
    for y in range(15, 20):
        for x in range(22, 26):
            grid[y][x] = 6
    for y in range(14, 19):
        for x in range(29, 33):
            grid[y][x] = 6
    # Pond
    for y in range(20, 23):
        for x in range(30, 34):
            grid[y][x] = 8
    # Trees
    def place_tree(rx, ry):
        grid[ry][rx] = 19
        grid[ry][rx+1] = 20
        grid[ry+1][rx] = 21
        grid[ry+1][rx+1] = 22
    for tx in [20, 24, 28, 32]:
        place_tree(tx, 10)
        place_tree(tx, 20)

    canvas = Image.new("RGBA", (cols * 32, rows * 32), (0, 0, 0, 255))
    for r in range(rows):
        for c in range(cols):
            gx = view_x + c
            gy = view_y + r
            tid = grid[gy][gx] if (0 <= gy < 28 and 0 <= gx < 44) else 0
            tile = get_tile(tid)
            canvas.paste(tile, (c * 32, r * 32), tile)

    # Entities:
    # Player at (27, 16) -> (27 - 20, 16 - 12) = (7, 4)
    player_frame = get_char_frame("assets/HGSS_boy.png", 0, 1).resize((32, 32), Image.NEAREST)
    canvas.paste(player_frame, (7 * 32, 4 * 32), player_frame)

    # Follower Charmander at (27, 15) -> (7, 3)
    charm_img = Image.open("assets/overworld/ow_149.png").convert("RGBA").resize((32, 32), Image.NEAREST)
    canvas.paste(charm_img, (7 * 32, 3 * 32), charm_img)

    # Wild Bulbasaur at (21, 17) -> (1, 5)
    bulba_img = Image.open("assets/overworld/ow_134.png").convert("RGBA").resize((32, 32), Image.NEAREST)
    canvas.paste(bulba_img, (1 * 32, 5 * 32), bulba_img)

    # Wild Pidgey at (31, 15) -> (11, 3)
    pidgey_img = Image.open("assets/overworld/ow_149.png").convert("RGBA").resize((32, 32), Image.NEAREST)
    canvas.paste(pidgey_img, (11 * 32, 3 * 32), pidgey_img)

    # Psyduck at (26, 21) -> (6, 9)
    psyduck_img = Image.open("assets/overworld/ow_147.png").convert("RGBA").resize((32, 32), Image.NEAREST)
    canvas.paste(psyduck_img, (6 * 32, 9 * 32), psyduck_img)

    # Snorlax at (36, 12) -> just off edge or at (33, 13) -> (13, 1)
    snorlax_img = Image.open("assets/overworld/ow_127.png").convert("RGBA").resize((48, 48), Image.NEAREST)
    canvas.paste(snorlax_img, (12 * 32, 1 * 32), snorlax_img)

    final_img = canvas.resize((960, 640), Image.NEAREST)
    draw = ImageDraw.Draw(final_img)
    draw.rectangle([0, 0, 960, 40], fill=(10, 15, 25, 220))
    draw.text((20, 10), "[WASD] Move   |   [Shift] Run   |   Whispering Woods   |   Partner: Charmander (Lv. 6 - HP: 22/22)", fill=(240, 240, 245), font=hud_font_sm)

    final_img.save(os.path.join(SCREENSHOTS_DIR, "whispering_woods.png"))
    print("Rendered whispering_woods.png")

# ==========================================
# SCENE 5: Boss Clearing Confrontation (Mewtwo)
# ==========================================
def render_mewtwo_encounter():
    cols = 15
    rows = 10
    view_x = 30
    view_y = 2

    grid = [[0 for _ in range(44)] for _ in range(28)]
    # Clearing path cols 34..39, rows 5..6
    for y in range(4, 8):
        for x in range(33, 40):
            grid[y][x] = 2
    # Trail south
    for y in range(7, 13):
        grid[y][33] = 2
        grid[y][34] = 2

    canvas = Image.new("RGBA", (cols * 32, rows * 32), (0, 0, 0, 255))
    for r in range(rows):
        for c in range(cols):
            gx = view_x + c
            gy = view_y + r
            tid = grid[gy][gx] if (0 <= gy < 28 and 0 <= gx < 44) else 0
            tile = get_tile(tid)
            canvas.paste(tile, (c * 32, r * 32), tile)

    # Boss Mewtwo at (37, 5) -> relative: (37 - 30, 5 - 2) = (7, 3)
    mewtwo_img = Image.open("assets/overworld/ow_131.png").convert("RGBA").resize((56, 56), Image.NEAREST)
    canvas.paste(mewtwo_img, (7 * 32 - 12, 3 * 32 - 16), mewtwo_img)

    # Player at (37, 7) -> (7, 5) facing UP
    player_frame = get_char_frame("assets/HGSS_boy.png", 3, 0).resize((32, 32), Image.NEAREST)
    canvas.paste(player_frame, (7 * 32, 5 * 32), player_frame)

    # Follower Charmander at (37, 8) -> (7, 6)
    charm_img = Image.open("assets/overworld/ow_149.png").convert("RGBA").resize((32, 32), Image.NEAREST)
    canvas.paste(charm_img, (7 * 32, 6 * 32), charm_img)

    final_img = canvas.resize((960, 640), Image.NEAREST)
    draw = ImageDraw.Draw(final_img)
    draw.rectangle([0, 0, 960, 40], fill=(10, 15, 25, 220))
    draw.text((20, 10), "Whispering Woods: Guardian Sanctuary   |   DANGER: Legendary Entity Detected", fill=(248, 113, 113), font=hud_font_sm)

    # Dialogue box
    draw.rectangle([40, 480, 920, 610], fill=(15, 20, 35, 245), outline=(168, 85, 247), width=3)
    draw.text((65, 495), "Mewtwo", fill=(168, 85, 247), font=hud_font)
    draw.text((65, 530), "The legendary Pokemon Mewtwo radiates overwhelming psychic energy!", fill=(255, 255, 255), font=hud_font)
    draw.text((65, 565), "Mewtwo: 'Mew... TWO!'   Prepare for battle!", fill=(200, 210, 225), font=hud_font_sm)

    final_img.save(os.path.join(SCREENSHOTS_DIR, "mewtwo_encounter.png"))
    print("Rendered mewtwo_encounter.png")

# ==========================================
# SCENE 6: Turn-Based Battle (Pikachu vs Charmander)
# ==========================================
def render_battle_scene():
    canvas = Image.new("RGBA", (960, 640), (22, 36, 30, 255))
    draw = ImageDraw.Draw(canvas)

    # Arena background gradient
    for y in range(450):
        c = int(22 + (y / 450) * 15)
        draw.line([(0, y), (960, y)], fill=(c, c + 18, c + 10))

    # Opponent platform ellipse
    draw.ellipse([540, 190, 880, 280], fill=(45, 80, 55, 200), outline=(70, 120, 85), width=3)
    # Player platform ellipse
    draw.ellipse([80, 370, 460, 470], fill=(45, 80, 55, 200), outline=(70, 120, 85), width=3)

    # Opponent Front Sprite: Pikachu at (640, 120)
    pika_front = Image.open("assets/pokemon/front/025_PIKACHU.png").convert("RGBA").resize((160, 160), Image.NEAREST)
    canvas.paste(pika_front, (630, 110), pika_front)

    # Player Back Sprite: Charmander at (180, 270)
    charm_back = Image.open("assets/pokemon/back/004_CHARMANDER.png").convert("RGBA").resize((200, 200), Image.NEAREST)
    canvas.paste(charm_back, (170, 250), charm_back)

    # Opponent HUD Box (Top Left)
    draw.rectangle([70, 60, 420, 150], fill=(15, 23, 42, 235), outline=(51, 65, 85), width=2)
    draw.text((90, 75), "Pikachu", fill=(245, 245, 250), font=hud_font_battle)
    draw.text((270, 78), "Lv. 5", fill=(234, 179, 8), font=hud_font_sm)
    draw.rectangle([340, 75, 400, 97], fill=(234, 179, 8, 50), outline=(234, 179, 8), width=1)
    draw.text((345, 78), "ELECTRIC", fill=(250, 204, 21), font=hud_font_sm)

    # HP bar background & fill
    draw.rectangle([90, 115, 400, 130], fill=(30, 41, 59), outline=(15, 23, 42), width=1)
    draw.rectangle([92, 117, 340, 128], fill=(34, 197, 94)) # ~75% HP

    # Player HUD Box (Bottom Right above battle menu)
    draw.rectangle([540, 320, 900, 420], fill=(15, 23, 42, 235), outline=(51, 65, 85), width=2)
    draw.text((560, 335), "Charmander", fill=(245, 245, 250), font=hud_font_battle)
    draw.text((750, 338), "Lv. 6", fill=(234, 179, 8), font=hud_font_sm)
    draw.rectangle([820, 335, 880, 357], fill=(249, 115, 22, 50), outline=(249, 115, 22), width=1)
    draw.text((833, 338), "FIRE", fill=(249, 115, 22), font=hud_font_sm)

    # Player HP bar
    draw.rectangle([560, 375, 880, 390], fill=(30, 41, 59), outline=(15, 23, 42), width=1)
    draw.rectangle([562, 377, 850, 388], fill=(34, 197, 94)) # ~90% HP
    draw.text((780, 395), "HP: 20/22", fill=(203, 213, 225), font=hud_font_sm)

    # Battle Command Box at Bottom
    draw.rectangle([0, 450, 960, 640], fill=(11, 17, 23, 250), outline=(44, 64, 83), width=3)

    # Left prompt
    draw.text((50, 485), "What will", fill=(241, 245, 249), font=hud_font_lg)
    draw.text((50, 530), "Charmander do?", fill=(241, 245, 249), font=hud_font_lg)

    # Right 2x2 Command Grid
    btn_w = 200
    btn_h = 60
    # Fight
    draw.rectangle([480, 480, 480 + btn_w, 480 + btn_h], fill=(24, 36, 48), outline=(234, 179, 8), width=2)
    draw.text((515, 498), "[1] FIGHT", fill=(234, 179, 8), font=hud_font)

    # Bag
    draw.rectangle([710, 480, 710 + btn_w, 480 + btn_h], fill=(24, 36, 48), outline=(51, 65, 85), width=1)
    draw.text((745, 498), "[2] BAG", fill=(241, 245, 249), font=hud_font)

    # Catch
    draw.rectangle([480, 555, 480 + btn_w, 555 + btn_h], fill=(24, 36, 48), outline=(51, 65, 85), width=1)
    draw.text((515, 573), "[3] CATCH", fill=(241, 245, 249), font=hud_font)

    # Run
    draw.rectangle([710, 555, 710 + btn_w, 555 + btn_h], fill=(24, 36, 48), outline=(51, 65, 85), width=1)
    draw.text((745, 573), "[4] RUN", fill=(241, 245, 249), font=hud_font)

    canvas.save(os.path.join(SCREENSHOTS_DIR, "battle_wild.png"))
    print("Rendered battle_wild.png")

# ==========================================
# SCENE 7: Battle Fight Move Selection
# ==========================================
def render_battle_moves():
    canvas = Image.open(os.path.join(SCREENSHOTS_DIR, "battle_wild.png")).convert("RGBA")
    draw = ImageDraw.Draw(canvas)

    # Redraw bottom command area with Move Selection
    draw.rectangle([0, 450, 960, 640], fill=(11, 17, 23, 250), outline=(44, 64, 83), width=3)

    moves = [
        {"key": "[1]", "name": "Scratch", "type": "NORMAL", "pwr": "40", "color": (148, 163, 184)},
        {"key": "[2]", "name": "Ember", "type": "FIRE", "pwr": "40", "color": (249, 115, 22)},
        {"key": "[3]", "name": "Smokescreen", "type": "NORMAL", "pwr": "--", "color": (148, 163, 184)},
        {"key": "[4]", "name": "Dragon Breath", "type": "DRAGON", "pwr": "60", "color": (99, 102, 241)}
    ]

    coords = [
        (40, 480),
        (340, 480),
        (40, 555),
        (340, 555)
    ]

    for m, (bx, by) in zip(moves, coords):
        draw.rectangle([bx, by, bx + 270, by + 60], fill=(24, 36, 48), outline=m["color"], width=2)
        draw.text((bx + 15, by + 12), f"{m['key']} {m['name']}", fill=(241, 245, 249), font=hud_font)
        draw.text((bx + 15, by + 36), f"TYPE: {m['type']}  PWR: {m['pwr']}", fill=m["color"], font=hud_font_sm)

    # Right info panel
    draw.rectangle([650, 475, 920, 615], fill=(18, 27, 36), outline=(51, 65, 85), width=1)
    draw.text((670, 495), "ACTIVE MOVE DETAILS", fill=(234, 179, 8), font=hud_font_sm)
    draw.text((670, 525), "Ember (Fire)", fill=(249, 115, 22), font=hud_font)
    draw.text((670, 555), "Power: 40 | Acc: 100%", fill=(203, 213, 225), font=hud_font_sm)
    draw.text((670, 580), "Press [Esc] to Return", fill=(148, 163, 184), font=hud_font_sm)

    canvas.save(os.path.join(SCREENSHOTS_DIR, "battle_moves.png"))
    print("Rendered battle_moves.png")

# ==========================================
# SCENE 8: Legendary Boss Battle (Mewtwo)
# ==========================================
def render_battle_boss():
    canvas = Image.new("RGBA", (960, 640), (20, 15, 35, 255))
    draw = ImageDraw.Draw(canvas)

    # Cosmic mystic arena gradient
    for y in range(450):
        c = int(20 + (y / 450) * 20)
        draw.line([(0, y), (960, y)], fill=(c, int(c * 0.7), int(c * 1.5)))

    # Platforms
    draw.ellipse([540, 190, 880, 280], fill=(60, 40, 85, 220), outline=(147, 51, 234), width=3)
    draw.ellipse([80, 370, 460, 470], fill=(45, 60, 55, 220), outline=(56, 189, 248), width=3)

    # Mewtwo Front Sprite at (610, 80)
    mewtwo_front = Image.open("assets/pokemon/front/150_MEWTWO.png").convert("RGBA").resize((210, 210), Image.NEAREST)
    canvas.paste(mewtwo_front, (600, 70), mewtwo_front)

    # Player Back Sprite: Charmander at (180, 270)
    charm_back = Image.open("assets/pokemon/back/004_CHARMANDER.png").convert("RGBA").resize((200, 200), Image.NEAREST)
    canvas.paste(charm_back, (170, 250), charm_back)

    # Boss HUD Box (Top Left)
    draw.rectangle([70, 50, 440, 150], fill=(25, 15, 40, 245), outline=(168, 85, 247), width=3)
    draw.text((90, 65), "Mewtwo [BOSS]", fill=(245, 245, 250), font=hud_font_battle)
    draw.text((310, 68), "Lv. 10", fill=(234, 179, 8), font=hud_font_sm)
    draw.rectangle([375, 65, 430, 87], fill=(168, 85, 247, 60), outline=(168, 85, 247), width=1)
    draw.text((380, 68), "PSYCHIC", fill=(216, 180, 254), font=hud_font_sm)

    # Boss HP bar
    draw.rectangle([90, 110, 420, 128], fill=(30, 20, 50), outline=(15, 10, 25), width=1)
    draw.rectangle([92, 112, 418, 126], fill=(239, 68, 68)) # Boss Health

    # Player HUD Box
    draw.rectangle([540, 320, 900, 420], fill=(15, 23, 42, 235), outline=(51, 65, 85), width=2)
    draw.text((560, 335), "Charmander", fill=(245, 245, 250), font=hud_font_battle)
    draw.text((750, 338), "Lv. 8", fill=(234, 179, 8), font=hud_font_sm)
    draw.rectangle([560, 375, 880, 390], fill=(30, 41, 59), outline=(15, 23, 42), width=1)
    draw.rectangle([562, 377, 850, 388], fill=(34, 197, 94))
    draw.text((780, 395), "HP: 24/28", fill=(203, 213, 225), font=hud_font_sm)

    # Bottom Dialog
    draw.rectangle([0, 450, 960, 640], fill=(11, 17, 23, 250), outline=(168, 85, 247), width=3)
    draw.text((50, 490), "The Forest Guardian Mewtwo unleashes Psystrike!", fill=(241, 245, 249), font=hud_font_lg)
    draw.text((50, 545), "Brace yourself for an overwhelming psionic impact!", fill=(203, 213, 225), font=hud_font)

    canvas.save(os.path.join(SCREENSHOTS_DIR, "battle_boss.png"))
    print("Rendered battle_boss.png")

# Execute all renders
render_town_square()
render_oak_lab()
render_pokemon_center()
render_whispering_woods()
render_mewtwo_encounter()
render_battle_scene()
render_battle_moves()
render_battle_boss()

# Generate hero showcase banner
hero_banner = Image.open(os.path.join(SCREENSHOTS_DIR, "town_square.png"))
hero_banner.save(os.path.join(SCREENSHOTS_DIR, "hero_showcase.png"))
print("All screenshots generated successfully.")

