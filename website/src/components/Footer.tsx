import React from 'react';
import { useRouter } from '../context/RouterContext';
import { FOOTER_SECTIONS } from '../data/navigation';
import { Terminal, Heart, ExternalLink, Code2 } from 'lucide-react';

export const Footer: React.FC = () => {
  const { navigate } = useRouter();

  return (
    <footer className="border-t border-rpg-border/70 bg-rpg-darkest text-slate-400">
      <div className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8 py-12 lg:py-16">
        <div className="grid grid-cols-1 md:grid-cols-4 gap-8 lg:gap-12">
          {/* Brand Col */}
          <div className="space-y-4 md:col-span-1">
            <div className="flex items-center gap-2.5 cursor-pointer" onClick={() => navigate('/')}>
              <div className="w-8 h-8 rounded-full bg-gradient-to-b from-red-500 to-slate-900 border-2 border-amber-500 flex items-center justify-center relative overflow-hidden">
                <div className="w-full h-0.5 bg-amber-500 absolute top-1/2 -translate-y-1/2"></div>
                <div className="w-3 h-3 rounded-full bg-slate-900 border-2 border-amber-500 z-10 flex items-center justify-center">
                  <div className="w-1 h-1 rounded-full bg-amber-400"></div>
                </div>
              </div>
              <span className="font-display font-black text-lg tracking-tight text-white">
                MONSTER<span className="text-amber-400">RPG</span>
              </span>
            </div>
            <p className="text-xs text-slate-400 leading-relaxed">
              An authentic 2D monster-catching RPG engineered in modern C++20 and SFML. Experience classic grid mechanics, companion followers, and elemental turn-based combat.
            </p>
            <div className="pt-2 flex items-center gap-3 text-xs text-slate-500 font-mono">
              <span className="inline-flex items-center gap-1">
                <Code2 className="w-3.5 h-3.5 text-amber-500" /> C++20
              </span>
              <span>•</span>
              <span>SFML 3.0.2</span>
              <span>•</span>
              <span>CMake &amp; Ninja</span>
            </div>
          </div>

          {/* Navigation Columns */}
          {FOOTER_SECTIONS.map((section) => (
            <div key={section.title} className="space-y-3">
              <h3 className="text-xs font-bold text-slate-200 tracking-wider uppercase font-mono">
                {section.title}
              </h3>
              <ul className="space-y-2 text-sm">
                {section.links.map((link) => (
                  <li key={link.label}>
                    <button
                      onClick={() => navigate(link.href)}
                      className="text-slate-400 hover:text-amber-400 transition-colors text-left"
                    >
                      {link.label}
                    </button>
                  </li>
                ))}
              </ul>
            </div>
          ))}
        </div>

        {/* Bottom Bar */}
        <div className="mt-12 pt-8 border-t border-rpg-border/50 flex flex-col sm:flex-row items-center justify-between text-xs text-slate-500 gap-4">
          <p>
            &copy; {new Date().getFullYear()} MonsterRPG Team. Released as an open-source educational game project.
          </p>
          <div className="flex items-center gap-4">
            <span className="text-slate-600">Built with craftsmanship &amp; retro passion</span>
            <span className="inline-block w-1 h-1 rounded-full bg-slate-700"></span>
            <button 
              onClick={() => navigate('/download')}
              className="text-amber-500 hover:underline font-mono"
            >
              v1.0.0 Windows Build
            </button>
          </div>
        </div>
      </div>
    </footer>
  );
};

