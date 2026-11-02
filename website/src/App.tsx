import React from 'react';
import { useRouter } from './context/RouterContext';
import { Navbar } from './components/Navbar';
import { Footer } from './components/Footer';

// Pages
import { HomePage } from './pages/HomePage';
import { AboutPage } from './pages/AboutPage';
import { FeaturesPage } from './pages/FeaturesPage';
import { GalleryPage } from './pages/GalleryPage';
import { DownloadPage } from './pages/DownloadPage';
import { DocsPage } from './pages/DocsPage';
import { ChangelogPage } from './pages/ChangelogPage';
import { DevelopmentPage } from './pages/DevelopmentPage';
import { FAQPage } from './pages/FAQPage';
import { AlertCircle } from 'lucide-react';

export const App: React.FC = () => {
  const { currentPath, navigate } = useRouter();

  // Router dispatcher
  const renderCurrentPage = () => {
    if (currentPath === '/' || currentPath === '') return <HomePage />;
    if (currentPath === '/about') return <AboutPage />;
    if (currentPath === '/features') return <FeaturesPage />;
    if (currentPath === '/gallery') return <GalleryPage />;
    if (currentPath === '/download') return <DownloadPage />;
    if (currentPath.startsWith('/docs')) return <DocsPage />;
    if (currentPath === '/changelog') return <ChangelogPage />;
    if (currentPath === '/development') return <DevelopmentPage />;
    if (currentPath === '/faq') return <FAQPage />;

    // 404 Fallback
    return (
      <div className="max-w-2xl mx-auto px-4 py-24 text-center space-y-6">
        <div className="w-16 h-16 rounded-full bg-amber-500/10 text-amber-400 border border-amber-500/30 flex items-center justify-center mx-auto">
          <AlertCircle className="w-8 h-8" />
        </div>
        <h1 className="font-display font-black text-3xl sm:text-4xl text-white">
          Page Not Found (404)
        </h1>
        <p className="text-sm text-slate-400">
          The requested page <code className="text-amber-400 font-mono">{currentPath}</code> does not exist in the Oakdale region.
        </p>
        <div>
          <button
            onClick={() => navigate('/')}
            className="px-6 py-3 rounded-xl bg-amber-500 hover:bg-amber-400 text-slate-950 font-bold text-sm transition-colors"
          >
            Return to Town Square
          </button>
        </div>
      </div>
    );
  };

  return (
    <div className="min-h-screen flex flex-col bg-rpg-darkest text-slate-100 selection:bg-amber-500 selection:text-slate-950 font-sans">
      <Navbar />
      <main className="flex-1">
        {renderCurrentPage()}
      </main>
      <Footer />
    </div>
  );
};
