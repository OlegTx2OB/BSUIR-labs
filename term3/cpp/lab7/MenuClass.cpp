#include <algorithm>
#include <random>
#include "MenuClass.h"

int MenuClass::getInt(string str, int lowerBound, int upperBound)
{
    if (!str.empty()) cout << "Enter " << str << " (" << lowerBound << " - " << upperBound << "): ";

    int d;
    while (!scanf("%d", &d) || d < lowerBound || d > upperBound)
    {
        cout << "invalid input" << endl;
        rewind(stdin);
    }
    return d;
}

vector<int> MenuClass::addNotesIntoFile()
{
    vector<Structure *> structureVector;
    vector<int> idVector;

    do
    {
        Structure *structureNote = new Structure();
        int id = getInt("id", 10, 99);
        char* infoChar = (char*)malloc(100 * sizeof(char));
        cout << "Enter info: ";
        scanf("%s", infoChar);
        string info(infoChar);
        structureNote->setId(id);
        structureNote->setInfo(info);
        structureVector.push_back(structureNote);
    }
    while(getInt("do you want more? (yes-1 or no-0)", 0, 1));

    BinFile* bf = new BinFile(structureVector);

    for (const auto& structureNote : structureVector) idVector.push_back(structureNote->getId());

    random_device rd;
    mt19937 g(rd());
    std::shuffle(idVector.begin(),idVector.end(),g);

    TxtFile* tf = new TxtFile(idVector);
    return idVector;
}
void MenuClass::changeNotesIntoFile(vector<int> idVector)
{
    int id;
    bool flag=true;
    do
    {
        do
        {

            std::cout << "Enter ID: ";
            std::cin >> id;
            std::cin.ignore();
            auto it = std::find(idVector.begin(), idVector.end(), id);

            if (it == idVector.end() && id != idVector.at(idVector.size()-1))
            {
                std::cout << "id is uncorrect" << std::endl;
                flag=false;
            }

        }
        while(!flag);

        changeNoteById(id);
    } while (getInt("do you want more? (yes-1 or no-0)", 0, 1));
}
void MenuClass::mixFiles()
{
    std::ifstream textFile("txt_file.txt");
    std::ifstream binaryFile("binary_file.bin");
    std::ofstream outputFile("output_file.txt");

    int id1, id2 = -1;
    Structure* structureNote = new Structure();

    while (textFile >> id1)
    {
        binaryFile.seekg(0, std::ios::beg);
        while (id1 != id2 )
        {

            binaryFile.read(reinterpret_cast<char*>(&id2), sizeof(int));
            int infoLength;
            binaryFile.read(reinterpret_cast<char*>(&infoLength), sizeof(int));
            char* buffer = new char[infoLength + 1];
            binaryFile.read(buffer, infoLength);
            buffer[infoLength] = '\0';

            structureNote->setId(id2);
            structureNote->setInfo(buffer);
        }
        outputFile << *structureNote;
    }

    delete structureNote;

    textFile.close();
    binaryFile.close();
    outputFile.close();
}
void MenuClass::changeNoteById(int id)
{
    std::ifstream inFile("output_file.txt");


    if (!inFile.is_open()) {
        std::cerr << "File cannot be opened" << std::endl;
        return;
    }

    std::vector<std::string> lines;
    std::string line;

    // Чтение строк из файла и сохранение в векторе
    while (std::getline(inFile, line)) {
        lines.push_back(line);
    }

    inFile.close();


    std::ofstream outFile("output_file.txt");

    if (!outFile.is_open()) {
        std::cerr << "File cannot be opened" << std::endl;
        return;
    }

    for ( std::string line : lines)
    {
        std::string num;
        num=line[5];
        int i=6;
        while(line[i]!=' ')
        {
            num += line[i];
            i++;
        }
        if(id==std::atoi(num.c_str()))
        {
            num="";
            std::cout<<"Enter new data: "<<std::endl;
            std::cin>>num;
            line="{id: " + std::to_string(id) + " | info: " + num + "}";
        }
        outFile << line<<std::endl;
    }

    outFile.close();


}