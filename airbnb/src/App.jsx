import React, { useEffect, useState } from 'react';
import Header from './components/Header';
import AuthModal from './components/AuthModal';
import HomePage from './components/HomePage';
import SearchPage from './components/SearchPage';
import PropertyDetailPage from './components/PropertyDetailPage';
import BookingsPage from './components/BookingsPage';
import HostDashboard from './components/HostDashboard';
import MessagesPage from './components/MessagesPage';
import ProfilePage from './components/ProfilePage';

const VacationRentalPlatform = () => {
  const [currentPage, setCurrentPage] = useState('home');
  const [currentUser, setCurrentUser] = useState(null);
  const [showAuthModal, setShowAuthModal] = useState(false);
  const [authMode, setAuthMode] = useState('login');
  const [searchFilters, setSearchFilters] = useState({
    location: '',
    checkIn: '',
    checkOut: '',
    guests: 2,
    minPrice: 0,
    maxPrice: 500,
  });
  const [selectedProperty, setSelectedProperty] = useState(null);
  const [favorites, setFavorites] = useState([]);
  const [properties, setProperties] = useState([]);
  const [bookings, setBookings] = useState([]);
  const [showMobileMenu, setShowMobileMenu] = useState(false);

  useEffect(() => {
    setProperties([
      {
        id: 1,
        title: 'Villa moderne avec piscine',
        location: "Nice, Côte d'Azur",
        price: 180,
        rating: 4.9,
        reviews: 127,
        image:
          'https://images.unsplash.com/photo-1613490493576-7fde63acd811?w=800',
        host: 'Marie Dubois',
        beds: 4,
        baths: 2,
        guests: 8,
        amenities: ['Piscine', 'WiFi', 'Parking', 'Climatisation'],
        description: 'Magnifique villa avec vue mer, idéale pour familles',
        cleaningFee: 50,
        cancellationPolicy: 'Flexible',
      },
      {
        id: 2,
        title: 'Appartement centre historique',
        location: 'Paris, Île-de-France',
        price: 120,
        rating: 4.7,
        reviews: 89,
        image:
          'https://images.unsplash.com/photo-1522708323590-d24dbb6b0267?w=800',
        host: 'Jean Martin',
        beds: 2,
        baths: 1,
        guests: 4,
        amenities: ['WiFi', 'Cuisine équipée', 'Lave-linge'],
        description: 'Charmant appartement au cœur de Paris',
        cleaningFee: 40,
        cancellationPolicy: 'Modérée',
      },
      {
        id: 3,
        title: 'Chalet montagne vue panoramique',
        location: 'Chamonix, Haute-Savoie',
        price: 250,
        rating: 5.0,
        reviews: 156,
        image:
          'https://images.unsplash.com/photo-1520250497591-112f2f40a3f4?w=800',
        host: 'Sophie Laurent',
        beds: 5,
        baths: 3,
        guests: 10,
        amenities: ['Cheminée', 'Sauna', 'WiFi', 'Parking'],
        description: 'Chalet de luxe face au Mont Blanc',
        cleaningFee: 80,
        cancellationPolicy: 'Stricte',
      },
      {
        id: 4,
        title: 'Maison de campagne provençale',
        location: 'Aix-en-Provence, PACA',
        price: 150,
        rating: 4.8,
        reviews: 94,
        image:
          'https://images.unsplash.com/photo-1564013799919-ab600027ffc6?w=800',
        host: 'Pierre Rousseau',
        beds: 3,
        baths: 2,
        guests: 6,
        amenities: ['Jardin', 'BBQ', 'WiFi', 'Piscine'],
        description: "Authentique mas provençal dans les oliviers",
        cleaningFee: 60,
        cancellationPolicy: 'Modérée',
      },
    ]);
  }, []);

  const hostListings = properties.slice(0, 2);

  const handleNavigate = (page) => {
    setCurrentPage(page);
    setShowMobileMenu(false);
    if (page !== 'property') {
      setSelectedProperty(null);
    }
  };

  const handleOpenAuthModal = () => {
    setAuthMode('login');
    setShowAuthModal(true);
  };

  const handleCloseMobileMenu = () => {
    setShowMobileMenu(false);
  };

  const handleAuthModeChange = (mode) => setAuthMode(mode);

  const handleCloseAuthModal = () => setShowAuthModal(false);

  const handleAuthenticate = (user) => {
    setCurrentUser(user);
  };

  const handleSearchFiltersChange = (filters) => setSearchFilters(filters);

  const handleToggleFavorite = (propertyId) => {
    setFavorites((previousFavorites) =>
      previousFavorites.includes(propertyId)
        ? previousFavorites.filter((id) => id !== propertyId)
        : [...previousFavorites, propertyId],
    );
  };

  const handleSelectProperty = (property) => {
    setSelectedProperty(property);
    setCurrentPage('property');
    setShowMobileMenu(false);
  };

  const handleRequireAuth = () => {
    handleOpenAuthModal();
  };

  const handleConfirmBooking = (booking) => {
    setBookings((previousBookings) => [...previousBookings, booking]);
  };

  const handleLogout = () => {
    setCurrentUser(null);
    setCurrentPage('home');
  };

  const handleToggleMobileMenu = () => {
    setShowMobileMenu((previousState) => !previousState);
  };

  return (
    <div className="font-sans">
      <Header
        currentUser={currentUser}
        onNavigate={handleNavigate}
        showMobileMenu={showMobileMenu}
        onToggleMobileMenu={handleToggleMobileMenu}
        onCloseMobileMenu={handleCloseMobileMenu}
        onOpenAuth={handleOpenAuthModal}
      />

      {currentPage === 'home' && (
        <HomePage
          searchFilters={searchFilters}
          onSearchFiltersChange={handleSearchFiltersChange}
          onNavigate={handleNavigate}
          properties={properties}
          favorites={favorites}
          onToggleFavorite={handleToggleFavorite}
          onSelectProperty={handleSelectProperty}
        />
      )}

      {currentPage === 'search' && (
        <SearchPage
          searchFilters={searchFilters}
          onSearchFiltersChange={handleSearchFiltersChange}
          properties={properties}
          favorites={favorites}
          onToggleFavorite={handleToggleFavorite}
          onSelectProperty={handleSelectProperty}
        />
      )}

      {currentPage === 'property' && (
        <PropertyDetailPage
          selectedProperty={selectedProperty}
          onNavigate={handleNavigate}
          currentUser={currentUser}
          onRequireAuth={handleRequireAuth}
          onConfirmBooking={handleConfirmBooking}
        />
      )}

      {currentPage === 'bookings' && (
        <BookingsPage bookings={bookings} onNavigate={handleNavigate} />
      )}

      {currentPage === 'host' && <HostDashboard hostListings={hostListings} />}

      {currentPage === 'messages' && <MessagesPage />}

      {currentPage === 'profile' && (
        <ProfilePage currentUser={currentUser} onLogout={handleLogout} />
      )}

      {showAuthModal && (
        <AuthModal
          authMode={authMode}
          onAuthModeChange={handleAuthModeChange}
          onClose={handleCloseAuthModal}
          onAuthenticate={handleAuthenticate}
        />
      )}

      {/* Footer */}
      <footer className="bg-gray-900 text-white py-12 mt-16">
        <div className="max-w-7xl mx-auto px-4">
          <div className="grid grid-cols-1 md:grid-cols-4 gap-8">
            <div>
              <h4 className="font-bold text-lg mb-4">VacancesPro</h4>
              <p className="text-gray-400">
                La plateforme de location de vacances entre particuliers
              </p>
            </div>
            <div>
              <h5 className="font-semibold mb-4">À propos</h5>
              <ul className="space-y-2 text-gray-400">
                <li>
                  <a href="#" className="hover:text-white">
                    Comment ça marche
                  </a>
                </li>
                <li>
                  <a href="#" className="hover:text-white">
                    Confiance et sécurité
                  </a>
                </li>
                <li>
                  <a href="#" className="hover:text-white">
                    Centre d'aide
                  </a>
                </li>
              </ul>
            </div>
            <div>
              <h5 className="font-semibold mb-4">Hôtes</h5>
              <ul className="space-y-2 text-gray-400">
                <li>
                  <a href="#" className="hover:text-white">
                    Devenir hôte
                  </a>
                </li>
                <li>
                  <a href="#" className="hover:text-white">
                    Ressources hôtes
                  </a>
                </li>
                <li>
                  <a href="#" className="hover:text-white">
                    Standards de qualité
                  </a>
                </li>
              </ul>
            </div>
            <div>
              <h5 className="font-semibold mb-4">Légal</h5>
              <ul className="space-y-2 text-gray-400">
                <li>
                  <a href="#" className="hover:text-white">
                    CGU
                  </a>
                </li>
                <li>
                  <a href="#" className="hover:text-white">
                    Politique de confidentialité
                  </a>
                </li>
                <li>
                  <a href="#" className="hover:text-white">
                    Cookies
                  </a>
                </li>
              </ul>
            </div>
          </div>
          <div className="border-t border-gray-800 mt-8 pt-8 text-center text-gray-400">
            <p>© 2025 VacancesPro. Tous droits réservés.</p>
          </div>
        </div>
      </footer>
    </div>
  );
};

export default VacationRentalPlatform;
