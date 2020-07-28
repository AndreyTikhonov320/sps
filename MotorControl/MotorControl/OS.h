#pragma once
namespace OS {
	class IOS
	{
	public:
		virtual ~IOS() {}
		virtual void sleep(uint32_t ms) = 0;
		virtual void enter_critical_section() = 0;
		virtual void leave_critical_section() = 0;
	};

	class WindowsOS : public IOS
	{
	public:
		virtual ~WindowsOS();
		static WindowsOS* instance();
		virtual void sleep(uint32_t ms);
	private:
		WindowsOS();
	public:
		virtual void enter_critical_section();
		virtual void leave_critical_section();
	};
};
