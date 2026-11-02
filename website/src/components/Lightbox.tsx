import React, { useEffect } from 'react';
import { X, ChevronLeft, ChevronRight } from 'lucide-react';

export interface LightboxImage {
  id: string;
  title: string;
  image: string;
  caption: string;
  category: string;
}

interface LightboxProps {
  images: LightboxImage[];
  currentIndex: number;
  onClose: () => void;
  onNavigate: (index: number) => void;
}

export const Lightbox: React.FC<LightboxProps> = ({
  images,
  currentIndex,
  onClose,
  onNavigate
}) => {
  const currentImage = images[currentIndex];

  useEffect(() => {
    const handleKeyDown = (e: KeyboardEvent) => {
      if (e.key === 'Escape') onClose();
      if (e.key === 'ArrowRight') onNavigate((currentIndex + 1) % images.length);
      if (e.key === 'ArrowLeft') onNavigate((currentIndex - 1 + images.length) % images.length);
    };

    window.addEventListener('keydown', handleKeyDown);
    return () => window.removeEventListener('keydown', handleKeyDown);
  }, [currentIndex, images.length, onClose, onNavigate]);

  if (!currentImage) return null;

  return (
    <div className="fixed inset-0 z-50 flex items-center justify-center bg-black/90 backdrop-blur-md p-4 sm:p-6">
      {/* Top action bar */}
      <div className="absolute top-4 right-4 z-50 flex items-center gap-3">
        <span className="text-xs font-mono text-slate-400 bg-slate-900/80 px-2.5 py-1 rounded-md border border-slate-800">
          {currentIndex + 1} / {images.length}
        </span>
        <button
          onClick={onClose}
          className="p-2 rounded-lg bg-slate-900/80 hover:bg-slate-800 text-slate-400 hover:text-white border border-slate-800 transition-colors"
          aria-label="Close Lightbox"
        >
          <X className="w-5 h-5" />
        </button>
      </div>

      {/* Prev button */}
      <button
        onClick={() => onNavigate((currentIndex - 1 + images.length) % images.length)}
        className="absolute left-3 sm:left-6 z-50 p-3 rounded-full bg-slate-900/80 hover:bg-slate-800 text-slate-200 border border-slate-800 transition-all transform hover:scale-105"
        aria-label="Previous Image"
      >
        <ChevronLeft className="w-6 h-6" />
      </button>

      {/* Next button */}
      <button
        onClick={() => onNavigate((currentIndex + 1) % images.length)}
        className="absolute right-3 sm:right-6 z-50 p-3 rounded-full bg-slate-900/80 hover:bg-slate-800 text-slate-200 border border-slate-800 transition-all transform hover:scale-105"
        aria-label="Next Image"
      >
        <ChevronRight className="w-6 h-6" />
      </button>

      {/* Content Container */}
      <div className="max-w-5xl max-h-[90vh] flex flex-col items-center justify-center p-2">
        <div className="relative overflow-hidden rounded-xl border border-rpg-border bg-slate-950 shadow-2xl">
          <img
            src={currentImage.image}
            alt={currentImage.title}
            className="max-h-[70vh] w-auto object-contain rounded-t-xl"
            style={{ imageRendering: 'pixelated' }}
          />
          <div className="p-4 sm:p-5 bg-slate-900/95 border-t border-slate-800">
            <div className="flex items-center gap-2 mb-1.5">
              <span className="text-[10px] font-mono font-bold uppercase tracking-wider text-amber-400 bg-amber-500/10 px-2 py-0.5 rounded border border-amber-500/30">
                {currentImage.category}
              </span>
              <h3 className="font-bold text-white text-base sm:text-lg">
                {currentImage.title}
              </h3>
            </div>
            <p className="text-xs sm:text-sm text-slate-300 leading-relaxed">
              {currentImage.caption}
            </p>
          </div>
        </div>
      </div>
    </div>
  );
};

