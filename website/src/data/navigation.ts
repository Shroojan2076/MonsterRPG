export interface NavItem {
  label: string;
  href: string;
  badge?: string;
  highlight?: boolean;
}

export const MAIN_NAV: NavItem[] = [
  { label: "Home", href: "#/" },
  { label: "The Game", href: "#/about" },
  { label: "Features", href: "#/features" },
  { label: "Gallery", href: "#/gallery" },
  { label: "Documentation", href: "#/docs" },
  { label: "Changelog", href: "#/changelog" },
  { label: "Development", href: "#/development" },
  { label: "Download", href: "#/download", highlight: true, badge: "v1.0" }
];

export const FOOTER_SECTIONS = [
  {
    title: "Discover",
    links: [
      { label: "Overview", href: "#/about" },
      { label: "Core Features", href: "#/features" },
      { label: "Visual Gallery", href: "#/gallery" },
      { label: "Monster Pokédex", href: "#/docs/monster-guide" }
    ]
  },
  {
    title: "Documentation",
    links: [
      { label: "Getting Started", href: "#/docs/getting-started" },
      { label: "Installation Guide", href: "#/docs/installation-guide" },
      { label: "Controls Reference", href: "#/docs/controls" },
      { label: "Battle Mechanics", href: "#/docs/battle-mechanics" },
      { label: "Elemental Type Chart", href: "#/docs/element-types" }
    ]
  },
  {
    title: "Release & Project",
    links: [
      { label: "Download Latest Build", href: "#/download" },
      { label: "Release Notes", href: "#/changelog" },
      { label: "Technical Architecture", href: "#/development" },
      { label: "FAQ & Support", href: "#/faq" },
      { label: "Troubleshooting", href: "#/docs/troubleshooting" }
    ]
  }
];

