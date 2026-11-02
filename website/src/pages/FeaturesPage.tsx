import React from 'react';
import { useRouter } from '../context/RouterContext';
import { Compass, Footprints, Users, Swords, Package, ShieldAlert, Sparkles, Check, ArrowRight } from 'lucide-react';

export const FeaturesPage: React.FC = () => {
  const { navigate } = useRouter();

  const featureSections = [
    {
      id: "explore-the-world",
      badge: "GRID MOVEMENT & BIOMES",
      icon: Compass,
      title: "Explore an Interconnected World",
      description: "Navigate deterministic 16-pixel tile grids with tactile retro movement. Tap to turn in place, hold Shift to sprint with running shoes, and enter detailed interior buildings.",
      bullets: [
        "Deterministic tile-to-tile movement interpolated linearly over delta-time.",
        "Tap-to-turn responsiveness lets you re-orient without advancing onto hazards.",
        "Running Shoes mechanism doubles speed from 55 px/sec to 120 px/sec.",
        "Seamless screen fade-to-black doorway warps connecting exteriors and interiors."
      ],
      image: "./assets/screenshots/town_square.png",
      imageAlt: "Oakdale Town Grid Exploration"
    },
    {
      id: "meet-characters",
      badge: "INTERACTIVE NPCS & COMPANIONS",
      icon: Users,
      title: "Meet Memorable Characters & Companions",
      description: "Oakdale Town is alive with diverse residents and companion creatures. Speak with mentors, healers, and friendly travelers who guide your journey.",
      bullets: [
        "Professor Oak introduces the region and entrusts you with your starter partner.",
        "Nurse Joy and Clefairy fully restore your monster party's HP at the Health Center.",
        "Cedric and Meowth explain elemental affinities and tall grass hazards.",
        "Across-counter raycasting lets you talk naturally across research desks and medical counters."
      ],
      image: "./assets/screenshots/pokemon_center.png",
      imageAlt: "Pokemon Center Clinic Interior"
    },
    {
      id: "discover-monsters",
      badge: "PARTNER & SPRITE ENGINE",
      icon: Sparkles,
      title: "Discover Monsters & Partner Companions",
      description: "Every monster is brought to life with authentic 64x64 battle textures and dedicated overworld sprites. Your active partner monster follows directly behind you wherever you roam.",
      bullets: [
        "FollowerPokemon tracks your exact tile trail and turns to match your direction.",
        "Real-time partner interaction reflects current health and emotional state.",
        "64x64 Front and Back battle sprites offer classic battle presentation.",
        "Overworld Pokémon bob with breathing animations and respond when approached."
      ],
      image: "./assets/screenshots/whispering_woods.png",
      imageAlt: "Whispering Woods Wild Monsters"
    },
    {
      id: "turn-based-battles",
      badge: "TACTICAL RPG COMBAT",
      icon: Swords,
      title: "Strategic Turn-Based Combat Engine",
      description: "Step into tall grass to engage wild creatures. Choose from Fight, Bag, Catch, and Run, and exploit elemental affinities for double damage.",
      bullets: [
        "Speed-based initiative determines turn priority between attacker and defender.",
        "Elemental affinities (Fire, Water, Grass, Electric, Psychic, Normal) yield 2.0x or 0.5x multipliers.",
        "Dynamic battle animations: lunging attackers, hit shakes, red damage flashes, and rising damage numbers.",
        "Capture mechanic with parabolic ball throw arc and wobbling platform suspense."
      ],
      image: "./assets/screenshots/battle_wild.png",
      imageAlt: "Turn-Based Wild Battle"
    },
    {
      id: "collect-items",
      badge: "INVENTORY & CONSUMABLES",
      icon: Package,
      title: "Collect Items & Manage Supplies",
      description: "Stock up on essential supplies for your expedition into the woods. Use Potions in combat or while wandering, and find hidden item balls hidden in nature.",
      bullets: [
        "Potions restore 20 HP in or out of combat to sustain long journeys.",
        "Poké Balls allow you to expand your team by capturing weakened wild monsters.",
        "Hidden item pickups tucked inside secluded groves and dead-ends.",
        "Safety blackout: if all monsters faint, you are safely revived at Nurse Joy's clinic."
      ],
      image: "./assets/screenshots/battle_moves.png",
      imageAlt: "Battle Move Selection"
    },
    {
      id: "challenge-bosses",
      badge: "LEGENDARY SHOWDOWN",
      icon: ShieldAlert,
      title: "Challenge the Forest Guardian Mewtwo",
      description: "The deepest sanctuary of Whispering Woods holds an ancient legend. Confront the psychic powerhouse Mewtwo in an intense, climactic boss battle.",
      bullets: [
        "Deep northern clearing accessible only after navigating winding forest trails.",
        "Overworld Mewtwo entity radiates overwhelming psionic power.",
        "High-level boss encounter featuring custom psionic visual FX and devastating moves.",
        "Triumphing over the Guardian earns the eternal gratitude of Oakdale Town!"
      ],
      image: "./assets/screenshots/battle_boss.png",
      imageAlt: "Legendary Boss Battle against Mewtwo"
    }
  ];

  return (
    <div className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8 py-12 lg:py-16 space-y-16 lg:space-y-24">
      {/* Header */}
      <div className="text-center max-w-3xl mx-auto space-y-3">
        <div className="inline-flex items-center gap-2 px-3 py-1 rounded-full bg-amber-500/10 border border-amber-500/30 text-amber-400 text-xs font-mono font-bold uppercase tracking-wider">
          <Sparkles className="w-3.5 h-3.5" />
          Game Systems Breakdown
        </div>
        <h1 className="font-display font-black text-4xl sm:text-5xl text-white tracking-tight">
          Core Features of MonsterRPG
        </h1>
        <p className="text-base text-slate-300 leading-relaxed">
          Every gameplay element in MonsterRPG has been built from scratch in C++20 with focused design decisions prioritizing authentic retro feel, clean tactile controls, and tactical depth.
        </p>
      </div>

      {/* Feature Modules */}
      <div className="space-y-16 lg:space-y-24">
        {featureSections.map((feature, idx) => {
          const isEven = idx % 2 === 0;
          const Icon = feature.icon;

          return (
            <div
              key={feature.id}
              className={`grid grid-cols-1 lg:grid-cols-12 gap-8 lg:gap-12 items-center ${
                isEven ? '' : 'lg:flex-row-reverse'
              }`}
            >
              {/* Text Side */}
              <div className={`space-y-5 ${isEven ? 'lg:col-span-6' : 'lg:col-span-6 lg:order-2'}`}>
                <div className="inline-flex items-center gap-2 text-xs font-mono font-bold text-amber-400 uppercase tracking-widest">
                  <Icon className="w-4 h-4 text-amber-500" />
                  {feature.badge}
                </div>
                <h2 className="font-display font-extrabold text-2xl sm:text-3xl text-white">
                  {feature.title}
                </h2>
                <p className="text-sm text-slate-300 leading-relaxed">
                  {feature.description}
                </p>

                <div className="space-y-2.5 pt-2">
                  {feature.bullets.map((b, i) => (
                    <div key={i} className="flex items-start gap-2.5 text-xs text-slate-300 leading-relaxed">
                      <div className="p-0.5 rounded-full bg-amber-500/10 text-amber-400 border border-amber-500/30 flex-shrink-0 mt-0.5">
                        <Check className="w-3 h-3" />
                      </div>
                      <span>{b}</span>
                    </div>
                  ))}
                </div>
              </div>

              {/* Image Side */}
              <div className={`${isEven ? 'lg:col-span-6' : 'lg:col-span-6 lg:order-1'}`}>
                <div className="rounded-xl overflow-hidden border-2 border-rpg-border shadow-2xl bg-slate-950 group">
                  <img
                    src={feature.image}
                    alt={feature.imageAlt}
                    className="w-full h-auto object-contain transform group-hover:scale-105 transition-transform duration-500"
                    style={{ imageRendering: 'pixelated' }}
                  />
                </div>
              </div>
            </div>
          );
        })}
      </div>

      {/* Bottom CTA */}
      <div className="p-8 sm:p-12 rounded-2xl bg-gradient-to-r from-rpg-card to-slate-900 border border-rpg-border text-center space-y-4">
        <h2 className="font-display font-black text-2xl sm:text-3xl text-white">
          Experience These Features Firsthand
        </h2>
        <p className="text-sm text-slate-300 max-w-xl mx-auto">
          Download the latest v1.0.0 release or read the technical documentation to inspect the engine architecture.
        </p>
        <div className="pt-2 flex flex-col sm:flex-row items-center justify-center gap-4">
          <button
            onClick={() => navigate('/download')}
            className="w-full sm:w-auto px-7 py-3 rounded-xl bg-amber-500 hover:bg-amber-400 text-slate-950 font-bold text-sm transition-colors"
          >
            Download Game (v1.0.0)
          </button>
          <button
            onClick={() => navigate('/docs/gameplay-guide')}
            className="w-full sm:w-auto px-6 py-3 rounded-xl bg-slate-800 hover:bg-slate-700 text-slate-200 font-semibold text-sm border border-slate-700 transition-colors"
          >
            Read Gameplay Guide
          </button>
        </div>
      </div>
    </div>
  );
};

