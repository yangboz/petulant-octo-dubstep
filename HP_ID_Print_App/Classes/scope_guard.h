#ifndef _SCOPE_GUARD_H_
#define _SCOPE_GUARD_H_

#include <functional>

// One shall use ON_SCOPE_EXIT() macro to create a anonymous ScopeGuard object.
// The anonymous function "callback" will be automatically called in the 
// deconstractor when the object is out of the scope.

// Usage:
//   ON_SCOPE_EXIT([&]{ CloseHandle(hFile);});
//   ON_SCOPE_EXIT([&p]{ delete p;});

namespace utility
{

	class ScopeGuard
	{
	public:
		ScopeGuard(std::function<void()> callback)
			:callback_(callback), dismissed_(false)
		{  }

		~ScopeGuard()
		{
			if (!dismissed_)
			{
				callback_();
			}
		}

		void Dismiss()
		{
			dismissed_ = true;
		}

		// Non-copyable. Disable copy constructor and assignment operator.
		ScopeGuard(const ScopeGuard&) = delete;
		ScopeGuard& operator=(const ScopeGuard&) = delete;

	private:
		std::function<void()> callback_;
		bool dismissed_;
	};

} // namespace utility

#define  SCOPE_GUARD_NAME_CANT(line)        _scope_guard_##line
#define  MAKE_SCOPE_GUARD(callback, line)   utility::ScopeGuard SCOPE_GUARD_NAME_CANT(line)(callback)

#define  ON_SCOPE_EXIT(callback)            MAKE_SCOPE_GUARD(callback, __LINE__)

#endif