#include "GameScreen.h"
#include "../entities/Tetromino.h"

GameScreen::GameScreen(sf::RenderWindow& window)
	: mWindow(window)
	, mWorldView(window.getDefaultView())
	//, mTextures()
	, mSceneGraph()
	, mSceneLayers()
	, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 2000.f)
	, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
	, mScrollSpeed(-50.f)
{
	loadResources();
	buildScene();

	// prepare the view
	mWorldView.setCenter(mSpawnPosition);
}

void GameScreen::update(sf::Time dt)
{
	// scroll the world
	mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());

	// move player sidewards 
	sf::Vector2f position = mPlayerTetromino->getPosition();
	sf::Vector2f velocity = mPlayerTetromino->getVelocity();

	// if player touches borders, flip its x velocity
	if (position.x <= mWorldBounds.left + 150.0f || position.x >= mWorldBounds.left + mWorldBounds.width - 150.f)
	{
		velocity.x = -velocity.x;
		mPlayerTetromino->setVelocity(velocity);
	}

	mSceneGraph.update(dt);
}

void GameScreen::draw()
{
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}

void GameScreen::loadResources()
{
}

void GameScreen::buildScene()
{
	const int tetrominosCounter = 30;
	sf::Vector2f centerShape(0.0f, 0.0f);

	sf::Vector2f windowSize(600.f, 600.f);
	sf::Vector2f centerScreen = windowSize / 2.0f;

	for (auto i = 0; i < tetrominosCounter; i++) {
		int randomId = rand() % 5 + 1;

		if (randomId == Tetromino::L) {
			std::unique_ptr<Tetromino>lShape(new Tetromino(Tetromino::T));
			mTetrominos.push_back(std::move(lShape));
			sf::Vector2f tetrominoCenter = lShape->findCenter(lShape->mShape);
			sf::Vector2f offsetToCenter = centerScreen - tetrominoCenter;
			sf::Vector2f moveToTop(offsetToCenter.x, offsetToCenter.y - 300.f);
			//mSpawnPosition = moveToTop;
			lShape->setPosition(moveToTop);

			mSceneLayers[Plataform]->attachChild(std::move(lShape));

		}
		else if (randomId == Tetromino::T) {
			std::unique_ptr<Tetromino>tShape(new Tetromino(Tetromino::T));
			mTetrominos.push_back(std::move(tShape));

			tShape->setPosition(mSpawnPosition);
			mSceneLayers[Plataform]->attachChild(std::move(tShape));

		}
		else if (randomId == Tetromino::O) {
			std::unique_ptr<Tetromino>oShape(new Tetromino(Tetromino::O));
			mTetrominos.push_back(std::move(oShape));
			oShape->setPosition(mSpawnPosition);
			mSceneLayers[Plataform]->attachChild(std::move(oShape));
		}
		else if (randomId == Tetromino::S) {
			std::unique_ptr<Tetromino>sShape(new Tetromino(Tetromino::S));
			mTetrominos.push_back(std::move(sShape));
			sShape->setPosition(mSpawnPosition);
			mSceneLayers[Plataform]->attachChild(std::move(sShape));
		}
		else if (randomId == Tetromino::Z) {
			std::unique_ptr<Tetromino>zShape(new Tetromino(Tetromino::Z));
			mTetrominos.push_back(std::move(zShape));
			zShape->setPosition(mSpawnPosition);
			mSceneLayers[Plataform]->attachChild(std::move(zShape));
		}
		else {
			std::unique_ptr<Tetromino>lShape(new Tetromino(Tetromino::L));
			mTetrominos.push_back(std::move(lShape));
			lShape->setPosition(mSpawnPosition);
			mSceneLayers[Plataform]->attachChild(std::move(lShape));
		}

		sf::Vector2f windowSize(600.f, 600.f);
		sf::Vector2f centerScreen = windowSize / 2.0f;

		sf::Vector2f tetrominoCenter = mTetrominos[i]->getCenter();
		sf::Vector2f offsetToCenter = centerScreen - tetrominoCenter;
		sf::Vector2f moveToTop(offsetToCenter.x, offsetToCenter.y - 300.f);

		/*for (std::size_t j = 0; j < mTetrominos[i]->mShape.getVertexCount(); j++) {
			mTetrominos[i]->mShape[j].position += moveToTop;
		}*/
	}
}
