import os
from PIL import Image, ImageDraw

SPRITES_DIR = os.path.join('assets', 'sprites')
OUT_PATH = os.path.join('assets', 'world_tileset.png')

def get_sprite(name):
    p = os.path.join(SPRITES_DIR, name)
    if not os.path.exists(p):
        raise FileNotFoundError(f"Missing sprite: {p}")
    return Image.open(p).convert('RGBA')

# 256x448 atlas: 8 columns x 14 rows = 112 tiles of 32x32 px each
tileset = Image.new('RGBA', (256, 448), (0, 0, 0, 255))

def paste_tile(tid, img):
    col = tid % 8
    row = tid // 8
    tileset.paste(img, (col * 32, row * 32))

# =========================================================================
# 0. Base Ground Textures
# =========================================================================
grass = get_sprite('grassland_ground_tile_03.png') # 32x32 seamless grass
stone_tile = get_sprite('stone_paving_tile_01.png').crop((0, 0, 32, 32))
dirt_tile = get_sprite('dirt_ground_tile_01.png').crop((0, 0, 32, 32))
sandstone = get_sprite('sandstone_floor_tile_01.png').crop((0, 0, 32, 32))
checkered = get_sprite('checkered_stone_floor_tile_01.png').crop((0, 0, 32, 32))

# Pre-fill all tiles with grass
for i in range(112):
    paste_tile(i, grass)

# =========================================================================
# ROW 0: Ground & Biome Core Tiles (0..7)
# =========================================================================
paste_tile(0, grass)
paste_tile(1, stone_tile)
paste_tile(2, dirt_tile)

# Tile 3: Tall Grass (Wild monster encounter patches)
tg_patch = get_sprite('grass_patch_01.png')
tg_tile = grass.copy()
tg_tile.alpha_composite(tg_patch, (0, 32 - tg_patch.height))
paste_tile(3, tg_tile)

# Tile 4: Red Flower Bush
f_red = get_sprite('flower_bush_red_01.png')
f_red_tile = grass.copy()
f_red_tile.alpha_composite(f_red, ((32 - f_red.width) // 2, 32 - f_red.height))
paste_tile(4, f_red_tile)

# Tile 5: Yellow Flower Patch
f_yellow = get_sprite('yellow_flower_patch_01.png').resize((26, 26), Image.Resampling.LANCZOS)
f_yellow_tile = grass.copy()
f_yellow_tile.alpha_composite(f_yellow, ((32 - 26) // 2, (32 - 26) // 2 + 2))
paste_tile(5, f_yellow_tile)

# Tile 6: Horizontal Wooden Fence
h_fence_spr = get_sprite('fence_gate_rail_or_lamppost_11.png')
h_part = h_fence_spr.crop((0, 0, 32, 32))
fence_h = grass.copy()
fence_h.alpha_composite(h_part, (0, 0))
paste_tile(6, fence_h)

# Tile 7: Vertical Wooden Fence
v_fence_spr = get_sprite('fence_gate_rail_or_lamppost_13.png')
v_part = v_fence_spr.crop((0, 16, 16, 48))
fence_v = grass.copy()
fence_v.alpha_composite(v_part, ((32 - 16) // 2, 0))
paste_tile(7, fence_v)

# =========================================================================
# ROW 1: Fence Corners, Posts & Decorative Flowers (8..15)
# =========================================================================
# Tile 8: Fence Corner Top-Left
fence_tl = grass.copy()
fence_tl.alpha_composite(h_part.crop((16, 0, 32, 32)), (16, 0))
fence_tl.alpha_composite(v_part.crop((0, 16, 16, 32)), ((32 - 16) // 2, 16))
paste_tile(8, fence_tl)

# Tile 9: Fence Corner Top-Right
fence_tr = grass.copy()
fence_tr.alpha_composite(h_part.crop((0, 0, 16, 32)), (0, 0))
fence_tr.alpha_composite(v_part.crop((0, 16, 16, 32)), ((32 - 16) // 2, 16))
paste_tile(9, fence_tr)

# Tile 10: Fence Corner Bottom-Left
fence_bl = grass.copy()
fence_bl.alpha_composite(h_part.crop((16, 0, 32, 32)), (16, 0))
fence_bl.alpha_composite(v_part.crop((0, 0, 16, 16)), ((32 - 16) // 2, 0))
paste_tile(10, fence_bl)

# Tile 11: Fence Corner Bottom-Right
fence_br = grass.copy()
fence_br.alpha_composite(h_part.crop((0, 0, 16, 32)), (0, 0))
fence_br.alpha_composite(v_part.crop((0, 0, 16, 16)), ((32 - 16) // 2, 0))
paste_tile(11, fence_br)

# Tile 12: Gate End Post Top
gate_top = grass.copy()
gate_top.alpha_composite(v_fence_spr.crop((0, 32, 16, 64)), ((32 - 16) // 2, 0))
paste_tile(12, gate_top)

# Tile 13: Gate End Post Bottom
gate_bot = grass.copy()
gate_bot.alpha_composite(v_fence_spr.crop((0, 0, 16, 32)), ((32 - 16) // 2, 0))
paste_tile(13, gate_bot)

# Tile 14: Fence T-Junction
fence_t = fence_h.copy()
fence_t.alpha_composite(v_part, ((32 - 16) // 2, 0))
paste_tile(14, fence_t)

# Tile 15: Blue Flower Bush
f_blue = get_sprite('flower_bush_blue_01.png')
f_blue_tile = grass.copy()
f_blue_tile.alpha_composite(f_blue, ((32 - f_blue.width) // 2, 32 - f_blue.height))
paste_tile(15, f_blue_tile)

# =========================================================================
# ROW 2: Props, Trees & Street Lamps (16..23)
# =========================================================================
paste_tile(16, grass)

# Tile 17: Town Signpost
sign_spr = get_sprite('town_prop_machine_sign_or_furniture_12.png')
sign_tile = grass.copy()
sign_tile.alpha_composite(sign_spr, ((32 - sign_spr.width) // 2, 32 - sign_spr.height))
paste_tile(17, sign_tile)

# Tile 18: Authentic Pokeball Item Ball
ball_spr = get_sprite('small_town_prop_or_decoration_12.png')
ball_tile = grass.copy()
ball_tile.alpha_composite(ball_spr, ((32 - ball_spr.width) // 2, (32 - ball_spr.height) // 2 + 2))
paste_tile(18, ball_tile)

# Tiles 19..22: 2x2 Broadleaf Forest Tree
tree_spr = get_sprite('broadleaf_tree_01.png')
tree_canvas = Image.new('RGBA', (64, 64), (0, 0, 0, 0))
for y in range(2):
    for x in range(2):
        tree_canvas.paste(grass, (x * 32, y * 32))
tree_scaled = tree_spr.resize((60, 64), Image.Resampling.LANCZOS)
tree_canvas.alpha_composite(tree_scaled, ((64 - 60) // 2, 0))

paste_tile(19, tree_canvas.crop((0, 0, 32, 32)))
paste_tile(20, tree_canvas.crop((32, 0, 64, 32)))
paste_tile(21, tree_canvas.crop((0, 32, 32, 64)))
paste_tile(22, tree_canvas.crop((32, 32, 64, 64)))

# Tile 23: Street Lamp
lamp_spr = get_sprite('street_lamp_01.png')
lamp_scaled = lamp_spr.resize((24, 32), Image.Resampling.LANCZOS)
lamp_tile = stone_tile.copy()
lamp_tile.alpha_composite(lamp_scaled, ((32 - 24) // 2, 0))
paste_tile(23, lamp_tile)

# =========================================================================
# BUILDING 1: Prof. Oak's Research Lab Exterior (Tiles 24..48, 5x5)
# =========================================================================
bh_spr = get_sprite('blue_roof_house_01.png')
bh_canvas = Image.new('RGBA', (160, 160))
for y in range(5):
    for x in range(5):
        bh_canvas.paste(grass, (x * 32, y * 32))
bx = (160 - bh_spr.width) // 2
by = 160 - bh_spr.height
bh_canvas.alpha_composite(bh_spr, (bx, by))

for r in range(5):
    for c in range(5):
        tid = 24 + (r * 5 + c)
        cell = bh_canvas.crop((c * 32, r * 32, (c + 1) * 32, (r + 1) * 32))
        paste_tile(tid, cell)

# =========================================================================
# BUILDING 2: Health Center / Clinic Exterior (Tiles 49..73, 5x5)
# =========================================================================
pc_spr = get_sprite('pokemon_center_building_01.png')
pc_canvas = Image.new('RGBA', (160, 160))
for y in range(5):
    for x in range(5):
        pc_canvas.paste(grass, (x * 32, y * 32))
px = (160 - pc_spr.width) // 2
py = 160 - pc_spr.height
pc_canvas.alpha_composite(pc_spr, (px, py))

for r in range(5):
    for c in range(5):
        tid = 49 + (r * 5 + c)
        cell = pc_canvas.crop((c * 32, r * 32, (c + 1) * 32, (r + 1) * 32))
        paste_tile(tid, cell)

# =========================================================================
# ROW 9: Room Side & Bottom Walls (74..79)
# =========================================================================
# Tile 74: Lab Side Wall Left
lab_sw_l = Image.new('RGBA', (32, 32), (115, 95, 68, 255))
d = ImageDraw.Draw(lab_sw_l)
d.rectangle([(0, 0), (6, 31)], fill=(75, 60, 42, 255))
d.line([(6, 0), (6, 31)], fill=(145, 120, 88, 255))
d.rectangle([(26, 0), (31, 31)], fill=(90, 72, 50, 255))
paste_tile(74, lab_sw_l)

# Tile 75: Lab Side Wall Right
lab_sw_r = Image.new('RGBA', (32, 32), (115, 95, 68, 255))
d = ImageDraw.Draw(lab_sw_r)
d.rectangle([(25, 0), (31, 31)], fill=(75, 60, 42, 255))
d.line([(25, 0), (25, 31)], fill=(145, 120, 88, 255))
d.rectangle([(0, 0), (5, 31)], fill=(90, 72, 50, 255))
paste_tile(75, lab_sw_r)

# Tile 76: Clinic Side Wall Left
cl_sw_l = Image.new('RGBA', (32, 32), (218, 230, 233, 255))
d = ImageDraw.Draw(cl_sw_l)
d.rectangle([(0, 0), (6, 31)], fill=(152, 184, 200, 255))
d.line([(6, 0), (6, 31)], fill=(245, 250, 252, 255))
d.rectangle([(26, 0), (31, 31)], fill=(195, 210, 215, 255))
paste_tile(76, cl_sw_l)

# Tile 77: Clinic Side Wall Right
cl_sw_r = Image.new('RGBA', (32, 32), (218, 230, 233, 255))
d = ImageDraw.Draw(cl_sw_r)
d.rectangle([(25, 0), (31, 31)], fill=(152, 184, 200, 255))
d.line([(25, 0), (25, 31)], fill=(245, 250, 252, 255))
d.rectangle([(0, 0), (5, 31)], fill=(195, 210, 215, 255))
paste_tile(77, cl_sw_r)

# Tile 78: Lab Bottom Wall
lab_bw = Image.new('RGBA', (32, 32), (75, 60, 42, 255))
d = ImageDraw.Draw(lab_bw)
d.line([(0, 0), (31, 0)], fill=(145, 120, 88, 255))
d.rectangle([(0, 22), (31, 31)], fill=(45, 35, 25, 255))
paste_tile(78, lab_bw)

# Tile 79: Clinic Bottom Wall
cl_bw = Image.new('RGBA', (32, 32), (160, 188, 198, 255))
d = ImageDraw.Draw(cl_bw)
d.line([(0, 0), (31, 0)], fill=(240, 248, 250, 255))
d.rectangle([(0, 22), (31, 31)], fill=(100, 128, 138, 255))
paste_tile(79, cl_bw)

# =========================================================================
# ROW 10: Interior Floors, Walls & Core Architecture (80..87)
# =========================================================================
# Tile 80: Void Border
void_tile = Image.new('RGBA', (32, 32), (18, 22, 30, 255))
paste_tile(80, void_tile)

# Tile 81: Lab Sandstone Floor
paste_tile(81, sandstone)

# Tile 82: Clinic Checkered Floor
paste_tile(82, checkered)

# Tile 83: Clinic Red Carpet Runner
carpet_tile = checkered.copy()
d_carp = ImageDraw.Draw(carpet_tile)
d_carp.rectangle([(2, 0), (29, 31)], fill=(178, 38, 38, 255))
d_carp.line([(2, 0), (2, 31)], fill=(225, 180, 50, 255))
d_carp.line([(29, 0), (29, 31)], fill=(225, 180, 50, 255))
d_carp.line([(5, 0), (26, 0)], fill=(195, 50, 50, 255))
d_carp.line([(5, 16), (26, 16)], fill=(160, 30, 30, 255))
paste_tile(83, carpet_tile)

# Tile 84: Lab Upper Wall
lab_wall_upper = Image.new('RGBA', (32, 32), (115, 95, 68, 255))
d_lwu = ImageDraw.Draw(lab_wall_upper)
d_lwu.rectangle([(0, 0), (31, 3)], fill=(85, 68, 48, 255))
d_lwu.line([(0, 3), (31, 3)], fill=(140, 118, 86, 255))
d_lwu.rectangle([(2, 7), (29, 31)], fill=(125, 104, 75, 255))
d_lwu.rectangle([(2, 7), (29, 31)], outline=(95, 78, 55, 255))
paste_tile(84, lab_wall_upper)

# Tile 85: Lab Lower Wall (Baseboard)
lab_wall_lower = Image.new('RGBA', (32, 32), (115, 95, 68, 255))
d_lwl = ImageDraw.Draw(lab_wall_lower)
d_lwl.rectangle([(2, 0), (29, 20)], fill=(125, 104, 75, 255))
d_lwl.rectangle([(2, 0), (29, 20)], outline=(95, 78, 55, 255))
d_lwl.rectangle([(0, 22), (31, 31)], fill=(75, 60, 42, 255))
d_lwl.line([(0, 22), (31, 22)], fill=(145, 120, 88, 255))
paste_tile(85, lab_wall_lower)

# Tile 86: Clinic Upper Wall
clinic_wall_upper = Image.new('RGBA', (32, 32), (218, 230, 233, 255))
d_cwu = ImageDraw.Draw(clinic_wall_upper)
d_cwu.rectangle([(0, 0), (31, 4)], fill=(152, 184, 200, 255))
d_cwu.line([(0, 4), (31, 4)], fill=(240, 248, 250, 255))
d_cwu.rectangle([(2, 8), (29, 31)], fill=(228, 238, 240, 255))
d_cwu.rectangle([(2, 8), (29, 31)], outline=(190, 210, 216, 255))
paste_tile(86, clinic_wall_upper)

# Tile 87: Clinic Lower Wall (Baseboard)
clinic_wall_lower = Image.new('RGBA', (32, 32), (218, 230, 233, 255))
d_cwl = ImageDraw.Draw(clinic_wall_lower)
d_cwl.rectangle([(2, 0), (29, 20)], fill=(228, 238, 240, 255))
d_cwl.rectangle([(2, 0), (29, 20)], outline=(190, 210, 216, 255))
d_cwl.rectangle([(0, 22), (31, 31)], fill=(160, 188, 198, 255))
d_cwl.line([(0, 22), (31, 22)], fill=(240, 248, 250, 255))
paste_tile(87, clinic_wall_lower)

# =========================================================================
# ROW 11: Oak's Lab Scientific Furniture (88..95)
# =========================================================================
bs_raw = get_sprite('door_wall_furniture_or_building_piece_15.png')
# Tile 88: Bookshelf Top A
bs_top = lab_wall_upper.copy()
bs_top.alpha_composite(bs_raw.crop((0, 0, 32, 32)), (0, 0))
paste_tile(88, bs_top)

# Tile 89: Bookshelf Bottom A
bs_bot = sandstone.copy()
bs_bot.alpha_composite(bs_raw.crop((0, 32, 32, 64)), (0, 0))
paste_tile(89, bs_bot)

# Tile 90: Whiteboard Top
wb_top = lab_wall_upper.copy()
d_wbt = ImageDraw.Draw(wb_top)
d_wbt.rectangle([(2, 6), (29, 31)], fill=(245, 245, 248, 255))
d_wbt.rectangle([(2, 6), (29, 31)], outline=(70, 75, 80, 255))
d_wbt.line([(6, 12), (18, 12)], fill=(40, 80, 180, 255))
d_wbt.line([(18, 12), (24, 18)], fill=(40, 80, 180, 255))
d_wbt.ellipse([(8, 18), (14, 24)], outline=(200, 40, 40, 255))
d_wbt.line([(8, 21), (14, 21)], fill=(200, 40, 40, 255))
d_wbt.line([(18, 22), (26, 22)], fill=(60, 60, 60, 255))
paste_tile(90, wb_top)

# Tile 91: Whiteboard Bottom
wb_bot = lab_wall_lower.copy()
d_wbb = ImageDraw.Draw(wb_bot)
d_wbb.rectangle([(2, 0), (29, 18)], fill=(245, 245, 248, 255))
d_wbb.rectangle([(2, 0), (29, 18)], outline=(70, 75, 80, 255))
d_wbb.rectangle([(6, 17), (25, 20)], fill=(120, 125, 130, 255))
d_wbb.rectangle([(8, 16), (12, 17)], fill=(40, 80, 180, 255))
d_wbb.rectangle([(14, 16), (18, 17)], fill=(200, 40, 40, 255))
paste_tile(91, wb_bot)

# Tile 92: Oak's Research Computer Terminal
comp_spr = get_sprite('town_prop_machine_sign_or_furniture_20.png')
comp_tile = sandstone.copy()
comp_tile.alpha_composite(comp_spr, ((32 - comp_spr.width) // 2, (32 - comp_spr.height) // 2))
paste_tile(92, comp_tile)

# Tile 93: Starter Pokéballs Tray Table
starter_tray_tile = sandstone.copy()
d_st = ImageDraw.Draw(starter_tray_tile)
d_st.rectangle([(2, 8), (29, 28)], fill=(195, 200, 205, 255))
d_st.rectangle([(2, 8), (29, 28)], outline=(120, 125, 130, 255))
d_st.rectangle([(4, 10), (27, 26)], fill=(165, 170, 178, 255))
mini_ball = ball_spr.resize((9, 9), Image.Resampling.LANCZOS)
starter_tray_tile.alpha_composite(mini_ball, (5, 13))
starter_tray_tile.alpha_composite(mini_ball, (12, 13))
starter_tray_tile.alpha_composite(mini_ball, (19, 13))
paste_tile(93, starter_tray_tile)

# Tile 94: Lab Research Desk Left
desk_l = sandstone.copy()
d_dl = ImageDraw.Draw(desk_l)
d_dl.rectangle([(0, 6), (31, 28)], fill=(145, 105, 68, 255))
d_dl.rectangle([(0, 6), (31, 28)], outline=(85, 60, 38, 255))
d_dl.line([(0, 6), (31, 6)], fill=(175, 135, 95, 255))
d_dl.rectangle([(4, 10), (16, 22)], fill=(240, 240, 235, 255))
d_dl.rectangle([(4, 10), (16, 22)], outline=(180, 180, 170, 255))
paste_tile(94, desk_l)

# Tile 95: Lab Research Desk Center
desk_c = sandstone.copy()
d_dc = ImageDraw.Draw(desk_c)
d_dc.rectangle([(0, 6), (31, 28)], fill=(145, 105, 68, 255))
d_dc.rectangle([(0, 6), (31, 28)], outline=(85, 60, 38, 255))
d_dc.line([(0, 6), (31, 6)], fill=(175, 135, 95, 255))
d_dc.rectangle([(6, 11), (25, 23)], fill=(220, 225, 230, 255))
d_dc.line([(15, 11), (15, 23)], fill=(150, 155, 160, 255))
d_dc.line([(8, 14), (13, 14)], fill=(50, 50, 60, 255))
d_dc.line([(8, 17), (13, 17)], fill=(50, 50, 60, 255))
d_dc.line([(17, 14), (23, 14)], fill=(50, 50, 60, 255))
d_dc.line([(17, 17), (23, 17)], fill=(50, 50, 60, 255))
paste_tile(95, desk_c)

# =========================================================================
# ROW 12: Desk Right, Mats, Counters & Clinic Props (96..103)
# =========================================================================
# Tile 96: Lab Research Desk Right
desk_r = sandstone.copy()
d_dr = ImageDraw.Draw(desk_r)
d_dr.rectangle([(0, 6), (31, 28)], fill=(145, 105, 68, 255))
d_dr.rectangle([(0, 6), (31, 28)], outline=(85, 60, 38, 255))
d_dr.line([(0, 6), (31, 6)], fill=(175, 135, 95, 255))
d_dr.ellipse([(18, 11), (25, 18)], fill=(60, 90, 140, 255))
d_dr.line([(22, 9), (22, 14)], fill=(30, 30, 30, 255))
paste_tile(96, desk_r)

# Tile 97: Lab Wooden Exit Mat
door_mat_spr = get_sprite('door_wall_furniture_or_building_piece_19.png')
lab_exit_mat = sandstone.copy()
lab_exit_mat.alpha_composite(door_mat_spr, (0, 16))
paste_tile(97, lab_exit_mat)

# Tile 98: Clinic Counter Left
counter_spr = get_sprite('town_prop_machine_sign_or_furniture_02.png')
counter_l = checkered.copy()
counter_l.alpha_composite(counter_spr.crop((0, 0, 32, 24)), (0, 8))
paste_tile(98, counter_l)

# Tile 99: Clinic Counter Right
counter_r = checkered.copy()
counter_r.alpha_composite(counter_spr.crop((32, 0, 64, 24)), (0, 8))
paste_tile(99, counter_r)

# Tile 100: Clinic Counter Center
counter_c = checkered.copy()
mid_slice = counter_spr.crop((24, 0, 40, 24)).resize((32, 24), Image.Resampling.NEAREST)
counter_c.alpha_composite(mid_slice, (0, 8))
paste_tile(100, counter_c)

# Tile 101: Wall-Mounted Healing Machine
heal_spr = get_sprite('small_statue_or_machine_01.png')
heal_tile = clinic_wall_lower.copy()
heal_tile.alpha_composite(heal_spr, ((32 - heal_spr.width) // 2, 0))
paste_tile(101, heal_tile)

# Tile 102: PC Storage Terminal
pc_spr = get_sprite('town_prop_machine_sign_or_furniture_21.png')
pc_tile = checkered.copy()
pc_tile.alpha_composite(pc_spr, ((32 - pc_spr.width) // 2, (32 - pc_spr.height) // 2))
paste_tile(102, pc_tile)

# Tile 103: Red & Blue Vending Machines
vending_spr = get_sprite('red_blue_vending_machines_01.png')
vending_tile = checkered.copy()
vending_tile.alpha_composite(vending_spr, (0, 32 - vending_spr.height))
paste_tile(103, vending_tile)

# =========================================================================
# ROW 13: Benches, Plants, Welcome Mat, Bookshelf B (104..111)
# =========================================================================
# Tile 104: Waiting Bench Left
bench_spr = get_sprite('wooden_bench_01.png')
bench_l = checkered.copy()
bench_l.alpha_composite(bench_spr.crop((0, 0, 31, 23)), (1, 32 - 23))
paste_tile(104, bench_l)

# Tile 105: Waiting Bench Right
bench_r = checkered.copy()
bench_r.alpha_composite(bench_spr.crop((31, 0, 62, 23)), (0, 32 - 23))
paste_tile(105, bench_r)

# Tile 106: Indoor Potted Plant (Lab)
plant_spr = get_sprite('planter_bed_flower_or_bench_08.png')
plant_tile_lab = sandstone.copy()
plant_tile_lab.alpha_composite(plant_spr, ((32 - plant_spr.width) // 2, 0))
paste_tile(106, plant_tile_lab)

# Tile 107: Indoor Potted Plant (Clinic)
plant_tile_clinic = checkered.copy()
plant_tile_clinic.alpha_composite(plant_spr, ((32 - plant_spr.width) // 2, 0))
paste_tile(107, plant_tile_clinic)

# Tile 108: Clinic Red Exit Welcome Mat
clinic_exit_mat = checkered.copy()
d_cem = ImageDraw.Draw(clinic_exit_mat)
d_cem.rectangle([(2, 10), (29, 29)], fill=(178, 38, 38, 255))
d_cem.rectangle([(2, 10), (29, 29)], outline=(225, 180, 50, 255))
d_cem.text((7, 14), "EXIT", fill=(255, 255, 255, 255))
paste_tile(108, clinic_exit_mat)

# Tile 109: Bookshelf Top B
bs_raw_b = get_sprite('door_wall_furniture_or_building_piece_20.png')
bs_top_b = lab_wall_upper.copy()
bs_top_b.alpha_composite(bs_raw_b.crop((0, 0, 32, 32)), (0, 0))
paste_tile(109, bs_top_b)

# Tile 110: Bookshelf Bottom B
bs_bot_b = sandstone.copy()
bs_bot_b.alpha_composite(bs_raw_b.crop((0, 32, 32, 64)), (0, 0))
paste_tile(110, bs_bot_b)

# Tile 111: Laboratory Microscope / Specimen Table
specimen_tile = sandstone.copy()
d_sp = ImageDraw.Draw(specimen_tile)
d_sp.rectangle([(3, 8), (28, 27)], fill=(120, 130, 140, 255))
d_sp.rectangle([(3, 8), (28, 27)], outline=(70, 75, 80, 255))
d_sp.rectangle([(7, 11), (15, 21)], fill=(40, 45, 50, 255))
d_sp.line([(11, 7), (11, 14)], fill=(180, 185, 190, 255))
d_sp.ellipse([(19, 12), (25, 18)], fill=(60, 190, 220, 200))
paste_tile(111, specimen_tile)

# Save final world tileset
tileset.save(OUT_PATH)
print(f"Successfully generated {OUT_PATH} (256x448, 112 tiles) with authentic labeled sprites!")
