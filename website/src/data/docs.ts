export interface DocArticle {
  id: string;
  slug: string;
  title: string;
  category: string;
  readTime: string;
  summary: string;
  content: string;
}

export const DOC_CATEGORIES = [
  "Getting Started",
  "Gameplay & World",
  "Combat & Monsters",
  "Items & Characters",
  "Reference & Support"
];

export const DOCS: DocArticle[] = [
  {
    id: "getting-started",
    slug: "getting-started",
    title: "Getting Started with MonsterRPG",
    category: "Getting Started",
    readTime: "3 min read",
    summary: "Welcome to MonsterRPG! Learn the core premise, starting steps, and how to embark on your journey in Oakdale Town.",
    content: `
### Welcome to Oakdale Town

**MonsterRPG** is a retro-inspired 2D monster-catching role-playing game developed in modern C++20 and powered by the Simple and Fast Multimedia Library (SFML 3.0.2). You step into the shoes of a young adventurer arriving in the peaceful settlement of Oakdale Town, on the threshold of the mysterious Whispering Woods.

#### Your First Steps

1. **Meet Professor Oak:**
   From your starting location in Oakdale Town Square (Grid \`10, 13\`), head north-west towards the building with the **Blue Roof**. Step directly on the door tile (\`6, 7\`) to enter **Prof. Oak's Research Lab**.
   
2. **Receive Your Starter Partner:**
   Walk up to Professor Oak's research table and press **\`[E]\`** or **\`[Space]\`** to speak with him. He will introduce you to the region and entrust you with a brave **Charmander (Fire-type)** along with starter Potions and Poké Balls.

3. **Explore with Your Follower:**
   As soon as you receive your starter, your partner Pokémon emerges to travel by your side! It will dynamically follow your footsteps everywhere you walk or run. You can turn towards it at any time and press **\`[E]\`** to check its mood and condition.

4. **Prepare for the Woods:**
   Walk south to the building with the **Red Roof** to visit the **Oakdale Pokémon Center**. Nurse Joy and her assistant Clefairy are stationed there to restore your team's health free of charge whenever needed.
`
  },
  {
    id: "installation-guide",
    slug: "installation-guide",
    title: "Installation & Setup Guide",
    category: "Getting Started",
    readTime: "4 min read",
    summary: "Step-by-step instructions for installing and running MonsterRPG on Windows PCs.",
    content: `
### Installation Guide

MonsterRPG is distributed as a self-contained portable Windows package. No system registry modifications or installer wizards are required.

#### Step 1: Download the Release Archive
Navigate to the [Official Download Page](#/download) and download the latest release package (\`MonsterRPG-v1.0.0-windows-x64.zip\`, approximately 4.34 MB).

#### Step 2: Extract the Files
1. Locate the downloaded \`.zip\` file in your Downloads folder.
2. Right-click the archive and select **Extract All...** (or use 7-Zip / WinRAR).
3. Choose your desired destination folder (e.g., \`C:\\Games\\MonsterRPG\` or your Desktop).

#### Step 3: Verify Folder Structure
Ensure that the \`assets\` directory is located directly alongside \`MonsterRPG.exe\`:
\`\`\`
MonsterRPG/
├── MonsterRPG.exe         # Game executable
├── README.txt             # Quickstart guide
└── assets/                # Core textures, tilesets, fonts & audio
    ├── world_tileset.png
    ├── font.ttf
    ├── pokemon/
    │   ├── front/
    │   └── back/
    ├── overworld/
    └── characters/
\`\`\`

#### Step 4: Launch the Game
Double-click \`MonsterRPG.exe\` to launch! The game starts in an optimized 960x640 window with crisp nearest-neighbor retro scaling.
`
  },
  {
    id: "system-requirements",
    slug: "system-requirements",
    title: "System Requirements",
    category: "Getting Started",
    readTime: "2 min read",
    summary: "Hardware and software specifications for running MonsterRPG smoothly.",
    content: `
### Hardware & Software Specifications

MonsterRPG is engineered with a custom lightweight C++20 engine that renders with hardware acceleration via SFML. It runs comfortably on modern Windows computers as well as older laptops.

| Specification | Minimum Requirement | Recommended Specification |
| :--- | :--- | :--- |
| **Operating System** | Windows 10 (64-bit) | Windows 11 (64-bit) |
| **Processor** | Dual-core 2.0 GHz Intel or AMD | Quad-core 2.5 GHz or higher |
| **Memory (RAM)** | 2 GB RAM | 4 GB RAM |
| **Graphics** | DirectX 11 / OpenGL 3.3 compatible (512 MB VRAM) | Dedicated GPU (Intel Iris Xe, NVIDIA GeForce, AMD Radeon) |
| **Storage** | 25 MB available storage space | 50 MB available storage space |
| **Audio** | Standard Windows-compatible sound device | Stereo headphones or speakers |
| **Input** | Standard Keyboard | Standard Keyboard |
`
  },
  {
    id: "controls",
    slug: "controls",
    title: "Controls & Keybindings",
    category: "Gameplay & World",
    readTime: "3 min read",
    summary: "Complete reference for exploration controls, running shoes, and battle shortcuts.",
    content: `
### Comprehensive Controls Reference

MonsterRPG features an authentic grid-based movement system with dedicated tap-to-turn mechanics and running shoes sprint functionality.

#### Overworld Exploration Controls

| Keybinding | Action | Description |
| :--- | :--- | :--- |
| **\`W\`** / **\`Up Arrow\`** | Move Up / Turn North | Steps one tile North. Quick tap turns direction in place. |
| **\`S\`** / **\`Down Arrow\`** | Move Down / Turn South | Steps one tile South. Quick tap turns direction in place. |
| **\`A\`** / **\`Left Arrow\`** | Move Left / Turn West | Steps one tile West. Quick tap turns direction in place. |
| **\`D\`** / **\`Right Arrow\`** | Move Right / Turn East | Steps one tile East. Quick tap turns direction in place. |
| **\`Left Shift\`** (Hold) | **Sprint / Run** | Increases movement speed from 55 px/sec to **120 px/sec** and toggles running sprites. |
| **\`E\`** / **\`Space\`** / **\`Enter\`** | **Interact / Talk** | Interacts with NPCs, signposts, item balls, or your following partner Pokémon. |

#### Turn-Based Battle Controls

| Keybinding | Action | Description |
| :--- | :--- | :--- |
| **\`1\`** | **FIGHT** | Opens your monster's move selection menu. |
| **\`2\`** | **BAG** | Uses an inventory item (e.g. Potion to heal active monster). |
| **\`3\`** | **CATCH** | Throws a Poké Ball to capture weakened wild monsters. |
| **\`4\`** | **RUN** | Attempts to safely escape from wild encounters. |
| **\`1\` - \`4\`** (In Move Menu) | **Select Move** | Executes the designated elemental move during combat. |
| **\`Esc\`** | **Back / Cancel** | Returns from move selection back to the main battle command menu. |
`
  },
  {
    id: "gameplay-guide",
    slug: "gameplay-guide",
    title: "Gameplay & World Guide",
    category: "Gameplay & World",
    readTime: "5 min read",
    summary: "Explore the dual biomes of Oakdale Town and Whispering Woods, indoor buildings, and partner companion mechanics.",
    content: `
### World Exploration & Mechanics

The world of MonsterRPG is structured as a continuous dual-biome region connected by dynamic warp points into building interiors.

#### 1. Oakdale Town (West Biome)
- **Town Square:** Spans columns 2 to 19, rows 3 to 24. Paved with cobblestone walkways, antique wrought-iron street lamps, and colorful flower beds.
- **Cedric & Meowth:** Located at Grid \`(13, 11)\` and \`(12, 11)\`. Cedric provides guidance on elemental type advantages, while Meowth playfully taps its shiny gold coin.
- **Professor Oak's Lab (Blue Roof):** Located at Grid \`(6, 7)\`. Step onto the doorway mat to transition into the research facility.
- **Oakdale Pokémon Center (Red Roof):** Located at Grid \`(6, 18)\`. Contains complete party healing services and computer storage terminals.

#### 2. Whispering Woods (East Biome)
- **Forest Trail:** Extending east from column 21 across column 34.
- **Tall Grass Patches:** Shaded dark grass patches. Stepping in tall grass triggers an **18% encounter chance** per step.
- **Secluded Pond & Grove:** South trail leading to rows 20-22 where Poliwags splash and a sleeping Snorlax rests.
- **Guardian Clearing Sanctuary:** North trail branching into columns 34-39, row 5. The home of the legendary Mewtwo.

#### 3. Building Interior Transitions
Entering or leaving a building initiates an alpha-interpolated fade-to-black transition (650 alpha units/sec). The player and their follower partner are automatically aligned to the interior entry mat facing forward.

#### 4. Following Partner Pokémon System
Whenever you have an active monster in your party, it travels behind you:
- Tracks previous grid coordinates tile-by-tile.
- Smoothly interpolates walking and running speeds to maintain formation.
- Displays responsive dialogues when interacted with, dynamically reflecting whether your partner is bursting with energy, determined, or needing healing.
`
  },
  {
    id: "monster-guide",
    slug: "monster-guide",
    title: "Monster Guide & Pokédex",
    category: "Combat & Monsters",
    readTime: "6 min read",
    summary: "Detailed breakdown of starters, wild forest creatures, companions, and the legendary boss.",
    content: `
### Complete Monster Roster

Every monster in MonsterRPG features unique base stats, elemental affinities, movesets, and authentic front, back, and overworld sprites.

#### Starter Pokémon

| ID | Name | Type | Base HP | Atk | Def | Spd | Starting Moves |
| :--- | :--- | :--- | :---: | :---: | :---: | :---: | :--- |
| **004** | **Charmander** | Fire | 20 | 12 | 10 | 14 | Scratch (40), Ember (40) |
| **007** | **Squirtle** | Water | 22 | 10 | 13 | 11 | Tackle (40), Water Gun (40) |
| **001** | **Bulbasaur** | Grass | 23 | 11 | 11 | 10 | Tackle (40), Vine Whip (45) |

#### Wild Forest Encounters

| ID | Name | Type | Base HP | Atk | Def | Spd | Encounter Spot |
| :--- | :--- | :--- | :---: | :---: | :---: | :---: | :--- |
| **025** | **Pikachu** | Electric | 18 | 13 | 9 | 16 | Tall grass clearing at Grid \`(25, 7)\` |
| **016** | **Pidgey** | Normal | 18 | 10 | 9 | 12 | Woods trail canopy at Grid \`(31, 15)\` |
| **054** | **Psyduck** | Water | 21 | 11 | 10 | 11 | Pond clearing at Grid \`(26, 21)\` |
| **060** | **Poliwag** | Water | 19 | 10 | 9 | 15 | Stream shore at Grid \`(34, 19)\` |
| **143** | **Snorlax** | Normal | 80 | 20 | 15 | 6 | Peaceful grove at Grid \`(36, 12)\` |

#### Legendary Guardian Boss

| ID | Name | Type | Base HP | Atk | Def | Spd | Signature Moves |
| :--- | :--- | :--- | :---: | :---: | :---: | :---: | :--- |
| **150** | **Mewtwo** | Psychic | 65 | 25 | 18 | 22 | Psychic (90), Psystrike (100) |
`
  },
  {
    id: "element-types",
    slug: "element-types",
    title: "Element Types & Type Chart",
    category: "Combat & Monsters",
    readTime: "4 min read",
    summary: "Master elemental affinities and type effectiveness multipliers in combat.",
    content: `
### Elemental Affinity System

In MonsterRPG, tactical superiority depends on exploiting elemental affinities. Attacking with a super-effective move deals **2.0x damage**, while attacking with a resisted move deals **0.5x damage**.

#### Elemental Type Effectiveness Matrix

| Attacker \\ Defender | Normal | Fire | Water | Grass | Electric | Psychic |
| :--- | :---: | :---: | :---: | :---: | :---: | :---: |
| **Normal** | 1.0x | 1.0x | 1.0x | 1.0x | 1.0x | 1.0x |
| **Fire** | 1.0x | 0.5x | **0.5x** | **2.0x** | 1.0x | 1.0x |
| **Water** | 1.0x | **2.0x** | 0.5x | **0.5x** | 1.0x | 1.0x |
| **Grass** | 1.0x | **0.5x** | **2.0x** | 0.5x | 1.0x | 1.0x |
| **Electric** | 1.0x | 1.0x | **2.0x** | **0.5x** | 0.5x | 1.0x |
| **Psychic** | 1.0x | 1.0x | 1.0x | 1.0x | 1.0x | 0.5x |

#### Core Elemental Axioms
- 🔥 **Fire scorches Grass** (\`2.0x\`), but is doused by **Water** (\`0.5x\`).
- 💧 **Water extinguishes Fire** (\`2.0x\`), but is absorbed by **Grass** (\`0.5x\`).
- 🌿 **Grass absorbs Water** (\`2.0x\`), but burns against **Fire** (\`0.5x\`).
- ⚡ **Electric conducts through Water** (\`2.0x\`), but grounds out against **Grass** (\`0.5x\`).
`
  },
  {
    id: "battle-mechanics",
    slug: "battle-mechanics",
    title: "Battle Mechanics & Formulas",
    category: "Combat & Monsters",
    readTime: "5 min read",
    summary: "In-depth guide to turn calculation, damage formulas, capture probability, and visual FX.",
    content: `
### Battle Engine Mechanics

Battles in MonsterRPG use an authentic turn-based state machine powered by \`BattleState\`.

#### Turn Resolution & Initiative
Speed (\`spd\`) determines turn order:
1. When you select **\`[1] FIGHT\`** and choose an attack, the monster with the higher speed stat acts first.
2. If speeds are tied, a deterministic coin flip decides the starting attacker.
3. If an opponent faints from the first strike, the round ends immediately without a counter-attack.

#### Damage Calculation Formula
Damage inflicted during combat follows this formula:
\`\`\`
BaseDamage = ((2 * Level / 5 + 2) * MovePower * (Attack / Defense)) / 50 + 2
FinalDamage = BaseDamage * TypeMultiplier * Variance(0.85 to 1.00)
\`\`\`

#### Capture Mechanics
Pressing **\`[3] CATCH\`** tosses a Poké Ball from your inventory:
- Wild monsters cannot be captured if your inventory has 0 Poké Balls.
- Bosses (such as Mewtwo) possess innate legendary resolve and cannot be captured with standard Poké Balls.
- Capture rate improves as the wild monster's HP decreases:
\`\`\`
CaptureChance = (1.0 - (CurrentHP / MaxHP)) * 0.85 + 0.15
\`\`\`
Weakening a wild monster into the red zone guarantees the highest capture probability!

#### Combat Visual FX
- **Lunge Animation:** Attacking monsters lunge forward 35 pixels toward their target and snap back.
- **Shake & Flash:** Defending monsters oscillate side-to-side while flashing red upon taking damage.
- **Floating Numbers:** Damage counters float upward and fade out smoothly.
- **Parabolic Throw:** Capture balls follow a bezier arc followed by a 3-stage platform wobble and starburst capture celebration.
`
  },
  {
    id: "items-and-inventory",
    slug: "items-and-inventory",
    title: "Items & Inventory Management",
    category: "Items & Characters",
    readTime: "3 min read",
    summary: "Reference guide for potions, capture balls, and hidden item pickups.",
    content: `
### Consumable Items & Bag Storage

Players manage their consumables through the inventory system, accessible both during exploration and in combat.

#### Available Items

| Item Name | Category | In-Game Effect | Starting Quantity |
| :--- | :--- | :--- | :---: |
| **Potion** | Healing | Restores **20 HP** to the active monster in combat or out of combat. | 3 |
| **Super Potion** | Healing | Restores **50 HP** to a wounded monster. | Found in woods |
| **Capture Ball** | Tool | Thrown during wild combat to capture weakened monsters. | 5 |

#### Finding Hidden Item Balls
Explorers venturing into Whispering Woods should look for glowing red-and-white item balls tucked in secluded corners. An item ball is hidden at Grid \`(38, 22)\` in the southern grove. Walk up to it and press **\`[E]\`** to collect valuable supplies!
`
  },
  {
    id: "npcs-and-interactions",
    slug: "npcs-and-interactions",
    title: "NPCs & World Interactions",
    category: "Items & Characters",
    readTime: "4 min read",
    summary: "Meet the residents of Oakdale Town and discover how across-counter interactions function.",
    content: `
### Characters & World Props

Every character and prop in MonsterRPG derives from the polymorphic \`Entity\` hierarchy.

#### Key Characters

- **Professor Oak (\`ProfessorNPC\`):**
  - **Location:** Oak's Research Lab at Grid \`(6, 3)\`, behind the research desk.
  - **Role:** Entrusts you with your starter Charmander and provides guidance on your journey.
  - **Dialogue Branching:** Greets you as a newcomer before you have a starter; offers training tips while adventuring; congratulates you as Champion once Mewtwo is pacified!

- **Nurse Joy (\`NurseNPC\`):**
  - **Location:** Oakdale Pokémon Center at Grid \`(6, 3)\`, behind the reception service counter.
  - **Role:** Completely restores all HP and status for your entire party.

- **Cedric (\`VillagerNPC\`):**
  - **Location:** Oakdale Town Square at Grid \`(13, 11)\`.
  - **Role:** Explains elemental type advantages (Fire, Water, Grass) and warns of dark tall grass.

- **Companion Entities (\`PokemonEntity\`):**
  - **Meowth:** In Town Square beside Cedric at Grid \`(12, 11)\`.
  - **Eevee:** Research assistant in Oak's Lab at Grid \`(9, 3)\`.
  - **Squirtle:** In Oak's Lab at Grid \`(3, 5)\`.
  - **Clefairy:** In Pokémon Center at Grid \`(7, 3)\`.
  - **Jigglypuff:** Resting in Pokémon Center lounge at Grid \`(4, 6)\`.

#### Across-Counter Interaction Raycasting
When interacting with Nurse Joy or Professor Oak across a counter or desk, the engine automatically checks two tiles forward if the immediate front tile is a solid counter. You can stand comfortably at Grid \`(6, 5)\` and speak directly across the desk!
`
  },
  {
    id: "faq",
    slug: "faq",
    title: "Frequently Asked Questions (FAQ)",
    category: "Reference & Support",
    readTime: "4 min read",
    summary: "Answers to common questions regarding gameplay, saving, platforms, and upcoming features.",
    content: `
### Frequently Asked Questions

#### Q1: Which platforms are currently supported?
**A:** MonsterRPG is officially released for **Windows 10 and Windows 11 (64-bit)**. Linux and macOS support are planned as part of the future cross-platform roadmap.

#### Q2: Does the game support controller / gamepad input?
**A:** Currently, MonsterRPG is tuned for keyboard input (\`WASD\` / Arrow keys for movement, \`Shift\` for sprint, \`E\` / \`Space\` for interactions, \`1-4\` for battle commands). Native XInput gamepad support is scheduled for a future update.

#### Q3: How do I heal my monsters if they faint?
**A:** Visit the Pokémon Center in the south-west of Oakdale Town (Red Roof) and speak with Nurse Joy behind the counter. If your entire team faints in battle, you safely blackout and respawn right in front of Nurse Joy!

#### Q4: How do I catch the Boss Mewtwo?
**A:** Mewtwo is an ancient Legendary Forest Guardian and cannot be captured with standard Poké Balls. Your objective is to battle, test your strength, and pacify its overwhelming psionic energy!

#### Q5: How is my game saved?
**A:** In the current v1.0.0 release, party progression, starter status, and boss flags persist in memory for the duration of your game session. Persistent file-based serialization (JSON/binary save profiles) is currently in development for release v1.1.0.
`
  },
  {
    id: "troubleshooting",
    slug: "troubleshooting",
    title: "Troubleshooting & Technical Support",
    category: "Reference & Support",
    readTime: "4 min read",
    summary: "Solutions for common launch issues, missing DLLs, audio driver warnings, and display scaling.",
    content: `
### Troubleshooting & Issue Resolution

#### 1. Game Fails to Launch / Missing DLL Error
- **Symptom:** Windows reports \`VCRUNTIME140.dll\` or \`MSVCP140.dll\` not found.
- **Fix:** Install the official Microsoft Visual C++ 2015-2022 Redistributable (x64) from Microsoft's official download page.

#### 2. Black Screen on Launch
- **Symptom:** Window opens with a black screen and closes after a few seconds.
- **Cause:** The \`assets\` directory is missing or located in a different directory.
- **Fix:** Verify that \`MonsterRPG.exe\` and the \`assets\` directory are in the **exact same folder**. Do not move the \`.exe\` out of the extracted release folder.

#### 3. Display Scaling on High-DPI Monitors
- **Symptom:** Pixels look slightly blurred on 4K or 200% Windows scaling.
- **Fix:** Right-click \`MonsterRPG.exe\` -> Properties -> Compatibility -> Change high DPI settings -> Check **Override high DPI scaling behavior** and set to **Application**.

#### 4. Need Further Help?
Join the MonsterRPG community discussions or submit an issue report on the official GitHub repository.
`
  }
];

