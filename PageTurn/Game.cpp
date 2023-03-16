/// <summary>
/// @author Peter Lowe
/// @date May 2019
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprites(); // load texture
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
		if (sf::Event::MouseButtonPressed == newEvent.type
			|| sf::Event::MouseButtonReleased == newEvent.type)
		{
			processMouseClicks(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

void Game::processMouseClicks(sf::Event t_event)
{
	std::string filename = "ASSETS\\IMAGES\\page";
	if (sf::Event::MouseButtonPressed == t_event.type)
	{
		if (sf::Mouse::Button::Left == t_event.mouseButton.button)
		{
			m_currentPage = ++m_currentPage % 3;
			filename = filename + std::to_string(m_currentPage) + ".jpg";
			m_pageTexture = m_nextPageTexture;
			m_nextPageTexture.loadFromFile(filename);
			m_nextPageSprite.setTexture(m_nextPageTexture);
			m_SpriteFirst = true;
		}
		if (sf::Mouse::Button::Right == t_event.mouseButton.button)
		{
			m_currentPage = (m_currentPage + 2) % 3;
			filename = filename + std::to_string(m_currentPage) + ".jpg";
			m_pageTexture = m_nextPageTexture;
			m_nextPageTexture.loadFromFile(filename);
			m_nextPageSprite.setTexture(m_nextPageTexture);
			m_SpriteFirst = true;
		}
	}
	if (sf::Event::MouseButtonReleased == t_event.type)
	{
		if (sf::Mouse::Button::Left == t_event.mouseButton.button)
		{
			m_turning = true;
			m_currentFrame = 0;

		}
		if (sf::Mouse::Button::Right == t_event.mouseButton.button)
		{
			m_turning = true;
			m_currentFrame = 0;
		}
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	if (m_turning)
	{
		m_turning = pageTurn();
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	if (m_SpriteFirst)
	{
		m_window.draw(m_nextPageSprite);
		m_window.draw(m_pageVertexArray, &m_pageTexture);
	}
	else
	{
		m_window.draw(m_nextPageSprite);
		//m_window.draw(m_pageVertexArray,&m_pageTexture);
		//m_window.draw(m_nextPageSprite);		
	}
	
	m_window.draw(m_instructions);
	
	m_window.display();
}

bool Game::pageTurn()
{
	float dx = 800.0f / MAX_FRAMES;
	float dy = 600.0f / MAX_FRAMES;

	m_pageVertexArray[2].position.x -= 2*dx;
	m_pageVertexArray[2].position.y += dy;
	m_pageVertexArray[3].position.x -= dx;
	m_pageVertexArray[3].position.y += 2*dy;
	


	m_currentFrame++;
	if (m_currentFrame > MAX_FRAMES)
	{
		m_SpriteFirst = false;
		resetVertexArray();
		return false;
	}
	return true;
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_instructions.setFont(m_ArialBlackfont);
	m_instructions.setString("Left mouse for next\nRight for previous");	
	m_instructions.setPosition(40.0f, 100.0f);
	m_instructions.setCharacterSize(20U);	
	m_instructions.setFillColor(sf::Color::Black);
	

}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprites()
{
	sf::Vertex point;

	if (!m_nextPageTexture.loadFromFile("ASSETS\\IMAGES\\page0.jpg"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading Page" << std::endl;
	}
	if (!m_pageTexture.loadFromFile("ASSETS\\IMAGES\\page0.jpg"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading Page" << std::endl;
	}
	m_nextPageSprite.setTexture(m_pageTexture);

	point.color = sf::Color::White;
	point.position.x = 0.0f;
	point.position.y = 600.0f;
	point.texCoords = point.position;
	m_pageVertexArray.append(point); // bottom left
	
	point.position.y = 0.0f;
	point.texCoords = point.position;
	m_pageVertexArray.append(point);  // top left
	
	point.position.x = 800.0f;
	point.texCoords = point.position;
	m_pageVertexArray.append(point); // top right

	m_pageVertexArray.append(point); // top right second

	point.position.y = 600.0f;
	point.texCoords = point.position;
	m_pageVertexArray.append(point); // bottom left


}

void Game::resetVertexArray()
{
	m_pageVertexArray[2].position = sf::Vector2f(800.0f, 0.0f);
	m_pageVertexArray[3].position = sf::Vector2f(800.0f, 0.0f);
}
