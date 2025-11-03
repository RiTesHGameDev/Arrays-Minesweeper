#include <iostream>
#include "../../header/GameLoop/GameLoop.h"
#include "../../header/UI/MainMenu/MainMenuManager.h"

namespace UI
{
	MainMenuManager::MainMenuManager(sf::RenderWindow* window)
	{
		game_window = window;
		Initialize();
	}
	void MainMenuManager::Initialize()
	{
		Initialize_Background();
		Initialize_Buttons();
	}
	void MainMenuManager::Initialize_Background()
	{
		if (!background_texture.loadFromFile(bacground_texture_path))
		{
			std::cerr << "Failed to load background texture" << std::endl;
			return;
		}
		background_sprite.setTexture(background_texture);
		background_sprite.setColor(sf::Color(255, 255, 255, background_aplha));
	}
	void MainMenuManager::Initialize_Buttons()
	{
		play_button = new Button(play_button_texture_path, Get_Button_Position(0.0f, play_button_y_position),
			button_width, button_height);
		quit_button = new Button(quit_button_texture_path, Get_Button_Position(0.0f, quit_button_y_position),
			button_width, button_height);

		Register_Button_Callbacks();
	}
	sf::Vector2f MainMenuManager::Get_Button_Position(float offset_x, float offset_y)
	{
		float x_position = (game_window->getSize().x - button_width) / 2.0f + offset_x;
		float y_position = offset_y;
		return sf::Vector2f(x_position, y_position);
	}
	void MainMenuManager::Register_Button_Callbacks()
	{
		play_button->Register_Callback_Function([this](MouseButtonType button_type)
			{Play_Button_Callback(button_type);});

		quit_button->Register_Callback_Function([this](MouseButtonType button_type)
			{Quit_Button_Callback(button_type);});
	}
	void MainMenuManager::Play_Button_Callback(MouseButtonType mouse_button_type)
	{
		if (mouse_button_type == MouseButtonType::LEFT_MOUSE_BUTTON)
		{
			Sound::SoundManager::PlaySound(Sound::SoundType::BUTTON_CLICK);
			GameLoop::setGameState(GameState::GAMEPLAY);
		}
	}
	void MainMenuManager::Quit_Button_Callback(MouseButtonType mouse_button_type)
	{
		if (mouse_button_type == MouseButtonType::LEFT_MOUSE_BUTTON)
		{
			Sound::SoundManager::PlaySound(Sound::SoundType::BUTTON_CLICK);
			GameLoop::setGameState(GameState::EXIT);
		}
	}
	void MainMenuManager::Render()
	{
		game_window->draw(background_sprite);
		if (play_button) play_button->Render(*game_window);
		if (quit_button) quit_button->Render(*game_window);
	}
	void MainMenuManager::Update(Event::EventPollingManager event_manager)
	{
		play_button->Handle_Button_Interactions(event_manager,*game_window);
		quit_button->Handle_Button_Interactions(event_manager, *game_window);
	}
}