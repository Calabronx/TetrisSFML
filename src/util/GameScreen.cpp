#include "GameScreen.h"
#include "../entities/Tetromino.h"

GameScreen::GameScreen(sf::RenderWindow& window)
	: mWindow(window)
	, mWorldView(window.getDefaultView())
	//, mTextures()
	, mSceneGraph()
	, mSceneLayers()
	, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 2000.f)
	, mSpawnPosition(0.0f, 500.0f)
	, mTetrominosSpawnPoints()
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
	//mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());

	// move player sidewards 
	sf::Vector2f position = mPlayerTetromino->getPosition();
	sf::Vector2f velocity = mPlayerTetromino->getVelocity();

	// if player touches borders, flip its x velocity
	if (position.x <= mWorldBounds.left + 150.0f || position.x >= mWorldBounds.left + mWorldBounds.width - 150.f)
	{
		velocity.x = -velocity.x;
		mPlayerTetromino->setVelocity(velocity);
	}

	spawnTetrominos();

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

	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachChild(std::move(layer));
	}

	addTetrominos();


	//sf::Vector2f windowSize(600.f, 600.f);
	//sf::Vector2f centerScreen = windowSize / 2.0f;


	//sf::Vector2f tetrominoCenter = mTetrominos[i]->getCenter();
	/*sf::Vector2f offsetToCenter = centerScreen - tetrominoCenter;
	sf::Vector2f moveToTop(offsetToCenter.x, offsetToCenter.y - 300.f);*/

	/*for (std::size_t j = 0; j < mTetrominos[i]->mShape.getVertexCount(); j++) {
		mTetrominos[i]->mShape[j].position += moveToTop;
	}*/

}

void GameScreen::spawnTetrominos()
{
	// Spawn all tetrominos entering the view area (including distance) this frame
	while (!mTetrominosSpawnPoints.empty() && mTetrominosSpawnPoints.back().y > getGamePlataformBounds().top)
	{
		SpawnPoint spawn = mTetrominosSpawnPoints.back();

		std::unique_ptr<Tetromino> tetromino(new Tetromino(spawn.type));
		tetromino->setPosition(spawn.x, spawn.y);
		tetromino->setRotation(90.f);

		mSceneLayers[Plataform]->attachChild(std::move(tetromino));

		mTetrominosSpawnPoints.pop_back();
	}
}

void GameScreen::destroyEntitiesOfView()
{
}

void GameScreen::addTetrominos()
{
	const int tetrominosCounter = 30;
	sf::Vector2f centerShape(0.0f, 0.0f);

	sf::Vector2f windowSize(600.f, 600.f);
	sf::Vector2f centerScreen = windowSize / 2.0f;

	// add random tetrominos
	for (auto i = 0; i < tetrominosCounter; i++) {
		int randomId = rand() % 5 + 1;

		std::unique_ptr<Tetromino>lShape(new Tetromino(Tetromino::L));
		//mTetrominos.push_back(std::move(lShape));
		//lShape->setPosition(mSpawnPosition);
		mPlayerTetromino = lShape.get();
		//mSceneLayers[Plataform]->attachChild(std::move(lShape));

		if (randomId == Tetromino::L) {
			//std::unique_ptr<Tetromino>lShape(new Tetromino(Tetromino::T));
			////mTetrominos.push_back(std::move(lShape));
			//sf::Vector2f tetrominoCenter = lShape->findCenter(lShape->mShape);
			//sf::Vector2f offsetToCenter = centerScreen - tetrominoCenter;
			//sf::Vector2f moveToTop(offsetToCenter.x, offsetToCenter.y - 300.f);
			////mSpawnPosition = moveToTop;
			//lShape->setPosition(mSpawnPosition);

			//mSceneLayers[Plataform]->attachChild(std::move(lShape));
			addTetromino(Tetromino::L);

		}
		else if (randomId == Tetromino::T) {
			//std::unique_ptr<Tetromino>tShape(new Tetromino(Tetromino::T));
			//mTetrominos.push_back(std::move(tShape));
			addTetromino(Tetromino::T);

		}
		else if (randomId == Tetromino::O) {
			addTetromino(Tetromino::O);
		}
		else if (randomId == Tetromino::S) {
			//std::unique_ptr<Tetromino>sShape(new Tetromino(Tetromino::S));
			////mTetrominos.push_back(std::move(sShape));
			//sShape->setPosition(mSpawnPosition);
			//mSceneLayers[Plataform]->attachChild(std::move(sShape));
			addTetromino(Tetromino::S);
		}
		else if (randomId == Tetromino::Z) {
			//std::unique_ptr<Tetromino>zShape(new Tetromino(Tetromino::Z));
			////mTetrominos.push_back(std::move(zShape));
			//zShape->setPosition(mSpawnPosition);
			//mSceneLayers[Plataform]->attachChild(std::move(zShape));
			addTetromino(Tetromino::Z);
		}
		else {
			//std::unique_ptr<Tetromino>lShape(new Tetromino(Tetromino::L));
			////mTetrominos.push_back(std::move(lShape));
			////lShape->setPosition(mSpawnPosition);
			//mPlayerTetromino = lShape.get();
			//mSceneLayers[Plataform]->attachChild(std::move(lShape));
			addTetromino(Tetromino::L);
		}
	}
}

// Only use if you want to change the position of the tetrominos appearing on the view
void GameScreen::addTetromino(Tetromino::Type type, float relX, float relY)
{
	SpawnPoint spawn(type, mSpawnPosition.x + relX, mSpawnPosition.y - relY);
	mTetrominosSpawnPoints.push_back(spawn);
}

void GameScreen::addTetromino(Tetromino::Type type)
{

	SpawnPoint spawn(type, mSpawnPosition.x, mSpawnPosition.y);
	mTetrominosSpawnPoints.push_back(spawn);
}

sf::FloatRect GameScreen::getViewBounds() const
{
	return sf::FloatRect(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
}

sf::FloatRect GameScreen::getGamePlataformBounds() const
{
	// Return view bounds + some area at top, where tetrominos spawn
	sf::FloatRect bounds = getViewBounds();
	bounds.top -= 100.f;
	bounds.height += 100.f;

	return bounds;
}
