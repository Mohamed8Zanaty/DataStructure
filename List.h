#pragma once
#include <iostream>
template <typename T>
class List {
    class Node {
    public:
        T data;
        Node* next;
        Node(T data, Node* next) : data(data), next(next) {}
    };
    Node* head = nullptr;
    int _size = 0;
    Node* _get(int index) {
        if (index >= _size) {
            return nullptr;
        }
        Node* curr = head;
        while (index--) {
            curr = curr->next;
        }
        return curr;
    }
public:
    List() : _size(0) {}
     explicit List(const int size) : _size(size) {
        for (int i = 0; i < size; i++) {
            Node* newNode = new Node({}, nullptr);
            if (head == nullptr) {
                head = newNode;
            }
            else {
                end()->next = newNode;
            }

        }
    }
    ~List() {
        Node* curr = head;
        while (curr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
    }
    void push_back(T data) {
        Node* newNode = new Node(data, nullptr);
        if (head == nullptr) {
            head = newNode;
        }
        else {
            end()->next = newNode;
        }
        _size++;
    }
    void push_front(T data) {
        Node* newNode = new Node(data, nullptr);
        if (head == nullptr) {
            head = newNode;
        }
        else {
            newNode->next = head;
            head = newNode;
        }
        _size++;
    }
    void pop_back() {
        if (_size < 2) {
            if (head == nullptr) return;
            head->next = nullptr;
            delete head->next;
            head = nullptr;
            _size = 0;
            return;
        }
        Node* end = _get(_size - 2);
        end->next = nullptr;
        delete end->next;
        _size--;
    }
    void pop_front() {
        if (_size < 2) {
            if (head == nullptr) return;
            head = nullptr;
            delete head;
        }
        else {
            head = head->next;
        }
        _size--;
    }
    Node* end() {
        Node* curr = head;
        while (curr->next) {
            curr = curr->next;
        }
        return curr;
    }

    void erase(const int index) {
        Node* curr = _get(index), *prev = _get(std::max(index - 1, 0));
        if (index == 0) {
            head = curr->next;
        }
        else prev->next = curr->next;
        curr = nullptr;
        delete curr;
        _size--;
    }
    void insert(const T data, const int index) {
        Node* newNode = new Node(data, nullptr);
        if (index == 0) {
            newNode->next = head;
            head = newNode;
            return;
        }
        Node* curr = _get(std::max(index -1, 0));
        newNode->next = curr->next;
        curr->next = newNode;
        _size++;
    }
    T get(const int index) {
        return _get(index)->data;
    }
    [[nodiscard]] int size() const {
        return _size;
    }
    friend std::ostream& operator<<(std::ostream& os, const List& list) {
        Node* current = list.head;
        os << '[';
        while (current != nullptr) {
            os << current->data;
            if (current->next != nullptr)
                os << ", ";
            current = current->next;
        }
        os << ']';
        return os;
    }
    friend std::istream& operator>>(std::istream& is, List& list) {
        Node* current = list.head;

        for (int i = 0; i < list._size; ++i) {
            if (!(is >> current->data)) {
                throw std::runtime_error("Invalid input");
            }
            current = current->next;
        }

        return is;
    }
    T& operator[](const int index) {
        if (index < 0 || index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        return _get(index)->data;
    }

    void clear() {
        Node* curr = head;
        while (curr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
        head = nullptr;
        _size = 0;
    }
    [[nodiscard]] bool empty() const {
        return !_size;
    }
    T front() const {
        if (_size == 0) {
            throw std::out_of_range("Empty list");
        }
        return head->data;
    }
    T back() {
        if (_size == 0) {
            throw std::out_of_range("Empty list");
        }
        return end()->data;
    }
    Node* begin()  {
        if (_size == 0) {
            throw std::out_of_range("Empty list");
        }
        return head;
    }
};






