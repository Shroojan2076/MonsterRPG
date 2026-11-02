import React, { useState } from 'react';
import { useRouter } from '../context/RouterContext';
import { HelpCircle, ChevronDown, ChevronUp, Search, MessageSquare, ArrowRight } from 'lucide-react';

interface FAQItem {
  question: string;
  category: 'General' | 'Gameplay' | 'Technical' | 'Future Updates';
  answer: string;
}

const FAQS: FAQItem[] = [
  {
    category: 'General',
    question: 'What is MonsterRPG?',
    answer: 'MonsterRPG is an authentic, retro-inspired 2D monster-catching role-playing game developed in modern C++20 and SFML. It features a continuous dual-biome world (Oakdale Town and Whispering Woods), full interior buildings, partner monster followers, and tactical turn-based elemental combat.'
  },
  {
    category: 'General',
    question: 'Is MonsterRPG free to play?',
    answer: 'Yes! MonsterRPG is released as a 100% free, open-source educational game project. There are no microtransactions, paywalls, or advertising.'
  },
  {
    category: 'Technical',
    question: 'What platforms can run MonsterRPG?',
    answer: 'MonsterRPG is officially packaged for 64-bit Windows (Windows 10 and Windows 11). Cross-platform compilation for Linux and macOS is supported via CMake and will be packaged in upcoming releases.'
  },
  {
    category: 'Technical',
    question: 'Do I need to install anything before playing?',
    answer: 'MonsterRPG is completely portable. Simply download the .zip archive from the Download page, extract all files into any folder, and double-click MonsterRPG.exe. If your system lacks standard C++ runtimes, install the official Microsoft Visual C++ 2015-2022 Redistributable (x64).'
  },
  {
    category: 'Gameplay',
    question: 'How do I get my starter Pokémon?',
    answer: 'From your spawn point in Oakdale Town Square, walk north-west to the building with the Blue Roof (Prof. Oak\'s Research Lab). Step on the door tile to enter, walk up to Professor Oak behind his desk, and press [E] or [Space]. He will welcome you and entrust you with a brave Charmander (Fire-type)!'
  },
  {
    category: 'Gameplay',
    question: 'How does the Partner Follower Pokémon work?',
    answer: 'As soon as Professor Oak gives you a starter monster, your active partner automatically steps out behind you. It follows your footsteps tile-by-tile in the overworld and indoors. You can turn towards it at any time and press [E] to check its mood and condition!'
  },
  {
    category: 'Gameplay',
    question: 'How do I run / sprint faster?',
    answer: 'Hold down the [Left Shift] key while moving with WASD or Arrow Keys. This activates the Running Shoes mechanism, boosting your movement speed from 55 px/sec to 120 px/sec and toggling your character\'s running spritesheet!'
  },
  {
    category: 'Gameplay',
    question: 'What happens if all my monsters faint in battle?',
    answer: 'MonsterRPG features a safety blackout system: if all monsters in your party faint, the screen fades to black and you are safely transported to Nurse Joy\'s reception desk at the Oakdale Pokémon Center with your party fully restored to health.'
  },
  {
    category: 'Gameplay',
    question: 'Can I capture the legendary Boss Mewtwo?',
    answer: 'No. The Forest Guardian Mewtwo is a high-level ancient entity with unyielding resolve that cannot be captured with standard Poké Balls. Your objective is to battle, test your strength, and pacify its overwhelming psionic energy.'
  },
  {
    category: 'Technical',
    question: 'How does game saving work in v1.0.0?',
    answer: 'In the v1.0.0 release, party state, starter acquisition, and boss flags persist in memory throughout your game session. Persistent file-based serialization (JSON/binary save profiles) is actively in development for the v1.1.0 update.'
  },
  {
    category: 'Future Updates',
    question: 'What features are planned for future updates?',
    answer: 'Our development roadmap includes an SFML::Audio sound engine with dynamic town, forest, and battle BGM, an in-game pause menu with party inspect, status ailments (Burn, Poison, Paralysis), and rival trainer encounters with line-of-sight challenge triggers.'
  }
];

export const FAQPage: React.FC = () => {
  const { navigate } = useRouter();
  const [selectedCategory, setSelectedCategory] = useState<string>('All');
  const [expandedIndex, setExpandedIndex] = useState<number | null>(0);
  const [searchQuery, setSearchQuery] = useState<string>('');

  const categories = ['All', 'General', 'Gameplay', 'Technical', 'Future Updates'];

  const filteredFaqs = FAQS.filter(faq => {
    const matchesCat = selectedCategory === 'All' || faq.category === selectedCategory;
    const matchesSearch = searchQuery.trim() === '' ||
      faq.question.toLowerCase().includes(searchQuery.toLowerCase()) ||
      faq.answer.toLowerCase().includes(searchQuery.toLowerCase());
    return matchesCat && matchesSearch;
  });

  return (
    <div className="max-w-4xl mx-auto px-4 sm:px-6 lg:px-8 py-12 lg:py-16 space-y-12">
      {/* Header */}
      <div className="text-center space-y-3">
        <div className="inline-flex items-center gap-2 px-3 py-1 rounded-full bg-amber-500/10 border border-amber-500/30 text-amber-400 text-xs font-mono font-bold uppercase tracking-wider">
          <HelpCircle className="w-3.5 h-3.5" />
          Got Questions?
        </div>
        <h1 className="font-display font-black text-4xl sm:text-5xl text-white tracking-tight">
          Frequently Asked Questions
        </h1>
        <p className="text-base text-slate-300 leading-relaxed max-w-xl mx-auto">
          Find answers regarding game mechanics, installation, controls, system compatibility, and development plans.
        </p>
      </div>

      {/* Search & Category Filter */}
      <div className="space-y-4">
        <div className="relative">
          <Search className="w-4 h-4 text-slate-400 absolute left-3.5 top-1/2 -translate-y-1/2 pointer-events-none" />
          <input
            type="text"
            placeholder="Search questions or keywords..."
            value={searchQuery}
            onChange={(e) => setSearchQuery(e.target.value)}
            className="w-full pl-10 pr-4 py-3 rounded-xl bg-rpg-card border border-rpg-border text-slate-200 placeholder-slate-500 text-sm focus:outline-none focus:border-amber-500 transition-colors"
          />
        </div>

        <div className="flex flex-wrap items-center justify-center gap-2">
          {categories.map((cat) => (
            <button
              key={cat}
              onClick={() => setSelectedCategory(cat)}
              className={`px-3.5 py-1.5 rounded-lg text-xs font-mono font-bold transition-colors ${
                selectedCategory === cat
                  ? 'bg-amber-500 text-slate-950 shadow-sm'
                  : 'bg-rpg-card text-slate-300 border border-rpg-border hover:bg-slate-800'
              }`}
            >
              {cat}
            </button>
          ))}
        </div>
      </div>

      {/* Accordion FAQ Items */}
      <div className="space-y-3">
        {filteredFaqs.map((faq, index) => {
          const isOpen = expandedIndex === index;

          return (
            <div
              key={index}
              className="rounded-xl border border-rpg-border bg-rpg-card overflow-hidden transition-all"
            >
              <button
                onClick={() => setExpandedIndex(isOpen ? null : index)}
                className="w-full p-5 text-left flex items-center justify-between gap-4 hover:bg-slate-800/40 transition-colors"
              >
                <div className="flex items-center gap-3">
                  <span className="text-[10px] font-mono font-bold uppercase text-amber-400 bg-amber-500/10 px-2 py-0.5 rounded border border-amber-500/30">
                    {faq.category}
                  </span>
                  <span className="font-bold text-white text-sm sm:text-base">
                    {faq.question}
                  </span>
                </div>
                {isOpen ? (
                  <ChevronUp className="w-5 h-5 text-amber-400 flex-shrink-0" />
                ) : (
                  <ChevronDown className="w-5 h-5 text-slate-400 flex-shrink-0" />
                )}
              </button>

              {isOpen && (
                <div className="px-5 pb-5 pt-1 text-xs sm:text-sm text-slate-300 leading-relaxed border-t border-slate-800">
                  {faq.answer}
                </div>
              )}
            </div>
          );
        })}

        {filteredFaqs.length === 0 && (
          <div className="text-center py-12 text-slate-400 text-sm">
            No questions matched your search criteria. Try a different query or browse categories.
          </div>
        )}
      </div>

      {/* Bottom Help Banner */}
      <div className="p-8 rounded-2xl border border-rpg-border bg-gradient-to-r from-rpg-card to-rpg-dark text-center space-y-3">
        <h3 className="font-display font-bold text-xl text-white">
          Still Have Questions?
        </h3>
        <p className="text-xs text-slate-400 max-w-md mx-auto">
          Explore our in-depth documentation articles covering battle mechanics, elemental type charts, and controls.
        </p>
        <button
          onClick={() => navigate('/docs/getting-started')}
          className="inline-flex items-center gap-1.5 px-5 py-2.5 rounded-lg bg-amber-500 hover:bg-amber-400 text-slate-950 font-bold text-xs transition-colors"
        >
          <span>Read the Documentation</span>
          <ArrowRight className="w-4 h-4" />
        </button>
      </div>
    </div>
  );
};

