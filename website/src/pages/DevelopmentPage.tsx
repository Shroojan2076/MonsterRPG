import React from 'react';
import { useRouter } from '../context/RouterContext';
import { Code2, Layers, Cpu, Compass, CheckCircle2, CircleDashed, Terminal, Shield, ArrowRight } from 'lucide-react';

export const DevelopmentPage: React.FC = () => {
  const { navigate } = useRouter();

  const roadmapMilestones = [
    {
      phase: "Milestone 1.0",
      title: "Core OOP Engine & Dual Biome Release",
      status: "COMPLETED",
      items: [
        "C++20 & SFML 3.0.2 rendering engine bootstrap.",
        "Deterministic 16px tile collision with tap-to-turn and running shoes.",
        "44x28 Dual Biome world connecting Oakdale Town and Whispering Woods.",
        "Multi-level interior maps for Oak's Lab and the Pokémon Center with fade warps.",
        "Turn-based combat engine with elemental type affinities and visual FX.",
        "Authentic overworld sprites and 64x64 front/back battle textures.",
        "Partner Follower Pokémon system with real-time mood dialogue."
      ]
    },
    {
      phase: "Milestone 1.1",
      title: "Audio Engine & Sound Effects Integration",
      status: "IN PROGRESS",
      items: [
        "SFML::Audio system manager for dynamic background music and sound effects.",
        "Town theme (peaceful acoustic), Forest theme (mysterious ambient), and Battle themes.",
        "Overworld footsteps, door chimes, and bump feedback SFX.",
        "Elemental combat sounds: fire whoosh, water splash, vine whip, thunder spark, and ball capture clicks."
      ]
    },
    {
      phase: "Milestone 1.2",
      title: "Save Profile Serialization & In-Game Menu",
      status: "PLANNED",
      items: [
        "Serializable SaveProfile saving coordinates, party, inventory, and world flags.",
        "In-game Pause Menu accessible via [Esc] / [Tab].",
        "Party summary inspector, bag inventory manager, and volume options.",
        "Safe error validation preventing save file corruption."
      ]
    },
    {
      phase: "Milestone 1.3",
      title: "Battle Mechanics & Tactical Depth Expansion",
      status: "PLANNED",
      items: [
        "In-combat party swapping allowing players to rotate team members.",
        "Status conditions engine: Burn, Poison, Paralysis, and Sleep with HUD icons.",
        "Buff and debuff moves (Growl, Leer, Agility, Recover).",
        "Move accuracy variance and critical hit mechanics (1.5x damage)."
      ]
    },
    {
      phase: "Milestone 1.4",
      title: "Autonomous NPC Wandering & Rival Trainer Battles",
      status: "PLANNED",
      items: [
        "Autonomous NPC wandering state machine (idle and patrol intervals).",
        "TrainerNPC class with line-of-sight challenge triggers (! exclamation mark).",
        "Multi-stage quest engine for Professor Oak's research tasks."
      ]
    }
  ];

  return (
    <div className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8 py-12 lg:py-16 space-y-16">
      {/* Header */}
      <div className="max-w-3xl space-y-4">
        <div className="inline-flex items-center gap-2 px-3 py-1 rounded-full bg-amber-500/10 border border-amber-500/30 text-amber-400 text-xs font-mono font-bold uppercase tracking-wider">
          <Code2 className="w-3.5 h-3.5" />
          Technical Overview &amp; Roadmap
        </div>
        <h1 className="font-display font-black text-4xl sm:text-5xl text-white tracking-tight">
          Development of MonsterRPG
        </h1>
        <p className="text-base text-slate-300 leading-relaxed font-normal">
          Learn about the architectural principles, software patterns, and technical roadmap behind MonsterRPG's custom 2D engine.
        </p>
      </div>

      {/* Vision & Design Philosophy */}
      <section className="grid grid-cols-1 lg:grid-cols-2 gap-8 items-center">
        <div className="space-y-4">
          <span className="text-xs font-mono font-bold text-amber-400 uppercase tracking-widest">
            ENGINE VISION
          </span>
          <h2 className="font-display font-extrabold text-2xl sm:text-3xl text-white">
            Built from First Principles
          </h2>
          <p className="text-sm text-slate-300 leading-relaxed">
            Rather than relying on heavyweight, multi-gigabyte modern game engines, MonsterRPG was intentionally built from the ground up using modern C++20 and SFML. This gives the game near-instant load times, minimal memory usage, crystal-clear pixel art rendering, and deterministic mechanics.
          </p>
          <div className="space-y-2.5 text-xs text-slate-300">
            <div className="flex items-center gap-2">
              <CheckCircle2 className="w-4 h-4 text-emerald-400 flex-shrink-0" />
              <span><strong>Pure OOP Architecture:</strong> Strict polymorphism with abstract base classes.</span>
            </div>
            <div className="flex items-center gap-2">
              <CheckCircle2 className="w-4 h-4 text-emerald-400 flex-shrink-0" />
              <span><strong>Finite State Machine:</strong> Clean separation between Overworld, Dialogue, and Battle states.</span>
            </div>
            <div className="flex items-center gap-2">
              <CheckCircle2 className="w-4 h-4 text-emerald-400 flex-shrink-0" />
              <span><strong>Hardware Accelerated:</strong> Direct GPU sprite batching via modern OpenGL/SFML pipelines.</span>
            </div>
          </div>
        </div>

        <div className="p-6 rounded-2xl border border-rpg-border bg-rpg-card space-y-4">
          <h3 className="font-mono font-bold text-sm text-amber-400 uppercase tracking-wider">
            Technical Stack
          </h3>
          <div className="grid grid-cols-2 gap-4 text-xs">
            <div className="p-3.5 rounded-lg bg-slate-900 border border-slate-800 space-y-1">
              <div className="text-slate-400 font-mono">Language</div>
              <div className="font-bold text-white text-sm">C++20 (ISO Standard)</div>
            </div>
            <div className="p-3.5 rounded-lg bg-slate-900 border border-slate-800 space-y-1">
              <div className="text-slate-400 font-mono">Multimedia Library</div>
              <div className="font-bold text-white text-sm">SFML 3.0.2</div>
            </div>
            <div className="p-3.5 rounded-lg bg-slate-900 border border-slate-800 space-y-1">
              <div className="text-slate-400 font-mono">Build System</div>
              <div className="font-bold text-white text-sm">CMake 3.28+ &amp; Ninja</div>
            </div>
            <div className="p-3.5 rounded-lg bg-slate-900 border border-slate-800 space-y-1">
              <div className="text-slate-400 font-mono">Compiler Support</div>
              <div className="font-bold text-white text-sm">GCC 14 / Clang / MSVC</div>
            </div>
          </div>
        </div>
      </section>

      {/* Engine Architecture Deep Dive */}
      <section className="space-y-6">
        <div className="space-y-2">
          <span className="text-xs font-mono font-bold text-amber-400 uppercase tracking-widest">
            SOFTWARE ARCHITECTURE
          </span>
          <h2 className="font-display font-extrabold text-2xl sm:text-3xl text-white">
            Core Engine Subsystems
          </h2>
        </div>

        <div className="grid grid-cols-1 md:grid-cols-3 gap-6">
          <div className="p-6 rounded-xl border border-rpg-border bg-rpg-card space-y-3">
            <div className="p-2.5 rounded-lg bg-amber-500/10 text-amber-400 border border-amber-500/20 w-fit">
              <Layers className="w-5 h-5" />
            </div>
            <h3 className="font-bold text-white text-base">Polymorphic Entity Model</h3>
            <p className="text-xs text-slate-300 leading-relaxed">
              All active actors and world props derive from the abstract <code className="text-amber-400">Entity</code> class. Specializations include <code className="text-amber-400">Character</code> (player and animated NPCs), <code className="text-amber-400">PokemonEntity</code> (single-frame overworld creatures with breathing animations), and <code className="text-amber-400">WorldObject</code>.
            </p>
          </div>

          <div className="p-6 rounded-xl border border-rpg-border bg-rpg-card space-y-3">
            <div className="p-2.5 rounded-lg bg-cyan-500/10 text-cyan-400 border border-cyan-500/20 w-fit">
              <Cpu className="w-5 h-5" />
            </div>
            <h3 className="font-bold text-white text-base">FSM State Management</h3>
            <p className="text-xs text-slate-300 leading-relaxed">
              The engine operates via a stack-based finite state machine managed by <code className="text-cyan-400">StateManager</code>. States like <code className="text-cyan-400">DialogueState</code> render as transparent overlays over <code className="text-cyan-400">OverworldState</code>, with pending transitions handled cleanly without frame collisions.
            </p>
          </div>

          <div className="p-6 rounded-xl border border-rpg-border bg-rpg-card space-y-3">
            <div className="p-2.5 rounded-lg bg-emerald-500/10 text-emerald-400 border border-emerald-500/20 w-fit">
              <Compass className="w-5 h-5" />
            </div>
            <h3 className="font-bold text-white text-base">TileMap &amp; Warp Engine</h3>
            <p className="text-xs text-slate-300 leading-relaxed">
              Tile maps feature dynamic dimensional sizing, custom 32x32 atlas parsing, and instant map switching between exterior town biomes and interior buildings. Raycasted collision checks prevent wall and counter clipping.
            </p>
          </div>
        </div>
      </section>

      {/* Development Roadmap */}
      <section className="space-y-8">
        <div className="space-y-2">
          <span className="text-xs font-mono font-bold text-amber-400 uppercase tracking-widest">
            FUTURE ENHANCEMENTS
          </span>
          <h2 className="font-display font-extrabold text-2xl sm:text-3xl text-white">
            Development Roadmap
          </h2>
          <p className="text-xs sm:text-sm text-slate-400">
            A structured look at current progress and upcoming feature milestones.
          </p>
        </div>

        <div className="space-y-6">
          {roadmapMilestones.map((m, idx) => (
            <div key={idx} className="p-6 rounded-2xl border border-rpg-border bg-rpg-card space-y-4">
              <div className="flex flex-wrap items-center justify-between gap-4">
                <div className="flex items-center gap-3">
                  <span className={`text-[10px] font-mono font-bold uppercase px-2.5 py-0.5 rounded ${
                    m.status === 'COMPLETED'
                      ? 'bg-emerald-500/20 text-emerald-400 border border-emerald-500/40'
                      : m.status === 'IN PROGRESS'
                      ? 'bg-amber-500/20 text-amber-400 border border-amber-500/40'
                      : 'bg-slate-800 text-slate-400 border border-slate-700'
                  }`}>
                    {m.status}
                  </span>
                  <h3 className="font-display font-bold text-lg text-white">
                    {m.phase}: {m.title}
                  </h3>
                </div>
              </div>

              <ul className="grid grid-cols-1 sm:grid-cols-2 gap-2 text-xs text-slate-300 pt-1">
                {m.items.map((item, itemIdx) => (
                  <li key={itemIdx} className="flex items-start gap-2">
                    {m.status === 'COMPLETED' ? (
                      <CheckCircle2 className="w-4 h-4 text-emerald-400 flex-shrink-0 mt-0.5" />
                    ) : (
                      <CircleDashed className="w-4 h-4 text-slate-500 flex-shrink-0 mt-0.5" />
                    )}
                    <span>{item}</span>
                  </li>
                ))}
              </ul>
            </div>
          ))}
        </div>
      </section>

      {/* CTA */}
      <div className="p-8 rounded-2xl bg-rpg-card border border-rpg-border flex flex-col sm:flex-row items-center justify-between gap-4">
        <div>
          <h3 className="font-bold text-white text-base">Want to inspect the complete changelog?</h3>
          <p className="text-xs text-slate-400">Read detailed release notes for every version.</p>
        </div>
        <button
          onClick={() => navigate('/changelog')}
          className="px-5 py-2.5 rounded-lg bg-amber-500 hover:bg-amber-400 text-slate-950 font-bold text-xs transition-colors inline-flex items-center gap-1.5"
        >
          <span>View Changelog</span>
          <ArrowRight className="w-4 h-4" />
        </button>
      </div>
    </div>
  );
};

