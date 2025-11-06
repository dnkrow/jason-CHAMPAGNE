import React from 'react';
import { Search, Star, Euro, MessageSquare } from 'lucide-react';
import PropertyCard from './PropertyCard';

const HomePage = ({
  searchFilters,
  onSearchFiltersChange,
  onNavigate,
  properties,
  favorites,
  onToggleFavorite,
  onSelectProperty,
}) => {
  const updateFilter = (field, value) => {
    onSearchFiltersChange({ ...searchFilters, [field]: value });
  };

  return (
    <div className="min-h-screen bg-gray-50">
      {/* Hero Section */}
      <div className="relative h-96 bg-gradient-to-r from-blue-600 to-blue-800 flex items-center justify-center">
        <div className="text-center text-white px-4">
          <h1 className="text-5xl font-bold mb-4">Trouvez votre location de rêve</h1>
          <p className="text-xl mb-8">
            Des milliers d'hébergements uniques vous attendent
          </p>

          <div className="bg-white rounded-full p-2 max-w-4xl mx-auto shadow-2xl">
            <div className="flex flex-col md:flex-row gap-2">
              <input
                type="text"
                placeholder="Où allez-vous ?"
                className="flex-1 px-6 py-3 rounded-full text-gray-800 focus:outline-none"
                value={searchFilters.location}
                onChange={(event) => updateFilter('location', event.target.value)}
              />
              <input
                type="date"
                className="px-6 py-3 rounded-full text-gray-800 focus:outline-none"
                value={searchFilters.checkIn}
                onChange={(event) => updateFilter('checkIn', event.target.value)}
              />
              <input
                type="date"
                className="px-6 py-3 rounded-full text-gray-800 focus:outline-none"
                value={searchFilters.checkOut}
                onChange={(event) => updateFilter('checkOut', event.target.value)}
              />
              <button
                onClick={() => onNavigate('search')}
                className="bg-blue-600 text-white px-8 py-3 rounded-full hover:bg-blue-700 font-medium flex items-center justify-center"
              >
                <Search size={20} className="mr-2" />
                Rechercher
              </button>
            </div>
          </div>
        </div>
      </div>

      {/* Featured Properties */}
      <div className="max-w-7xl mx-auto px-4 py-16">
        <h2 className="text-3xl font-bold mb-8">Destinations populaires</h2>
        <div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-4 gap-6">
          {properties.map((property) => (
            <PropertyCard
              key={property.id}
              property={property}
              isFavorite={favorites.includes(property.id)}
              onToggleFavorite={onToggleFavorite}
              onSelectProperty={onSelectProperty}
            />
          ))}
        </div>
      </div>

      {/* Features Section */}
      <div className="bg-white py-16">
        <div className="max-w-7xl mx-auto px-4">
          <h2 className="text-3xl font-bold text-center mb-12">Pourquoi VacancesPro ?</h2>
          <div className="grid grid-cols-1 md:grid-cols-3 gap-8">
            <div className="text-center">
              <div className="bg-blue-100 w-16 h-16 rounded-full flex items-center justify-center mx-auto mb-4">
                <Star className="text-blue-600" size={32} />
              </div>
              <h3 className="text-xl font-semibold mb-2">Hébergements vérifiés</h3>
              <p className="text-gray-600">
                Tous nos logements sont contrôlés et notés par nos voyageurs
              </p>
            </div>
            <div className="text-center">
              <div className="bg-blue-100 w-16 h-16 rounded-full flex items-center justify-center mx-auto mb-4">
                <Euro className="text-blue-600" size={32} />
              </div>
              <h3 className="text-xl font-semibold mb-2">Paiement sécurisé</h3>
              <p className="text-gray-600">
                Vos paiements sont protégés jusqu'au check-in
              </p>
            </div>
            <div className="text-center">
              <div className="bg-blue-100 w-16 h-16 rounded-full flex items-center justify-center mx-auto mb-4">
                <MessageSquare className="text-blue-600" size={32} />
              </div>
              <h3 className="text-xl font-semibold mb-2">Support 24/7</h3>
              <p className="text-gray-600">
                Notre équipe est toujours disponible pour vous aider
              </p>
            </div>
          </div>
        </div>
      </div>
    </div>
  );
};

export default HomePage;
