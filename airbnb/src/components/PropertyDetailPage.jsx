import React from 'react';
import { ChevronLeft, Star, MapPin } from 'lucide-react';

const PropertyDetailPage = ({
  selectedProperty,
  onNavigate,
  currentUser,
  onRequireAuth,
  onConfirmBooking,
}) => {
  if (!selectedProperty) return null;

  const nights = 3;
  const total = selectedProperty.price * nights + selectedProperty.cleaningFee;

  const handleBooking = () => {
    if (!currentUser) {
      onRequireAuth();
      return;
    }

    onConfirmBooking({
      id: Date.now(),
      property: selectedProperty,
      checkIn: '2025-06-15',
      checkOut: '2025-06-18',
      total,
      status: 'confirmée',
    });

    // Keep UX feedback consistent with original version
    alert('Réservation confirmée !');
    onNavigate('bookings');
  };

  return (
    <div className="min-h-screen bg-gray-50">
      <div className="max-w-7xl mx-auto px-4 py-8">
        <button
          onClick={() => onNavigate('search')}
          className="flex items-center text-blue-600 mb-4 hover:underline"
        >
          <ChevronLeft size={20} />
          Retour aux résultats
        </button>

        <div className="bg-white rounded-xl shadow-lg overflow-hidden">
          {/* Image Gallery */}
          <div className="relative h-96">
            <img
              src={selectedProperty.image}
              alt={selectedProperty.title}
              className="w-full h-full object-cover"
            />
          </div>

          <div className="p-8">
            <div className="grid grid-cols-1 lg:grid-cols-3 gap-8">
              {/* Left Column */}
              <div className="lg:col-span-2">
                <h1 className="text-3xl font-bold mb-4">{selectedProperty.title}</h1>

                <div className="flex items-center space-x-4 mb-6">
                  <div className="flex items-center">
                    <Star size={20} className="text-yellow-400 fill-current" />
                    <span className="ml-1 font-medium">{selectedProperty.rating}</span>
                    <span className="text-gray-500 ml-1">
                      ({selectedProperty.reviews} avis)
                    </span>
                  </div>
                  <div className="flex items-center text-gray-600">
                    <MapPin size={20} />
                    <span className="ml-1">{selectedProperty.location}</span>
                  </div>
                </div>

                <div className="border-t border-b py-6 mb-6">
                  <div className="flex items-center space-x-6 text-gray-700">
                    <span>{selectedProperty.guests} voyageurs</span>
                    <span>{selectedProperty.beds} chambres</span>
                    <span>{selectedProperty.baths} salles de bain</span>
                  </div>
                </div>

                <div className="mb-6">
                  <h3 className="text-xl font-semibold mb-3">Description</h3>
                  <p className="text-gray-700">{selectedProperty.description}</p>
                </div>

                <div className="mb-6">
                  <h3 className="text-xl font-semibold mb-3">Équipements</h3>
                  <div className="grid grid-cols-2 gap-3">
                    {selectedProperty.amenities.map((amenity, index) => (
                      <div key={index} className="flex items-center">
                        <div className="w-2 h-2 bg-blue-600 rounded-full mr-2"></div>
                        <span>{amenity}</span>
                      </div>
                    ))}
                  </div>
                </div>

                <div className="border-t pt-6">
                  <h3 className="text-xl font-semibold mb-3">
                    Votre hôte : {selectedProperty.host}
                  </h3>
                  <div className="flex items-center space-x-4">
                    <div className="w-16 h-16 bg-blue-600 rounded-full flex items-center justify-center text-white text-2xl font-bold">
                      {selectedProperty.host.charAt(0)}
                    </div>
                    <div>
                      <p className="text-gray-600">Hôte depuis 2020</p>
                      <p className="text-gray-600">Taux de réponse : 98%</p>
                    </div>
                  </div>
                </div>
              </div>

              {/* Right Column - Booking Card */}
              <div>
                <div className="bg-white border-2 border-gray-200 rounded-xl p-6 sticky top-24">
                  <div className="mb-4">
                    <span className="text-3xl font-bold text-blue-600">
                      {selectedProperty.price}€
                    </span>
                    <span className="text-gray-600"> / nuit</span>
                  </div>

                  <div className="space-y-3 mb-4">
                    <div>
                      <label className="block text-sm font-medium mb-1">Arrivée</label>
                      <input type="date" className="w-full px-3 py-2 border rounded-lg" />
                    </div>
                    <div>
                      <label className="block text-sm font-medium mb-1">Départ</label>
                      <input type="date" className="w-full px-3 py-2 border rounded-lg" />
                    </div>
                    <div>
                      <label className="block text-sm font-medium mb-1">Voyageurs</label>
                      <select className="w-full px-3 py-2 border rounded-lg">
                        <option>1 voyageur</option>
                        <option>2 voyageurs</option>
                        <option>3 voyageurs</option>
                        <option>4 voyageurs</option>
                      </select>
                    </div>
                  </div>

                  <div className="border-t pt-4 mb-4 space-y-2">
                    <div className="flex justify-between text-gray-700">
                      <span>
                        {selectedProperty.price}€ x {nights} nuits
                      </span>
                      <span>{selectedProperty.price * nights}€</span>
                    </div>
                    <div className="flex justify-between text-gray-700">
                      <span>Frais de ménage</span>
                      <span>{selectedProperty.cleaningFee}€</span>
                    </div>
                    <div className="flex justify-between font-bold text-lg border-t pt-2">
                      <span>Total</span>
                      <span>{total}€</span>
                    </div>
                  </div>

                  <button
                    onClick={handleBooking}
                    className="w-full bg-blue-600 text-white py-3 rounded-lg font-medium hover:bg-blue-700"
                  >
                    Réserver
                  </button>

                  <p className="text-center text-sm text-gray-500 mt-3">
                    Vous ne serez pas débité maintenant
                  </p>

                  <div className="mt-4 p-3 bg-green-50 rounded-lg text-sm text-green-700">
                    <strong>Annulation {selectedProperty.cancellationPolicy}</strong>
                    <p className="text-xs mt-1">
                      Remboursement complet jusqu'à 24h avant l'arrivée
                    </p>
                  </div>
                </div>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
  );
};

export default PropertyDetailPage;
