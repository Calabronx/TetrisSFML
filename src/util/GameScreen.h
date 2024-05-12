#pragma once
#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <SFML/Graphics.hpp>
#include "../nodes/SceneNode.h"
#include "../entities/Tetromino.h"
#include <array>
#include "../input/CommandQueue.h"

namespace sf {
	class RenderWindow;
}

class GameScreen : private sf::NonCopyable
{
		public:
			explicit								GameScreen(sf::RenderWindow& window);
			void									update(sf::Time dt);
			void									draw();

			CommandQueue&				getCommandQueue();

		private:
			void			loadResources();
			void			buildScene();
			void			spawnTetrominos();
			void			destroyEntitiesOfView();
			void			adaptPlayerVelocity();
			void			adaptPlayerPosition();
			void handleCollisions();

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

			struct GameLimit : public Entity 
			{
				GameLimit(sf::FloatRect rect,Category::Type type)
					:rect(rect),type(type)
				{
				}	
				GameLimit(sf::RectangleShape shape,Category::Type type)
					:shape(shape),type(type)
				{
				}
				Category::Type type;
				sf::FloatRect rect;
				sf::RectangleShape shape;
				virtual sf::FloatRect getBoundingRect() const {
					return getWorldTransform().transformRect(shape.getLocalBounds());
				}
				virtual unsigned int getCategory() const {
					return Category::Floor;
				}
			};

			// deberia ser privado..
		public:
			//Player manejar el input con esta clase
			Tetromino*								mPlayerTetromino;


		private:
			sf::RenderWindow&								mWindow;
			sf::View											mWorldView;
			//TextureHolder						mTextures;


			SceneNode												mSceneGraph;
			std::array<SceneNode*, LayerCount>		mSceneLayers;
			CommandQueue									mCommandQueue;

			sf::FloatRect									mWorldBounds;
			sf::Vector2f									mSpawnPosition;
			float													mScrollSpeed;

			std::vector<std::unique_ptr<Tetromino>> mTetrominos;
			std::vector<std::unique_ptr<Tetromino>> mTetrominosLanded;

			std::vector<SpawnPoint>				mTetrominosSpawnPoints;
			//std::vector<Tetromino&>				mActiveTetrominos;
			std::unique_ptr<GameLimit>			mFloorLimit;
			


};
bool matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2);
#endif // !GAMESCREEN_H

