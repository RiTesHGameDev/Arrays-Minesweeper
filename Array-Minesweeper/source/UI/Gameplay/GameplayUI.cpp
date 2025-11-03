#include <iostream>
#include "../../../header/UI/Gameplay/GameplayUI.h"
#include "../../header/GameLoop/Gameplay/GameplayManager.h"

namespace UI
{
	GameplayUI::GameplayUI(GameplayManager* gameplay_manager)
	{
		Initialize(gameplay_manager);
	}
	void GameplayUI::Initialize(GameplayManager* gameplay_manager)
	{
		this->gameplay_manager = gameplay_manager;
		Load_Fonts();
		Initialize_Texts();
	}
	void GameplayUI::Initialize_Texts()
	{
		mine_text.setFont(ds_digib_font);
		mine_text.setCharacterSize(font_size);
		mine_text.setFillColor(text_color);
		mine_text.setPosition(mine_text_left_offset, mine_text_top_offset);
		mine_text.setString("000");

		time_text.setFont(ds_digib_font);
		time_text.setCharacterSize(font_size);
		time_text.setFillColor(text_color);
		time_text.setPosition(time_text_left_offset, time_text_top_offset);
		time_text.setString("000");
	}
	void GameplayUI::Load_Fonts()
	{
		if (!bubbule_bobble_font.loadFromFile("assets/fonts/bubbleBobble.ttf"))
			std::cerr << "Error loading bubbleBobble font" << std::endl;
		if (!ds_digib_font.loadFromFile("assets/fonts/DS_DIGIB.ttf"))
			std::cerr << "Error loading DS_DIGIB font" << std::endl;
	}
	void GameplayUI::Update(int remaining_mines, int remaining_time,Event::EventPollingManager& event_manager,
		sf::RenderWindow& window)
	{
		mine_text.setString(std::to_string(remaining_mines));
		time_text.setString(std::to_string(remaining_time));
	}
	void GameplayUI::Render(sf::RenderWindow& window)
	{
		window.draw(mine_text);
		window.draw(time_text);
	}
}