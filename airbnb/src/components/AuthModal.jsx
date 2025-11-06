import React from 'react';
import { X } from 'lucide-react';

const AuthModal = ({ authMode, onAuthModeChange, onClose, onAuthenticate }) => {
  const handleSubmit = (event) => {
    event.preventDefault();
    onAuthenticate({ id: 1, name: 'Jean Dupont', email: 'jean@example.com' });
    onClose();
  };

  return (
    <div className="fixed inset-0 bg-black bg-opacity-50 flex items-center justify-center z-50 p-4">
      <div className="bg-white rounded-2xl p-8 max-w-md w-full">
        <div className="flex justify-between items-center mb-6">
          <h2 className="text-2xl font-bold">
            {authMode === 'login' ? 'Connexion' : 'Inscription'}
          </h2>
          <button onClick={onClose}>
            <X size={24} />
          </button>
        </div>

        <form onSubmit={handleSubmit}>
          {authMode === 'register' && (
            <input
              type="text"
              placeholder="Nom complet"
              className="w-full px-4 py-3 border rounded-lg mb-3"
              required
            />
          )}
          <input
            type="email"
            placeholder="Email"
            className="w-full px-4 py-3 border rounded-lg mb-3"
            required
          />
          <input
            type="password"
            placeholder="Mot de passe"
            className="w-full px-4 py-3 border rounded-lg mb-4"
            required
          />

          <button
            type="submit"
            className="w-full bg-blue-600 text-white py-3 rounded-lg font-medium hover:bg-blue-700 mb-4"
          >
            {authMode === 'login' ? 'Se connecter' : "S'inscrire"}
          </button>

          <div className="flex space-x-3 mb-4">
            <button
              type="button"
              className="flex-1 border py-3 rounded-lg hover:bg-gray-50"
            >
              Google
            </button>
            <button
              type="button"
              className="flex-1 border py-3 rounded-lg hover:bg-gray-50"
            >
              Facebook
            </button>
          </div>

          <p className="text-center text-sm text-gray-600">
            {authMode === 'login' ? "Pas encore de compte ?" : "Déjà inscrit ?"}{' '}
            <button
              type="button"
              onClick={() =>
                onAuthModeChange(authMode === 'login' ? 'register' : 'login')
              }
              className="text-blue-600 font-medium"
            >
              {authMode === 'login' ? "S'inscrire" : 'Se connecter'}
            </button>
          </p>
        </form>
      </div>
    </div>
  );
};

export default AuthModal;
