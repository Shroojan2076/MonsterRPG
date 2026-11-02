/** @type {import('tailwindcss').Config} */
export default {
  content: [
    "./index.html",
    "./src/**/*.{js,ts,jsx,tsx}",
  ],
  theme: {
    extend: {
      colors: {
        rpg: {
          darkest: '#0b1117',
          dark: '#121b24',
          card: '#182430',
          panel: '#1f2f3e',
          border: '#2c4053',
          muted: '#8b9bb0',
          light: '#e6edf3',
          gold: '#eab308',
          goldHover: '#facc15',
          amber: '#f59e0b',
          emerald: '#10b981',
          fire: '#f97316',
          water: '#0ea5e9',
          grass: '#22c55e',
          electric: '#eab308',
          psychic: '#a855f7',
          normal: '#94a3b8'
        }
      },
      fontFamily: {
        sans: ['Inter', 'system-ui', '-apple-system', 'sans-serif'],
        display: ['Outfit', 'Inter', 'sans-serif'],
        mono: ['JetBrains Mono', 'Fira Code', 'monospace'],
        pixel: ['"Press Start 2P"', 'monospace']
      },
      boxShadow: {
        'pixel': '0 4px 0 rgba(0, 0, 0, 0.4)',
        'pixel-lg': '0 6px 0 rgba(0, 0, 0, 0.5)',
        'panel': '0 8px 24px -4px rgba(0, 0, 0, 0.35)',
        'glow-gold': '0 0 20px -3px rgba(234, 179, 8, 0.3)'
      }
    },
  },
  plugins: [],
}

