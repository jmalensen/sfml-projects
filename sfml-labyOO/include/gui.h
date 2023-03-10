#ifndef GUI_H
#define GUI_H

#include "stdHeader.h"

enum button_states
{
	BTN_IDLE = 0,
	BTN_HOVER,
	BTN_ACTIVE
};

namespace gui
{
	const float p2pX(const float perc, const sf::VideoMode &vm);
	const float p2pY(const float perc, const sf::VideoMode &vm);
	const unsigned calcCharSize(const sf::VideoMode &vm, const unsigned modifier = 60);

	const float scale(const float initialSize, sf::RenderWindow *window);
	const float getFactor(const float initialSize, sf::RenderWindow *window);

	class Button
	{
	public:
		Button(float x, float y, float width, float height,
					 sf::Font *font, std::string text, unsigned characterSize,
					 sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
					 sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
					 sf::Color outlineIdleColor = sf::Color::Transparent, sf::Color outlineHoverColor = sf::Color::Transparent, sf::Color outlineActiveColor = sf::Color::Transparent,
					 short unsigned id = 0);
		~Button();

		// Accessors
		const bool isPressed() const;
		const std::string getText() const;
		const short unsigned &getId() const;

		// Modifiers
		void setText(const std::string text);
		void setId(const short unsigned id);

		// Functions
		void update(const sf::Vector2i &mousePosWindow);
		void draw(sf::RenderTarget &target);

	private:
		short unsigned buttonState;
		short unsigned id;

		sf::RectangleShape shape;
		sf::Font *font;
		sf::Text text;

		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlineActiveColor;
	};

	class DropDownList
	{
	public:
		DropDownList(float x, float y, float width, float height,
								 sf::Font &font, unsigned characterSize, std::string list[],
								 unsigned nrOfElements, unsigned defaultIndex = 0);
		~DropDownList();

		// Accessors
		const unsigned short &getActiveElementId() const;

		// Functions
		const bool getKeytime();
		void updateKeytime(const float &dt);
		void update(const sf::Vector2i &mousePosWindow, const float &dt);
		void draw(sf::RenderTarget &target);

	private:
		float keytime;
		float keytimeMax;

		sf::Font &font;
		gui::Button *activeElement;
		std::vector<gui::Button *> list;
		bool showList;
	};
}

#endif
