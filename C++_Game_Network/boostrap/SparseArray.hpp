/*
** EPITECH PROJECT, 2022
** boostrap
** File description:
** SparseArray
*/


#ifndef SPARSEARRAY_HPP_
#define SPARSEARRAY_HPP_

#include <vector>
#include <optional>

template <typename Component>
class sparse_array {
    public :
        using value_type = std::optional<Component>; // optional component type
        using reference_type = value_type &;
        using const_reference_type = value_type const &;
        using container_t = std::vector<value_type>; // optionally add your allocatortemplate here .
        using size_type = typename container_t::size_type;
        using iterator = typename container_t::iterator;
        using const_iterator = typename container_t::const_iterator;


    public :
        sparse_array () {} // You can add more constructors .
        
        sparse_array(sparse_array const &model) {
            this->_data = model._data;
        } // copy constructor
        sparse_array(sparse_array &&model) noexcept {
            this->_data = model._data;
        } // move constructor
        ~sparse_array() {};

        sparse_array & operator=(sparse_array const &); // copy assignment operator
        sparse_array & operator=(sparse_array &&) noexcept; // move assignment operator

        reference_type operator[](size_t idx) {
            return _data[idx];
        }
        const_reference_type operator[]( size_t idx) const {
            return _data[idx];
        }
    
        iterator begin() {
            return _data.begin();
        }
        const_iterator begin() const {
            return _data.begin();
        }
        const_iterator cbegin() const {
            return _data.cbegin();
        }
    
        iterator end() {
            return _data.end();
        }
        const_iterator end() const {
            return _data.end();
        }
        const_iterator cend() const {
            return _data.cend();
        }
    
        size_type size() const
        {
            return this->_data.size();
        }

        Component at(size_t ite) {
            return this->_data.at(ite).value();
        }
    
        reference_type insert_at(size_type pos, Component const &new_component) {
            if (_data.size() <= pos) {
                _data.resize(pos + 1);
                _data[pos] = new_component;
            }
            else {
                _data[pos] = new_component;
            }
            return _data[pos];
        }

        reference_type insert_at(size_type pos, Component &&new_component) {
            if (_data.size() > pos)
                _data[pos] = new_component;
            else {
                _data.resize(pos + 1);
                _data[pos] = new_component;
            }
            return _data[pos];
        }

        template <class ... Params>
        reference_type emplace_at( size_type pos , Params &&...arg) { // optional
            // container_t argv = {arg...};
            std::allocator<Component> alloc;

            if (_data.size() <= pos)
                _data.resize(pos + 1);
            else {
                std::allocator_traits<decltype(alloc)>::destroy
                (alloc, std::addressof(this->_data.at(pos)));
            }
            std::allocator_traits<decltype(alloc)>::construct
            (alloc, std::addressof(this->_data.at(pos)), std::forward<Params>(arg)...);
            return _data[pos];
        }

        void erase(size_type pos) 
        {
            if  (pos < _data.size()) {
                _data[pos] = std::nullopt;
            }
            // _data.erase(_data.begin() + pos);
        }

        size_type get_index(value_type const &elem) const
        {
            int i = 0;

            for (i = 0; i < _data.size(); i++) {
                if (_data[i] == elem)
                    return i;
            }
            return 42;
        }
        
        void display() const {
            std::cout << "{ ";
            for (auto const &v : _data) {
                std::cout << v << " ";
            }
            std::cout << "}" << std::endl;
        }

    private:
        container_t _data;
};

#endif /* !SPARSEARRAY_HPP_ */
