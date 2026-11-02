import React, { useState } from 'react';
import { Lightbox, LightboxImage } from '../components/Lightbox';
import galleryData from '../data/gallery.json';
import { Image as ImageIcon, Filter, Maximize2 } from 'lucide-react';

export const GalleryPage: React.FC = () => {
  const [selectedCategory, setSelectedCategory] = useState<string>('All');
  const [lightboxIndex, setLightboxIndex] = useState<number | null>(null);

  const categories = ['All', 'Overworld', 'Interiors', 'Combat', 'Exploration', 'Boss Encounter'];

  const filteredImages = selectedCategory === 'All'
    ? galleryData
    : galleryData.filter(item => item.category === selectedCategory || item.tags.includes(selectedCategory));

  const lightboxImages: LightboxImage[] = filteredImages.map(img => ({
    id: img.id,
    title: img.title,
    image: img.image,
    caption: img.caption,
    category: img.category
  }));

  return (
    <div className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8 py-12 lg:py-16 space-y-12">
      {/* Header */}
      <div className="text-center max-w-3xl mx-auto space-y-3">
        <div className="inline-flex items-center gap-2 px-3 py-1 rounded-full bg-amber-500/10 border border-amber-500/30 text-amber-400 text-xs font-mono font-bold uppercase tracking-wider">
          <ImageIcon className="w-3.5 h-3.5" />
          Official In-Game Showcase
        </div>
        <h1 className="font-display font-black text-4xl sm:text-5xl text-white tracking-tight">
          Visual Gallery
        </h1>
        <p className="text-base text-slate-300 leading-relaxed">
          High-resolution captures taken directly from the running C++ engine. Inspect town environments, interior lab facilities, wild forest clearings, and tactical battle scenes.
        </p>
      </div>

      {/* Filter Tabs */}
      <div className="flex flex-wrap items-center justify-center gap-2 pt-2">
        {categories.map((cat) => (
          <button
            key={cat}
            onClick={() => setSelectedCategory(cat)}
            className={`px-4 py-2 rounded-lg text-xs font-medium font-mono uppercase tracking-wider transition-all ${
              selectedCategory === cat
                ? 'bg-amber-500 text-slate-950 font-bold shadow-md shadow-amber-500/20'
                : 'bg-rpg-card hover:bg-slate-800 text-slate-300 border border-rpg-border hover:border-slate-600'
            }`}
          >
            {cat}
          </button>
        ))}
      </div>

      {/* Responsive Gallery Grid */}
      <div className="grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 gap-6">
        {filteredImages.map((item, index) => (
          <div
            key={item.id}
            onClick={() => setLightboxIndex(index)}
            className="group cursor-pointer rounded-xl border border-rpg-border bg-rpg-card overflow-hidden hover:border-amber-500/60 transition-all duration-300 hover:shadow-xl hover:-translate-y-1"
          >
            {/* Thumbnail Box */}
            <div className="relative aspect-[3/2] overflow-hidden bg-slate-950">
              <img
                src={item.image}
                alt={item.title}
                className="w-full h-full object-cover group-hover:scale-105 transition-transform duration-500"
                style={{ imageRendering: 'pixelated' }}
                loading="lazy"
              />
              <div className="absolute inset-0 bg-black/40 opacity-0 group-hover:opacity-100 transition-opacity flex items-center justify-center">
                <div className="p-3 rounded-full bg-slate-900/90 text-amber-400 border border-amber-500/40 shadow-lg transform scale-90 group-hover:scale-100 transition-transform">
                  <Maximize2 className="w-5 h-5" />
                </div>
              </div>
              <span className="absolute top-3 left-3 text-[10px] font-mono font-bold uppercase tracking-wider bg-slate-950/90 text-amber-300 px-2.5 py-1 rounded border border-amber-500/30">
                {item.category}
              </span>
            </div>

            {/* Info Box */}
            <div className="p-4 sm:p-5 space-y-2">
              <h3 className="font-display font-bold text-base sm:text-lg text-white group-hover:text-amber-400 transition-colors">
                {item.title}
              </h3>
              <p className="text-xs text-slate-400 line-clamp-2 leading-relaxed">
                {item.caption}
              </p>
              <div className="flex flex-wrap gap-1.5 pt-2">
                {item.tags.map(tag => (
                  <span key={tag} className="text-[10px] font-mono text-slate-400 bg-slate-900 px-2 py-0.5 rounded border border-slate-800">
                    #{tag}
                  </span>
                ))}
              </div>
            </div>
          </div>
        ))}
      </div>

      {/* Lightbox Modal */}
      {lightboxIndex !== null && (
        <Lightbox
          images={lightboxImages}
          currentIndex={lightboxIndex}
          onClose={() => setLightboxIndex(null)}
          onNavigate={(index) => setLightboxIndex(index)}
        />
      )}
    </div>
  );
};

