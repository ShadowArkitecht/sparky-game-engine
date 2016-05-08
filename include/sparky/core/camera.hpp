///////////////////////////////////////////////////////////////////////////////////////////////////
// 
// Sparky Engine
// 2016 - Benjamin Carter (benjamin.mark.carter@hotmail.com)
// 
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
// 
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
// 
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgement
//    in the product documentation would be appreciated but is not required.
// 
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
// 
// 3. This notice may not be removed or altered from any source distribution.
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __SPARKY_CAMERA_HPP__
#define __SPARKY_CAMERA_HPP__

/*
====================
Class Includes
====================
*/
#include <sparky\math\transform.hpp>	// Camera has its own transform.
#include <sparky\math\vector2.hpp>		// The dimensions of the Camera are a Vector2.

namespace sparky
{
	/*
	====================
	Sparky Forward Declarations
	====================
	*/
	class ConfigFile;
	class Window;

	class Camera final
	{
	private:
		/*
		====================
		Member Variables
		====================
		*/
		Transform	   m_transform;	 // The transform ( position and rotation ) of the Camera.
		float		   m_fov;		 // The field of view of the Camera.
		Vector2f       m_dimensions; // The width and height of the Camera.
		float		   m_nearPlane;	 // Near clipping plane.
		float		   m_farPlane;   // Far clipping plane.

		static Camera* m_pMain;		 // Main camera of the application.

	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Default construction of the Camera object, which sets
		///		   the member variables to default values.
		////////////////////////////////////////////////////////////
		explicit Camera(void);

		////////////////////////////////////////////////////////////
		/// \brief Destruction of the Camera object.
		////////////////////////////////////////////////////////////
		~Camera(void) = default;

		/*
		====================
		Getters and Setters
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Retrieves the main Camera object.
		///
		/// The main Camera is either the first camera initialised 
		/// upon program execution or the Camera that has been implicitly
		/// set to main.
		///
		/// \retval Camera&		The main Camera of the application.
		///
		////////////////////////////////////////////////////////////
		static Camera& getMain(void);

		////////////////////////////////////////////////////////////
		/// \brief Sets the main Camera object.
		///
		/// The main Camera is the Camera in which all objects within
		/// a scene use to render.
		///
		/// \param camera		The Camera to set to the main Camera.
		///
		////////////////////////////////////////////////////////////
		static void setMain(Camera& camera);

		////////////////////////////////////////////////////////////
		/// \brief Gets the transform of the Camera object.
		///
		/// The Transform of the Camera controls its position and rotation
		/// within 3D space.
		///
		/// \retval Transform&	The Transform of the Camera object.
		///
		////////////////////////////////////////////////////////////
		Transform& getTransform(void);

		////////////////////////////////////////////////////////////
		/// \brief Retrieves the field-of-view of the Camera object.
		///
		/// The field of view controls how wide of a view the Camera
		/// can currently see.
		///
		/// \retval float	The field-of-view of the Camera object.
		///
		////////////////////////////////////////////////////////////
		float getFoV(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Set the field-of-view of the Camera object.
		///
		/// The field of view controls how wide of a view the Camera
		/// can currently see.
		///
		/// \param fov	The new field-of-view of the Camera.
		///
		////////////////////////////////////////////////////////////
		void setFoV(const float fov);

		////////////////////////////////////////////////////////////
		/// \brief Gets the dimensions of the Camera object.
		///
		/// The dimensions of the Camera control the size of the 
		/// rendering Window. The dimensions are independent of the 
		/// Window.
		///
		/// \retval Vector2f&	The dimensions of the Camera object.
		///
		////////////////////////////////////////////////////////////
		const Vector2f& getDimensions(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Set the dimensions of the Camera object.
		///
		/// The dimensions of the Camera control the size of the 
		/// rendering Window. The dimensions are independent of the 
		/// Window.
		///
		/// \param dimensions	The new dimensions of the Camera.
		///
		////////////////////////////////////////////////////////////
		void setDimensions(const Vector2f& dimensions);

		////////////////////////////////////////////////////////////
		/// \brief Gets the near clipping plane of the Camera object.
		/// 
		/// Sets the near clipping plane of the Camera. The near clipping 
		/// plane controls the cut-off point where objects that are less
		/// than this distance away, are not rendered. Issues begin to occur 
		/// with values less than 10.0f.
		///
		/// \retval float	The near clipping plane.
		///
		////////////////////////////////////////////////////////////
		float getNearPlane(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Sets the near clipping plane of the Camera object.
		///
		/// Sets the near clipping plane of the Camera. The near clipping 
		/// plane controls the cut-off point where objects that are less
		/// than this distance away, are not rendered. Issues begin to occur
		/// with values less than 10.0f.
		/// 
		/// \param plane	The new near clipping plane.
		///
		////////////////////////////////////////////////////////////
		void setNearPlane(const float plane);

		////////////////////////////////////////////////////////////
		/// \brief Retrieves the far clipping plane of the Camera object.
		/// 
		/// Sets the far clipping plane of the Camera. The far clipping plane
		/// controls the cut-off point where objects that are greater than this 
		/// distance away, are not rendered.
		///
		/// \retval float	The far clipping plane.
		///
		////////////////////////////////////////////////////////////
		float getFarPlane(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Sets the far clipping plane of the Camera.
		///
		/// The far clipping plane controls the cut-off point where objects
		/// that are greater than this distance away, are not rendered.
		/// 
		/// \param plane	The new far clipping plane.
		///
		////////////////////////////////////////////////////////////
		void setFarPlane(const float plane);

		////////////////////////////////////////////////////////////
		/// \brief Gets the current projection matrix of the Camera. 
		///
		/// A projection matrix is responsible for projecting 3D points
		/// (such as vectors) that; when multiplied by camera space, are 
		/// projected onto the screen buffer in the correct positions.
		/// 
		/// \retval Matrix4f	The camera's projection matrix.
		///
		////////////////////////////////////////////////////////////
		Matrix4f getProjection(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Gets the view matrix of the camera. 
		///
		/// The view can be thought of as the user view into the projected world. 
		/// With the use of view projection, the world is projected into a 3D
		/// environment.
		/// 
		/// \retval Matrix4f	The perspective matrix of the camera.
		///
		////////////////////////////////////////////////////////////
		Matrix4f getView(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Gets the view projection of the current Camera object.
		/// 
		/// The view projection is just the multiplied result of the 
		/// Camera's view * projection.
		///
		/// \retval Matrix4f	The view projection of the Camera object.
		///
		////////////////////////////////////////////////////////////
		Matrix4f getViewProjection(void) const;

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Creates a Camera object with the values from a default
		///		   config file.
		////////////////////////////////////////////////////////////
		void create(void);

		////////////////////////////////////////////////////////////
		/// \brief Creates a Camera object from a user defined Config
		///		   file.
		///
		/// \param file		The configuration file to read the variables from.
		///
		////////////////////////////////////////////////////////////
		void create(const ConfigFile& file);

		////////////////////////////////////////////////////////////
		/// \brief Creates a Camera object from the dimensions of a
		///		   Window.
		///
		/// \param window	The Window object to read the variables from.
		///
		////////////////////////////////////////////////////////////
		void create(const Window& window);

		////////////////////////////////////////////////////////////
		/// \brief Creates a Camera object using user defined variables
		///		   to set the members.
		///
		/// \param fov			The field-of-view.
		/// \param dimensions	The rendering dimensions of the Camera.
		/// \param nearPlane	The near clipping plane.
		/// \param farPlane		The far clipping plane.
		///
		////////////////////////////////////////////////////////////
		void create(const float fov, const Vector2f& dimensions, const float nearPlane, const float farPlane);
	};

}//namespace sparky

#endif//__SPARKY_CAMERA_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::Camera
/// \ingroup core
///
/// sparky::Camera can be thought of as the user's point-of-view into 
/// the 3D game environment. The camera will calculate the projection
/// and perspective of objects and place them correctly within the scenes.
/// The camera can be adjusted around the scene, where the view-port will 
/// update in real-time accordingly. Below is a code example.
///
/// Usage example:
/// \code
/// // Create a config for the Window and Camera.
/// sparky::ConfigFile config;
/// config.open("data/config.scfg");
///
/// // Create a Window.
/// sparky::Window window;
/// window.create(config);
///
/// // Create a Camera.
/// sparky::Camera camera;
/// camera.create(config);
///
/// // (Inside a shader object) Multiply the transform by the Camera's view projection.
/// Matrix4f mvp = transform.getTransformation() * Camera::getMain().getViewProjection();
/// \endcode
///
////////////////////////////////////////////////////////////