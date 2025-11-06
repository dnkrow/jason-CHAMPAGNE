import React from 'react';
import { MessageSquare } from 'lucide-react';

const MessagesPage = () => (
  <div className="min-h-screen bg-gray-50">
    <div className="max-w-7xl mx-auto px-4 py-8">
      <h1 className="text-3xl font-bold mb-8">Messages</h1>

      <div className="bg-white rounded-xl shadow-md overflow-hidden">
        <div className="grid grid-cols-1 md:grid-cols-3 h-[600px]">
          {/* Conversations List */}
          <div className="border-r overflow-y-auto">
            <div className="p-4 border-b">
              <input
                type="text"
                placeholder="Rechercher..."
                className="w-full px-4 py-2 border rounded-lg"
              />
            </div>
            <div className="divide-y">
              {[
                {
                  id: 1,
                  name: 'Marie Dubois',
                  message: 'Merci pour votre réservation !',
                  time: '10:30',
                  unread: true,
                },
                {
                  id: 2,
                  name: 'Jean Martin',
                  message: 'Le check-in se fait à quelle heure ?',
                  time: 'Hier',
                  unread: false,
                },
                {
                  id: 3,
                  name: 'Sophie Laurent',
                  message: 'Parfait, à bientôt !',
                  time: 'Lundi',
                  unread: false,
                },
              ].map((conversation) => (
                <div
                  key={conversation.id}
                  className={`p-4 hover:bg-gray-50 cursor-pointer ${
                    conversation.unread ? 'bg-blue-50' : ''
                  }`}
                >
                  <div className="flex items-center space-x-3">
                    <div className="w-12 h-12 bg-blue-600 rounded-full flex items-center justify-center text-white font-bold">
                      {conversation.name.charAt(0)}
                    </div>
                    <div className="flex-1 min-w-0">
                      <div className="flex items-center justify-between mb-1">
                        <h4 className="font-semibold truncate">
                          {conversation.name}
                        </h4>
                        <span className="text-xs text-gray-500">
                          {conversation.time}
                        </span>
                      </div>
                      <p
                        className={`text-sm truncate ${
                          conversation.unread
                            ? 'font-medium text-gray-900'
                            : 'text-gray-600'
                        }`}
                      >
                        {conversation.message}
                      </p>
                    </div>
                    {conversation.unread && (
                      <div className="w-3 h-3 bg-blue-600 rounded-full"></div>
                    )}
                  </div>
                </div>
              ))}
            </div>
          </div>

          {/* Chat Area */}
          <div className="md:col-span-2 flex flex-col">
            <div className="p-4 border-b flex items-center space-x-3">
              <div className="w-10 h-10 bg-blue-600 rounded-full flex items-center justify-center text-white font-bold">
                M
              </div>
              <div>
                <h3 className="font-semibold">Marie Dubois</h3>
                <p className="text-sm text-gray-600">En ligne</p>
              </div>
            </div>

            <div className="flex-1 p-4 overflow-y-auto space-y-4">
              <div className="flex justify-start">
                <div className="bg-gray-100 rounded-2xl px-4 py-2 max-w-xs">
                  <p>Bonjour ! J'ai une question concernant le stationnement.</p>
                  <span className="text-xs text-gray-500 mt-1 block">09:45</span>
                </div>
              </div>
              <div className="flex justify-end">
                <div className="bg-blue-600 text-white rounded-2xl px-4 py-2 max-w-xs">
                  <p>Bonjour ! Bien sûr, il y a deux places de parking privées.</p>
                  <span className="text-xs text-blue-200 mt-1 block">09:47</span>
                </div>
              </div>
              <div className="flex justify-start">
                <div className="bg-gray-100 rounded-2xl px-4 py-2 max-w-xs">
                  <p>Parfait ! Merci pour votre réservation 😊</p>
                  <span className="text-xs text-gray-500 mt-1 block">10:30</span>
                </div>
              </div>
            </div>

            <div className="p-4 border-t">
              <div className="flex items-center space-x-2">
                <input
                  type="text"
                  placeholder="Écrivez votre message..."
                  className="flex-1 px-4 py-3 border rounded-full focus:outline-none focus:border-blue-500"
                />
                <button className="bg-blue-600 text-white p-3 rounded-full hover:bg-blue-700">
                  <MessageSquare size={20} />
                </button>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
);

export default MessagesPage;
