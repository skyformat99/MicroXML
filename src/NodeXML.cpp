#include <MicroXML/NodeXML.hpp>
#include <MicroXML/MicroXML.hpp>
#include <iostream>

/// Constructors
NodeXML::NodeXML() :
    _name(""),
    _data(""),
    _topNode(nullptr)
{}

NodeXML::NodeXML(std::string name) :
    _name(name),
    _data(""),
    _topNode(nullptr)
{}

/// Changes node's data
void NodeXML::setData(std::string data)
{
    _data = data;
}

/// Set attributes
void NodeXML::setAttr(const std::map<std::string, std::string>& attr)
{
    _attr = attr;
}

/// Creates and adds a sub node
NodeXML* NodeXML::addSubNode(std::string name)
{
    NodeXML* newNode = new NodeXML(name);
    _subNodes.addNode(newNode);
    newNode->_topNode = this;

    return &(*_subNodes().back());
}

/// Access an attribute by its name
std::string NodeXML::operator[](std::string attr)
{
    return get(attr);
}

std::string NodeXML::get(const std::string& attr) const
{
    if (_attr.find(attr) != _attr.end())
        return _attr.at(attr);
    return "";
}

/// Different exploration methods
NodeSet NodeXML::operator()(std::string path)
{
    NodeSet result;
    result.addNode(this);
    return result(path, MicroXML::getDefaultSeparator());
}

NodeSet NodeXML::operator()(std::string path, const std::string& sep)
{
    NodeSet result;
    result.addNode(this);
    return result(path, sep);
}

/// Return node's name
std::string NodeXML::getName() const
{
    return _name;
}

/// Returns all sub nodes
NodeSet& NodeXML::getNodeSet()
{
    return _subNodes;
}

void NodeXML::print() const
{
    print("");
}

void NodeXML::print(std::string indent) const
{
    std::cout << indent << "+"+_name;
    if (!_data.empty())
        std::cout << " -> " << _data;
    std::cout << std::endl;

    for (auto& node : _subNodes)
        node->print(indent+"  ");

    std::cout << indent << "-"+_name << std::endl;
}

/// Return node's data casted into desired type
int NodeXML::asInt() const
{
    return strToInt(_data);
}

double NodeXML::asDouble() const
{
    return strToDouble(_data);
}

std::string NodeXML::asString() const
{
    return _data;
}
