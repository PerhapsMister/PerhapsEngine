#ifndef PERHAPS_EVENT_SYSTEM
#define PERHAPS_EVENT_SYSTEM
#include "../../PerhapsPch.h"

namespace Perhaps
{


	class Event
	{
	public:
		typedef const char* DescriptorType;

		virtual DescriptorType GetType() const = 0;
	};

	class EventDispatcher
	{
	public:
		typedef std::function<void(const Event&)> SlotType;

		class StoredFunction
		{
		public:

			int id = -1;
			Event::DescriptorType descriptor = nullptr;
			EventDispatcher::SlotType slot;
		};

		/// <summary>
		/// Subscribe to a certain type of event.
		/// </summary>
		/// <param name="descriptor"></param>
		/// <param name="function"></param>
		/// <returns>event listen ID</returns>
		static int Subscribe(Event::DescriptorType descriptor, SlotType&& function)
		{
			int id = ++idReel;
			StoredFunction* f = new StoredFunction();
			f->descriptor = descriptor;
			f->slot = function;
			f->id = id;

			observers[descriptor].push_back(f);
			idToFun.insert(std::make_pair(id, f));

			return id;
		}


		static void UnSubscribe(int id)
		{
			if (idToFun.find(id) == idToFun.end())
			{
				return;
			}

			StoredFunction* e = idToFun.at(id);
			auto& vector = observers[e->descriptor];
			SlotType* slot = &e->slot;

			for (size_t i = 0; i < vector.size(); i++)
			{
				SlotType* currnet = &vector[i]->slot;

				if (currnet == slot)
				{
					vector.erase(vector.begin() + i);
					idToFun.erase(id);
					delete(e);
					return;
				}
			}
		}


		static void DispatchEvent(const Event& event)
		{
			Event::DescriptorType type = event.GetType();

			if (observers.find(type) == observers.end())
			{
				return;
			}

			auto&& observerList = observers.at(type);

			for (size_t i = 0; i < observerList.size(); i++)
			{
				auto e = observerList[i]->slot;
				if (&e == nullptr)
				{
					observerList.erase(observerList.begin() + i);
					i--;
				}
				else
				{
					std::invoke(observerList[i]->slot, event);
				}
			}
		}

	private:
		static std::map<Event::DescriptorType, std::vector<StoredFunction*>> observers;
		static std::map<int, StoredFunction*> idToFun;
		static int idReel;
	};

}
#endif