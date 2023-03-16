/// <summary>
/// author Pete Lowe May 2019
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupSprites();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_instructions; // text used for message on screen
	sf::Texture m_pageTexture; // texture used for current page
	sf::Texture m_nextPageTexture; // texture for next page
	
	sf::VertexArray m_pageVertexArray{ sf::TriangleFan }; // departing page
	sf::Sprite m_nextPageSprite; // page behind
	bool m_exitGame; // control exiting game



};

#endif // !GAME_HPP

