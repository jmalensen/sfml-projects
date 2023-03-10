#include "../include/settingsstate.h"

void SettingsState::initVariables()
{
	this->m_modes = sf::VideoMode::getFullscreenModes();
	// sf::VideoMode bigScreen1(3720, 1920);
	// sf::VideoMode bigScreen2(2480, 1280);
	// sf::VideoMode bigScreen3(1860, 960); // accepted resolutions to keep the ratio correct
	// sf::VideoMode bigScreen4(1550, 800);
	// sf::VideoMode bigScreen5(1240, 640);
	// std::vector<sf::VideoMode> possibleResolutions{bigScreen1, bigScreen2, bigScreen3, bigScreen4, bigScreen5};
	// this->m_modes = possibleResolutions;
}

void SettingsState::initGui()
{
	this->window->setPosition(sf::Vector2i(0, 0));
	const sf::VideoMode &vm = this->stateData->gfxSettings->resolution;

	std::cout << "Settings resolution !" << vm.width << " " << vm.height << std::endl;

	this->m_background.setSize(
			sf::Vector2f(
					static_cast<float>(vm.width),
					static_cast<float>(vm.height)));

	if (!this->m_backgroundTexture.loadFromFile("images/bg1.jpg"))
	{
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->m_background.setTexture(&this->m_backgroundTexture);

	this->m_buttons["BACK"] = new gui::Button(
			gui::p2pX(72.f, vm), gui::p2pY(81.5f, vm),
			gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
			&this->m_font, "Back", gui::calcCharSize(vm),
			sf::Color(70, 120, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
			sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->m_buttons["APPLY"] = new gui::Button(
			gui::p2pX(60.f, vm), gui::p2pY(81.5f, vm),
			gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
			&this->m_font, "Apply", gui::calcCharSize(vm),
			sf::Color(70, 120, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
			sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	std::vector<std::string> modes_str;
	for (auto &i : this->m_modes)
	{
		modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	}

	this->m_dropDownLists["RESOLUTION"] = new gui::DropDownList(gui::p2pX(42.f, vm), gui::p2pY(42.f, vm),
																															gui::p2pX(10.4f, vm), gui::p2pY(4.5f, vm), this->m_font, gui::calcCharSize(vm, 100), modes_str.data(), modes_str.size());

	this->m_optionsText.setFont(this->m_font);
	this->m_optionsText.setPosition(sf::Vector2f(gui::p2pX(5.2f, vm), gui::p2pY(41.7f, vm)));
	this->m_optionsText.setCharacterSize(gui::calcCharSize(vm));
	this->m_optionsText.setFillColor(sf::Color(255, 255, 255, 200));

	this->m_optionsText.setString(
			"Resolution \n\nFullscreen ");
}

void SettingsState::resetGui()
{
	/*
	 * Clears the GUI elements and re-initialises the GUI.
	 *
	 * @return void
	 */

	auto it = this->m_buttons.begin();
	for (it = this->m_buttons.begin(); it != this->m_buttons.end(); ++it)
	{
		delete it->second;
	}
	this->m_buttons.clear();

	auto it2 = this->m_dropDownLists.begin();
	for (it2 = this->m_dropDownLists.begin(); it2 != this->m_dropDownLists.end(); ++it2)
	{
		delete it2->second;
	}
	this->m_dropDownLists.clear();

	// this->initGui();
}

void SettingsState::initFonts()
{
	if (!this->m_font.loadFromFile("fonts/arial.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void SettingsState::initKeybinds()
{
	std::ifstream ifs("config/mainmenustate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}

SettingsState::SettingsState(StateData *stateData)
		: State(stateData)
{
	this->initVariables();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
}

SettingsState::~SettingsState()
{
	auto it = this->m_buttons.begin();
	for (it = this->m_buttons.begin(); it != this->m_buttons.end(); ++it)
	{
		delete it->second;
	}

	auto it2 = this->m_dropDownLists.begin();
	for (it2 = this->m_dropDownLists.begin(); it2 != this->m_dropDownLists.end(); ++it2)
	{
		delete it2->second;
	}
}

// Accessors

// Functions
void SettingsState::updateInput(const float &dt)
{
}

void SettingsState::updateGui(const float &dt)
{
	/*Updates all the gui elements in the state and handle their functionality.*/
	// Buttons
	for (auto &it : this->m_buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	// Button functionality
	// Quit the game
	if (this->m_buttons["BACK"]->isPressed())
	{
		this->endState();
		this->states->push(new MainMenuState(this->stateData));
	}

	// Apply selected settings
	if (this->m_buttons["APPLY"]->isPressed())
	{
		// TEST REMOVE LATER
		this->stateData->gfxSettings->resolution = this->m_modes[this->m_dropDownLists["RESOLUTION"]->getActiveElementId()];

		// Memory leak here or not ?
		this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, sf::Style::Default);

		// this->window->setSize(
		// 		sf::Vector2u(
		// 				static_cast<int>(this->stateData->gfxSettings->resolution.width),
		// 				static_cast<int>(this->stateData->gfxSettings->resolution.height)));

		// // Update the view to the new size of the window
		// sf::FloatRect visibleArea(0.f, 0.f, this->stateData->gfxSettings->resolution.width, this->stateData->gfxSettings->resolution.height);
		// this->window->setView(sf::View(visibleArea));

		// this->resetGui();

		this->endState();
		this->states->push(new SettingsState(this->stateData));
	}

	// Dropdown lists
	for (auto &it : this->m_dropDownLists)
	{
		it.second->update(this->mousePosWindow, dt);
	}
}

void SettingsState::update(const float &dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateGui(dt);
}

void SettingsState::drawGui(sf::RenderTarget &target)
{
	for (auto &it : this->m_buttons)
	{
		it.second->draw(target);
	}

	for (auto &it : this->m_dropDownLists)
	{
		it.second->draw(target);
	}
}

void SettingsState::draw(sf::RenderTarget *target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->m_background);

	this->drawGui(*target);

	target->draw(this->m_optionsText);

	// REMOVE LATER!!!
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouseText.setFont(this->m_font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);
}