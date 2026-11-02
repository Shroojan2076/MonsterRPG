# MonsterRPG — Official Website & Release Platform

This is the production-grade official website and release platform for **MonsterRPG**, an authentic retro 2D monster-catching RPG engineered in modern C++20 and SFML.

---

## 🌟 Key Features

1. **Discover:** Immersive introduction to the world, dual biomes (Oakdale Town and Whispering Woods), following partner companions, and turn-based elemental combat.
2. **Explore:** Rich documentation hub (12 comprehensive guides), interactive creature Pokédex, battle mechanics breakdown, elemental type charts, and high-resolution screenshot gallery with fullscreen Lightbox.
3. **Download:** Official release platform featuring version metadata, portable Windows x64 zip package, SHA-256 integrity checksum verification, system requirements, and step-by-step installation instructions.
4. **Release Management:** Centralized `releases.json` configuration driving version numbers, download links, file sizes, platforms, and changelogs without UI alterations.

---

## 🛠️ Tech Stack

- **Framework:** React 19 + TypeScript
- **Bundler:** Vite 6 (Static build with relative path resolution for GitHub Pages / subfolder hosting)
- **Styling:** Tailwind CSS with custom RPG color palette, retro typography, and pixel-art rendering rules
- **Icons:** Lucide React
- **Client Routing:** Hash-based deep link routing with full state persistence and 404 fallback

---

## 🚀 Development & Build

### Install Dependencies
```bash
cd website
npm install
```

### Start Development Server
```bash
npm run dev
```
Runs locally at `http://localhost:3000`.

### Build for Production
```bash
npm run build
```
Generates an optimized, static production bundle in `website/dist/`.

---

## 📦 Release Management Workflow

To publish a new game build to the website:

1. Compile the latest C++ game binary into `MonsterRPG.exe`.
2. Run the packaging script to generate the release archive:
   ```bash
   python scripts/package_release.py
   ```
   This compresses the executable, assets, and quickstart documentation into `website/public/downloads/MonsterRPG-vX.Y.Z-windows-x64.zip` and calculates its SHA-256 hash.
3. Update `website/src/data/releases.json` with the new version number, file size, SHA-256 hash, and changelog notes.
4. Rebuild the website with `npm run build`.

---

## 🌐 Deployment Options

The `website/dist/` directory is 100% static and self-contained:
- **GitHub Pages:** Deploy `dist` to `gh-pages` branch.
- **Vercel / Netlify / Cloudflare Pages:** Connect repository with root directory set to `website` and build command `npm run build`.
- **Local / USB:** You can open `dist/index.html` in any web browser directly.
