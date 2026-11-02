import React from 'react';
import { useRouter } from '../context/RouterContext';
import { Download, Compass, Sparkles, Shield, Swords, Users, MapPin, ArrowRight, Zap, CheckCircle2 } from 'lucide-react';
import releasesData from '../data/releases.json';
import monstersData from '../data/monsters.json';

export const HomePage: React.FC = () => {
  const { navigate } = useRouter();
  const currentRelease = releasesData.currentRelease;

  return (
    <div className="space-y-20 lg:space-y-28 pb-16">
      {/* ========================================================
          HERO SECTION
         ======================================================== */}
      <section className="relative overflow-hidden pt-12 pb-16 lg:pt-20 lg:pb-24 border-b border-rpg-border/60">
        {/* Subtle background ambient glows */}
        <div className="absolute top-1/4 left-1/2 -translate-x-1/2 w-[700px] h-[350px] bg-gradient-to-tr from-amber-500/10 via-emerald-500/5 to-transparent blur-3xl pointer-events-none -z-10"></div>
        
        <div className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8">
          <div className="grid grid-cols-1 lg:grid-cols-12 gap-12 items-center">
            
            {/* Left Content Column */}
            <div className="lg:col-span-7 space-y-6 text-center lg:text-left">
              {/* Release Pill Badge */}
              <div className="inline-flex items-center gap-2 px-3 py-1.5 rounded-full bg-amber-500/10 border border-amber-500/30 text-amber-300 text-xs font-semibold tracking-wide shadow-sm">
                <Sparkles className="w-3.5 h-3.5 text-amber-400 animate-spin" style={{ animationDuration: '6s' }} />
                <span>Official Release {currentRelease.version} is Live!</span>
              </div>

              {/* Title & Tagline */}
              <div className="space-y-3">
                <h1 className="font-display font-black text-4xl sm:text-5xl lg:text-6xl tracking-tight text-white leading-tight">
                  A True 2D Retro Adventure in <span className="text-transparent bg-clip-text bg-gradient-to-r from-amber-400 via-amber-300 to-amber-500">C++ &amp; SFML</span>
                </h1>
                <p className="text-base sm:text-lg text-slate-300 max-w-2xl mx-auto lg:mx-0 font-normal leading-relaxed">
                  Step into the vibrant world of Oakdale Town and Whispering Woods. Experience deterministic grid exploration, partner monster followers, and strategic elemental combat built from scratch in C++20.
                </p>
              </div>

              {/* CTAs */}
              <div className="flex flex-col sm:flex-row items-center justify-center lg:justify-start gap-4 pt-2">
                <button
                  onClick={() => navigate('/download')}
                  className="w-full sm:w-auto inline-flex items-center justify-center gap-2.5 px-7 py-3.5 rounded-xl bg-gradient-to-r from-amber-500 to-amber-600 hover:from-amber-400 hover:to-amber-500 text-slate-950 font-bold text-base shadow-lg shadow-amber-500/25 transition-all transform hover:-translate-y-0.5 active:translate-y-0"
                >
                  <Download className="w-5 h-5 text-slate-950" />
                  <span>Download v1.0.0</span>
                  <span className="text-xs bg-slate-950/20 text-slate-900 px-2 py-0.5 rounded font-mono font-black ml-1">
                    Win 64-bit
                  </span>
                </button>

                <button
                  onClick={() => navigate('/about')}
                  className="w-full sm:w-auto inline-flex items-center justify-center gap-2 px-6 py-3.5 rounded-xl bg-rpg-card hover:bg-slate-800 text-slate-200 hover:text-white font-semibold text-base border border-rpg-border transition-all"
                >
                  <Compass className="w-5 h-5 text-amber-400" />
                  <span>Explore the Game</span>
                </button>
              </div>

              {/* Quick Feature Badges */}
              <div className="pt-4 grid grid-cols-2 sm:grid-cols-4 gap-3 text-left">
                <div className="p-2.5 rounded-lg bg-slate-900/60 border border-slate-800/80">
                  <div className="text-amber-400 font-mono text-xs font-bold">16px Tile Grid</div>
                  <div className="text-[11px] text-slate-400">Deterministic movement</div>
                </div>
                <div className="p-2.5 rounded-lg bg-slate-900/60 border border-slate-800/80">
                  <div className="text-amber-400 font-mono text-xs font-bold">Partner Follower</div>
                  <div className="text-[11px] text-slate-400">Accompanies footsteps</div>
                </div>
                <div className="p-2.5 rounded-lg bg-slate-900/60 border border-slate-800/80">
                  <div className="text-amber-400 font-mono text-xs font-bold">Elemental Combat</div>
                  <div className="text-[11px] text-slate-400">Turn-based affinities</div>
                </div>
                <div className="p-2.5 rounded-lg bg-slate-900/60 border border-slate-800/80">
                  <div className="text-amber-400 font-mono text-xs font-bold">Authentic Sprites</div>
                  <div className="text-[11px] text-slate-400">Front, back &amp; overworld</div>
                </div>
              </div>
            </div>

            {/* Right Showcase Column (Pixel Art Frame) */}
            <div className="lg:col-span-5 relative">
              <div className="relative mx-auto max-w-md lg:max-w-none rounded-2xl p-2 bg-gradient-to-b from-slate-700 via-slate-800 to-slate-950 border-2 border-rpg-border shadow-2xl shadow-black/80">
                <div className="relative rounded-xl overflow-hidden border border-slate-700/80 bg-slate-950">
                  <img
                    src="./assets/screenshots/hero_showcase.png"
                    alt="MonsterRPG Oakdale Town Exploration"
                    className="w-full h-auto object-cover transform hover:scale-105 transition-transform duration-500"
                    style={{ imageRendering: 'pixelated' }}
                  />
                  <div className="absolute bottom-0 inset-x-0 bg-gradient-to-t from-slate-950/95 via-slate-950/60 to-transparent p-4 flex items-center justify-between">
                    <div>
                      <div className="text-xs font-bold text-white flex items-center gap-1.5">
                        <MapPin className="w-3.5 h-3.5 text-amber-400" />
                        Oakdale Town Square
                      </div>
                      <div className="text-[11px] text-slate-300 font-mono">
                        Partner: Charmander (Lv. 6)
                      </div>
                    </div>
                    <span className="text-[10px] font-mono bg-emerald-500/20 text-emerald-400 border border-emerald-500/30 px-2 py-0.5 rounded font-semibold">
                      IN-GAME ENGINE
                    </span>
                  </div>
                </div>
              </div>
            </div>

          </div>
        </div>
      </section>

      {/* ========================================================
          THE ADVENTURE & WORLD PREVIEW
         ======================================================== */}
      <section className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8">
        <div className="text-center max-w-3xl mx-auto space-y-3 mb-14">
          <span className="text-xs font-mono font-bold tracking-widest text-amber-400 uppercase">
            IMMERSIVE SETTING
          </span>
          <h2 className="font-display font-extrabold text-3xl sm:text-4xl text-white">
            Discover a Region of Mystery and Adventure
          </h2>
          <p className="text-sm sm:text-base text-slate-400">
            From the welcoming cobblestone roads of Oakdale Town to the wild, untamed tall grass of Whispering Woods, every tile has been carefully crafted.
          </p>
        </div>

        <div className="grid grid-cols-1 md:grid-cols-3 gap-6">
          {/* Card 1: Oakdale Town */}
          <div className="rounded-xl border border-rpg-border bg-rpg-card/80 overflow-hidden hover:border-slate-600 transition-all group">
            <div className="h-48 overflow-hidden relative bg-slate-950">
              <img
                src="./assets/screenshots/town_square.png"
                alt="Oakdale Town"
                className="w-full h-full object-cover group-hover:scale-105 transition-transform duration-300"
                style={{ imageRendering: 'pixelated' }}
              />
              <span className="absolute top-3 left-3 text-[10px] font-mono font-bold bg-slate-900/90 text-amber-300 px-2 py-0.5 rounded border border-amber-500/30">
                OAKDALE SETTLEMENT
              </span>
            </div>
            <div className="p-6 space-y-3">
              <h3 className="font-display font-bold text-xl text-white">Oakdale Town</h3>
              <p className="text-xs text-slate-400 leading-relaxed">
                A peaceful haven featuring charming street lamps, blooming flower gardens, and local residents. Speak with Cedric and his companion Meowth for guidance.
              </p>
              <button 
                onClick={() => navigate('/about')}
                className="text-xs text-amber-400 hover:text-amber-300 font-semibold inline-flex items-center gap-1 transition-colors"
              >
                Learn about Oakdale &rarr;
              </button>
            </div>
          </div>

          {/* Card 2: Research Lab & Clinic Interiors */}
          <div className="rounded-xl border border-rpg-border bg-rpg-card/80 overflow-hidden hover:border-slate-600 transition-all group">
            <div className="h-48 overflow-hidden relative bg-slate-950">
              <img
                src="./assets/screenshots/oak_lab.png"
                alt="Oak's Research Lab Interior"
                className="w-full h-full object-cover group-hover:scale-105 transition-transform duration-300"
                style={{ imageRendering: 'pixelated' }}
              />
              <span className="absolute top-3 left-3 text-[10px] font-mono font-bold bg-slate-900/90 text-cyan-300 px-2 py-0.5 rounded border border-cyan-500/30">
                INTERIOR BUILDING WARPS
              </span>
            </div>
            <div className="p-6 space-y-3">
              <h3 className="font-display font-bold text-xl text-white">Authentic Interiors</h3>
              <p className="text-xs text-slate-400 leading-relaxed">
                Step inside Professor Oak's Research Lab to receive your starter Charmander, or enter the Pokémon Center where Nurse Joy and Clefairy completely heal your team.
              </p>
              <button 
                onClick={() => navigate('/features')}
                className="text-xs text-cyan-400 hover:text-cyan-300 font-semibold inline-flex items-center gap-1 transition-colors"
              >
                View Interior Mechanics &rarr;
              </button>
            </div>
          </div>

          {/* Card 3: Whispering Woods */}
          <div className="rounded-xl border border-rpg-border bg-rpg-card/80 overflow-hidden hover:border-slate-600 transition-all group">
            <div className="h-48 overflow-hidden relative bg-slate-950">
              <img
                src="./assets/screenshots/whispering_woods.png"
                alt="Whispering Woods Wilderness"
                className="w-full h-full object-cover group-hover:scale-105 transition-transform duration-300"
                style={{ imageRendering: 'pixelated' }}
              />
              <span className="absolute top-3 left-3 text-[10px] font-mono font-bold bg-slate-900/90 text-emerald-300 px-2 py-0.5 rounded border border-emerald-500/30">
                WILD CANOPY TRAILS
              </span>
            </div>
            <div className="p-6 space-y-3">
              <h3 className="font-display font-bold text-xl text-white">Whispering Woods</h3>
              <p className="text-xs text-slate-400 leading-relaxed">
                Dense foliage, shaded tall grass, and winding trails teeming with wild monsters like Pikachu, Bulbasaur, and Psyduck, leading to the Guardian Sanctuary.
              </p>
              <button 
                onClick={() => navigate('/docs/gameplay-guide')}
                className="text-xs text-emerald-400 hover:text-emerald-300 font-semibold inline-flex items-center gap-1 transition-colors"
              >
                Read Explorer's Guide &rarr;
              </button>
            </div>
          </div>
        </div>
      </section>

      {/* ========================================================
          TURN-BASED BATTLE ENGINE SPOTLIGHT
         ======================================================== */}
      <section className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8">
        <div className="rounded-2xl border border-rpg-border bg-gradient-to-b from-slate-900 via-rpg-card to-rpg-darkest p-6 sm:p-10 lg:p-12 relative overflow-hidden">
          <div className="grid grid-cols-1 lg:grid-cols-12 gap-10 items-center">
            
            {/* Left text */}
            <div className="lg:col-span-6 space-y-6">
              <span className="text-xs font-mono font-bold text-amber-400 tracking-wider uppercase inline-flex items-center gap-1.5">
                <Swords className="w-4 h-4 text-amber-500" />
                STRATEGIC COMBAT SYSTEM
              </span>
              <h2 className="font-display font-extrabold text-3xl sm:text-4xl text-white leading-tight">
                Turn-Based Battles with Elemental Affinities
              </h2>
              <p className="text-sm text-slate-300 leading-relaxed">
                Encounter wild creatures in dark grass and test your tactical choices. Attack with elemental moves, heal wounded monsters with Potions, or toss Capture Balls to build your dream team.
              </p>

              <div className="space-y-3 text-sm text-slate-300">
                <div className="flex items-start gap-3">
                  <CheckCircle2 className="w-5 h-5 text-emerald-400 flex-shrink-0 mt-0.5" />
                  <span><strong>Elemental Multipliers:</strong> Fire scorches Grass, Water extinguishes Fire, Grass absorbs Water, and Electric shocks Water!</span>
                </div>
                <div className="flex items-start gap-3">
                  <CheckCircle2 className="w-5 h-5 text-emerald-400 flex-shrink-0 mt-0.5" />
                  <span><strong>Dynamic Combat Animation:</strong> Attacker lunges forward, defenders shake and red-flash, and floating damage numbers pop in real time.</span>
                </div>
                <div className="flex items-start gap-3">
                  <CheckCircle2 className="w-5 h-5 text-emerald-400 flex-shrink-0 mt-0.5" />
                  <span><strong>Authentic Front &amp; Back Sprites:</strong> Inspect your monster from behind while facing opponents in 64x64 pixel clarity.</span>
                </div>
              </div>

              <div className="pt-2 flex items-center gap-4">
                <button
                  onClick={() => navigate('/docs/battle-mechanics')}
                  className="px-5 py-2.5 rounded-lg bg-amber-500 hover:bg-amber-400 text-slate-950 font-bold text-sm transition-colors"
                >
                  Battle Mechanics Guide
                </button>
                <button
                  onClick={() => navigate('/docs/element-types')}
                  className="px-5 py-2.5 rounded-lg bg-slate-800 hover:bg-slate-700 text-slate-200 font-semibold text-sm border border-slate-700 transition-colors"
                >
                  Type Chart
                </button>
              </div>
            </div>

            {/* Right battle preview image */}
            <div className="lg:col-span-6">
              <div className="rounded-xl overflow-hidden border-2 border-rpg-border shadow-2xl bg-slate-950">
                <img
                  src="./assets/screenshots/battle_wild.png"
                  alt="Turn-Based Battle Screen"
                  className="w-full h-auto object-contain"
                  style={{ imageRendering: 'pixelated' }}
                />
              </div>
            </div>

          </div>
        </div>
      </section>

      {/* ========================================================
          MONSTER ROSTER HIGHLIGHT
         ======================================================== */}
      <section className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8">
        <div className="flex flex-col sm:flex-row sm:items-end justify-between mb-10 gap-4">
          <div>
            <span className="text-xs font-mono font-bold tracking-widest text-amber-400 uppercase">
              CREATURE CATALOG
            </span>
            <h2 className="font-display font-extrabold text-3xl text-white mt-1">
              Featured Monster Companions
            </h2>
            <p className="text-sm text-slate-400 mt-1">
              Meet some of the creatures you will entrust, battle alongside, and encounter in the forest.
            </p>
          </div>
          <button
            onClick={() => navigate('/docs/monster-guide')}
            className="inline-flex items-center gap-1.5 text-sm text-amber-400 hover:text-amber-300 font-semibold transition-colors"
          >
            <span>View Full Monster Guide</span>
            <ArrowRight className="w-4 h-4" />
          </button>
        </div>

        <div className="grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-4 gap-6">
          {monstersData.slice(0, 4).map((monster) => (
            <div
              key={monster.id}
              className="rounded-xl border border-rpg-border bg-rpg-card/90 p-5 space-y-4 hover:border-amber-500/50 hover:shadow-lg transition-all flex flex-col justify-between group"
            >
              <div>
                <div className="flex items-center justify-between text-xs font-mono mb-2">
                  <span className="text-slate-400 font-bold">#{monster.id}</span>
                  <span className={`px-2 py-0.5 rounded font-bold uppercase text-[10px] ${
                    monster.type === 'Fire' ? 'bg-orange-500/20 text-orange-400 border border-orange-500/30' :
                    monster.type === 'Water' ? 'bg-sky-500/20 text-sky-400 border border-sky-500/30' :
                    monster.type === 'Grass' ? 'bg-emerald-500/20 text-emerald-400 border border-emerald-500/30' :
                    'bg-yellow-500/20 text-yellow-400 border border-yellow-500/30'
                  }`}>
                    {monster.type}
                  </span>
                </div>

                <div className="h-28 flex items-center justify-center py-2 bg-slate-950/60 rounded-lg border border-slate-800/80 group-hover:bg-slate-900/60 transition-colors">
                  <img
                    src={monster.frontSprite}
                    alt={monster.name}
                    className="h-24 w-24 object-contain transform group-hover:scale-110 transition-transform duration-300"
                    style={{ imageRendering: 'pixelated' }}
                  />
                </div>

                <h3 className="font-display font-bold text-lg text-white mt-3">{monster.name}</h3>
                <p className="text-xs text-slate-400 mt-1 line-clamp-2">{monster.description}</p>
              </div>

              <div className="pt-3 border-t border-slate-800/80 text-[11px] text-slate-400 flex items-center justify-between font-mono">
                <span>HP: {monster.baseStats.hp}</span>
                <span>ATK: {monster.baseStats.atk}</span>
                <span>DEF: {monster.baseStats.def}</span>
                <span>SPD: {monster.baseStats.spd}</span>
              </div>
            </div>
          ))}
        </div>
      </section>

      {/* ========================================================
          DEVELOPMENT & RELEASE STATUS CARD
         ======================================================== */}
      <section className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8">
        <div className="rounded-2xl border border-rpg-border bg-rpg-card/60 p-8 lg:p-10">
          <div className="grid grid-cols-1 md:grid-cols-3 gap-8 items-center">
            
            <div className="space-y-3 md:col-span-2">
              <div className="flex items-center gap-2">
                <span className="w-2.5 h-2.5 rounded-full bg-emerald-500"></span>
                <span className="text-xs font-mono font-bold text-emerald-400 uppercase tracking-wider">
                  Active Stable Milestone • {currentRelease.version}
                </span>
              </div>
              <h3 className="font-display font-extrabold text-2xl text-white">
                Engineered for Stability, Modularity, and Performance
              </h3>
              <p className="text-sm text-slate-300 leading-relaxed">
                MonsterRPG is developed under a clean Object-Oriented C++20 architecture with strict separation of game states, deterministic tile collision callbacks, and zero external runtime dependencies beyond SFML.
              </p>
              <div className="flex flex-wrap gap-4 pt-1 text-xs text-slate-400 font-mono">
                <span className="bg-slate-900/80 px-2.5 py-1 rounded border border-slate-800">C++20 Standard</span>
                <span className="bg-slate-900/80 px-2.5 py-1 rounded border border-slate-800">SFML 3.0.2</span>
                <span className="bg-slate-900/80 px-2.5 py-1 rounded border border-slate-800">CMake &amp; Ninja</span>
                <span className="bg-slate-900/80 px-2.5 py-1 rounded border border-slate-800">Windows Portable Executable</span>
              </div>
            </div>

            <div className="flex flex-col sm:flex-row md:flex-col gap-3 justify-center">
              <button
                onClick={() => navigate('/changelog')}
                className="w-full px-5 py-3 rounded-xl bg-slate-800 hover:bg-slate-700 text-slate-200 text-sm font-semibold border border-slate-700 transition-colors text-center"
              >
                Read v1.0.0 Changelog
              </button>
              <button
                onClick={() => navigate('/development')}
                className="w-full px-5 py-3 rounded-xl bg-rpg-panel hover:bg-slate-800 text-amber-400 text-sm font-semibold border border-rpg-border transition-colors text-center"
              >
                View Technical Architecture
              </button>
            </div>

          </div>
        </div>
      </section>

      {/* ========================================================
          FINAL DOWNLOAD CALL TO ACTION
         ======================================================== */}
      <section className="max-w-5xl mx-auto px-4 sm:px-6 lg:px-8 text-center space-y-6">
        <div className="p-10 sm:p-14 rounded-3xl bg-gradient-to-b from-amber-950/40 via-rpg-card to-rpg-darkest border-2 border-amber-500/30 shadow-2xl relative overflow-hidden">
          <div className="max-w-2xl mx-auto space-y-4">
            <h2 className="font-display font-black text-3xl sm:text-4xl text-white">
              Ready to Begin Your Monster Journey?
            </h2>
            <p className="text-sm sm:text-base text-slate-300">
              Download the official Windows build today. Extract, run, and meet Professor Oak in Oakdale Town!
            </p>
            <div className="pt-4 flex flex-col sm:flex-row items-center justify-center gap-4">
              <button
                onClick={() => navigate('/download')}
                className="w-full sm:w-auto inline-flex items-center justify-center gap-2 px-8 py-4 rounded-xl bg-gradient-to-r from-amber-500 to-amber-600 hover:from-amber-400 hover:to-amber-500 text-slate-950 font-extrabold text-base shadow-xl shadow-amber-500/20 transition-all transform hover:-translate-y-0.5 active:translate-y-0"
              >
                <Download className="w-5 h-5" />
                <span>Download MonsterRPG ({currentRelease.fileSize})</span>
              </button>
              <button
                onClick={() => navigate('/docs/getting-started')}
                className="w-full sm:w-auto px-6 py-4 rounded-xl bg-slate-900/80 hover:bg-slate-800 text-slate-200 font-semibold text-base border border-slate-700 transition-colors"
              >
                Getting Started Guide
              </button>
            </div>
            <div className="text-xs text-slate-400 pt-2 font-mono">
              Version {currentRelease.version} • Windows 10 / 11 (64-bit) • No install required
            </div>
          </div>
        </div>
      </section>
    </div>
  );
};

