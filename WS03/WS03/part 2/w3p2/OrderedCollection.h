#ifndef SDDS_ORDERED_COLLECTION_H
#define SDDS_ORDERED_COLLECTION_H

#include "Collection.h"

namespace sdds
{
	template <typename T>
	class OrderedCollection : public Collection<T, 72u>
	{
	public:
		OrderedCollection() : Collection<T, 72u>() {};

		OrderedCollection(const OrderedCollection& oc) = delete;

		~OrderedCollection() = default;
	
		bool operator+=(const T& ro)
		{
			if (this->size() < this->capacity())
			{
				this->incrSize();
				
				if (ro > this->getLargestItem())
				{
					this->operator[](this->size()-1) = ro;
					this->setLargestItem(ro);
				}
				else
				{
					unsigned int targetIndex = 0u;
					bool foundTarget = false;
					for (unsigned i = 0u; i < this->size() && !foundTarget; i++)
					{
						if (this->operator[](i) > ro)
						{
							targetIndex = i;
							foundTarget = true;
						}
					}
					for (unsigned i = (this->size() - 1); i > targetIndex; i--)
					{
						this->operator[](i) = this->operator[](i - 1);
					}
					this->operator[](targetIndex) = ro;
					
				}
				this->setSmallestItem(ro);
				return true;
			}
			else
			{
				return false;
			}
		}
	};
}

#endif
