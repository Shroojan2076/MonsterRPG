import os
import zipfile
import hashlib

os.makedirs("website/public/downloads", exist_ok=True)
zip_path = "website/public/downloads/MonsterRPG-v1.0.0-windows-x64.zip"

print("Packaging release zip...")
with zipfile.ZipFile(zip_path, 'w', zipfile.ZIP_DEFLATED) as zipf:
    # Add MonsterRPG.exe
    if os.path.exists("MonsterRPG.exe"):
        zipf.write("MonsterRPG.exe", "MonsterRPG.exe")
    
    # Add assets directory
    for root, dirs, files in os.walk("assets"):
        for file in files:
            file_path = os.path.join(root, file)
            # Avoid packing redundant large zips inside assets
            if not file.endswith(".zip"):
                arcname = os.path.relpath(file_path, ".")
                zipf.write(file_path, arcname)
                
    # Add README.txt
    readme_content = """=====================================================
 MonsterRPG - Official Windows Release (v1.0.0)
 2D Retro Adventure in Modern C++20 and SFML
=====================================================

QUICKSTART:
1. Extract all files to a folder on your PC.
2. Ensure the "assets" folder is in the same directory as "MonsterRPG.exe".
3. Double-click "MonsterRPG.exe" to launch the game!

CONTROLS:
- [W, A, S, D] or Arrow Keys : Move (Tap to turn without stepping)
- [Left Shift] (Hold)        : Run / Sprint (120 px/sec)
- [E] or [Space]             : Talk / Interact with NPCs & Props
- [1, 2, 3, 4]               : Select Battle Commands and Moves
- [Esc]                      : Back / Cancel

STARTING YOUR JOURNEY:
- You begin in Oakdale Town Square.
- Walk North-West to enter Professor Oak's Research Lab.
- Speak with Prof. Oak behind the research desk to receive your starter Charmander!
- Once you receive your starter, your partner Pokémon will follow you everywhere.
- Head East into Whispering Woods to explore, catch wild monsters, and face the Guardian!

WEBSITE & DOCS:
https://github.com/MonsterRPG
"""
    zipf.writestr("README.txt", readme_content)

file_size = os.path.getsize(zip_path)
size_mb = file_size / (1024 * 1024)

# Calculate SHA256
sha256_hash = hashlib.sha256()
with open(zip_path, "rb") as f:
    for byte_block in iter(lambda: f.read(65536), b""):
        sha256_hash.update(byte_block)
sha256 = sha256_hash.hexdigest()

print(f"Packaged {zip_path}")
print(f"Size: {size_mb:.2f} MB ({file_size} bytes)")
print(f"SHA-256: {sha256}")

