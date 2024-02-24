#pragma once
#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <SFML/Graphics.hpp>
#include "../nodes/SceneNode.h"
#include "../entities/Tetromino.h"
#include <array>

namespace sf {
	class RenderWindow;
}

class GameScreen : private sf::NonCopyable
{
		public:
			explicit		GameScreen(sf::RenderWindow& window);
			void			update(sf::Time dt);
			void			draw();

		private:
			void			loadResources();
			void			buildScene();
			void			spawnTetrominos();
			void			destroyEntitiesOfView();
			void			addTetrominos();
			void			addTetromino(Tetromino::Type type, float relX, float relY);
			void			addTetromino(Tetromino::Type type);
			sf::FloatRect	getViewBounds() const;
			sf::FloatRect	getGamePlataformBounds() const;

		private:
			enum Layer
			{
				Background,
				Plataform,
				LayerCount
			};

			struct SpawnPoint
			{
					SpawnPoint(Tetromino::Type type, float x, float y)
					: type(type)
					, x(x)
					, y(y)
					{
					}

					Tetromino::Type type;
					float x;
					float y;
			};


		private:
			sf::RenderWindow&								mWindow;
			sf::View											mWorldView;
			//TextureHolder						mTextures;


			SceneNode											mSceneGraph;
			std::array<SceneNode*, LayerCount>		mSceneLayers;

			sf::FloatRect									mWorldBounds;
			sf::Vector2f									mSpawnPosition;
			float													mScrollSpeed;

			std::vector<std::unique_ptr<Tetromino>> mTetrominos;
			std::vector<std::unique_ptr<Tetromino>> mTetrominosReached;
			//Player manejar el input con esta clase
			Tetromino*								mPlayerTetromino;

			std::vector<SpawnPoint>				mTetrominosSpawnPoints;
			std::vector<Tetromino*>				mActiveTetrominos;

};
#endif // !GAMESCREEN_H

