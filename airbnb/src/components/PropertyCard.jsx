import React from 'react';
import { Heart, MapPin, Star } from 'lucide-react';

const PropertyCard = ({
  property,
  isFavorite,
  onToggleFavorite,
  onSelectProperty,
}) => (
  <div className="bg-white rounded-xl shadow-md overflow-hidden hover:shadow-xl transition-shadow cursor-pointer">
    <div className="relative">
      <img
        src={property.image}
        alt={property.title}
        className="w-full h-48 object-cover"
      />
      <button
        onClick={(event) => {
          event.stopPropagation();
          onToggleFavorite(property.id);
        }}
        className="absolute top-3 right-3 bg-white p-2 rounded-full shadow-lg hover:scale-110 transition"
      >
        <Heart
          size={20}
          className={isFavorite ? 'fill-red-500 text-red-500' : 'text-gray-600'}
        />
      </button>
    </div>
    <div
      className="p-4"
      onClick={() => onSelectProperty(property)}
    >
      <div className="flex items-start justify-between mb-2">
        <h3 className="font-semibold text-lg">{property.title}</h3>
      </div>
      <div className="flex items-center text-sm text-gray-600 mb-2">
        <MapPin size={16} className="mr-1" />
        {property.location}
      </div>
      <div className="flex items-center mb-3">
        <Star size={16} className="text-yellow-400 fill-current" />
        <span className="ml-1 font-medium">{property.rating}</span>
        <span className="text-gray-500 text-sm ml-1">
          ({property.reviews} avis)
        </span>
      </div>
      <div className="flex items-center justify-between">
        <div>
          <span className="text-2xl font-bold text-blue-600">
            {property.price}€
          </span>
          <span className="text-gray-600 text-sm"> / nuit</span>
        </div>
      </div>
    </div>
  </div>
);

export default PropertyCard;
