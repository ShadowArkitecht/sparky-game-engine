#ifndef __GAME_HPP__
#define __GAME_HPP__

/*
====================
Class Includes
====================
*/
#include <sparky\core\scene.hpp>			// Game is a scene in the application.
#include <sparky\generation\world.hpp>
#include <sparky\rendering\texture.hpp>
#include <sparky\input\input.hpp>
#include <sparky\rendering\deferredshader.hpp>
#include <sparky\lighting\directionallight.hpp>

class Game : public sparky::Scene
{
private:
	sparky::World*	          m_pWorld;
	sparky::Texture*          m_pTexture;
	sparky::Input*		      m_pInput;
	sparky::DirectionalLight* m_pLight;
	sparky::DirectionalLight* m_pLight2;

	sparky::DeferredShader*   m_pShader;

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