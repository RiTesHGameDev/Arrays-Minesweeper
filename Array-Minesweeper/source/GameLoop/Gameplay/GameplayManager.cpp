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
		board = new Board();
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
		board->Update(event_manager, window);
	}
}