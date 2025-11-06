import React from 'react';

const ProfilePage = ({ currentUser, onLogout }) => (
  <div className="min-h-screen bg-gray-50">
    <div className="max-w-4xl mx-auto px-4 py-8">
      <h1 className="text-3xl font-bold mb-8">Mon profil</h1>

      <div className="bg-white rounded-xl shadow-md p-8 mb-6">
        <div className="flex items-center space-x-6 mb-8">
          <div className="w-24 h-24 bg-blue-600 rounded-full flex items-center justify-center text-white text-4xl font-bold">
            {currentUser?.name?.charAt(0)}
          </div>
          <div>
            <h2 className="text-2xl font-bold">{currentUser?.name}</h2>
            <p className="text-gray-600">{currentUser?.email}</p>
            <button className="mt-2 text-blue-600 hover:underline text-sm">
              Modifier la photo
            </button>
          </div>
        </div>

        <div className="space-y-4">
          <div>
            <label className="block text-sm font-medium mb-1">Nom complet</label>
            <input
              type="text"
              defaultValue={currentUser?.name}
              className="w-full px-4 py-2 border rounded-lg"
            />
          </div>
          <div>
            <label className="block text-sm font-medium mb-1">Email</label>
            <input
              type="email"
              defaultValue={currentUser?.email}
              className="w-full px-4 py-2 border rounded-lg"
            />
          </div>
          <div>
            <label className="block text-sm font-medium mb-1">Téléphone</label>
            <input
              type="tel"
              placeholder="+33 6 12 34 56 78"
              className="w-full px-4 py-2 border rounded-lg"
            />
          </div>
          <div>
            <label className="block text-sm font-medium mb-1">Biographie</label>
            <textarea
              rows="4"
              placeholder="Parlez-nous de vous..."
              className="w-full px-4 py-2 border rounded-lg"
            ></textarea>
          </div>
          <div>
            <label className="block text-sm font-medium mb-1">Langues parlées</label>
            <input
              type="text"
              placeholder="Français, Anglais..."
              className="w-full px-4 py-2 border rounded-lg"
            />
          </div>
        </div>

        <div className="mt-6 flex space-x-4">
          <button className="bg-blue-600 text-white px-6 py-2 rounded-lg hover:bg-blue-700">
            Enregistrer les modifications
          </button>
          <button className="border px-6 py-2 rounded-lg hover:bg-gray-50">
            Annuler
          </button>
        </div>
      </div>

      {/* Verification */}
      <div className="bg-white rounded-xl shadow-md p-8 mb-6">
        <h3 className="text-xl font-bold mb-4">Vérification d'identité</h3>
        <div className="space-y-3">
          <div className="flex items-center justify-between p-4 border rounded-lg">
            <div className="flex items-center space-x-3">
              <div className="w-10 h-10 bg-green-100 rounded-full flex items-center justify-center">
                <span className="text-green-600 font-bold">✓</span>
              </div>
              <span>Adresse email vérifiée</span>
            </div>
          </div>
          <div className="flex items-center justify-between p-4 border rounded-lg">
            <div className="flex items-center space-x-3">
              <div className="w-10 h-10 bg-gray-100 rounded-full flex items-center justify-center">
                <span className="text-gray-400 font-bold">○</span>
              </div>
              <span>Numéro de téléphone</span>
            </div>
            <button className="text-blue-600 hover:underline text-sm">
              Vérifier
            </button>
          </div>
          <div className="flex items-center justify-between p-4 border rounded-lg">
            <div className="flex items-center space-x-3">
              <div className="w-10 h-10 bg-gray-100 rounded-full flex items-center justify-center">
                <span className="text-gray-400 font-bold">○</span>
              </div>
              <span>Pièce d'identité</span>
            </div>
            <button className="text-blue-600 hover:underline text-sm">
              Ajouter
            </button>
          </div>
        </div>
      </div>

      {/* Preferences */}
      <div className="bg-white rounded-xl shadow-md p-8">
        <h3 className="text-xl font-bold mb-4">Préférences</h3>
        <div className="space-y-4">
          <div className="flex items-center justify-between">
            <span>Recevoir des emails promotionnels</span>
            <label className="relative inline-flex items-center cursor-pointer">
              <input type="checkbox" className="sr-only peer" defaultChecked />
              <div className="w-11 h-6 bg-gray-200 peer-focus:outline-none peer-focus:ring-4 peer-focus:ring-blue-300 rounded-full peer peer-checked:after:translate-x-full peer-checked:after:border-white after:content-[''] after:absolute after:top-[2px] after:left-[2px] after:bg-white after:border-gray-300 after:border after:rounded-full after:h-5 after:w-5 after:transition-all peer-checked:bg-blue-600"></div>
            </label>
          </div>
          <div className="flex items-center justify-between">
            <span>Notifications de réservation</span>
            <label className="relative inline-flex items-center cursor-pointer">
              <input type="checkbox" className="sr-only peer" defaultChecked />
              <div className="w-11 h-6 bg-gray-200 peer-focus:outline-none peer-focus:ring-4 peer-focus:ring-blue-300 rounded-full peer peer-checked:after:translate-x-full peer-checked:after:border-white after:content-[''] after:absolute after:top-[2px] after:left-[2px] after:bg-white after:border-gray-300 after:border after:rounded-full after:h-5 after:w-5 after:transition-all peer-checked:bg-blue-600"></div>
            </label>
          </div>
        </div>
      </div>

      <button
        onClick={onLogout}
        className="mt-6 text-red-600 hover:underline"
      >
        Se déconnecter
      </button>
    </div>
  </div>
);

export default ProfilePage;
