#pragma once

#include <functional>
#include <list>

namespace SDL_GUI {
template <typename T>
class TreeNode {
    T *_node = nullptr;
    TreeNode<T> *_parent = nullptr;
    std::list<TreeNode<T> *> _children;
    std::list<TreeNode<T> *> _children_reversed;

public:
    /**
     * Constructor
     *
     * @param node
     *   The Object this node represents
     */
    TreeNode<T>(T *node) : _node(node) {}

    /**
     * Destructor
     * Recursively freeing memory for TreeNode structures. This does not destruct the node objetcs itself.
     */
    ~TreeNode<T>() {
        for (TreeNode<T> *child: this->_children) {
            delete child;
        }
    }

    /**
     * Getter for _node
     *
     * @returns
     *   the Object this node represents
     */
    T *node() const {
        return this->_node;
    }

    /**
     * Getter for the _parent member
     *
     * @returns
     *   The Parent node in the tree
     */
    TreeNode<T> *parent() {
        return this->_parent;
    }

    /**
     * getter for the list of children
     *
     * @param reversed
     *   flag to determine if the list should be returned reversed
     * @returns
     *   list of children
     */
    std::list<TreeNode<T> *> children(bool reversed = false) {
        return reversed ? this->_children_reversed : this->_children;
    }

    const std::list<TreeNode<T> *> children(bool reversed = false) const {
        return reversed ? this->_children_reversed : this->_children;
    }

    /**
     * construct a Node for the given objetc and set it as a child
     *
     * @param child
     *   object to construct child node for
     * @returns
     *   The added child node
     */
    TreeNode<T> *add_child(T *child) {
        TreeNode<T> * t = new TreeNode{child};
        this->_children.push_back(t);
        this->_children_reversed.push_front(t);
        return t;
    }

    /**
     * add a given treenode as childo
     *
     * @returns
     *   The added child node
     */
    TreeNode<T> *add_child(TreeNode<T> *child) {
        this->_children.push_back(child);
        this->_children_reversed.push_front(child);
        return child;
    }

    /**
     * Find a node further down the tree representing a given Object
     *
     * @param node
     *   pointer to the Object to find
     * @returns
     *   Node representing the given object. nullptr if not found.
     */
    TreeNode<T> *find(T *node) const {
        if (this->_node == node) {
            return this;
        }
        for (TreeNode<T> *n: this->_children) {
            TreeNode<T> *found = n->find(node);
            if (found != nullptr) {
                return found;
            }
        }
        return nullptr;
    }

    /**
     * create list of Nodes by filtering this subtree
     * @param f filter to apply
     * @return list of filtered Nodes
     */
    std::vector<TreeNode<T> *> filter(std::function<bool(T *)> f) {
        std::vector<T *> filtered;
        if (f(this->_node)) {
            filtered.push_back(this->_node);
        }
        for (TreeNode<T> *n: this->_children) {
            std::vector<T *> filtered_child = n->filter(f);
            filtered.insert(filtered.end(), filtered_child.begin(), filtered_child.end());
        }
        return filtered;
    }

    std::vector<const TreeNode<T> *> filter(std::function<bool(T *)> f) const {
        std::vector<const TreeNode<T> *> filtered;
        if (f(this->_node)) {
            filtered.push_back(this->_node);
        }
        for (TreeNode<T> *n: this->_children) {
            std::vector<const TreeNode<T> *> filtered_child = n->filter(f);
            filtered.insert(filtered.end(), filtered_child.begin(), filtered_child.end());
        }
        return filtered;
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
    virtual void map(std::function<void (T *)> f, bool reversed = false) {
        f(this->_node);
        for (TreeNode<T> *child: this->children(reversed)) {
            child->map(f, reversed);
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
    virtual void bottom_up_map(std::function<void (T *)> f, bool reversed = false) {
        for (TreeNode<T> *child: this->children(reversed)) {
            child->map(f, reversed);
        }
        f(this->_node);
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
        R this_value = f(this->_node, value);
        for (TreeNode<T> *child: this->children(reversed)) {
            child->reduce(f, this_value, reversed);
        }
    }

    template<typename R>
    void reduce(std::function<R (const T *, R)> f, R value, bool reversed = false) const {
        R this_value = f(this->_node, value);
        for (const TreeNode<T> *child: this->children(reversed)) {
            child->reduce(f, this_value, reversed);
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
            return f(this->_node, value);
        }
        std::vector<R> vec;
        for (TreeNode<T> *child: this->children(reversed)) {
            vec.push_back(child->reduce(f, value, aggregate, reversed));
        }
        return f(this->_node, aggregate(vec));
    }
};

template <typename T>
class Tree {
    TreeNode<T> *_root = nullptr;
public:
    /**
     * Destructor
     */
    ~Tree<T>() {
        delete this->_root;
    }

    /**
     * construct a node for the given object and set it as root of the tree
     *
     * @param node
     *   Object to construct root node for
     * @returns
     *   The added root node
     */
    TreeNode<T> *set_root(T *node) {
        this->_root =  new TreeNode<T>(node);
        return this->_root;
    }

    /**
     * set a treenode as root node
     *
     * @param node
     *   treenode to set as root
     * @param returns
     *   set treenode
     */
    TreeNode<T> *set_root(TreeNode<T> *node) {
        this->_root = node;
        return this->_root;
    }

    /**
     * construct a node for the given object and set it as child of a given parent
     *
     * @param node
     *   Object to construct node for
     * @param parent
     *   Object to add the constructed Node as child to
     * @returns
     *   constructed node
     */
    TreeNode<T> *add(T *node, T *parent) {
        TreeNode<T> *parent_node = this->find(parent);
        if (parent_node == nullptr) {
            return nullptr;
        }
        parent_node->add_child(node);
    }

    /**
     * finds the given object in the tree
     *
     * @param node
     *   Object to find in tree
     * @returns
     *   Node representing the given object. nullptr if not in tree.
     */
    TreeNode<T> *find(T *node) const {
        if (this->_root == nullptr) {
            return nullptr;
        }
        return this->_root->find(node);
    }

    /**
     * filter the tree for a list of nodes
     * @param f filter to apply to each object
     * @return filtered list of Nodes
     */
    std::vector<TreeNode<T> *> filter(std::function<bool(T *)> f) {
        std::vector<TreeNode<T> *> filtered;
        if (this->_root == nullptr) {
            return filtered;
        }
        return this->_root->filter(f);
    }

    std::vector<const TreeNode<T> *> filter(std::function<bool(T *)> f) const {
        std::vector<const TreeNode<T> *> filtered;
        if (this->_root == nullptr) {
            return filtered;
        }
        return this->_root->filter(f);
    }

    /**
     * apply a function recursively to this
     *
     * @param f
     *   function to apply
     * @param reversed
     *   flag to determine the order of child processing. If true, the list of childs get
     *   reversed before applying f
     */
    void map(std::function<void (T *)> f, bool reversed = false) {
        if (this->_root == nullptr) {
            return;
        }
        this->_root->map(f, reversed);
    }

    /**
     * apply a function recursively to this from bottom to top of the tree
     *
     * @param f
     *   function to apply
     * @param reversed
     *   flag to determine the order of child processing. If true, the list of childs get
     *   reversed before applying f
     */
    void bottom_up_map(std::function<void (T *)> f, bool reversed = false) {
        if (this->_root == nullptr) {
            return;
        }
        this->_root->bottom_up_map(f, reversed);
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
        if (this->_root == nullptr) {
            return;
        }
        this->_root->reduce(f, value, reversed);
    }

    template<typename R>
    void reduce(std::function<R (const T *, R)> f, R value, bool reversed = false) const {
        if (this->_root == nullptr) {
            return;
        }
        this->_root->reduce(f, value, reversed);
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
        if (this->_root == nullptr) {
            return;
        }
        return this->_root->bottom_up_reduce(f, value, aggregate, reversed);
    }

};
}
