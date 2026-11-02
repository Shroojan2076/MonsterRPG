import React, { useState } from 'react';
import { useRouter } from '../context/RouterContext';
import { MAIN_NAV } from '../data/navigation';
import { Menu, X, Download, Compass, Shield } from 'lucide-react';

export const Navbar: React.FC = () => {
  const { currentPath, navigate } = useRouter();
  const [mobileMenuOpen, setMobileMenuOpen] = useState(false);

  const isActive = (href: string) => {
    const cleanHref = href.replace(/^#/, '');
    if (cleanHref === '/' && currentPath === '/') return true;
    if (cleanHref !== '/' && currentPath.startsWith(cleanHref)) return true;
    return false;
  };

  return (
    <header className="sticky top-0 z-40 w-full border-b border-rpg-border/60 bg-rpg-darkest/90 backdrop-blur-md">
      {/* Top micro-banner */}
      <div className="bg-gradient-to-r from-amber-950/40 via-amber-900/30 to-amber-950/40 border-b border-amber-500/20 px-4 py-1 text-center text-xs text-amber-200/90 font-medium tracking-wide flex items-center justify-center gap-2">
        <span className="inline-block w-2 h-2 rounded-full bg-emerald-500 animate-pulse"></span>
        <span>MonsterRPG <strong>v1.0.0 Stable</strong> is now available for Windows 64-bit!</span>
        <button 
          onClick={() => navigate('/download')}
          className="ml-2 text-amber-400 hover:text-amber-300 underline font-semibold transition-colors"
        >
          Download Now &rarr;
        </button>
      </div>

      <div className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8">
        <div className="flex items-center justify-between h-16">
          {/* Logo */}
          <div className="flex-shrink-0 flex items-center gap-3 cursor-pointer" onClick={() => navigate('/')}>
            <div className="w-9 h-9 rounded-full bg-gradient-to-b from-red-500 to-slate-900 border-2 border-amber-500 shadow-md flex items-center justify-center relative overflow-hidden group">
              <div className="w-full h-0.5 bg-amber-500 absolute top-1/2 -translate-y-1/2"></div>
              <div className="w-3.5 h-3.5 rounded-full bg-slate-900 border-2 border-amber-500 z-10 flex items-center justify-center">
                <div className="w-1.5 h-1.5 rounded-full bg-amber-400"></div>
              </div>
            </div>
            <div>
              <span className="font-display font-black text-xl tracking-tight text-white flex items-center gap-1.5">
                MONSTER<span className="text-amber-400 font-extrabold">RPG</span>
              </span>
              <span className="hidden sm:block text-[10px] text-slate-400 tracking-wider font-mono uppercase -mt-1">
                2D C++20 Indie RPG
              </span>
            </div>
          </div>

          {/* Desktop Navigation */}
          <nav className="hidden md:flex items-center space-x-1 lg:space-x-2">
            {MAIN_NAV.map((item) => {
              const active = isActive(item.href);
              if (item.highlight) {
                return (
                  <button
                    key={item.href}
                    onClick={() => navigate(item.href)}
                    className="ml-3 inline-flex items-center gap-1.5 px-3.5 py-1.5 rounded-lg bg-gradient-to-r from-amber-500 to-amber-600 hover:from-amber-400 hover:to-amber-500 text-slate-950 font-bold text-sm shadow-md shadow-amber-500/20 transition-all duration-200 transform hover:-translate-y-0.5 active:translate-y-0"
                  >
                    <Download className="w-4 h-4" />
                    <span>{item.label}</span>
                    {item.badge && (
                      <span className="ml-1 text-[10px] bg-slate-950/30 text-slate-950 px-1.5 py-0.5 rounded font-mono font-black">
                        {item.badge}
                      </span>
                    )}
                  </button>
                );
              }

              return (
                <button
                  key={item.href}
                  onClick={() => navigate(item.href)}
                  className={`px-3 py-1.5 rounded-md text-sm font-medium transition-colors ${
                    active
                      ? 'text-amber-400 bg-rpg-card/90 shadow-sm border border-rpg-border'
                      : 'text-slate-300 hover:text-white hover:bg-slate-800/40'
                  }`}
                >
                  {item.label}
                </button>
              );
            })}
          </nav>

          {/* Mobile Menu Button */}
          <div className="flex md:hidden">
            <button
              onClick={() => setMobileMenuOpen(!mobileMenuOpen)}
              className="p-2 rounded-lg text-slate-400 hover:text-white hover:bg-slate-800 transition-colors"
              aria-label="Toggle Navigation Menu"
            >
              {mobileMenuOpen ? <X className="w-6 h-6" /> : <Menu className="w-6 h-6" />}
            </button>
          </div>
        </div>
      </div>

      {/* Mobile Drawer */}
      {mobileMenuOpen && (
        <div className="md:hidden border-b border-rpg-border bg-rpg-dark/95 backdrop-blur-xl px-4 pt-3 pb-6 space-y-2">
          {MAIN_NAV.map((item) => {
            const active = isActive(item.href);
            return (
              <button
                key={item.href}
                onClick={() => {
                  navigate(item.href);
                  setMobileMenuOpen(false);
                }}
                className={`w-full flex items-center justify-between px-4 py-2.5 rounded-lg text-sm font-medium transition-colors ${
                  item.highlight
                    ? 'bg-amber-500 text-slate-950 font-bold shadow-md'
                    : active
                    ? 'bg-slate-800 text-amber-400 border border-slate-700'
                    : 'text-slate-200 hover:bg-slate-800/60'
                }`}
              >
                <span>{item.label}</span>
                {item.badge && (
                  <span className="text-[10px] bg-slate-900/40 text-current px-2 py-0.5 rounded font-mono font-bold">
                    {item.badge}
                  </span>
                )}
              </button>
            );
          })}
        </div>
      )}
    </header>
  );
};

