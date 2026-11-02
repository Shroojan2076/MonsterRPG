import React, { useState } from 'react';
import { useRouter } from '../context/RouterContext';
import releasesData from '../data/releases.json';
import { History, Tag, Sparkles, Wrench, Bug, AlertCircle, Download, Check } from 'lucide-react';

export const ChangelogPage: React.FC = () => {
  const { navigate } = useRouter();
  const [selectedVersion, setSelectedVersion] = useState<string>('all');

  const allReleases = releasesData.releases;

  const filteredReleases = selectedVersion === 'all'
    ? allReleases
    : allReleases.filter(r => r.version === selectedVersion);

  return (
    <div className="max-w-5xl mx-auto px-4 sm:px-6 lg:px-8 py-12 lg:py-16 space-y-12">
      {/* Header */}
      <div className="space-y-4">
        <div className="inline-flex items-center gap-2 px-3 py-1 rounded-full bg-amber-500/10 border border-amber-500/30 text-amber-400 text-xs font-mono font-bold uppercase tracking-wider">
          <History className="w-3.5 h-3.5" />
          Release Notes &amp; History
        </div>
        <h1 className="font-display font-black text-4xl sm:text-5xl text-white tracking-tight">
          Changelog
        </h1>
        <p className="text-base text-slate-300 leading-relaxed max-w-2xl">
          Comprehensive release notes, feature highlights, optimizations, and bug fixes across all released builds of MonsterRPG.
        </p>

        {/* Filter Pills */}
        <div className="flex flex-wrap gap-2 pt-2">
          <button
            onClick={() => setSelectedVersion('all')}
            className={`px-3 py-1.5 rounded-lg text-xs font-mono font-bold transition-colors ${
              selectedVersion === 'all'
                ? 'bg-amber-500 text-slate-950'
                : 'bg-rpg-card text-slate-300 border border-rpg-border hover:bg-slate-800'
            }`}
          >
            All Releases ({allReleases.length})
          </button>
          {allReleases.map(r => (
            <button
              key={r.version}
              onClick={() => setSelectedVersion(r.version)}
              className={`px-3 py-1.5 rounded-lg text-xs font-mono font-bold transition-colors ${
                selectedVersion === r.version
                  ? 'bg-amber-500 text-slate-950'
                  : 'bg-rpg-card text-slate-300 border border-rpg-border hover:bg-slate-800'
              }`}
            >
              {r.version}
            </button>
          ))}
        </div>
      </div>

      {/* Release Timeline */}
      <div className="space-y-12 relative before:absolute before:inset-0 before:left-4 md:before:left-6 before:w-0.5 before:bg-rpg-border/60">
        {filteredReleases.map((release) => (
          <div key={release.version} className="relative pl-10 md:pl-14 space-y-6">
            
            {/* Timeline node icon */}
            <div className="absolute left-1.5 md:left-3.5 top-1.5 w-6 h-6 rounded-full bg-rpg-darkest border-2 border-amber-500 flex items-center justify-center -translate-x-1/2 shadow-md">
              <div className="w-2 h-2 rounded-full bg-amber-400"></div>
            </div>

            {/* Release Header Card */}
            <div className="p-6 rounded-2xl border border-rpg-border bg-rpg-card space-y-4">
              <div className="flex flex-wrap items-center justify-between gap-4 pb-4 border-b border-slate-800">
                <div>
                  <div className="flex items-center gap-3">
                    <h2 className="font-display font-extrabold text-2xl text-white">
                      {release.version}
                    </h2>
                    <span className="text-sm font-semibold text-amber-400 font-display">
                      "{release.codename}"
                    </span>
                    <span className="text-[10px] font-mono bg-slate-800 text-slate-300 px-2 py-0.5 rounded border border-slate-700">
                      {release.type}
                    </span>
                  </div>
                  <div className="text-xs text-slate-400 mt-1">
                    Released on {release.date}
                  </div>
                </div>

                {release.downloadUrl ? (
                  <button
                    onClick={() => navigate('/download')}
                    className="inline-flex items-center gap-2 px-4 py-2 rounded-lg bg-amber-500 hover:bg-amber-400 text-slate-950 font-bold text-xs shadow-md transition-all"
                  >
                    <Download className="w-4 h-4" />
                    <span>Download {release.version}</span>
                  </button>
                ) : (
                  <span className="text-xs font-mono text-slate-500">
                    Archived Build
                  </span>
                )}
              </div>

              {/* Features List */}
              {release.features && release.features.length > 0 && (
                <div className="space-y-2.5">
                  <h3 className="text-xs font-mono font-bold text-amber-400 uppercase tracking-wider flex items-center gap-2">
                    <Sparkles className="w-3.5 h-3.5" />
                    New Features &amp; Additions
                  </h3>
                  <ul className="space-y-1.5 text-xs text-slate-300">
                    {release.features.map((f, fi) => (
                      <li key={fi} className="flex items-start gap-2.5">
                        <span className="text-emerald-400 font-bold mt-0.5">&bull;</span>
                        <span>{f}</span>
                      </li>
                    ))}
                  </ul>
                </div>
              )}

              {/* Improvements */}
              {release.improvements && release.improvements.length > 0 && (
                <div className="space-y-2.5 pt-2">
                  <h3 className="text-xs font-mono font-bold text-sky-400 uppercase tracking-wider flex items-center gap-2">
                    <Wrench className="w-3.5 h-3.5" />
                    Improvements &amp; Optimizations
                  </h3>
                  <ul className="space-y-1.5 text-xs text-slate-300">
                    {release.improvements.map((imp, ii) => (
                      <li key={ii} className="flex items-start gap-2.5">
                        <span className="text-sky-400 font-bold mt-0.5">&bull;</span>
                        <span>{imp}</span>
                      </li>
                    ))}
                  </ul>
                </div>
              )}

              {/* Fixes */}
              {release.fixes && release.fixes.length > 0 && (
                <div className="space-y-2.5 pt-2">
                  <h3 className="text-xs font-mono font-bold text-emerald-400 uppercase tracking-wider flex items-center gap-2">
                    <Bug className="w-3.5 h-3.5" />
                    Bug Fixes
                  </h3>
                  <ul className="space-y-1.5 text-xs text-slate-300">
                    {release.fixes.map((fix, fxi) => (
                      <li key={fxi} className="flex items-start gap-2.5">
                        <span className="text-emerald-400 font-bold mt-0.5">&bull;</span>
                        <span>{fix}</span>
                      </li>
                    ))}
                  </ul>
                </div>
              )}

              {/* Known Issues */}
              {release.knownIssues && release.knownIssues.length > 0 && (
                <div className="space-y-2.5 pt-2 border-t border-slate-800">
                  <h3 className="text-xs font-mono font-bold text-amber-500 uppercase tracking-wider flex items-center gap-2">
                    <AlertCircle className="w-3.5 h-3.5" />
                    Known Issues &amp; Next Milestone
                  </h3>
                  <ul className="space-y-1.5 text-xs text-slate-400">
                    {release.knownIssues.map((issue, isi) => (
                      <li key={isi} className="flex items-start gap-2.5">
                        <span className="text-amber-500/70 font-bold mt-0.5">&bull;</span>
                        <span>{issue}</span>
                      </li>
                    ))}
                  </ul>
                </div>
              )}
            </div>

          </div>
        ))}
      </div>
    </div>
  );
};

