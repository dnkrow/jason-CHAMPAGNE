import React from 'react';
import { Filter } from 'lucide-react';
import PropertyCard from './PropertyCard';

const SearchPage = ({
  searchFilters,
  onSearchFiltersChange,
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
      <div className="max-w-7xl mx-auto px-4 py-8">
        {/* Filters */}
        <div className="bg-white rounded-xl shadow-md p-6 mb-6">
          <div className="flex items-center justify-between mb-4">
            <h2 className="text-xl font-bold flex items-center">
              <Filter size={20} className="mr-2" />
              Filtres de recherche
            </h2>
          </div>
          <div className="grid grid-cols-1 md:grid-cols-4 gap-4">
            <input
              type="text"
              placeholder="Destination"
              className="px-4 py-2 border rounded-lg"
              value={searchFilters.location}
              onChange={(event) => updateFilter('location', event.target.value)}
            />
            <input
              type="number"
              placeholder="Voyageurs"
              className="px-4 py-2 border rounded-lg"
              value={searchFilters.guests}
              onChange={(event) => updateFilter('guests', event.target.value)}
            />
            <input
              type="number"
              placeholder="Prix min"
              className="px-4 py-2 border rounded-lg"
              value={searchFilters.minPrice}
              onChange={(event) => updateFilter('minPrice', event.target.value)}
            />
            <input
              type="number"
              placeholder="Prix max"
              className="px-4 py-2 border rounded-lg"
              value={searchFilters.maxPrice}
              onChange={(event) => updateFilter('maxPrice', event.target.value)}
            />
          </div>
        </div>

        {/* Results */}
        <div className="mb-4">
          <p className="text-gray-600">{properties.length} hébergements trouvés</p>
        </div>
        <div className="grid grid-cols-1 md:grid-cols-3 lg:grid-cols-4 gap-6">
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
    </div>
  );
};

export default SearchPage;
