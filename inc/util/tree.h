#pragma once

#include <functional>
#include <list>

template <typename T>
class Tree {
protected:
    T *_parent = nullptr;
    std::list<T *> _children;
    std::list<T *> _children_reversed;
public:
    /**
     * getter for the list of children
     *
     * @param reversed
     *   flag to determine if the list should be returned reversed
     * @returns
     *   list of children
     */
    std::list<T *> children(bool reversed = false) {
        return reversed ? this->_children_reversed : this->_children;
    }

    /**
     * apply a function recursively to this and all children
     *
     * @param f
     *   function to apply
     * @param reversed
     *   flag to determine the order of child processing. If true, the list of childs get
     *   reversed before applying f
     */
    virtual void map(T *begin, std::function<void (T *)> f, bool reversed = false) {
        f(begin);
        for (T *child: this->children(reversed)) {
            child->map(child, f);
        }
    }

    /**
     * apply a function recursively to this and all children from bottom to top of the tree
     *
     * @param f
     *   function to apply
     * @param reversed
     *   flag to determine the order of child processing. If true, the list of childs get
     *   reversed before applying f
     */
    virtual void bottom_up_map(T *begin, std::function<void (T *)> f, bool reversed = false) {
        for (T *child: this->children(reversed)) {
            child->map(child, f);
        }
        f(begin);
    }

    /**
     * apply a function recursively to this and all children propagating a value
     *
     * @param f
     *   function to apply
     * @param value
     *   initial value
     * @param reversed
     *   flag to determine the order of child processing. If true, the list of childs get
     *   reversed before applying f
     */
    template<typename R>
    void reduce(std::function<R (T *, R)> f, R value, bool reversed = false) {
        R this_value = f(this, value);
        for (T *child: this->children(reversed)) {
            child->reduce(f, this_value);
        }
    }

    /**
     * apply a function recursively reversed, from bottom to top of the tree aggregating the return value
     *
     * @param f
     *   function to apply
     * @param value
     *   initial value
     * @param aggregate
     *   function to aggregate return values from all children
     * @param reversed
     *   flag to determine the order of child processing. If true, the list of childs get
     *   reversed before applying f
     * @returns
     *   last aggregated propagation value
     */
    template<typename R>
    R bottom_up_reduce(std::function<R (T *, R)> f, R value, std::function<R (std::vector<R>)> aggregate, bool reversed = false) {
        if (this->_children.empty()) {
            return f(this, value);
        }
        std::vector<R> vec;
        for (T *child: this->children(reversed)) {
            vec.push_back(child->reduce(f, value, aggregate));
        }
        return f(this, aggregate(vec));
    }
};
