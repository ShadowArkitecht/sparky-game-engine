#include <sparky\generation\voxel.hpp>

namespace sparky
{
	Voxel::Voxel(void)
		: m_active(true), m_type(eVoxelType::DIRT)
	{
	}

	eVoxelType Voxel::getType(void) const
	{
		return m_type;
	}

	void Voxel::setType(const eVoxelType type)
	{
		m_type = type;
	}

	bool Voxel::isActive(void) const
	{
		return m_active;
	}

	void Voxel::setActive(const bool active)
	{
		m_active = active;
	}

}//namespace sparky