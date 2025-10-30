#pragma once
#include "../../header/UI/UIElements/Buttons/Button.h"
#include "../../header/Event/EventPollingManager.h"

using namespace UIElements;

namespace Gameplay
{
    enum class CellState
    {
        HIDDEN,
        OPEN,
        FLAGGED,
    };

    enum class CellType
    {
        EMPTY,
        ONE,
        TWO,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        MINE,
    };
	class Cell
	{
	private:
		sf::Vector2i position;

		const int tile_size = 128;
		const int slice_count = 12;
		const std::string cell_texture_path = "assets/textures/cells.jpeg";

		Buttons::Button* cell_button;
        CellState current_cell_state;
        CellType cell_type;

        const float cell_top_offset = 274.0f;
        const float cell_left_offset = 583.0f;

        void Initialize(float width, float height, sf::Vector2i position);

        sf::Vector2f Get_Cell_Screen_Position(float width,float height)const;

	public:
		Cell(float width, float height, sf::Vector2i position);
		~Cell() = default;

		void Render(sf::RenderWindow& window);

        CellState Get_Cell_State()const;
        void Set_Cell_State(CellState state);

        CellType Get_Cell_Tyoe()const;
        void Set_Cell_Type(CellType type);

        void Set_Cell_Texture();
	};
}