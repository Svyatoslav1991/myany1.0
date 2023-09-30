#pragma once
#include <typeinfo>
#include <memory>
#include <stdexcept>

class MyAny
{
public:
	MyAny();
	~MyAny() = default;

	template <typename T>
	MyAny(const T& value);

	//retrieving data with type checking
	template<typename T>
	T cast() const;


	template <typename T>
	bool isType() const;

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
		Holder(const T& value);

		//overridden method that returns data type information
		virtual const type_info& type() const override;

		T m_value;
	};


	std::shared_ptr<BaseHolder> m_pData;
};


/////////////////////////////////////////////////////////////////////////////////////////////////////


MyAny::MyAny() : m_pData(nullptr)
{
}

//-----------------------------------------------------------------------

template<typename T>
inline MyAny::MyAny(const T& value) : m_pData(std::make_shared<Holder<T>>(value))
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
inline bool MyAny::isType() const
{
	if (!m_pData)
	{
		return false;
	}

	return m_pData->type() == typeid(T);
}

//-----------------------------------------------------------------------

template<typename T>
inline MyAny::Holder<T>::Holder(const T& value) : m_value (value)
{

}

//-----------------------------------------------------------------------

template<typename T>
inline const type_info& MyAny::Holder<T>::type() const
{
	return typeid(T);
}
