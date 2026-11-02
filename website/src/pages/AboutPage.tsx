import React from 'react';
import { useRouter } from '../context/RouterContext';
import { Compass, BookOpen, Shield, Swords, Sparkles, MapPin, Users, Heart, Award, ArrowRight } from 'lucide-react';

export const AboutPage: React.FC = () => {
  const { navigate } = useRouter();

  return (
    <div className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8 py-12 lg:py-16 space-y-16 lg:space-y-24">
      {/* Header */}
      <div className="max-w-3xl space-y-4">
        <div className="inline-flex items-center gap-2 px-3 py-1 rounded-full bg-amber-500/10 border border-amber-500/30 text-amber-400 text-xs font-mono font-bold uppercase tracking-wider">
          <BookOpen className="w-3.5 h-3.5" />
          The Official Handbook
        </div>
        <h1 className="font-display font-black text-4xl sm:text-5xl text-white tracking-tight">
          About MonsterRPG
        </h1>
        <p className="text-base sm:text-lg text-slate-300 leading-relaxed font-normal">
          MonsterRPG is an authentic, retro-inspired 2D monster-catching role-playing game crafted from first principles in modern C++20 and SFML. Designed as a heartfelt tribute to classic handheld gaming, it emphasizes deterministic grid movement, deep elemental combat, and an evocative pixel-art world.
        </p>
      </div>

      {/* Concept & Premise */}
      <section className="grid grid-cols-1 lg:grid-cols-12 gap-10 items-center">
        <div className="lg:col-span-6 space-y-5">
          <span className="text-xs font-mono font-bold text-amber-400 uppercase tracking-widest">
            THE PREMISE
          </span>
          <h2 className="font-display font-extrabold text-3xl text-white">
            An Unfolding Journey from Oakdale Town
          </h2>
          <p className="text-sm text-slate-300 leading-relaxed">
            You arrive in Oakdale Town, a calm border settlement nestled at the foot of Whispering Woods. To the east lies an untamed expanse where wild monsters roam through tall grass, and ancient power stirs in the northern groves.
          </p>
          <p className="text-sm text-slate-300 leading-relaxed">
            Professor Oak, the town's premier researcher, seeks an aspiring explorer to investigate unusual psionic disturbances in the forest clearing. Armed with a starter Charmander, custom Potions, and Capture Balls, your journey through nature begins.
          </p>
          <div className="p-4 rounded-xl bg-rpg-card border border-rpg-border flex items-center gap-4">
            <div className="p-3 rounded-lg bg-amber-500/10 text-amber-400 border border-amber-500/20">
              <Award className="w-6 h-6" />
            </div>
            <div>
              <div className="text-sm font-bold text-white">The Champion's Objective</div>
              <div className="text-xs text-slate-400">
                Tame wild monsters, master elemental combat, and test your mettle against the legendary Guardian Mewtwo.
              </div>
            </div>
          </div>
        </div>

        <div className="lg:col-span-6">
          <div className="rounded-2xl overflow-hidden border-2 border-rpg-border shadow-2xl bg-slate-950">
            <img
              src="./assets/screenshots/town_square.png"
              alt="Oakdale Town Overview"
              className="w-full h-auto object-cover"
              style={{ imageRendering: 'pixelated' }}
            />
          </div>
        </div>
      </section>

      {/* Dual Biomes & World Design */}
      <section className="space-y-8">
        <div className="max-w-3xl space-y-2">
          <span className="text-xs font-mono font-bold text-amber-400 uppercase tracking-widest">
            THE WORLD ARCHITECTURE
          </span>
          <h2 className="font-display font-extrabold text-3xl text-white">
            Seamless Exploration &amp; Dynamic Biomes
          </h2>
          <p className="text-sm text-slate-300">
            The game world is governed by a unified 44x28 tile map, bridging civilization and untamed wilderness with seamless multi-level building interiors.
          </p>
        </div>

        <div className="grid grid-cols-1 md:grid-cols-2 gap-8">
          {/* Biome 1: Oakdale Town */}
          <div className="p-6 rounded-xl border border-rpg-border bg-rpg-card space-y-4">
            <div className="flex items-center justify-between">
              <h3 className="font-display font-bold text-xl text-white flex items-center gap-2">
                <MapPin className="w-5 h-5 text-amber-400" />
                Oakdale Town (West Biome)
              </h3>
              <span className="text-[11px] font-mono text-slate-400 bg-slate-800 px-2 py-0.5 rounded">
                Grid: 2..19 x 3..24
              </span>
            </div>
            <p className="text-xs text-slate-300 leading-relaxed">
              Constructed with cobblestone avenues, antique cast-iron street lamps, flower beds, and wooden perimeter fences. Houses two primary institutions:
            </p>
            <ul className="text-xs text-slate-300 space-y-2">
              <li className="flex items-start gap-2">
                <span className="text-cyan-400 font-bold">&bull;</span>
                <span><strong>Prof. Oak's Research Lab (Blue Roof):</strong> Research tables, specimen analysis microscopes, starter Pokéball tray, and the professor's assistant Eevee.</span>
              </li>
              <li className="flex items-start gap-2">
                <span className="text-rose-400 font-bold">&bull;</span>
                <span><strong>Oakdale Pokémon Center (Red Roof):</strong> Full-service healing clinic staffed by Nurse Joy and Clefairy, complete with network storage PCs and vending machines.</span>
              </li>
            </ul>
          </div>

          {/* Biome 2: Whispering Woods */}
          <div className="p-6 rounded-xl border border-rpg-border bg-rpg-card space-y-4">
            <div className="flex items-center justify-between">
              <h3 className="font-display font-bold text-xl text-white flex items-center gap-2">
                <Compass className="w-5 h-5 text-emerald-400" />
                Whispering Woods (East Biome)
              </h3>
              <span className="text-[11px] font-mono text-slate-400 bg-slate-800 px-2 py-0.5 rounded">
                Grid: 21..43 x 1..27
              </span>
            </div>
            <p className="text-xs text-slate-300 leading-relaxed">
              A sprawling temperate forest with branching paths, tall grass patches, and natural water bodies:
            </p>
            <ul className="text-xs text-slate-300 space-y-2">
              <li className="flex items-start gap-2">
                <span className="text-emerald-400 font-bold">&bull;</span>
                <span><strong>Tall Grass Patches:</strong> Shaded grass patches triggering an 18% wild monster encounter chance per step.</span>
              </li>
              <li className="flex items-start gap-2">
                <span className="text-sky-400 font-bold">&bull;</span>
                <span><strong>Secluded Pond &amp; Grove:</strong> Southward trail to a serene pond where Poliwag splashes and a massive Snorlax snoozes.</span>
              </li>
              <li className="flex items-start gap-2">
                <span className="text-purple-400 font-bold">&bull;</span>
                <span><strong>Guardian Clearing:</strong> Northward trail terminating at the secluded sanctuary of the legendary Mewtwo.</span>
              </li>
            </ul>
          </div>
        </div>
      </section>

      {/* Building Interiors Showcase */}
      <section className="grid grid-cols-1 lg:grid-cols-2 gap-8 items-center">
        <div className="space-y-4">
          <span className="text-xs font-mono font-bold text-amber-400 uppercase tracking-widest">
            AUTHENTIC INTERIORS
          </span>
          <h2 className="font-display font-extrabold text-3xl text-white">
            Fade-to-Black Doorway Warps
          </h2>
          <p className="text-sm text-slate-300 leading-relaxed">
            Unlike basic flat maps, MonsterRPG features dedicated interior rooms with authentic architectural tile layouts. When the player steps onto a doorway, the screen smoothly fades to black, swaps the active entity collection and tile layout, and places the player and their follower safely on the interior welcome mat.
          </p>
          <div className="space-y-3 pt-2">
            <div className="p-3.5 rounded-lg bg-rpg-card border border-rpg-border flex items-center justify-between text-xs">
              <span className="text-white font-semibold">Oak's Lab Entrance Warp</span>
              <span className="font-mono text-cyan-400">Overworld (6, 7) &rarr; OakLab (6, 8)</span>
            </div>
            <div className="p-3.5 rounded-lg bg-rpg-card border border-rpg-border flex items-center justify-between text-xs">
              <span className="text-white font-semibold">Pokémon Center Entrance Warp</span>
              <span className="font-mono text-rose-400">Overworld (6, 18) &rarr; Clinic (6, 8)</span>
            </div>
          </div>
        </div>

        <div className="rounded-xl overflow-hidden border border-rpg-border shadow-xl bg-slate-950">
          <img
            src="./assets/screenshots/oak_lab.png"
            alt="Prof Oak Lab Interior"
            className="w-full h-auto object-contain"
            style={{ imageRendering: 'pixelated' }}
          />
        </div>
      </section>

      {/* Partner Follower & Combat Summary */}
      <section className="p-8 sm:p-10 rounded-2xl border border-rpg-border bg-gradient-to-r from-rpg-card via-rpg-dark to-rpg-card space-y-6">
        <div className="max-w-2xl space-y-3">
          <span className="text-xs font-mono font-bold text-amber-400 uppercase tracking-widest">
            PARTNER DYNAMICS
          </span>
          <h2 className="font-display font-extrabold text-3xl text-white">
            Your Loyal Pokémon Companion
          </h2>
          <p className="text-sm text-slate-300 leading-relaxed">
            The moment you receive your starter Pokémon from Professor Oak, it steps out to journey alongside you in the overworld. As you navigate the trails, it tracks your footsteps, turns to face you when spoken with, and communicates its mood and health state based on recent battles.
          </p>
        </div>

        <div className="grid grid-cols-1 sm:grid-cols-3 gap-4 pt-2">
          <div className="p-4 rounded-xl bg-slate-900/80 border border-slate-800">
            <div className="text-amber-400 font-bold text-sm">Full Health Mood</div>
            <p className="text-xs text-slate-400 mt-1">"It is bursting with vibrant energy and ready for anything!"</p>
          </div>
          <div className="p-4 rounded-xl bg-slate-900/80 border border-slate-800">
            <div className="text-emerald-400 font-bold text-sm">Determined Mood</div>
            <p className="text-xs text-slate-400 mt-1">"It gives you a determined nod and nudges your knee."</p>
          </div>
          <div className="p-4 rounded-xl bg-slate-900/80 border border-slate-800">
            <div className="text-rose-400 font-bold text-sm">Exhausted Mood</div>
            <p className="text-xs text-slate-400 mt-1">"It looks slightly exhausted, but stays bravely by your side."</p>
          </div>
        </div>
      </section>

      {/* Next Actions */}
      <div className="pt-6 border-t border-rpg-border flex flex-col sm:flex-row items-center justify-between gap-4">
        <div>
          <h3 className="font-bold text-white text-base">Want to inspect every game mechanic in detail?</h3>
          <p className="text-xs text-slate-400">Read our dedicated feature breakdown and combat guides.</p>
        </div>
        <div className="flex items-center gap-3">
          <button
            onClick={() => navigate('/features')}
            className="px-5 py-2.5 rounded-lg bg-amber-500 hover:bg-amber-400 text-slate-950 font-bold text-sm transition-colors"
          >
            Explore Game Features &rarr;
          </button>
          <button
            onClick={() => navigate('/download')}
            className="px-5 py-2.5 rounded-lg bg-slate-800 hover:bg-slate-700 text-slate-200 font-semibold text-sm border border-slate-700 transition-colors"
          >
            Download v1.0.0
          </button>
        </div>
      </div>
    </div>
  );
};

