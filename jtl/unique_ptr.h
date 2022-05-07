/**
 *
 *  @file      unique_ptr.h
 *  @brief     Manages the storage of a pointer, providing a limited garbage-collection facility.
 *  @details	unique_ptr objects automatically delete the object they manage (using a deleter) 
 *				as soon as they themselves are destroyed, or as soon as their value changes either 
 *				by an assignment operation or by an explicit call to unique_ptr::reset.
 *  @see https://www.cplusplus.com/reference/memory/unique_ptr/  
 *  @author    Jeremy Thornton
 *  @date      15.01.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H


#include "macro_cpp11.h"
#include "null_ptr_t.h"
#include "default_delete.h"

namespace jtl {

    /**
     *
     *  @class   unique_ptr
     *  @brief   Manages the storage of a pointer
     *  @details ~Providing a limited garbage-collection facility, with little to no overhead over built-in pointers (depending on the deleter used).
     *  @tparam  T The type of the managed object, aliased as member type element_type.
     *  @tparam  D Type of the callable object used as deleter, aliased as member type deleter_type.
     *  By default, this is default_delete, which is a stateless functor that simply uses the global delete for the operation, with class causing no additional overhead overall over a built-in pointer.
     */
    template <typename T, typename D = default_delete<T> >
    class unique_ptr {

    public:

        typedef T element_type;
        typedef D deleter_type;
        typedef T* pointer;

        unique_ptr() noexcept : p_(static_cast<T*>(0))  {}

        unique_ptr(nullptr_t) noexcept : p_(static_cast<T*>(0)) {}

        explicit unique_ptr(pointer p) noexcept : p_(p) {}

        unique_ptr(pointer p, const D& del) noexcept : p_(p), stored_deleter(del) {}

        ~unique_ptr() { stored_deleter(p_); }

        unique_ptr& operator=(nullptr_t) noexcept {
            reset();
            return *this;
        }

        inline pointer get() const noexcept { return p_; }

        deleter_type& get_deleter() noexcept { return stored_deleter; }

        const deleter_type& get_deleter() const noexcept { return stored_deleter; }

        operator bool() const noexcept {
           return get() != 0;
        }

        pointer release() noexcept {
            pointer p = get();
            p_ = pointer();
            return p;
        }

        inline void reset(pointer p = pointer(0)) {
            stored_deleter(p_);
            p_ = p;
        }

        void swap(unique_ptr& u) noexcept {
            pointer ptemp = p_;
            p_ = u.p_;
            u.p_ = ptemp;
            deleter_type dtemp = stored_deleter;
            stored_deleter = u.stored_deleter;
            u.stored_deleter = dtemp;
        }

        inline element_type& operator*() const noexcept { return *p_; }

        inline pointer operator->() const noexcept { return p_; }

    private:

        pointer p_;
        deleter_type stored_deleter;

        unique_ptr(unique_ptr<T, D>&);              
        unique_ptr& operator=(unique_ptr<T, D>&);

    };

    /**
     *
     *  @class   unique_ptr 
     *  @brief    specialized for arrays with runtime length
     *  @details ~
     *  @tparam  T The type of the managed object, aliased as member type element_type.
     *  @tparam  D Type of the callable object used as deleter, aliased as member type deleter_type.
     *  Stateless functor that simply uses the global array delete for the operation, with class causing no additional overhead overall over a built-in pointer.
     */
    template <typename T, typename D>
    class unique_ptr<T[], D> {

    public:

        typedef T element_type;
        typedef D deleter_type;
        typedef T* pointer;

        unique_ptr() noexcept : p_(static_cast<T*>(0)) {}

        unique_ptr(nullptr_t) noexcept : p_(static_cast<T*>(0)) {}

        explicit unique_ptr(pointer p) noexcept : p_(p) {}

        unique_ptr(pointer p, const D& del) noexcept : p_(p), stored_deleter(del) {}

        ~unique_ptr() { stored_deleter(p_); }

        unique_ptr& operator=(nullptr_t) noexcept {
            reset();
            return *this;
        }

        inline pointer get() const noexcept { return p_; }

        deleter_type& get_deleter() noexcept { return stored_deleter; }

        const deleter_type& get_deleter() const noexcept { return stored_deleter; }

        operator bool() const noexcept {
            return get() != 0;
        }

        pointer release() noexcept {
            pointer p = get();
            p_ = pointer();
            return p;
        }

        inline void reset(pointer p = pointer()) {
            pointer q = p;
            p_ = p;
            stored_deleter(q);  // delete must be last to avoid nasty little bugs with DOS
        }

        void swap(unique_ptr& u) noexcept {
            pointer q = p_;
            p_ = u.p_;
            u.p_ = q;
            deleter_type d = stored_deleter;
            stored_deleter = u.stored_deleter;
            u.stored_deleter = d;
        }

        element_type& operator[](int i) const {
            i *= sizeof(element_type);
            return *(p_ + i);
        }

    private:

        pointer p_;
        deleter_type stored_deleter;

        unique_ptr(unique_ptr<T, D>&);             
        unique_ptr& operator=(unique_ptr<T, D>&);

    };

    /**
     *  @brief  specializes the std::swap algorithm
     *  @tparam T The type of the managed object, aliased as member type element_type.
     *  @tparam D Type of the callable object used as deleter, aliased as member type deleter_type.
     *  By default, this is default_delete, which is a stateless functor that simply uses the 
     *  global delete for the operation, with class causing no additional overhead overall over a built-in pointer.
     *  @param  a smart pointers whose contents to swap
     *  @param  b 
     */
    template< class T, class D >
    void swap(unique_ptr<T, D>& a, unique_ptr<T, D>& b) noexcept {
        a.swap(b);
    }

    template <class T1, class D1, class T2, class D2>
    inline bool operator== (const unique_ptr<T1, D1>& lhs, const unique_ptr<T2, D2>& rhs) {
        return lhs.get() == rhs.get();
    }

}

#endif