#include "GameScreen.h"
#include "../entities/Tetromino.h"
#include <iostream>

GameScreen::GameScreen(sf::RenderWindow& window)
	: mWindow(window)
	, mWorldView(window.getDefaultView())
	//, mTextures()
	, mSceneGraph()
	, mSceneLayers()
	, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 2000.f)
	, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
	, mTetrominosSpawnPoints()
	, mScrollSpeed(-50.f)
	, mPlayerTetromino(nullptr)
{
	loadResources();
	buildScene();

	mWorldView.setCenter(mSpawnPosition);
	// prepare the view
	/*std::unique_ptr<Tetromino>lShape(new Tetromino(Tetromino::L));
	mPlayerTetromino = lShape.get();*/
	/*std::unique_ptr<Tetromino>lShape(new Tetromino(Tetromino::L));
	mPlayerTetromino = lShape.get();*/
	spawnTetrominos();
}

void GameScreen::update(sf::Time dt)
{
	// scroll the world
	mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());

	mPlayerTetromino->setVelocity(0.0f, 0.0f);

	// Forward commands to the scene graph
	while (!mCommandQueue.isEmpty())
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);
	adaptPlayerVelocity();

	const float MAX_FLOOR = 540.649f;
	/*if (velocity.y > MAX_FLOOR) {
	}
		*/
	//if(mPlayerTetromino.)
	spawnTetrominos();
	mSceneGraph.update(dt);
	adaptPlayerPosition();

}

void GameScreen::draw()
{

	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}

CommandQueue& GameScreen::getCommandQueue()
{
	return mCommandQueue;
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
	// Tengo que modificar este metodo para que spawnee un nuevo tetromino cuando llega al final de la plataforma
	while (!mTetrominosSpawnPoints.empty() && mTetrominosSpawnPoints.back().y > getGamePlataformBounds().top)
	{
		SpawnPoint spawn = mTetrominosSpawnPoints.back();

		std::unique_ptr<Tetromino> tetromino(new Tetromino(spawn.type));

		tetromino->setPosition(spawn.x, spawn.y);

		mPlayerTetromino = tetromino.get();

		mSceneLayers[Plataform]->attachChild(std::move(tetromino));

		mTetrominosSpawnPoints.pop_back();
	}
}

void GameScreen::destroyEntitiesOfView()
{
}

void GameScreen::adaptPlayerVelocity()
{
	sf::Vector2f velocity = mPlayerTetromino->getVelocity();
	if (velocity.x != 0.f && velocity.y != 0.f) {
		std::cout << "vy " << velocity.y << std::endl;
		std::cout << "vx " << velocity.x << std::endl;
		assert(velocity.y != 0.0f);
		assert(velocity.x != 0.0f);
		mPlayerTetromino->setVelocity(velocity / std::sqrt(2.f));
	}
	assert(mScrollSpeed != 0.f);
	mPlayerTetromino->moveEntity(0.f,mScrollSpeed);

}

void GameScreen::adaptPlayerPosition()
{
	// Keep player's position inside the screen bounds, at least borderDistance units from the border
	sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
	const float borderDistance = 40.f;

	sf::Vector2f position = mPlayerTetromino->getPosition();
	position.x = std::max(position.x, viewBounds.left + borderDistance);
	position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
	position.y = std::max(position.y, viewBounds.top + borderDistance);
	position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
	mPlayerTetromino->setPosition(position);
}

void GameScreen::handleCollisions()
{
	std::set<SceneNode::Pair> collisionPairs;
	mSceneGraph.checkSceneCollision(mSceneGraph, collisionPairs);

	for (SceneNode::Pair pair : collisionPairs)
	{
		// if tetromino lands to the floor
		if (matchesCategories(pair, Category::PlayerTetromino, Category::LandedTetromino)) {
			auto& player = static_cast<Tetromino&>(*pair.first);
			auto& landedTetromino = static_cast<Tetromino&>(*pair.second);
			/*std::unique_ptr<Tetromino> playerTetro = std::make_unique<Tetromino>(std::move(player));
			mTetrominosLanded.push_back(playerTetro);
			mPlayerTetromino->destroy();*/
		}
		else if (matchesCategories(pair, Category::PlayerTetromino, Category::Floor)) {
			auto& player = static_cast<Tetromino&>(*pair.first);
			//auto& floor = static_cast<Tetromino&>(*pair.second);
			/*std::unique_ptr<Tetromino> playerTetro = std::make_unique<Tetromino>(std::move(player));
			mTetrominosLanded.push_back(playerTetro);
			mPlayerTetromino->destroy();*/
		}
	}
}

bool matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2)
{
	unsigned int category1 = colliders.first->getCategory();
	unsigned int category2 = colliders.second->getCategory();

	// Make sure first pair entry has category type1 and second has type2
	if (type1 & category1 && type2 & category2)
	{
		return true;
	}
	else if (type1 & category2 && type2 & category1)
	{
		std::swap(colliders.first, colliders.second);
		return true;
	}
	else
	{
		return false;
	}
}

void GameScreen::addTetrominos()
{
	/*std::unique_ptr<Tetromino>lShape(new Tetromino(Tetromino::L));
	mPlayerTetromino = lShape.get();
	std::unique_ptr<Tetromino> tetromino(new Tetromino(spawn.type));

		tetromino->setPosition(spawn.x, spawn.y);

		mSceneLayers[Plataform]->attachChild(std::move(tetromino));
	*/
	/*std::unique_ptr<Tetromino>lShape(new Tetromino(Tetromino::L));
	mPlayerTetromino = lShape.get();
	mPlayerTetromino->setPosition(mSpawnPosition);
	mSceneLayers[Plataform]->attachChild(std::move(lShape));*/
	//spawnTetrominos();
	addTetromino(mPlayerTetromino->L);

	// add random tetrominos
	//for (auto i = 0; i < tetrominosCounter; i++) {
	//	int randomId = rand() % 5 + 1;

	//	//if (randomId == Tetromino::L) {
	//	//	//std::unique_ptr<Tetromino>lShape(new Tetromino(Tetromino::T));
	//	//	////mTetrominos.push_back(std::move(lShape));
	//	//	//sf::Vector2f tetrominoCenter = lShape->findCenter(lShape->mShape);
	//	//	//sf::Vector2f offsetToCenter = centerScreen - tetrominoCenter;
	//	//	//sf::Vector2f moveToTop(offsetToCenter.x, offsetToCenter.y - 300.f);
	//	//	////mSpawnPosition = moveToTop;
	//	//	//lShape->setPosition(mSpawnPosition);

	//	//	//mSceneLayers[Plataform]->attachChild(std::move(lShape));
	//	//	addTetromino(Tetromino::L);

	//	//}
	//	//else if (randomId == Tetromino::T) {
	//	//	//std::unique_ptr<Tetromino>tShape(new Tetromino(Tetromino::T));
	//	//	//mTetrominos.push_back(std::move(tShape));
	//	//	addTetromino(Tetromino::T);

	//	//}
	//	//else if (randomId == Tetromino::O) {
	//	//	addTetromino(Tetromino::O);
	//	//}
	//	//else if (randomId == Tetromino::S) {
	//	//	//std::unique_ptr<Tetromino>sShape(new Tetromino(Tetromino::S));
	//	//	////mTetrominos.push_back(std::move(sShape));
	//	//	//sShape->setPosition(mSpawnPosition);
	//	//	//mSceneLayers[Plataform]->attachChild(std::move(sShape));
	//	//	addTetromino(Tetromino::S);
	//	//}
	//	//else if (randomId == Tetromino::Z) {
	//	//	//std::unique_ptr<Tetromino>zShape(new Tetromino(Tetromino::Z));
	//	//	////mTetrominos.push_back(std::move(zShape));
	//	//	//zShape->setPosition(mSpawnPosition);
	//	//	//mSceneLayers[Plataform]->attachChild(std::move(zShape));
	//	//	addTetromino(Tetromino::Z);
	//	//}
	//	//else {
	//	//	//std::unique_ptr<Tetromino>lShape(new Tetromino(Tetromino::L));
	//	//	////mTetrominos.push_back(std::move(lShape));
	//	//	////lShape->setPosition(mSpawnPosition);
	//	//	//mPlayerTetromino = lShape.get();
	//	//	//mSceneLayers[Plataform]->attachChild(std::move(lShape));
	//	//	addTetromino(Tetromino::L);
	//	//}
	//}
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


