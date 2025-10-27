#include "../../header/GameLoop/Gameplay/Board.h"
#include <iostream>

namespace Gameplay
{
	Board::Board()
	{
		Initialize();
	}
	void Board::Initialize()
	{
		Initialize_Board_Image();
	}
	void Board::Initialize_Board_Image()
	{
		if (!board_texture.loadFromFile(board_texture_path))
		{
			std::cerr << "Failed to load board texture" << std::endl;
		}
		board_sprite.setTexture(board_texture);
		board_sprite.setPosition(board_position,0);
		board_sprite.setScale(board_width / board_texture.getSize().x, board_height / board_texture.getSize().y);

	}
	void Board::Render(sf::RenderWindow& window)
	{
		window.draw(board_sprite);
	}
}