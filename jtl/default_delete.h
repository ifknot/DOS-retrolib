/**
 *
 *  @file      default_delete.h
 *  @brief     A stateless functor that simply uses the global delete for the operation, with class causing no additional overhead overall over a built-in pointer.
 *  @details   Function object class, whose function-like invokation takes an object of type T* and deletes it.
 *  The non-specialized version simply uses delete for the deletion operation.
 *  Likewise, the specialization for arrays with runtime length uses delete[].
 *  @see https://www.cplusplus.com/reference/memory/default_delete/
 *  @author    Jeremy Thornton
 *  @date      13.02.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef DEFAULT_DELETE_H
#define DEFAULT_DELETE_H

namespace jtl {

    /**
     *  @struct default_delete functor
     *  @brief  Default deleter
     *  @tparam T The type of object to be deleted.
     */
    template<typename T>
    struct default_delete {
        
        typedef T element_type;
        typedef T* pointer;

        inline void operator()(pointer ptr) const { delete ptr; }

    };

    /**
     *  @struct default_delete functor
     *  @brief  specialisation for array types
     *  @tparam T The type of object to be deleted.
     */
    template <typename T>
    struct default_delete<T[]> {

        typedef T element_type;
        typedef T* pointer;

        inline void operator()(T* ptr) const { delete[] ptr; }

    };

}

#endif