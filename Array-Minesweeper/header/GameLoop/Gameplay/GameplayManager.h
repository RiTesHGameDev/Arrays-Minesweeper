#pragma once
#include "../../header/GameLoop/Gameplay/Board.h"
#include "../../header/Event/EventPollingManager.h"
#include "SFML/Graphics.hpp"

namespace Gameplay
{
	enum class GameResult
	{
		NONE,
		WON,
		LOST
	};
	class GameplayManager
	{
	private:
		const float background_aplha = 85.0f;

		sf::Texture background_texture;
		sf::Sprite background_sprite;
		std::string background_texture_path = "assets/textures/minesweeper_bg.png";
		Board* board;

		GameResult game_result;

		void Initialize();
		void Initialize_Variables();
		void Initialize_Background_Image();

		bool Has_Game_Ended();

	public:
		GameplayManager();
		~GameplayManager();
		void SetGameResult(GameResult gameResult);
		void Render(sf::RenderWindow& window);
		void Update(Event::EventPollingManager& event_manager, const sf::RenderWindow& window);
	};
}