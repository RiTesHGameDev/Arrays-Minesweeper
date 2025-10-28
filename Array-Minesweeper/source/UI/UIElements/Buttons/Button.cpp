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
	}
}