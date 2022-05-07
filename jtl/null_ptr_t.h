/**
 *
 *  @file      null_ptr_t.h
 *  @brief     nice approximation of std::nullptr_t, but it is nothing more than that.
 *  @see         https://gist.github.com/mooware/5392031
 *  @see         https://stackoverflow.com/questions/61283569/how-does-c-nullptr-implementation-work 
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      13.02.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef NULL_PTR_T_H 
#define NULL_PTR_T_H

namespace jtl {

	struct nullptr_t {

		template <typename T>
		operator T* () const { return static_cast<T*>(0); }

		template <class T, class U>
		operator T U::* () const { return static_cast<T*>(0); }

		friend  inline bool operator==(nullptr_t, nullptr_t) { return true; }

		friend  inline bool operator!=(nullptr_t, nullptr_t) { return false; }

	};

}

jtl::nullptr_t nullptr;

#endif
