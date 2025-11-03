#include <iostream>
#include "../../header/UI/UIElements/Buttons/Button.h"

namespace UIElements
{
	namespace Buttons
	{
		Button::Button(const std::string& texture_path, const sf::Vector2f& position, float width, float height)
		{
			Initialize(texture_path,position,width,height);
		}
		void Button::Initialize(const std::string& texture_path,
			const sf::Vector2f& position, float width, float height)
		{
			if (!button_texture.loadFromFile(texture_path))
			{
				std::cerr << "Failed to load butoon texture!" << std::endl;
			}
			button_sprite.setTexture(button_texture);
			button_sprite.setPosition(position);
			button_sprite.setScale(width / button_texture.getSize().x, height 
				/ button_texture.getSize().y);
		}
		void Button::Set_Texture_Rect(const sf::IntRect& rect)
		{
			button_sprite.setTextureRect(rect);
		}
		void Button::Render(sf::RenderWindow& window)const
		{
			window.draw(button_sprite);
		}
		bool Button::Is_Mouse_On_Sprite(Event::EventPollingManager& event_manager,const sf::RenderWindow& window)
		{
			sf::Vector2i mouse_position = event_manager.getMousePosition();
			return button_sprite.getGlobalBounds().contains(static_cast<float>(mouse_position.x),
				static_cast<float>(mouse_position.y));
		}
		void Button::Handle_Button_Interactions(Event::EventPollingManager& event_manager,
			const sf::RenderWindow& window)
		{
			if (event_manager.pressedLeftMouseButton() && Is_Mouse_On_Sprite(event_manager, window))
			{
				std::cerr << "Left mouse button click detected!" << std::endl;
				call_back_function(MouseButtonType::LEFT_MOUSE_BUTTON);
			}
			else if (event_manager.pressedRightMouseButton() && Is_Mouse_On_Sprite(event_manager, window))
			{
				std::cerr << "Right mouse button click detected!" << std::endl;
				call_back_function(MouseButtonType::RIGHT_MOUSE_BUTTON);
			}
		}
		void Button::Register_Callback_Function(CallBackFunction button_callback)
		{
			call_back_function = button_callback;
		}
	}
}