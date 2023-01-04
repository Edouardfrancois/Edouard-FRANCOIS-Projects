/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre.tran [WSL : Ubuntu-20.04]
** File description:
** convert_function
*/

#ifndef CONVERT_FUNCTION_HPP_
#define CONVERT_FUNCTION_HPP_

#include <functional>

namespace utils {
    /**
     * @brief convert any function to void(), 
     * input the name of the function
     * along with the arguments
     * 
     * @tparam function_type 
     * @tparam Params 
     * @param f 
     * @param tp 
     * @return std::function<void()> 
     */
    template<typename Fun_type, class... Params>
    std::function<void()> convert_function(Fun_type f, Params&&...tp)
    {
        return std::function<void()>([&, f] {
            f(std::forward<Params>(tp)...);
        });
    }
}

#endif /* !CONVERT_FUNCTION_HPP_ */
