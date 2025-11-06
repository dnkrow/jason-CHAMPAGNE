import React from 'react';
import { Euro, Calendar, Star, Home } from 'lucide-react';

const HostDashboard = ({ hostListings }) => (
  <div className="min-h-screen bg-gray-50">
    <div className="max-w-7xl mx-auto px-4 py-8">
      <div className="flex items-center justify-between mb-8">
        <h1 className="text-3xl font-bold">Tableau de bord hôte</h1>
        <button className="bg-blue-600 text-white px-6 py-3 rounded-lg hover:bg-blue-700 font-medium">
          + Créer une annonce
        </button>
      </div>

      {/* Stats Cards */}
      <div className="grid grid-cols-1 md:grid-cols-4 gap-6 mb-8">
        <div className="bg-white rounded-xl p-6 shadow-md">
          <div className="flex items-center justify-between mb-2">
            <span className="text-gray-600">Revenus totaux</span>
            <Euro className="text-blue-600" size={24} />
          </div>
          <p className="text-3xl font-bold">2,450€</p>
          <p className="text-sm text-green-600 mt-1">+12% ce mois</p>
        </div>
        <div className="bg-white rounded-xl p-6 shadow-md">
          <div className="flex items-center justify-between mb-2">
            <span className="text-gray-600">Réservations</span>
            <Calendar className="text-blue-600" size={24} />
          </div>
          <p className="text-3xl font-bold">18</p>
          <p className="text-sm text-green-600 mt-1">+3 cette semaine</p>
        </div>
        <div className="bg-white rounded-xl p-6 shadow-md">
          <div className="flex items-center justify-between mb-2">
            <span className="text-gray-600">Taux d'occupation</span>
            <Star className="text-blue-600" size={24} />
          </div>
          <p className="text-3xl font-bold">76%</p>
          <p className="text-sm text-gray-500 mt-1">Moyenne mensuelle</p>
        </div>
        <div className="bg-white rounded-xl p-6 shadow-md">
          <div className="flex items-center justify-between mb-2">
            <span className="text-gray-600">Note moyenne</span>
            <Star className="text-yellow-400 fill-current" size={24} />
          </div>
          <p className="text-3xl font-bold">4.8</p>
          <p className="text-sm text-gray-500 mt-1">Sur 45 avis</p>
        </div>
      </div>

      {/* My Properties */}
      <div className="bg-white rounded-xl shadow-md p-6 mb-8">
        <h2 className="text-2xl font-bold mb-6">Mes annonces</h2>
        {hostListings.length === 0 ? (
          <div className="text-center py-12">
            <Home size={64} className="mx-auto text-gray-400 mb-4" />
            <h3 className="text-xl font-semibold mb-2">Aucune annonce</h3>
            <p className="text-gray-600 mb-6">
              Commencez à gagner de l'argent en louant votre logement
            </p>
            <button className="bg-blue-600 text-white px-6 py-3 rounded-lg hover:bg-blue-700">
              Créer ma première annonce
            </button>
          </div>
        ) : (
          <div className="space-y-4">
            {hostListings.map((property) => (
              <div
                key={property.id}
                className="flex items-center space-x-4 p-4 border rounded-lg hover:shadow-md transition"
              >
                <img
                  src={property.image}
                  alt={property.title}
                  className="w-24 h-24 object-cover rounded-lg"
                />
                <div className="flex-1">
                  <h3 className="font-semibold text-lg">{property.title}</h3>
                  <p className="text-gray-600">{property.location}</p>
                  <p className="text-blue-600 font-medium">{property.price}€ / nuit</p>
                </div>
                <div className="space-x-2">
                  <button className="px-4 py-2 border rounded-lg hover:bg-gray-50">
                    Modifier
                  </button>
                  <button className="px-4 py-2 border rounded-lg hover:bg-gray-50">
                    Statistiques
                  </button>
                </div>
              </div>
            ))}
          </div>
        )}
      </div>

      {/* Recent Bookings */}
      <div className="bg-white rounded-xl shadow-md p-6">
        <h2 className="text-2xl font-bold mb-6">Réservations récentes</h2>
        <div className="space-y-4">
          <div className="flex items-center justify-between p-4 border rounded-lg">
            <div>
              <h4 className="font-semibold">Sophie Martin</h4>
              <p className="text-sm text-gray-600">Villa moderne avec piscine</p>
              <p className="text-sm text-gray-500">15-18 juin 2025</p>
            </div>
            <div className="text-right">
              <p className="font-bold text-blue-600">540€</p>
              <span className="text-sm text-green-600">Confirmée</span>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
);

export default HostDashboard;
