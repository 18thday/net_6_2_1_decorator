#include <string>
#include <iostream>

class Text {
public:
    virtual void render(const std::string& data) const {
        std::cout << data;
    }
};

class DecoratedText : public Text {
public:
    explicit DecoratedText(Text* text) : text_(text) {}
    Text* text_;
};

class Paragraph : public DecoratedText {
public:
    explicit Paragraph(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const override {
        std::cout << "<p>";
        text_->render(data);
        std::cout << "</p>";
    }
};

class Reversed : public DecoratedText {
public:
    explicit Reversed(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const override {
        text_->render(std::string(data.rbegin(), data.rend()));
    }
};

class Link : public DecoratedText {
public:
    explicit Link(Text* text) : DecoratedText(text) {}
    void render(const std::string& link, const std::string& text) const {
        std::cout << "<a href=";
        text_->render(link);
        std::cout << ">";
        text_->render(text);
        std::cout << "</a>";
    }
};

class ItalicText : public DecoratedText {
public:
    explicit ItalicText(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const override {
        std::cout << "<i>";
        text_->render(data);
        std::cout << "</i>";
    }
};

class BoldText : public DecoratedText {
public:
    explicit BoldText(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const override {
        std::cout << "<b>";
        text_->render(data);
        std::cout << "</b>";
    }
};

int main() {
    {
        auto text_block = new ItalicText(new BoldText(new Text()));
        text_block->render("Hello world");
        std::cout << std::endl;
    }
    {
        auto text_block = new Paragraph(new Text());
        text_block->render("Hello world");
        std::cout << std::endl;
    }
    {
        auto text_block = new Reversed(new Text());
        text_block->render("Hello world");
        std::cout << std::endl;
    }
    {
        auto text_block = new Link(new Text());
        text_block->render("netology.ru","Hello world");
        std::cout << std::endl;
    }
}