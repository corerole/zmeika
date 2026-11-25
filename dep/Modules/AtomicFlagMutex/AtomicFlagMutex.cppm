module;

export module AtomicFlagMutex;
import std;

export struct AtomicFlagMutex {
	private:
		std::atomic_flag flag{};

	public:
		void lock() { while (flag.test_and_set(std::memory_order_acquire)) { std::this_thread::yield(); } }
		bool try_lock() { return !flag.test_and_set(std::memory_order_acquire); }
		void unlock() { flag.clear(std::memory_order_release); }
};
