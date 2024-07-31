#include <iostream>
#include <memory>
#include <string>

class Text {
public:
    virtual void render(std::ostream& os, const std::string& data) const {
        os << data;
    }
};

class DecoratedText : public Text {
public:
    explicit DecoratedText(Text* text) : text_(text) {}
    virtual ~DecoratedText() = default;
    Text* text_;
};

class Paragraph : public DecoratedText {
public:
    explicit Paragraph(Text* text) : DecoratedText(text) {}
    void render(std::ostream& os, const std::string& data) const override {
        os << "<p>";
        text_->render(os, data);
        os << "</p>";
    }
};

class Reversed : public DecoratedText {
public:
    explicit Reversed(Text* text) : DecoratedText(text) {}
    void render(std::ostream& os, const std::string& data) const override {
        text_->render(os,std::string(data.rbegin(), data.rend()));
    }
};

class Link : public DecoratedText {
public:
    explicit Link(Text* text) : DecoratedText(text) {}
    void render(std::ostream& os, const std::string& link, const std::string& text) const {
        os << "<a href=";
        text_->render(os,link);
        os << ">";
        text_->render(os,text);
        os << "</a>";
    }
};

class ItalicText : public DecoratedText {
public:
    explicit ItalicText(Text* text) : DecoratedText(text) {}
    void render(std::ostream& os, const std::string& data) const override {
        os << "<i>";
        text_->render(os, data);
        os << "</i>";
    }
};

class BoldText : public DecoratedText {
public:
    explicit BoldText(Text* text) : DecoratedText(text) {}
    void render(std::ostream& os, const std::string& data) const override {
        os << "<b>";
        text_->render(os, data);
        os << "</b>";
    }
};

int main() {
    {
        auto text = Text();
        auto bt = BoldText(&text);
        auto text_block = std::make_unique<ItalicText>(&bt);
        text_block->render(std::cout, "Hello world");
        std::cout << std::endl;
    }
    {
        auto text = Text();
        auto text_block = std::make_unique<Paragraph>(&text);
        text_block->render(std::cout,"Hello world");
        std::cout << std::endl;
    }
    {
        auto text = Text();
        auto text_block = std::make_unique<Reversed>(&text);
        text_block->render(std::cout,"Hello world");
        std::cout << std::endl;
    }
    {
        auto text = Text();
        auto text_block = std::make_unique<Link>(&text);
        text_block->render(std::cout,"netology.ru","Hello world");
        std::cout << std::endl;
    }
}