#pragma once
#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <SFML/Graphics.hpp>
#include "../nodes/SceneNode.h"
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

		private:
			enum Layer
			{
				Background,
				Plataform,
				LayerCount
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

};
#endif // !GAMESCREEN_H

