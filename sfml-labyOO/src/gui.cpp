#include "../include/gui.h"

const float gui::p2pX(const float perc, const sf::VideoMode &vm)
{
	/*
	 * Converts a percentage value to pixels relative to the current resolution in the x-axis.
	 *
	 * @param		float perc				The percentage value.
	 * @param		sf::VideoMode& vm		The current videomode of the window (resolution).
	 *
	 * @return		float					The calculated pixel value.
	 */

	return std::floor(static_cast<float>(vm.width) * (perc / 100.f));
}

const float gui::p2pY(const float perc, const sf::VideoMode &vm)
{
	/*
	 * Converts a percentage value to pixels relative to the current resolution in the y-axis.
	 *
	 * @param		float perc				The percentage value.
	 * @param		sf::VideoMode& vm		The current videomode of the window (resolution).
	 *
	 * @return		float					The calculated pixel value.
	 */

	return std::floor(static_cast<float>(vm.height) * (perc / 100.f));
}

const unsigned gui::calcCharSize(const sf::VideoMode &vm, const unsigned modifier)
{
	/*
	 * Calculates the character size for text using the current resolution and a constant.
	 *
	 * @param		sf::VideoMode& vm		The current videomode of the window (resolution).
	 * @param		unsigned modifier		Used to modify the character size in a more custom way.
	 *
	 * @return		unsigned				The calculated character size value.
	 */

	return static_cast<unsigned>((vm.width + vm.height) / modifier);
}

const float gui::scale(const float initialSize, sf::RenderWindow *window)
{
	// 60 / 1860 init width
	float factor = initialSize / 1860;

	return static_cast<float>(factor * window->getSize().x);
}

const float gui::getFactor(const float initialSize, sf::RenderWindow *window)
{
	// 60 / 1860 init width
	return static_cast<float>(((initialSize / 1860) * window->getSize().x) / initialSize);
}

gui::Button::Button(float x, float y, float width, float height,
										sf::Font *font, std::string text, unsigned characterSize,
										sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
										sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
										sf::Color outlineIdleColor, sf::Color outlineHoverColor, sf::Color outlineActiveColor,
										short unsigned id)
{
	this->buttonState = BTN_IDLE;
	this->id = id;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(idleColor);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outlineIdleColor);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(textIdleColor);
	this->text.setCharacterSize(characterSize);
	// std::cout << this->text.getGlobalBounds().width << "\n";
	this->text.setPosition(
			this->shape.getPosition().x,
			this->shape.getPosition().y);

	this->textIdleColor = textIdleColor;
	this->textHoverColor = textHoverColor;
	this->textActiveColor = textActiveColor;

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->outlineIdleColor = outlineIdleColor;
	this->outlineHoverColor = outlineHoverColor;
	this->outlineActiveColor = outlineActiveColor;
}

gui::Button::~Button()
{
}

// Accessors
const bool gui::Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
	{
		return true;
	}

	return false;
}

const std::string gui::Button::getText() const
{
	return this->text.getString();
}

const short unsigned &gui::Button::getId() const
{
	return this->id;
}

// Modifiers
void gui::Button::setText(const std::string text)
{
	this->text.setString(text);
}

void gui::Button::setId(const short unsigned id)
{
	this->id = id;
}

// Functions
void gui::Button::update(const sf::Vector2i &mousePosWindow)
{
	/*Update the booleans for hover and pressed*/

	// Idle
	this->buttonState = BTN_IDLE;

	// Hover
	if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
	{
		this->buttonState = BTN_HOVER;

		// Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->textIdleColor);
		this->shape.setOutlineColor(this->outlineIdleColor);
		break;

	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		this->shape.setOutlineColor(this->outlineHoverColor);
		break;

	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		this->shape.setOutlineColor(this->outlineActiveColor);
		break;

	default:
		this->shape.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::Blue);
		this->shape.setOutlineColor(sf::Color::Green);
		break;
	}
}

void gui::Button::draw(sf::RenderTarget &target)
{
	target.draw(this->shape);
	target.draw(this->text);
}

// DROP DOWN LIST =============================================

gui::DropDownList::DropDownList(float x, float y, float width, float height,
																sf::Font &font, unsigned characterSize, std::string list[],
																unsigned nrOfElements, unsigned defaultIndex)
		: font(font), showList(false), keytimeMax(1.f), keytime(0.f)
{
	// unsigned nrOfElements = sizeof(list) / sizeof(std::string);

	this->activeElement = new gui::Button(
			x, y, width, height,
			&this->font, list[defaultIndex], characterSize,
			sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 200), sf::Color(20, 20, 20, 50),
			sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
			sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50));

	for (size_t i = 0; i < nrOfElements; i++)
	{
		this->list.push_back(
				new gui::Button(
						x, y + ((i + 1) * height), width, height,
						&this->font, list[i], characterSize,
						sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
						sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
						sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0), sf::Color(20, 20, 20, 0),
						i));
	}
}

gui::DropDownList::~DropDownList()
{
	delete this->activeElement;
	for (size_t i = 0; i < this->list.size(); i++)
	{
		delete this->list[i];
	}
}

// Accessors
const bool gui::DropDownList::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}

	return false;
}

const unsigned short &gui::DropDownList::getActiveElementId() const
{
	return this->activeElement->getId();
}

// Functions
void gui::DropDownList::updateKeytime(const float &dt)
{
	if (this->keytime < this->keytimeMax)
	{
		this->keytime += 10.f * dt;
	}
}

void gui::DropDownList::update(const sf::Vector2i &mousePosWindow, const float &dt)
{
	this->updateKeytime(dt);

	this->activeElement->update(mousePosWindow);

	// Show and hide the list
	if (this->activeElement->isPressed() && this->getKeytime())
	{
		if (this->showList)
		{
			this->showList = false;
		}
		else
		{
			this->showList = true;
		}
	}

	if (this->showList)
	{
		for (auto &i : this->list)
		{
			i->update(mousePosWindow);

			if (i->isPressed() && this->getKeytime())
			{
				this->showList = false;
				this->activeElement->setText(i->getText());
				this->activeElement->setId(i->getId());
			}
		}
	}
}

void gui::DropDownList::draw(sf::RenderTarget &target)
{
	this->activeElement->draw(target);

	if (this->showList)
	{
		for (auto &i : this->list)
		{
			i->draw(target);
		}
	}
}
