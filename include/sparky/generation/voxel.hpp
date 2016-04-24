#ifndef __SPARKY_VOXEL_HPP__
#define __SPARKY_VOXEL_HPP__

namespace sparky
{
	enum class eVoxelType
	{
		DIRT,
		STONE
	};

	class Voxel
	{
	private:
		eVoxelType m_type;
		bool	   m_active;

	public:
		explicit Voxel(void);
		~Voxel(void) = default;

		eVoxelType getType(void) const;
		void setType(const eVoxelType type);

		bool isActive(void) const;
		void setActive(const bool active);
	};

}//namespace sparky

#endif//__SPARKY_VOXEL_HPP__