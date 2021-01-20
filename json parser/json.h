#pragma once

#include <istream>
#include <unordered_map>
#include <string>
#include <variant>
#include <vector>

namespace Json {

  class Node : std::variant<std::vector<Node>,
                            std::unordered_map<std::string, Node>,
                            double,
                            bool,
                            std::string> {
  public:
    using variant::variant;

    const auto& AsArray() const {
      return std::get<std::vector<Node>>(*this);
    }
    const auto& AsUnorderedMap() const {
      return std::get<std::unordered_map<std::string, Node>>(*this);
    }
    int AsDouble() const {
      return std::get<double>(*this);
    }
    int AsBool() const {
      return std::get<bool>(*this);
    }
    const auto& AsString() const {
      return std::get<std::string>(*this);
    }
  };

  class Document {
  public:
    explicit Document(Node root);

    const Node& GetRoot() const;

  private:
    Node root;
  };

  Document Load(std::istream& input);

} // namespace Json