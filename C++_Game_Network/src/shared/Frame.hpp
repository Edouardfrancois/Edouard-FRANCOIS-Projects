/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-pierre.tran
** File description:
** Frame
*/

#ifndef FRAME_HPP_
#define FRAME_HPP_

class Frame {
    public:
        Frame() {
            this->_nb = 0;
        }
        ~Frame() {};

        /**
         * @brief add 1 to the frame
         * 
         */
        void Increment() {
            this->_nb += 1;
        };

        /**
         * @brief reset the frame
         * 
         */
        void Reset() {
            this->_nb = 0;
        }

        /**
         * @brief get the frame
         * 
         * @return the value of frame
         */
        int Get() {
            return this->_nb;
        }
    protected:
    private:
        int _nb;
};

#endif /* !FRAME_HPP_ */