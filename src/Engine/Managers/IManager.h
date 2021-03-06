#pragma once

namespace Engine
{
	class Application;

	class IManager
	{
	public:
		IManager() = default;
		virtual ~IManager() = default;

		bool IsInitialized() { return m_initialized; }

		void OnInit()
		{
			VirtualOnInit(); // calls virtual function
			m_initialized = true;

		};
		void OnDestroy()
		{
			VirtualOnDestroy(); // calls virtual function
			m_initialized = false;
		};
	private:

		virtual void VirtualOnInit() { /* NO IMPLEMENTATION IN BASE CLASS */ };
		virtual void VirtualOnDestroy() { /* NO IMPLEMENTATION IN BASE CLASS */ };
		bool m_initialized = false;

	friend class Application; // only application should be able to init/destroy managers
	};
};