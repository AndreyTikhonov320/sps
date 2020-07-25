#pragma once
namespace OS {
	class OS
	{
	public:
		virtual ~OS() {}
		virtual void sleep(uint32_t ms) = 0;
	};

	class WindowsOS : public OS
	{
	public:
		virtual ~WindowsOS();
		static WindowsOS* instance();
		virtual void sleep(uint32_t ms);
	private:
		WindowsOS();
	};
};
