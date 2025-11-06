import React from 'react';
import { Calendar } from 'lucide-react';

const BookingsPage = ({ bookings, onNavigate }) => (
  <div className="min-h-screen bg-gray-50">
    <div className="max-w-7xl mx-auto px-4 py-8">
      <h1 className="text-3xl font-bold mb-8">Mes réservations</h1>

      {bookings.length === 0 ? (
        <div className="bg-white rounded-xl p-12 text-center">
          <Calendar size={64} className="mx-auto text-gray-400 mb-4" />
          <h3 className="text-xl font-semibold mb-2">Aucune réservation</h3>
          <p className="text-gray-600 mb-6">
            Commencez à explorer nos hébergements
          </p>
          <button
            onClick={() => onNavigate('search')}
            className="bg-blue-600 text-white px-6 py-3 rounded-lg hover:bg-blue-700"
          >
            Explorer les logements
          </button>
        </div>
      ) : (
        <div className="space-y-4">
          {bookings.map((booking) => (
            <div
              key={booking.id}
              className="bg-white rounded-xl shadow-md p-6 flex items-center space-x-6"
            >
              <img
                src={booking.property.image}
                alt={booking.property.title}
                className="w-32 h-32 object-cover rounded-lg"
              />
              <div className="flex-1">
                <h3 className="text-xl font-semibold mb-2">
                  {booking.property.title}
                </h3>
                <p className="text-gray-600 mb-1">{booking.property.location}</p>
                <p className="text-sm text-gray-500">
                  Du {booking.checkIn} au {booking.checkOut}
                </p>
                <span
                  className={`inline-block mt-2 px-3 py-1 rounded-full text-sm ${
                    booking.status === 'confirmée'
                      ? 'bg-green-100 text-green-700'
                      : 'bg-yellow-100 text-yellow-700'
                  }`}
                >
                  {booking.status}
                </span>
              </div>
              <div className="text-right">
                <p className="text-2xl font-bold text-blue-600">{booking.total}€</p>
                <button className="mt-2 text-blue-600 hover:underline text-sm">
                  Contacter l'hôte
                </button>
              </div>
            </div>
          ))}
        </div>
      )}
    </div>
  </div>
);

export default BookingsPage;
