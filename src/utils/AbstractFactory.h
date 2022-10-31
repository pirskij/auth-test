#pragma once
#include <assert.h>
#include <functional>
#include <map>
#include <memory>
#include <string>

namespace sol::utils
{
	template<typename T, typename D>
	T* objCreator()
	{
		return static_cast<T*>(new (std::nothrow) D());
	}

	template <typename T, typename Base, typename Pointer, typename Tag = void>
	struct SmartCreator;


	template <typename T, typename Base, typename Pointer>
	struct SmartCreator<T, Base, Pointer, typename std::enable_if<std::is_pointer<Pointer>::value, void>::type>
	{
		Pointer operator()() { return new (std::nothrow) T(); };
	};

	template <typename T, typename Base, typename Pointer>
	struct SmartCreator<T, Base, Pointer, typename std::enable_if<std::is_same<Pointer, std::shared_ptr<Base>>::value>::type>
	{
		//template<typename T, typename Pointer>
		Pointer operator()() { return std::make_shared<T>(); };
	};
	
	template<typename T, typename Pointer, typename TKEY = std::string>
	class AbstractFactory
	{
	public:

		using TCreateFunc = std::function<Pointer(void)>;
		using key_type = TKEY;

		virtual ~AbstractFactory() = default;

		template<typename ProductType>
		void lazyAddCreator(const TKEY& key)
		{
			auto itr = m_creators.find(key);
			if (itr != m_creators.end())
				assert(false);
			
			m_creators[key] = SmartCreator<ProductType, T, Pointer>();
		}

		template<typename D>
		void addCreator(const TKEY& key)
		{
			addCreator(key, getCreatorPtr<D>());
		}

		void addCreator(const TKEY& key, TCreateFunc const& creatorFn)
		{
			auto itr = m_creators.find(key);
			if (itr != m_creators.end())
				assert(false);

			m_creators[key] = creatorFn;
		}

		void removeCreator(const TKEY& key)
		{
			auto itr = m_creators.find(key);
			if (itr != m_creators.end())
				m_creators.erase(itr);
		}

		void clearCreators()
		{
			m_creators.clear();
		}

		Pointer createObject(const TKEY& key)
		{
			auto itr = m_creators.find(key);
		
			if (itr == m_creators.end())
				return nullptr;

			return itr->second();
		}
		
		std::shared_ptr<T> createObjectPtr(const TKEY& key)
		{
			return std::shared_ptr<T>(createObject(key));
		}

		template <typename D>
		TCreateFunc getCreatorPtr()
		{
			return &objCreator<T, D>;
		}

		virtual void fillCreators() = 0;

	protected:
		std::map<TKEY, TCreateFunc> m_creators;
	};

	template<typename T, typename D, typename ARG_T>
	T* objCreatorArg(ARG_T const& arg)
	{
		return static_cast<T*>(new (std::nothrow) D(arg));
	}

	template<typename T, typename ARG_T, typename TKEY = std::string>
	class AbstractFactoryWithArgs
	{
	public:
		using TCreateFunc = std::function<T*(ARG_T const&)>;
		using key_type = TKEY;

		virtual ~AbstractFactoryWithArgs() = default;

		template<typename D>
		void addCreator(const TKEY& key)
		{
			addCreator(key, getCreatorPtr<D>());
		}

		void addCreator(const TKEY& key, TCreateFunc const& creatorFn)
		{
			auto itr = m_creators.find(key);
			if (itr != m_creators.end())
				assert(false);

			m_creators[key] = creatorFn;
		}

		void removeCreator(const TKEY& key)
		{
			auto itr = m_creators.find(key);
			if (itr != m_creators.end())
				m_creators.erase(itr);
		}

		void clearCreators()
		{
			m_creators.clear();
		}

		T* createObject(const TKEY& key, ARG_T const& arg)
		{
			auto itr = m_creators.find(key);
			if (itr == m_creators.end())
				return nullptr;

			return itr->second(arg);
		}

		std::shared_ptr<T> createObjectPtr(const TKEY& key, ARG_T const& arg)
		{
			return std::shared_ptr<T>(createObject(key, arg));
		}

		template <typename D>
		TCreateFunc getCreatorPtr()
		{
			return &objCreatorArg<T, D, ARG_T>;
		}

		virtual void fillCreators() = 0;

	protected:
		std::map<TKEY, TCreateFunc> m_creators;
	};
} // namespace sol::utils
