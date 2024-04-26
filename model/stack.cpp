#include "stack.hpp"

void Stack::push_left(double data, Type type, Priority priority) {
  auto newNode = std::make_shared<Node>(data, type, priority);
  newNode->next = head;
  if (head != nullptr) {
    head->prev = newNode;
  } else {
    tail = newNode;
  }
  head = newNode;
}

void Stack::push_right(double data, Type type, Priority priority) {
  auto newNode = std::make_shared<Node>(data, type, priority);
  newNode->prev = tail;
  if (tail != nullptr) {
    tail->next = newNode;
  } else {
    head = newNode;
  }
  tail = newNode;
}

std::shared_ptr<Node> Stack::pop_head() {
  if (!head) return nullptr;
  auto temp = head;
  head = head->next;
  if (head) {
    head->prev.reset();
  } else {
    tail.reset();
  }
  return temp;
}

std::shared_ptr<Node> Stack::pop_tail() {
  if (!tail) return nullptr;
  auto temp = tail;
  // Преобразование weak_ptr в shared_ptr перед использованием
  auto prevNode = temp->prev.lock();
  tail = prevNode;
  if (tail) {
    tail->next.reset();  // Отсоединяем последний элемент от предыдущего
  } else {
    head.reset();  // Если в стеке больше нет элементов, сбрасываем head
  }
  temp->prev.reset();  // Обязательно отсоединяем temp от предыдущего узла
  return temp;
}

std::shared_ptr<Node> Stack::peek_left() const { return head; }

std::shared_ptr<Node> Stack::peek_right() const { return tail; }

void Stack::clear_stack() {
  while (head) {
    pop_head();
  }
}

bool Stack::isEmpty() const { return head == nullptr; }

void Stack::printStack() const {
  std::shared_ptr<Node> current = head;
  std::cout << "---------------\n";
  while (current != nullptr) {
    std::cout << "Data: " << current->data
              << " | Type: " << static_cast<int>(current->type)
              << " | Priority: " << static_cast<int>(current->priority)
              << std::endl;
    current = current->next;
  }
  std::cout << "---------------\n";
}