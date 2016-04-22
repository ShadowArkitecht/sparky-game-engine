#include <sparky\generation\voxel.hpp>

namespace sparky
{
	Voxel::Voxel(void)
		: m_active(true)
	{
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