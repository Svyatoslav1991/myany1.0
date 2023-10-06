#pragma once
#include <typeinfo>
#include <memory>
#include <stdexcept>

class MyAny
{
public:
	MyAny() noexcept;
	~MyAny() = default;

	MyAny(const MyAny& other) noexcept;
	MyAny(MyAny&& other) noexcept;

	MyAny& operator=(const MyAny& other) noexcept;
	MyAny& operator=(MyAny&& other) noexcept;

	template <typename T>
	MyAny(const T& value) noexcept;

	//retrieving data with type checking
	template<typename T>
	T cast() const;


	template <typename T>
	bool isType() const noexcept;

private:
	//class for storing data of various types
	struct BaseHolder
	{
		virtual ~BaseHolder() {};
		virtual const type_info& type() const = 0;
	};

	//data storage class of a given type
	template <typename T>
	struct Holder : public BaseHolder
	{
		Holder(const T& value) noexcept;

		//overridden method that returns data type information
		virtual const type_info& type() const noexcept override;

		T m_value;
	};


	std::shared_ptr<BaseHolder> m_pData;
};


/////////////////////////////////////////////////////////////////////////////////////////////////////


MyAny::MyAny() noexcept : m_pData(nullptr)
{
}

//-----------------------------------------------------------------------

inline MyAny::MyAny(const MyAny& other) noexcept
{
	if (other.m_pData)
	{
		m_pData = other.m_pData;
	}
	else
	{
		m_pData = nullptr;
	}
}

//-----------------------------------------------------------------------

inline MyAny& MyAny::operator=(const MyAny& other) noexcept
{
	if (this != &other)
	{
		if (other.m_pData)
		{
			m_pData = other.m_pData;
		}
		else
		{
			m_pData = nullptr;
		}
	}

	return *this;
}

//-----------------------------------------------------------------------

inline MyAny& MyAny::operator=(MyAny&& other) noexcept
{
	if (this != &other)
	{
		m_pData = nullptr;

		m_pData = other.m_pData;

		other.m_pData = nullptr;
	}

	return *this;
}

//-----------------------------------------------------------------------

inline MyAny::MyAny(MyAny&& other) noexcept : m_pData(std::move(other.m_pData))
{
	other.m_pData = nullptr;
}

//-----------------------------------------------------------------------

template<typename T>
inline MyAny::MyAny(const T& value) noexcept : m_pData(std::make_shared<Holder<T>>(value))
{
}

//-----------------------------------------------------------------------

template<typename T>
inline T MyAny::cast() const
{
	if (!m_pData)
	{
		throw std::bad_cast();
	}
	else if (m_pData->type() != typeid(T))
	{
		throw std::bad_cast();
	}
	
	return static_cast<Holder<T>*>(m_pData.get())->m_value;
}

//-----------------------------------------------------------------------

template<typename T>
inline bool MyAny::isType() const noexcept
{
	if (!m_pData)
	{
		return false;
	}

	return m_pData->type() == typeid(T);
}

//-----------------------------------------------------------------------

template<typename T>
inline MyAny::Holder<T>::Holder(const T& value) noexcept : m_value (value)
{

}

//-----------------------------------------------------------------------

template<typename T>
inline const type_info& MyAny::Holder<T>::type() const noexcept
{
	return typeid(T);
}
