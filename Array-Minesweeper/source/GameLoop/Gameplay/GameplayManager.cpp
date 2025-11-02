#include <iostream>
#include"../../header/GameLoop/Gameplay/GameplayManager.h"

namespace Gameplay
{
	GameplayManager::GameplayManager()
	{
		Initialize();
	}
	GameplayManager::~GameplayManager()
	{

	}
	void GameplayManager::Initialize()
	{
		Initialize_Variables();
		Initialize_Background_Image();
	}
	void GameplayManager::Initialize_Variables()
	{
		board = new Board(this);
	}
	void GameplayManager::Initialize_Background_Image()
	{
		if (!background_texture.loadFromFile(background_texture_path))
		{
			std::cerr << "Failed to load background texture!" << std::endl;
		}
		background_sprite.setTexture(background_texture);
		background_sprite.setColor(sf::Color(255, 255, 255, background_aplha));
	}
	void GameplayManager::Render(sf::RenderWindow& window)
	{
		window.draw(background_sprite);
		board->Render(window);
	}
	void GameplayManager::Update(Event::EventPollingManager& event_manager,
		const sf::RenderWindow& window)
	{
		if (!Has_Game_Ended())
		{
			board->Update(event_manager, window);
		}
	}
	void GameplayManager::SetGameResult(GameResult gameResult)
	{
		this->game_result = gameResult;
	}
	bool GameplayManager::Has_Game_Ended()
	{
		return game_result != GameResult::NONE;
	}
}