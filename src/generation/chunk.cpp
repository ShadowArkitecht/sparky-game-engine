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

#include <iostream>
/*
====================
Class Includes
====================
*/
#include <sparky\generation\chunk.hpp>		// Class Definition.
#include <sparky\rendering\meshdata.hpp>	// For adding vertices and faces.
#include <sparky\rendering\ishader.hpp>		// The shader needs to be updated with the transform.
#include <sparky\math\frustum.hpp>			// Will only render when inside the viewport.
#include <sparky\utils\GLdevice.hpp>
#include <sparky\generation\world.hpp>

namespace sparky
{
	/*
	====================
	Constant Variables
	====================
	*/
	////////////////////////////////////////////////////////////
	const int Chunk::SIZE = 16;

	/*
	====================
	Ctor and Dtor
	====================
	*/
	////////////////////////////////////////////////////////////
	Chunk::Chunk(void)
		: Ref(), m_transform(), m_voxels(), m_pMesh(nullptr), m_pWorld(nullptr), m_isActive(false), m_checks(), m_shouldLoad(false)
	{
		for (auto& voxel : m_voxels)
		{
			voxel.setActive(false);
		}

		m_pMesh = new MeshData();
		m_pMesh->addRef();

		m_checks.fill(false);
	}

	////////////////////////////////////////////////////////////
	Chunk::~Chunk(void)
	{
		Ref::release(m_pMesh);
	}

	/*
	====================
	Getters and Setters
	====================
	*/
	////////////////////////////////////////////////////////////
	int Chunk::getSize(void)
	{
		return SIZE;
	}

	////////////////////////////////////////////////////////////
	Transform& Chunk::getTransform(void)
	{
		return m_transform;
	}

	////////////////////////////////////////////////////////////
	Voxel* Chunk::getVoxel(const Vector3i& pos)
	{
		return this->getVoxel(pos.x, pos.y, pos.z);
	}

	////////////////////////////////////////////////////////////
	Voxel* Chunk::getVoxel(const int x, const int y, const int z)
	{
		if (x < SIZE && y < SIZE && z < SIZE)
		{
			return &m_voxels.at((x * SIZE * SIZE) + (y * SIZE) + z);
		}

		return m_pWorld->getVoxel(Vector3i(m_transform.getPosition()) + Vector3i(x, y, z));
	}

	////////////////////////////////////////////////////////////
	MeshData* Chunk::getMesh(void) const
	{
		return m_pMesh;
	}
	////////////////////////////////////////////////////////////
	void Chunk::setWorld(World* pWorld)
	{
		m_pWorld = pWorld;
	}

	/*
	====================
	Private Methods
	====================
	*/
	////////////////////////////////////////////////////////////
	void Chunk::checkNeighbours(const Vector3i& pos)
	{
		if (pos.x > 0)
		{
			m_checks[FACE_WEST] = getVoxel(pos.x - 1, pos.y, pos.z)->isActive() ? false : true;
		}
		else
		{
			m_checks[FACE_WEST] = true;
		}

		if (pos.x < SIZE - 1)
		{
			m_checks[FACE_EAST] = getVoxel(pos.x + 1, pos.y, pos.z)->isActive() ? false : true;
		}
		else
		{
			m_checks[FACE_EAST] = true;
		}

		if (pos.y > 0)
		{
			m_checks[FACE_SOUTH] = getVoxel(pos.x, pos.y - 1, pos.z)->isActive() ? false : true;
		}
		else
		{
			m_checks[FACE_SOUTH] = true;
		}

		if (pos.y < SIZE - 1)
		{
			m_checks[FACE_NORTH] = getVoxel(pos.x, pos.y + 1, pos.z)->isActive() ? false : true;
		}
		else
		{
			m_checks[FACE_NORTH] = true;
		}

		if (pos.z > 0)
		{
			m_checks[FACE_FORWARD] = getVoxel(pos.x, pos.y, pos.z - 1)->isActive() ? false : true;
		}
		else
		{
			m_checks[FACE_FORWARD] = true;
		}

		if (pos.z < SIZE - 1)
		{
			m_checks[FACE_BACKWARD] = getVoxel(pos.x, pos.y, pos.z + 1)->isActive() ? false : true;
		}
		else
		{
			m_checks[FACE_BACKWARD] = true;
		}
	}

	////////////////////////////////////////////////////////////
	void Chunk::addToMesh(const Vector3i& pos)
	{
		Vector3f position(pos);
		const float RENDER_SIZE = 1.0f;

		Vector2f uv0(0.0f, 0.0f);
		Vector2f uv1(1.0f, 0.0f);
		Vector2f uv2(1.0f, 1.0f);
		Vector2f uv3(0.0f, 1.0f);

		if (m_checks[FACE_FORWARD])
		{
			//front face
			Vertex_t v0(Vector3f(position.x,			   position.y,				 position.z), uv0);
			Vertex_t v1(Vector3f(position.x + RENDER_SIZE, position.y,				 position.z), uv1);
			Vertex_t v2(Vector3f(position.x + RENDER_SIZE, position.y + RENDER_SIZE, position.z), uv2);
			Vertex_t v3(Vector3f(position.x,			   position.y + RENDER_SIZE, position.z), uv3);

			m_pMesh->addFace(v0, v1, v2, v3, false);
		}

		if (m_checks[FACE_NORTH])
		{
			Vertex_t v0(Vector3f(position.x,			   position.y + RENDER_SIZE, position.z			     ), uv0);
			Vertex_t v1(Vector3f(position.x + RENDER_SIZE, position.y + RENDER_SIZE, position.z			     ), uv1);
			Vertex_t v2(Vector3f(position.x + RENDER_SIZE, position.y + RENDER_SIZE, position.z + RENDER_SIZE), uv2);
			Vertex_t v3(Vector3f(position.x,			   position.y + RENDER_SIZE, position.z + RENDER_SIZE), uv3);

			m_pMesh->addFace(v0, v1, v2, v3, false);
		}

		if (m_checks[FACE_BACKWARD])
		{
			//back face			
			Vertex_t v0(Vector3f(position.x				 , position.y			   , position.z + RENDER_SIZE), uv0);
			Vertex_t v1(Vector3f(position.x + RENDER_SIZE, position.y			   , position.z + RENDER_SIZE), uv1);
			Vertex_t v2(Vector3f(position.x + RENDER_SIZE, position.y + RENDER_SIZE, position.z + RENDER_SIZE), uv2);
			Vertex_t v3(Vector3f(position.x				 , position.y + RENDER_SIZE, position.z + RENDER_SIZE), uv3);

			m_pMesh->addFace(v0, v1, v2, v3, true);
		}

		if (m_checks[FACE_SOUTH])
		{
			//bottom face
			Vertex_t v0(Vector3f(position.x			     , position.y, position.z + RENDER_SIZE), uv0);
			Vertex_t v1(Vector3f(position.x + RENDER_SIZE, position.y, position.z + RENDER_SIZE), uv1);
			Vertex_t v2(Vector3f(position.x + RENDER_SIZE, position.y, position.z			   ), uv2);
			Vertex_t v3(Vector3f(position.x				 , position.y, position.z			   ), uv3);

			m_pMesh->addFace(v0, v1, v2, v3, false);
		}

		if (m_checks[FACE_WEST])
		{
			//left face
			Vertex_t v0(Vector3f(position.x, position.y				 , position.z + RENDER_SIZE), uv0);
			Vertex_t v1(Vector3f(position.x, position.y				 , position.z			   ), uv1);
			Vertex_t v2(Vector3f(position.x, position.y + RENDER_SIZE, position.z			   ), uv2);
			Vertex_t v3(Vector3f(position.x, position.y + RENDER_SIZE, position.z + RENDER_SIZE), uv3);

			m_pMesh->addFace(v0, v1, v2, v3, false);
		}

		if (m_checks[FACE_EAST])
		{
			//right face
			Vertex_t v0(Vector3f(position.x + RENDER_SIZE, position.y			   , position.z + RENDER_SIZE), uv0);
			Vertex_t v1(Vector3f(position.x + RENDER_SIZE, position.y			   , position.z				 ), uv1);
			Vertex_t v2(Vector3f(position.x + RENDER_SIZE, position.y + RENDER_SIZE, position.z				 ), uv2);
			Vertex_t v3(Vector3f(position.x + RENDER_SIZE, position.y + RENDER_SIZE, position.z + RENDER_SIZE), uv3);

			m_pMesh->addFace(v0, v1, v2, v3, true);
		}
	}

	/*
	====================
	Methods
	====================
	*/
	////////////////////////////////////////////////////////////
	void Chunk::culled(void)
	{
		for (int z = 0; z < SIZE; z++)
		{
			for (int y = 0; y < SIZE; y++)
			{
				for (int x = 0; x < SIZE; x++)
				{
					Vector3i pos(x, y, z);

					if (getVoxel(pos)->isActive())
					{
						checkNeighbours(pos);
						addToMesh(pos);
					}
				}
			}
		}

		std::cout << "Generated." << std::endl;
		m_pMesh->calculateNormals();

		m_shouldLoad = true;
	}

	////////////////////////////////////////////////////////////
	void Chunk::greedy(void)
	{
		const std::array<int, 3> dimensions = { SIZE, SIZE, SIZE };
		int index = 0;

		for (int axis = 0; axis < 3; ++axis)
		{
			const int u = (axis + 1) % 3;
			const int v = (axis + 2) % 3;
			
			std::array<int, 3> x;
			x.fill(0);

			std::array<int, 3> q;
			q.fill(0);

			// The mask of the current side of the voxel chunk to be working on.
			int* mask = new int[dimensions[u] * dimensions[v]];

			q[axis] = 1;

			for (x[axis] = -1; x[axis] < dimensions[axis];)
			{
				int counter = 0;

				for (x[v] = 0; x[v] < dimensions[v]; ++x[v])
				{
					for (x[u] = 0; x[u] < dimensions[u]; ++x[u], ++counter)
					{
						bool a1 = 0 <= x[axis] ? getVoxel(x[0], x[1], x[2])->isActive() : false;
						bool a2 = x[axis] < dimensions[axis] - 1 ? getVoxel(x[0] + q[0], x[1] + q[1], x[2] + q[2])->isActive() : false;

						eVoxelType v1 = 0 <= x[axis] ? getVoxel(x[0], x[1], x[2])->getType() : eVoxelType::DIRT;
						eVoxelType v2 = x[axis] < dimensions[axis] - 1 ? getVoxel(x[0] + q[0], x[1] + q[1], x[2] + q[2])->getType() : eVoxelType::DIRT;

						if (a1 == a2 && v1 == v2)
						{
							mask[counter] = 0;
						}
						else if (a1)
						{
							mask[counter] = static_cast<int>(a1);
						}
						else
						{
							mask[counter] = -1;
						}
					}
				}

				++x[axis];

				int width = 0, height = 0;

				counter = 0;
				for (int j = 0; j < dimensions[v]; ++j)
				{
					for (int i = 0; i < dimensions[u];)
					{
						int c = mask[counter];
						if (c)
						{
							// Calculates the width of the new face. Increments width while less than the dimensions and
							// c equals the mask at the position.
							for (width = 1; c == mask[counter + width] && i + width < dimensions[u]; ++width) {}

							// Calculates the height of the new face
							bool done = false;
							for (height = 1; j + height < dimensions[v]; ++height)
							{
								for (int k = 0; k < width; ++k)
								{
									if (c != mask[counter + k + height * dimensions[u]])
									{
										done = true;
										break;
									}
								}

								if (done)
									break;
							}

							// Add quad
							x[u] = i;
							x[v] = j;

							int du[3] = { 0 }, dv[3] = { 0 };
							bool flip;

							if (c > 0)
							{
								flip = true;
								dv[v] = height;
								du[u] = width;
							}
							else
							{
								flip = false;
								c = -c;
								du[v] = height;
								dv[u] = width;
							}

							Vertex_t v1(Vector3f(Vector3i(x[0],                 x[1],                 x[2])),				  Vector2f(0.0f, 0.0f));
							Vertex_t v2(Vector3f(Vector3i(x[0] + du[0],         x[1] + du[1],         x[2] + du[2])),         Vector2f(1.0f, 0.0f));
							Vertex_t v3(Vector3f(Vector3i(x[0] + du[0] + dv[0], x[1] + du[1] + dv[1], x[2] + du[2] + dv[2])), Vector2f(1.0f, 1.0f));
							Vertex_t v4(Vector3f(Vector3i(x[0] + dv[0],         x[1] + dv[1],         x[2] + dv[2])),		  Vector2f(0.0f, 1.0f));

							m_pMesh->addFace(v1, v2, v3, v4, flip);
							m_pMesh->calculateFaceNormals(index, flip);

							for (int b = 0; b < width; ++b)
							{
								for (int a = 0; a < height; ++a)
								{
									mask[counter + b + a * dimensions[u]] = 0;
								}
							}
							// Increment counters
							i += width; 
							counter += width;
							index += 6;
						}
						else
						{
							++i;
							++counter;
						}
					}
				}
			}

			delete mask;
		}

		std::cout << "Generated" << std::endl;

		if (m_pMesh->getVertexCount() > 0)
		{
			m_isActive = true;
		}

		m_shouldLoad = true;
	}

	////////////////////////////////////////////////////////////
	void Chunk::reset(void)
	{
		m_pMesh->reset();
	}

	////////////////////////////////////////////////////////////
	void Chunk::render(IShaderComponent* pShader)
	{
		if (m_isActive)
		{
			if (m_shouldLoad)
			{
				m_pMesh->generate(false);
				m_shouldLoad = false;
			}

			if (Frustum::checkCube(m_transform.getPosition(), static_cast<float>(Chunk::SIZE)))
			{
				pShader->update(m_transform);
				m_pMesh->render();
			}
		}
	}

}//namespace sparky