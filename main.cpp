#include <iostream>
#include "include/csvreader.h"
#include <cassert>
#include "include/SaveCommand.h"
#include "include/DBSingleton.h"

int main(int argc, char *argv[])
{
    const std::string CATEGORY_TABLE_NAME = "category";
    assert(argc > 1);   // Specifying filepath is required.

    std::cout << argv[1] << std::endl;
    std::string filepath(argv[1]);

    CSVreader * reader = new CSVreader(filepath);
    std::string * resValues;
    std::string categoryName = "";

    std::string * fields = new std::string[1];
    fields[0] = "name";
    SaveCommand * categorySaveCmd = new SaveCommand(CATEGORY_TABLE_NAME.c_str(),
            fields, 1);

    while ((resValues = reader->parseLine()) != 0) {
        if (categoryName != resValues[3]) {
            categoryName = resValues[3];
            std::string * data = new std::string[1];
            data[0] = resValues[3];
            categorySaveCmd->addData(data);
        }

        //productSaveCmd->addData(resValues);
        //std::cout << "name: " << resValues[0] << std::endl;
        //std::cout << "code: " << resValues[1] << std::endl;
        //std::cout << "cost: " << resValues[2] << std::endl;
        //std::cout << "section: " << resValues[3] << std::endl;
        //std::cout << "-----------------" << std::endl;
        delete[] resValues;
    }
    categorySaveCmd->execute();


    fields = new std::string[4];
    fields[0] = "name";
    fields[1] = "code";
    fields[2] = "price";
    fields[3] = "category_id";
    SaveCommand * productSaveCmd = new SaveCommand("product", fields, 4);

    std::string categoryFields[2] = {"id", "name"};
    auto db = DBSingleton::getSingleton();
    std::list<std::vector<std::string>> CATEGORIES = db->getTableData(
            CATEGORY_TABLE_NAME, categoryFields, 2);

    std::string categoryId = "";
    while ((resValues = reader->parseLine()) != 0) {
        if (categoryName != resValues[3]) {
            categoryName = resValues[3];

            // Gets id of category.
            for (auto it = CATEGORIES.begin(); it != CATEGORIES.end(); ++it) {
                std::cout << "'" << it->at(1) << "'" << std::endl;
                std::cout << categoryName << " <-" << std::endl;
                std::cout << (it->at(1) == categoryName) << std::endl;
                if (it->at(1) == categoryName) {
                    std::cout << 123 << std::endl;
                    categoryId = it->at(0);
                }
            }

            
        }
        assert(categoryId != "");
        std::string * data = new std::string[4];
        data[0] = resValues[0];
        data[1] = resValues[1];
        data[2] = resValues[2];
        data[3] = categoryId;
        productSaveCmd->addData(data);
        delete[] resValues;
    }
    bool res = productSaveCmd->execute();

    delete categorySaveCmd;
    delete productSaveCmd;
    delete reader;
    return 0;
}
