import React from 'react';
import { Home, User, MessageSquare, Menu, X } from 'lucide-react';

const Header = ({
  currentUser,
  onNavigate,
  showMobileMenu,
  onToggleMobileMenu,
  onCloseMobileMenu,
  onOpenAuth,
}) => (
  <header className="bg-white shadow-sm sticky top-0 z-50">
    <div className="max-w-7xl mx-auto px-4 py-4">
      <div className="flex items-center justify-between">
        <div
          className="flex items-center space-x-2 cursor-pointer"
          onClick={() => {
            onNavigate('home');
            onCloseMobileMenu();
          }}
        >
          <Home className="text-blue-600" size={32} />
          <span className="text-2xl font-bold text-gray-800">VacancesPro</span>
        </div>

        {/* Desktop Navigation */}
        <nav className="hidden md:flex items-center space-x-6">
          <button
            onClick={() => onNavigate('search')}
            className="text-gray-700 hover:text-blue-600 font-medium"
          >
            Explorer
          </button>
          {currentUser && (
            <>
              <button
                onClick={() => onNavigate('messages')}
                className="text-gray-700 hover:text-blue-600 font-medium flex items-center"
              >
                <MessageSquare size={20} className="mr-1" />
                Messages
              </button>
              <button
                onClick={() => onNavigate('bookings')}
                className="text-gray-700 hover:text-blue-600 font-medium"
              >
                Mes réservations
              </button>
              <button
                onClick={() => onNavigate('host')}
                className="text-gray-700 hover:text-blue-600 font-medium"
              >
                Devenir hôte
              </button>
            </>
          )}
        </nav>

        <div className="flex items-center space-x-4">
          {currentUser ? (
            <div className="flex items-center space-x-3">
              <span className="hidden md:block text-sm text-gray-600">
                Bonjour, {currentUser.name}
              </span>
              <button
                onClick={() => onNavigate('profile')}
                className="bg-blue-600 text-white px-4 py-2 rounded-full hover:bg-blue-700 flex items-center"
              >
                <User size={20} />
              </button>
            </div>
          ) : (
            <button
              onClick={() => {
                onCloseMobileMenu();
                onOpenAuth();
              }}
              className="bg-blue-600 text-white px-6 py-2 rounded-full hover:bg-blue-700 font-medium"
            >
              Connexion
            </button>
          )}
          <button className="md:hidden" onClick={onToggleMobileMenu}>
            {showMobileMenu ? <X size={24} /> : <Menu size={24} />}
          </button>
        </div>
      </div>

      {/* Mobile Menu */}
      {showMobileMenu && (
        <div className="md:hidden mt-4 pb-4 border-t pt-4">
          <button
            onClick={() => {
              onNavigate('search');
              onCloseMobileMenu();
            }}
            className="block w-full text-left py-2 text-gray-700"
          >
            Explorer
          </button>
          {currentUser && (
            <>
              <button
                onClick={() => {
                  onNavigate('messages');
                  onCloseMobileMenu();
                }}
                className="block w-full text-left py-2 text-gray-700"
              >
                Messages
              </button>
              <button
                onClick={() => {
                  onNavigate('bookings');
                  onCloseMobileMenu();
                }}
                className="block w-full text-left py-2 text-gray-700"
              >
                Mes réservations
              </button>
              <button
                onClick={() => {
                  onNavigate('host');
                  onCloseMobileMenu();
                }}
                className="block w-full text-left py-2 text-gray-700"
              >
                Devenir hôte
              </button>
            </>
          )}
        </div>
      )}
    </div>
  </header>
);

export default Header;
