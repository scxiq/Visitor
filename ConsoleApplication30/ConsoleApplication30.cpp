#include <iostream>
#include <vector>

// Інтерфейс Відвідувача
class Visitor;

// Абстрактний клас елемента
class Element {
public:
    virtual void accept(Visitor& visitor) = 0;
    virtual ~Element() = default;
};

// Конкретний клас елемента A
class ElementA : public Element {
public:
    void accept(Visitor& visitor) override;
    void operationA() {
        std::cout << "ElementA: OperationA\n";
    }
};

// Конкретний клас елемента B
class ElementB : public Element {
public:
    void accept(Visitor& visitor) override;
    void operationB() {
        std::cout << "ElementB: OperationB\n";
    }
};

// Інтерфейс Відвідувача
class Visitor {
public:
    virtual void visitElementA(ElementA& elementA) = 0;
    virtual void visitElementB(ElementB& elementB) = 0;
    virtual ~Visitor() = default;
};

// Конкретний Відвідувач
class ConcreteVisitor : public Visitor {
public:
    void visitElementA(ElementA& elementA) override {
        std::cout << "ConcreteVisitor: Visiting ElementA\n";
        elementA.operationA();
    }

    void visitElementB(ElementB& elementB) override {
        std::cout << "ConcreteVisitor: Visiting ElementB\n";
        elementB.operationB();
    }
};

// Реалізація методів accept для конкретних елементів
void ElementA::accept(Visitor& visitor) {
    visitor.visitElementA(*this);
}

void ElementB::accept(Visitor& visitor) {
    visitor.visitElementB(*this);
}

// Клас, що містить колекцію елементів та викликає методи accept Відвідувача
class ObjectStructure {
public:
    void addElement(std::shared_ptr<Element> element) {
        elements_.push_back(element);
    }

    void acceptVisitor(Visitor& visitor) {
        for (const auto& element : elements_) {
            element->accept(visitor);
        }
    }

private:
    std::vector<std::shared_ptr<Element>> elements_;
};

int main() {
    // Використання паттерна "Відвідувач"
    ObjectStructure objectStructure;

    // Додавання конкретних елементів до колекції
    objectStructure.addElement(std::make_shared<ElementA>());
    objectStructure.addElement(std::make_shared<ElementB>());

    // Створення конкретного Відвідувача
    ConcreteVisitor concreteVisitor;

    // Виклик методів accept для всіх елементів колекції
    objectStructure.acceptVisitor(concreteVisitor);

    return 0;
}
