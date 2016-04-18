////////////////////////////////////////////////////////////
template <typename T>
ResourceHolder<T>::ResourceHolder(void)
	: m_resources()
{
}

////////////////////////////////////////////////////////////
template <typename T>
ResourceHolder<T>::~ResourceHolder(void)
{
	for (auto& r : m_resources)
	{
		//Ref::release(r->second);
	}

	m_resources.clear();
}

////////////////////////////////////////////////////////////
template <typename T>
T* ResourceHolder<T>::get(const String& name) const
{
	auto itr = m_resources.find(name);

	if (itr != m_resources.end())
	{
		return itr->second;
	}

	DebugLog::warning(name, "was not a stored resource.");
	return nullptr;
}

////////////////////////////////////////////////////////////
template <typename T>
void ResourceHolder<T>::add(const String& name, T* pResource)
{
	auto itr = m_resources.find(name);

	if (itr != m_resources.end())
	{
		DebugLog::warning(name, "is already a resource in this list.");
		return;
	}

	pResource->addRef();
	m_resources.insert(std::make_pair(name, pResource));
}

////////////////////////////////////////////////////////////
template <typename T>
template <typename... Args>
void ResourceHolder<T>::add(const String& name, Args&&... args)
{
	auto itr = m_resources.find(name);

	if (itr != m_resources.end())
	{
		DebugLog::warning(name, "is already a resource in this list.");
		return;
	}


	T* pResource = new T(std::forward<Args>(args)...);
	pResource->addRef();

	m_resources.insert(std::make_pair(name, pResource));
}

////////////////////////////////////////////////////////////
template <typename T>
void ResourceHolder<T>::remove(const String& name)
{
	auto itr = m_resources.find(name);

	if (itr != m_resources.end())
	{
		m_resources.erase(itr);
		Ref::release(itr->second);
	}

	DebugLog::warning(name, "was not a stored resource, so is not removed.");
}