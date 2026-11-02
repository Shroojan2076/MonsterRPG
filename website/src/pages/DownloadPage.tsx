import React, { useState } from 'react';
import { useRouter } from '../context/RouterContext';
import releasesData from '../data/releases.json';
import { Download, Check, Copy, ShieldCheck, Terminal, AlertTriangle, HardDrive, Cpu, Monitor, FileCode2, History } from 'lucide-react';

export const DownloadPage: React.FC = () => {
  const { navigate } = useRouter();
  const current = releasesData.currentRelease;
  const previousReleases = releasesData.releases.slice(1);
  const [copiedSha, setCopiedSha] = useState(false);

  const handleCopySha = () => {
    navigator.clipboard.writeText(current.sha256);
    setCopiedSha(true);
    setTimeout(() => setCopiedSha(false), 2500);
  };

  return (
    <div className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8 py-12 lg:py-16 space-y-16">
      {/* Header */}
      <div className="text-center max-w-3xl mx-auto space-y-3">
        <div className="inline-flex items-center gap-2 px-3 py-1 rounded-full bg-emerald-500/10 border border-emerald-500/30 text-emerald-400 text-xs font-mono font-bold uppercase tracking-wider">
          <ShieldCheck className="w-3.5 h-3.5" />
          Official Release Platform
        </div>
        <h1 className="font-display font-black text-4xl sm:text-5xl text-white tracking-tight">
          Download MonsterRPG
        </h1>
        <p className="text-base text-slate-300 leading-relaxed">
          Get the official release package for Windows 64-bit. Fully portable with zero installation required — simply extract and embark on your journey.
        </p>
      </div>

      {/* Main Release Download Card */}
      <div className="max-w-4xl mx-auto rounded-3xl border-2 border-amber-500/30 bg-gradient-to-b from-rpg-card via-rpg-dark to-slate-950 p-8 sm:p-12 shadow-2xl relative overflow-hidden">
        <div className="absolute top-0 right-0 p-8 opacity-10 pointer-events-none">
          <Download className="w-48 h-48 text-amber-500" />
        </div>

        <div className="space-y-8 relative z-10">
          {/* Top release metadata */}
          <div className="flex flex-wrap items-center justify-between gap-4 pb-6 border-b border-rpg-border">
            <div>
              <div className="flex items-center gap-3">
                <h2 className="font-display font-extrabold text-2xl sm:text-3xl text-white">
                  MonsterRPG {current.version}
                </h2>
                <span className="text-xs font-mono font-bold uppercase bg-emerald-500/20 text-emerald-400 border border-emerald-500/40 px-2.5 py-0.5 rounded-full">
                  {current.statusBadge}
                </span>
              </div>
              <p className="text-xs text-slate-400 mt-1">
                Released on {current.releaseDate} • Architecture: {current.architecture}
              </p>
            </div>

            <div className="text-right">
              <div className="text-xs font-mono text-slate-400">Package Size</div>
              <div className="font-bold font-mono text-lg text-amber-400">{current.fileSize}</div>
            </div>
          </div>

          {/* Description & Highlights */}
          <div className="space-y-4">
            <p className="text-sm text-slate-300 leading-relaxed">
              {current.summary}
            </p>

            <div className="grid grid-cols-1 sm:grid-cols-2 gap-2.5 pt-2">
              {current.highlights.map((h, i) => (
                <div key={i} className="flex items-start gap-2 text-xs text-slate-300">
                  <Check className="w-4 h-4 text-emerald-400 flex-shrink-0 mt-0.5" />
                  <span>{h}</span>
                </div>
              ))}
            </div>
          </div>

          {/* Primary Action Button */}
          <div className="pt-2 flex flex-col sm:flex-row items-center gap-4">
            <a
              href={current.downloadUrl}
              download={current.filename}
              className="w-full sm:w-auto inline-flex items-center justify-center gap-3 px-8 py-4 rounded-xl bg-gradient-to-r from-amber-500 to-amber-600 hover:from-amber-400 hover:to-amber-500 text-slate-950 font-black text-base shadow-xl shadow-amber-500/25 transition-all transform hover:-translate-y-0.5 active:translate-y-0"
            >
              <Download className="w-5 h-5 text-slate-950" />
              <span>Download {current.filename}</span>
            </a>

            <button
              onClick={() => navigate('/changelog')}
              className="w-full sm:w-auto px-6 py-4 rounded-xl bg-slate-800 hover:bg-slate-700 text-slate-200 font-semibold text-sm border border-slate-700 transition-colors"
            >
              View Full Changelog
            </button>
          </div>

          {/* Checksum & Integrity Box */}
          <div className="p-4 rounded-xl bg-slate-950/80 border border-slate-800 flex flex-col sm:flex-row items-start sm:items-center justify-between gap-3 text-xs">
            <div className="font-mono text-slate-400 break-all">
              <span className="text-slate-500 uppercase font-bold mr-2">SHA-256:</span>
              <span className="text-slate-300">{current.sha256}</span>
            </div>
            <button
              onClick={handleCopySha}
              className="flex-shrink-0 inline-flex items-center gap-1.5 px-3 py-1.5 rounded-lg bg-slate-900 hover:bg-slate-800 text-slate-300 border border-slate-700 transition-colors font-mono"
            >
              {copiedSha ? (
                <>
                  <Check className="w-3.5 h-3.5 text-emerald-400" />
                  <span className="text-emerald-400">Copied!</span>
                </>
              ) : (
                <>
                  <Copy className="w-3.5 h-3.5 text-slate-400" />
                  <span>Copy Hash</span>
                </>
              )}
            </button>
          </div>
        </div>
      </div>

      {/* System Requirements Comparison */}
      <section className="space-y-6">
        <div className="text-center max-w-2xl mx-auto space-y-2">
          <h2 className="font-display font-extrabold text-2xl sm:text-3xl text-white">
            System Requirements
          </h2>
          <p className="text-xs sm:text-sm text-slate-400">
            MonsterRPG is engineered for efficiency with hardware-accelerated 2D rendering.
          </p>
        </div>

        <div className="grid grid-cols-1 md:grid-cols-2 gap-6 max-w-4xl mx-auto">
          {/* Minimum */}
          <div className="p-6 rounded-2xl border border-rpg-border bg-rpg-card space-y-4">
            <h3 className="font-display font-bold text-lg text-white flex items-center gap-2">
              <HardDrive className="w-5 h-5 text-slate-400" />
              Minimum Specifications
            </h3>
            <div className="space-y-2.5 text-xs text-slate-300 font-mono">
              <div className="flex justify-between py-1 border-b border-slate-800">
                <span className="text-slate-400">OS:</span>
                <span className="text-right">{current.systemRequirements.minimum.os}</span>
              </div>
              <div className="flex justify-between py-1 border-b border-slate-800">
                <span className="text-slate-400">CPU:</span>
                <span className="text-right">{current.systemRequirements.minimum.processor}</span>
              </div>
              <div className="flex justify-between py-1 border-b border-slate-800">
                <span className="text-slate-400">RAM:</span>
                <span className="text-right">{current.systemRequirements.minimum.memory}</span>
              </div>
              <div className="flex justify-between py-1 border-b border-slate-800">
                <span className="text-slate-400">GPU:</span>
                <span className="text-right">{current.systemRequirements.minimum.graphics}</span>
              </div>
              <div className="flex justify-between py-1">
                <span className="text-slate-400">Disk:</span>
                <span className="text-right">{current.systemRequirements.minimum.storage}</span>
              </div>
            </div>
          </div>

          {/* Recommended */}
          <div className="p-6 rounded-2xl border border-amber-500/40 bg-gradient-to-b from-rpg-card to-rpg-dark space-y-4">
            <h3 className="font-display font-bold text-lg text-amber-400 flex items-center gap-2">
              <Cpu className="w-5 h-5 text-amber-400" />
              Recommended Specifications
            </h3>
            <div className="space-y-2.5 text-xs text-slate-300 font-mono">
              <div className="flex justify-between py-1 border-b border-slate-800">
                <span className="text-slate-400">OS:</span>
                <span className="text-right">{current.systemRequirements.recommended.os}</span>
              </div>
              <div className="flex justify-between py-1 border-b border-slate-800">
                <span className="text-slate-400">CPU:</span>
                <span className="text-right">{current.systemRequirements.recommended.processor}</span>
              </div>
              <div className="flex justify-between py-1 border-b border-slate-800">
                <span className="text-slate-400">RAM:</span>
                <span className="text-right">{current.systemRequirements.recommended.memory}</span>
              </div>
              <div className="flex justify-between py-1 border-b border-slate-800">
                <span className="text-slate-400">GPU:</span>
                <span className="text-right">{current.systemRequirements.recommended.graphics}</span>
              </div>
              <div className="flex justify-between py-1">
                <span className="text-slate-400">Disk:</span>
                <span className="text-right">{current.systemRequirements.recommended.storage}</span>
              </div>
            </div>
          </div>
        </div>
      </section>

      {/* Step-by-Step Installation & Quickstart */}
      <section className="max-w-4xl mx-auto space-y-6">
        <h2 className="font-display font-extrabold text-2xl text-white">
          Installation &amp; First Launch Guide
        </h2>

        <div className="grid grid-cols-1 sm:grid-cols-3 gap-4">
          <div className="p-5 rounded-xl border border-rpg-border bg-rpg-card space-y-2">
            <div className="w-7 h-7 rounded-full bg-amber-500/20 text-amber-400 font-mono font-bold flex items-center justify-center text-xs">
              1
            </div>
            <h3 className="font-bold text-white text-sm">Download Archive</h3>
            <p className="text-xs text-slate-400 leading-relaxed">
              Download the official release zip package using the primary button above.
            </p>
          </div>

          <div className="p-5 rounded-xl border border-rpg-border bg-rpg-card space-y-2">
            <div className="w-7 h-7 rounded-full bg-amber-500/20 text-amber-400 font-mono font-bold flex items-center justify-center text-xs">
              2
            </div>
            <h3 className="font-bold text-white text-sm">Extract Entire Folder</h3>
            <p className="text-xs text-slate-400 leading-relaxed">
              Extract all files into a local folder. Ensure <code className="text-amber-400">assets</code> remains in the same folder as <code className="text-amber-400">MonsterRPG.exe</code>.
            </p>
          </div>

          <div className="p-5 rounded-xl border border-rpg-border bg-rpg-card space-y-2">
            <div className="w-7 h-7 rounded-full bg-amber-500/20 text-amber-400 font-mono font-bold flex items-center justify-center text-xs">
              3
            </div>
            <h3 className="font-bold text-white text-sm">Run &amp; Explore</h3>
            <p className="text-xs text-slate-400 leading-relaxed">
              Double click <code className="text-amber-400">MonsterRPG.exe</code> to start! Use WASD to move and E to talk to Prof. Oak.
            </p>
          </div>
        </div>
      </section>

      {/* Troubleshooting Checklist */}
      <section className="max-w-4xl mx-auto p-6 rounded-2xl border border-rpg-border bg-slate-900/60 space-y-4">
        <h3 className="font-bold text-white text-base flex items-center gap-2">
          <AlertTriangle className="w-5 h-5 text-amber-400" />
          Common Setup Troubleshooting
        </h3>
        <div className="space-y-3 text-xs text-slate-300">
          <div>
            <strong className="text-white">&bull; VCRUNTIME140.dll / MSVCP140.dll Error:</strong> If Windows complains about missing runtime libraries, download and install the official Microsoft Visual C++ 2015-2022 Redistributable (x64).
          </div>
          <div>
            <strong className="text-white">&bull; Black Screen on Launch:</strong> Make sure you extracted the <code className="text-amber-400">assets</code> folder alongside <code className="text-amber-400">MonsterRPG.exe</code>. The executable relies on the assets directory to load textures, fonts, and tiles.
          </div>
          <div>
            <strong className="text-white">&bull; High-DPI Display Scaling:</strong> If pixel art appears blurry on 4K monitors, right click <code className="text-amber-400">MonsterRPG.exe</code> &rarr; Properties &rarr; Compatibility &rarr; Change high DPI settings &rarr; Override high DPI scaling behavior set to "Application".
          </div>
        </div>
      </section>

      {/* Previous Releases Archive */}
      {previousReleases.length > 0 && (
        <section className="max-w-4xl mx-auto space-y-4 pt-6 border-t border-rpg-border">
          <h3 className="font-bold text-white text-lg flex items-center gap-2">
            <History className="w-5 h-5 text-slate-400" />
            Previous Releases &amp; Milestones
          </h3>
          <div className="space-y-3">
            {previousReleases.map(rel => (
              <div key={rel.version} className="p-4 rounded-xl border border-rpg-border bg-rpg-card flex items-center justify-between text-xs">
                <div>
                  <div className="font-bold text-white text-sm">{rel.version} — {rel.codename}</div>
                  <div className="text-slate-400 mt-0.5">{rel.date} • {rel.type}</div>
                </div>
                <button
                  onClick={() => navigate('/changelog')}
                  className="text-amber-400 hover:text-amber-300 font-semibold transition-colors"
                >
                  View Release Notes &rarr;
                </button>
              </div>
            ))}
          </div>
        </section>
      )}
    </div>
  );
};

