#ifndef __SPARKY_VOXEL_HPP__
#define __SPARKY_VOXEL_HPP__

namespace sparky
{
	class Voxel
	{
	private:
		bool m_active;

	public:
		explicit Voxel(void);
		~Voxel(void) = default;

		bool isActive(void) const;
		void setActive(const bool active);
	};

}//namespace sparky

#endif//__SPARKY_VOXEL_HPP__