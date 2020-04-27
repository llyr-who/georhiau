#pragma once
#include <stdlib.h>
#include <iterator>

// temp stole this code! I am going to rewrite it.
// just so I can get this blog post done! :)

namespace georhiau {
template <class type>
class cdl_list {
public:
    //! \struct cdlNode
    struct cdlNode {
    public:
        cdlNode(const type &in_data, cdlNode *in_next = NULL,
                cdlNode *in_prev = NULL)
            : data(in_data), next(in_next), prev(in_prev){};

        cdlNode *next;  //!< points to the next node in the Dlist
        cdlNode *prev;  //!< point to the previous node in the Dlist
        type data;      //!< points to the data contained at the current node
    };

    std::size_t count;  //!< number of elements in the Dlist
    cdlNode *root;      //!< sentinel root node of Dlist
    friend class iterator;

    //! \class iterator
    class iterator {
    public:
        cdlNode *itr_node;

        friend class cdl_list<type>;

        iterator(cdlNode *in_node = NULL) { itr_node = in_node; }

        // inline iterator(const iterator &in_itr):itr_node(in_itr.itr_node){}

        // Destructor needs no implementation
        ~iterator() {}

        // Assignment operator
        /* Note the const in the following operators. This is necessary
         * because only l-values can be bound to non-const references. Temporary
         * objects are rvalue and they can't be bound to non-const references.
         * So, for example, when binding a temporary object (i.e. begin() or
         * end()) to a reference to const on the stack, the lifetime of the
         * temporary object is extended to the lifetime of the const reference
         * itself.
         */
        iterator &operator=(const iterator &rhs) {
            itr_node = rhs.itr_node;
            return (*this);
        }

        // Equality operator
        bool operator==(const iterator &rhs) {
            return (itr_node == rhs.itr_node);
        }

        // Inequality operator
        bool operator!=(const iterator &rhs) {
            return (!(itr_node == rhs.itr_node));
        }

        // Prefix increment operator
        iterator &operator++() {
            itr_node = itr_node->next;
            return (*this);
        }

        // Prefix decrement operator
        iterator &operator--() {
            itr_node = itr_node->prev;
            return (*this);
        }

        // Postfix increment operator
        iterator operator++(int) {
            iterator tmp(itr_node);
            itr_node = itr_node->next;
            return (tmp);
        }

        // Postfix decrement operator
        iterator operator--(int) {
            iterator tmp(*this);
            itr_node = itr_node->prev;
            return (tmp);
        }

        // Return a reference to the value in the node for updating
        cdlNode &operator*() { return (*itr_node); }

        cdlNode *operator->() { return (itr_node); }

    };  // End iterator class

    // Get iterator to beginning or list
    iterator begin() { return (iterator(root->next)); }

    // Get iterator to end of list
    iterator end() { return (iterator(root)); }


    // TODO: CLEAN THIS UP.
    // next, prev are some dirty functions because this cll uses sentinal nodes
    iterator next(iterator &it) {
        if (it->next == root) return it->next->next;
        return it->next;
    }

    iterator prev(iterator &it) {
        if (it->prev == root) return it->prev->prev;
        return it->prev;
    }


    // Constructor malloc's root node and sets it circular
    cdl_list();

    // Deep copy constructor
    cdl_list(const cdl_list &rhs);

    // Destructor clears list and free's root node
    ~cdl_list();

    // Clear cdl_list
    void clear();

    // size of cll
    std::size_t size() { return count; }

    // Check if cdl_list is empty
    bool empty();

    // Insert a node containing data BEFORE the iterator
    void insert_before(iterator &itr, const type &in_data);

    // Insert a node containing data AFTER the iterator
    void insert_after(iterator &itr, type &in_data);

    // Erase a node
    void erase(iterator &itr);

    // Add a node containing data to the back of list
    void push_back(const type &data);

    // Add a node containing data to the front of list
    void push_front(type &data);

    // Erase the end node of Dlist
    void pop_back();

    // Erase the end node of Dlist
    void pop_front();
};

/*****************************************************************************/
/**
 * cdl_list constructor implementation. Creates only the sentinel node
 *
 * @return void
 *
 */
template <class type>
cdl_list<type>::cdl_list() {  //:root(cdlNode(type())),count(0){

    root = new cdlNode(type());
    root->prev = root;
    root->next = root;
    count = 0;

}  // End cdl_list constructor

/*****************************************************************************/
/**
 * cdl_list destructor implementation. This function destroys cdl_list
 *
 * @return void
 *
 */
template <class type>
cdl_list<type>::~cdl_list() {
    clear();
    delete root;
}

/*****************************************************************************/
/**
 * cdl_list empty(...) implementation. This function tells whether or not
 * the list is empty.
 *
 * @return bool
 *
 */
template <class type>
bool cdl_list<type>::empty() {
    return (root == root->next);
}

/*****************************************************************************/
/**
 * cdl_list clear(...) implementation. This function destroys cdl_list.
 *
 * @return void
 *
 */
template <class type>
void cdl_list<type>::clear() {
    while (!empty()) {
        pop_back();
    }

    return;
}

/*****************************************************************************/
/**
 * cdl_list insert_before(...) implementation. This function inserts into
 * cdl_list BEFORE the location of the iterator.
 *
 * @return void
 *
 */
template <class type>
void cdl_list<type>::insert_before(iterator &itr, const type &in_data) {
    cdl_list::cdlNode *tmp =
        new cdlNode(in_data, itr.itr_node, itr.itr_node->prev);

    // Check if only the root node exists
    if (itr.itr_node == root->prev) {
        itr.itr_node->prev = tmp;
    }

    // Re-route the pointers
    itr.itr_node->prev = tmp;
    tmp->prev->next = tmp;

    ++count;

    return;
}

/*****************************************************************************/
/**
 * cdl_list insert_after(...) implementation. This function inserts into
 * cdl_list AFTER the location of the iterator.
 *
 * @return void
 *
 */
template <class type>
void cdl_list<type>::insert_after(iterator &itr, type &in_data) {
    cdl_list::cdlNode *tmp =
        new cdlNode(in_data, itr.itr_node->next, itr.itr_node);

    // Check if only the root node exists
    if (itr.itr_node == root->prev) {
        itr.itr_node->next = tmp;
    }

    // Re-route the pointers
    itr.itr_node->next = tmp;
    tmp->next->prev = tmp;

    ++count;

    return;
}

/*****************************************************************************/
/**
 * cdl_list push_back(...) implementation. This function adds a node
 * to the back.
 *
 * @param[in] data pinfo structure containing data to be copied into the new
 * node
 *
 * @return void
 *
 */
template <class type>
void cdl_list<type>::push_back(const type &data) {
    cdl_list::iterator itr_end = end();
    insert_before(itr_end, data);

    return;
}

/*****************************************************************************/
/**
 * cdl_list push_front(...) implementation. This function adds a node
 * to the front node of the list.
 *
 * @param[in] data pinfo structure containing data to be copied
 *
 * @return void
 *
 */
template <class type>
void cdl_list<type>::push_front(type &data) {
    cdl_list::iterator itr_begin = begin();
    insert_before(itr_begin, data);

    return;
}

/******************************************************************************/
/**
 * cdl_list pop_back(...) implementation. This function deletes the
 * back node of the list
 *
 * @return void
 *
 */
template <class type>
void cdl_list<type>::pop_back() {
    iterator itr(--end());  // Increment back since end() is the root node
    erase(itr);

    return;
}

/******************************************************************************/
/**
 * cdl_list pop_front(...) implementation. This function deletes the
 * front node of the list
 *
 * @return void
 *
 */
template <class type>
void cdl_list<type>::pop_front() {
    iterator itr(begin());
    erase(itr);

    return;
}

/*****************************************************************************/
/**
 * cdl_list erase(...) implementation. This function deletes a node
 * pointed at by itr
 *
 * @param[in] &itr iterator
 *
 * @return void
 *
 */
template <class type>
void cdl_list<type>::erase(iterator &itr) {
    // Make sure the root node is not deleted
    if (itr.itr_node == root) {
        return;
    }

    cdlNode *tmp = itr.itr_node;  // Store the node
    itr.itr_node = tmp->prev;     // Move iterator back so its still valid

    // Re-route the pointers around the node to be deleted
    tmp->prev->next = tmp->next;
    tmp->next->prev = tmp->prev;
    delete tmp;

    --count;

    return;
}
}  // namespace georhiau
