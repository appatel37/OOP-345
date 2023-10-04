#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H

#include <iostream>
#include "Book.h"

namespace sdds
{

	template <typename T, const unsigned C>
	class Collection
	{
		const unsigned m_capacity = C;
		unsigned m_size{};
		T m_items[C]{};
		static T m_smallestItem;
		static T m_largestItem;
	protected:
		
		void setSmallestItem(const T& item) 
		{
			if (m_smallestItem > item)
			{
				m_smallestItem = item;
			}
		}
	
		void setLargestItem(const T& item) 
		{
			if (m_largestItem < item)
			{
				m_largestItem = item;
			}
		}
	public:
		
		Collection() = default;
		
		Collection(const Collection&) = delete;
		
		static T getSmallestItem()
		{
			return m_smallestItem;
		}
		
		static T getLargestItem() 
		{
			return m_largestItem;
		}
	
		unsigned size() const
		{
			return m_size;
		}
		
		unsigned capacity() const
		{
			return m_capacity;

		}
		
		operator bool() const
		{
			return m_size;
		}
		
		bool operator+=(const T& ro)
		{
			if (m_size < m_capacity)
			{
				setSmallestItem(ro);
				setLargestItem(ro);
				m_items[m_size] = ro;
				m_size++;
				return true;
			}
			else
			{
				return false;
			}
		}

		void print(std::ostream& out) const
		{
			if (*this)
			{
			
				out << '[';
				for (size_t i = 0u; i < m_size; i++)
				{
					out << m_items[i] << ((i == (m_size - 1)) ? ']' : ',');
				}
				out << std::endl;
			}
		}
	};

	template <typename T,const unsigned C>
	T Collection<T,C>::m_smallestItem = 9999;
	template <typename T,const unsigned C>
	T Collection<T,C>::m_largestItem = -9999;

	
	template <>
	Book Collection<Book,10>::m_smallestItem("",1,1000);
	template <>
	Book Collection<Book, 10>::m_largestItem("", 10000, 1);


}

#endif 
