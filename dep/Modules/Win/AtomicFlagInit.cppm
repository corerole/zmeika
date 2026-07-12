module;

#include <atomic>

export module AtomicFlagInit;

#if 0

auto atomic_flag_init = ATOMIC_FLAG_INIT;
#undef ATOMIC_FLAG_INIT
export auto ATOMIC_FLAG_INIT = std::move(atomic_flag_init);

#endif