import React, { useState } from 'react';
import { useRouter } from '../context/RouterContext';
import { DOCS, DOC_CATEGORIES, DocArticle } from '../data/docs';
import { Search, BookOpen, ChevronRight, ArrowLeft, ArrowRight, Clock, FileText, Compass, ExternalLink } from 'lucide-react';

export const DocsPage: React.FC = () => {
  const { currentPath, docSlug, navigate } = useRouter();
  const [searchQuery, setSearchQuery] = useState('');

  // Default to getting-started if on /docs or invalid slug
  const activeDoc: DocArticle = DOCS.find(d => d.slug === docSlug) || DOCS[0];
  const activeIndex = DOCS.findIndex(d => d.slug === activeDoc.slug);
  const prevDoc = activeIndex > 0 ? DOCS[activeIndex - 1] : null;
  const nextDoc = activeIndex < DOCS.length - 1 ? DOCS[activeIndex + 1] : null;

  // Filter docs by search
  const filteredDocs = searchQuery.trim() === ''
    ? DOCS
    : DOCS.filter(d => 
        d.title.toLowerCase().includes(searchQuery.toLowerCase()) ||
        d.summary.toLowerCase().includes(searchQuery.toLowerCase()) ||
        d.category.toLowerCase().includes(searchQuery.toLowerCase()) ||
        d.content.toLowerCase().includes(searchQuery.toLowerCase())
      );

  return (
    <div className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8 py-8 lg:py-12">
      <div className="grid grid-cols-1 lg:grid-cols-12 gap-8 lg:gap-12">
        
        {/* ========================================================
            SIDEBAR NAVIGATION (4 Cols on LG)
           ======================================================== */}
        <aside className="lg:col-span-4 space-y-6">
          {/* Search Bar */}
          <div className="relative">
            <Search className="w-4 h-4 text-slate-400 absolute left-3.5 top-1/2 -translate-y-1/2 pointer-events-none" />
            <input
              type="text"
              placeholder="Search documentation..."
              value={searchQuery}
              onChange={(e) => setSearchQuery(e.target.value)}
              className="w-full pl-10 pr-4 py-2.5 rounded-xl bg-rpg-card border border-rpg-border text-slate-200 placeholder-slate-500 text-sm focus:outline-none focus:border-amber-500 transition-colors"
            />
            {searchQuery && (
              <button
                onClick={() => setSearchQuery('')}
                className="absolute right-3 top-1/2 -translate-y-1/2 text-xs text-slate-400 hover:text-white"
              >
                Clear
              </button>
            )}
          </div>

          {/* Category Grouping */}
          <nav className="space-y-6">
            {DOC_CATEGORIES.map(category => {
              const categoryDocs = filteredDocs.filter(d => d.category === category);
              if (categoryDocs.length === 0) return null;

              return (
                <div key={category} className="space-y-2">
                  <h3 className="text-xs font-mono font-bold uppercase tracking-wider text-slate-400 px-3">
                    {category}
                  </h3>
                  <div className="space-y-1">
                    {categoryDocs.map(doc => {
                      const isActive = doc.slug === activeDoc.slug;
                      return (
                        <button
                          key={doc.slug}
                          onClick={() => navigate(`/docs/${doc.slug}`)}
                          className={`w-full flex items-center justify-between px-3 py-2 rounded-lg text-xs font-medium text-left transition-all ${
                            isActive
                              ? 'bg-amber-500/10 text-amber-400 border border-amber-500/30 font-bold'
                              : 'text-slate-300 hover:bg-slate-800/60 hover:text-white'
                          }`}
                        >
                          <span className="truncate">{doc.title}</span>
                          {isActive && <ChevronRight className="w-3.5 h-3.5 flex-shrink-0 text-amber-400 ml-2" />}
                        </button>
                      );
                    })}
                  </div>
                </div>
              );
            })}
          </nav>
        </aside>

        {/* ========================================================
            MAIN ARTICLE CONTENT (8 Cols on LG)
           ======================================================== */}
        <main className="lg:col-span-8 space-y-8">
          {/* Breadcrumbs & Metadata */}
          <div className="flex flex-wrap items-center justify-between gap-4 pb-4 border-b border-rpg-border text-xs text-slate-400">
            <div className="flex items-center gap-1.5 font-mono">
              <span className="hover:text-white cursor-pointer" onClick={() => navigate('/docs')}>Docs</span>
              <span>/</span>
              <span className="text-amber-400">{activeDoc.category}</span>
              <span>/</span>
              <span className="text-slate-200 truncate max-w-[200px]">{activeDoc.title}</span>
            </div>

            <div className="flex items-center gap-1.5 font-mono">
              <Clock className="w-3.5 h-3.5 text-slate-500" />
              <span>{activeDoc.readTime}</span>
            </div>
          </div>

          {/* Article Header */}
          <div className="space-y-3">
            <h1 className="font-display font-extrabold text-3xl sm:text-4xl text-white">
              {activeDoc.title}
            </h1>
            <p className="text-base text-slate-300 leading-relaxed font-normal bg-rpg-card/60 p-4 rounded-xl border border-rpg-border">
              {activeDoc.summary}
            </p>
          </div>

          {/* Article Body Content (Formatted Markdown) */}
          <article className="prose prose-invert prose-amber max-w-none space-y-6 text-sm text-slate-300 leading-relaxed">
            {activeDoc.content.split('\n\n').map((paragraph, index) => {
              const trimmed = paragraph.trim();

              // Heading 3
              if (trimmed.startsWith('### ')) {
                return (
                  <h3 key={index} className="font-display font-bold text-xl sm:text-2xl text-white pt-4 pb-1 border-b border-rpg-border/60">
                    {trimmed.replace('### ', '')}
                  </h3>
                );
              }

              // Heading 4
              if (trimmed.startsWith('#### ')) {
                return (
                  <h4 key={index} className="font-display font-bold text-base sm:text-lg text-amber-400 pt-3">
                    {trimmed.replace('#### ', '')}
                  </h4>
                );
              }

              // Table
              if (trimmed.includes('|') && trimmed.includes('---')) {
                const lines = trimmed.split('\n').filter(l => l.trim().length > 0);
                const headerLine = lines[0];
                const dataLines = lines.slice(2);
                const headers = headerLine.split('|').filter(c => c.trim().length > 0);

                return (
                  <div key={index} className="overflow-x-auto my-4 rounded-xl border border-rpg-border bg-rpg-card">
                    <table className="w-full text-left text-xs border-collapse">
                      <thead>
                        <tr className="border-b border-rpg-border bg-slate-900/80 font-mono text-slate-200">
                          {headers.map((h, hi) => (
                            <th key={hi} className="p-3 font-bold uppercase">{h.trim()}</th>
                          ))}
                        </tr>
                      </thead>
                      <tbody className="divide-y divide-slate-800">
                        {dataLines.map((row, ri) => {
                          const cells = row.split('|').filter(c => c.trim().length > 0);
                          return (
                            <tr key={ri} className="hover:bg-slate-800/40">
                              {cells.map((cell, ci) => (
                                <td key={ci} className="p-3 text-slate-300">{cell.trim().replace(/\*\*/g, '')}</td>
                              ))}
                            </tr>
                          );
                        })}
                      </tbody>
                    </table>
                  </div>
                );
              }

              // Code block
              if (trimmed.startsWith('```')) {
                const codeContent = trimmed.replace(/^```[a-z]*\n?/, '').replace(/\n?```$/, '');
                return (
                  <div key={index} className="p-4 rounded-xl bg-slate-950 border border-slate-800 font-mono text-xs text-amber-300 overflow-x-auto my-3 leading-normal">
                    <pre>{codeContent}</pre>
                  </div>
                );
              }

              // Numbered list
              if (/^[0-9]+\.\s/.test(trimmed)) {
                const listItems = trimmed.split(/\n(?=[0-9]+\.\s)/);
                return (
                  <ol key={index} className="space-y-3 pl-2 my-3">
                    {listItems.map((item, li) => {
                      const cleanItem = item.replace(/^[0-9]+\.\s\*\*/, '').replace(/\*\*:/, ':');
                      return (
                        <li key={li} className="flex items-start gap-3 text-xs sm:text-sm">
                          <span className="w-5 h-5 rounded-full bg-amber-500/20 text-amber-400 font-mono font-bold text-xs flex items-center justify-center flex-shrink-0 mt-0.5">
                            {li + 1}
                          </span>
                          <span className="leading-relaxed">{cleanItem}</span>
                        </li>
                      );
                    })}
                  </ol>
                );
              }

              // Bullet list
              if (trimmed.startsWith('- ')) {
                const items = trimmed.split('\n- ');
                return (
                  <ul key={index} className="space-y-2 pl-2 my-3">
                    {items.map((item, bi) => (
                      <li key={bi} className="flex items-start gap-2.5 text-xs sm:text-sm">
                        <span className="w-1.5 h-1.5 rounded-full bg-amber-400 flex-shrink-0 mt-2"></span>
                        <span className="leading-relaxed">{item.replace(/^- /, '')}</span>
                      </li>
                    ))}
                  </ul>
                );
              }

              // Standard paragraph
              return (
                <p key={index} className="leading-relaxed">
                  {trimmed}
                </p>
              );
            })}
          </article>

          {/* Prev / Next Article Navigation Footer */}
          <div className="pt-8 border-t border-rpg-border flex flex-col sm:flex-row items-center justify-between gap-4">
            {prevDoc ? (
              <button
                onClick={() => navigate(`/docs/${prevDoc.slug}`)}
                className="w-full sm:w-auto p-4 rounded-xl border border-rpg-border bg-rpg-card hover:bg-slate-800 text-left transition-colors flex items-center gap-3 group"
              >
                <ArrowLeft className="w-5 h-5 text-slate-400 group-hover:text-amber-400 transition-colors flex-shrink-0" />
                <div>
                  <div className="text-[10px] font-mono uppercase text-slate-400">Previous Article</div>
                  <div className="text-xs sm:text-sm font-bold text-white group-hover:text-amber-400 transition-colors">{prevDoc.title}</div>
                </div>
              </button>
            ) : <div />}

            {nextDoc && (
              <button
                onClick={() => navigate(`/docs/${nextDoc.slug}`)}
                className="w-full sm:w-auto p-4 rounded-xl border border-rpg-border bg-rpg-card hover:bg-slate-800 text-right transition-colors flex items-center justify-end gap-3 group ml-auto"
              >
                <div>
                  <div className="text-[10px] font-mono uppercase text-slate-400">Next Article</div>
                  <div className="text-xs sm:text-sm font-bold text-white group-hover:text-amber-400 transition-colors">{nextDoc.title}</div>
                </div>
                <ArrowRight className="w-5 h-5 text-slate-400 group-hover:text-amber-400 transition-colors flex-shrink-0" />
              </button>
            )}
          </div>
        </main>

      </div>
    </div>
  );
};

