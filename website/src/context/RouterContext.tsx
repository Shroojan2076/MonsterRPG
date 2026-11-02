import React, { createContext, useContext, useEffect, useState } from 'react';

interface RouterContextType {
  currentPath: string;
  docSlug?: string;
  navigate: (path: string) => void;
}

const RouterContext = createContext<RouterContextType>({
  currentPath: '/',
  navigate: () => {}
});

export const RouterProvider: React.FC<{ children: React.ReactNode }> = ({ children }) => {
  const getHashPath = () => {
    const hash = window.location.hash.replace(/^#/, '');
    if (!hash || hash === '') return '/';
    return hash.startsWith('/') ? hash : `/${hash}`;
  };

  const [currentPath, setCurrentPath] = useState<string>(getHashPath());

  useEffect(() => {
    const handleHashChange = () => {
      const path = getHashPath();
      setCurrentPath(path);
      window.scrollTo(0, 0);
    };

    window.addEventListener('hashchange', handleHashChange);
    return () => window.removeEventListener('hashchange', handleHashChange);
  }, []);

  const navigate = (path: string) => {
    const cleanPath = path.startsWith('#') ? path.replace(/^#/, '') : path;
    window.location.hash = cleanPath.startsWith('/') ? cleanPath : `/${cleanPath}`;
  };

  // Parse doc slug if on /docs/:slug
  let docSlug: string | undefined = undefined;
  if (currentPath.startsWith('/docs/')) {
    docSlug = currentPath.replace('/docs/', '').split('/')[0];
  }

  return (
    <RouterContext.Provider value={{ currentPath, docSlug, navigate }}>
      {children}
    </RouterContext.Provider>
  );
};

export const useRouter = () => useContext(RouterContext);

