#ifndef __GAME_HPP__
#define __GAME_HPP__

/*
====================
Class Includes
====================
*/
#include <sparky\core\scene.hpp>			// Game is a scene in the application.
#include <sparky\generation\chunk.hpp>
#include <sparky\rendering\texture.hpp>
#include <sparky\input\input.hpp>
#include <sparky\rendering\basicshader.hpp>

class Game : public sparky::Scene
{
private:
	sparky::Chunk*	     m_pChunk;
	sparky::Texture*     m_pTexture;
	sparky::Input*		 m_pInput;
	sparky::BasicShader* m_pShader;

public:
	/*
	====================
	Ctor and Dtor
	====================
	*/
	Game(void);
	~Game(void);

	/*
	====================
	Methods
	====================
	*/
	void update(void) override;
	void render(void) override;
};

#endif//__GAME_HPP__