#ifndef SAVECOMMAND_H
#define SAVECOMMAND_H
#include <string>
#include <vector>
class SaveCommand
{
public:
    SaveCommand(const char*  table, std::string fields[], size_t n);
    SaveCommand();
    size_t getFieldsLength() const;
    std::string * getFields() const;
    virtual ~SaveCommand();
    bool execute() const;
    void addData(std::string data[]);
    void clearData();

private:
    std::vector <std::string *> _data;
    std::string * _fields;
    size_t _n;
    std::string _table;
};

#endif //SAVECOMMAND_H
