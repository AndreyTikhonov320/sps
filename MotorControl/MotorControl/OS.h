#pragma once
namespace OS {
	class OS
	{
	public:
		virtual ~OS() {}
		virtual void sleep(uint32_t ms) = 0;
		virtual void enter_critical_section() = 0;
		virtual void leave_critical_section() = 0;
	};

	class WindowsOS : public OS
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
