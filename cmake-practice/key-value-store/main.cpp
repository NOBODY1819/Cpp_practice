// Key-value store

#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <unordered_map>
#include <fstream>

void trim_spaces(std::string &line); //trims leading/trailing spaces
bool valid_key(std::string key); // check if key has spaces or isempty
void load_store(std::unordered_map<std::string, std::string> &store); // load the data from file to store
void save_store(std::unordered_map<std::string, std::string> &store); // sace the data from store to file

int main()
{

  std::cout << "Simple Key-Value store\n";
  std::cout << "Type 'quit' to exit.\n\n";

  std::string line;
  std::unordered_map<std::string, std::string> store; // declared a variable container to store pairs

  while (true)
  {
    std::cout << " > ";
    std::getline(std::cin, line); // getting whole line as input

    trim_spaces(line);

    if (line.empty())
    {
      continue;
    }

    size_t first_space = line.find(" "); // get positon of first space
    std::string command;

    if (first_space == std::string::npos)
    {
      command = line; // single line command
    }
    else
    {
      command = line.substr(0, first_space); // cmd - substring from pos 0 till first space
    }

    // convert command to lowercase
    for (char &c : command)
    {
      c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }

    if (command == "quit")
    {
      std::cout << "\nGoodBye!.\n";
      break;
    }
    else if (command == "help")
    {
      std::cout << "\nAvailable Commands\n";
      std::cout << "\tset <key> <value>  - store a key-value pair (or s)\n";
      std::cout << "\tget <key>          - retrive value for key (or g)\n";
      std::cout << "\thelp               - shows available commands\n";
      std::cout << "\tquit               - exit the program\n";
      std::cout << "(more commands coming soon...)\n\n";
    }
    else if (command == "set" || command == "s")
    {
      if (first_space == std::string::npos)
      {
        std::cout << "usage - set/s <key> <value>\n";
        continue;
      }
      command = line.substr(first_space + 1);
      trim_spaces(command);

      size_t second_space = command.find(" "); // get position of second space
      if (second_space == std::string::npos)
      {
        std::cout << "error 1: no value for set command. \n usage: set/s <key> <value>\n\n";
        continue;
      }

      std::string key, value;
      key = command.substr(0, second_space);    // key - substring till second space
      value = command.substr(second_space + 1); // vale everything from second space+1 till line ends.

      trim_spaces(key);
      trim_spaces(value);

      store[key] = value;
      std::cout << "set: \"" << key << "\" -> \"" << value << "\"\n\n";
    }
    else if (command == "get" || command == "g")
    {
      if (first_space == std::string::npos)
      {
        std::cout << "usage: get/g <key>\n\n";
        continue;
      }

      std::string key = line.substr(first_space + 1);
      trim_spaces(key);

      if(!valid_key(key)){
        continue;
      }
      else  if (store.find(key) != store.end())
      {
        std::cout << "value for \"" << key << "\": " << store[key] << "\n\n";
      }
      else
      {
        std::cout << "not found: \"" << key << "\"\n\n";
      }
    }
    else if(command == "delete" || command == "d"){
      if(first_space==std::string::npos){
        std::cout<<"error   30: no key provided\n\tusage: delete <key> (or d <key>)\n\n";
        continue;
      }
      std::string key = line.substr(first_space+1);
      trim_spaces(key);

      if(!valid_key(key)){
        continue;
      }else if(store.find(key) != store.end()){
        std::cout<<"delete: \""<<key<<"\" -> \""<<store[key]<<"\"\n\n";
        store.erase(key);
      }
      else{
        std::cout<<"Not found: \""<<key<<"\"\n\n";
      }
    }
    else
    {
      std::cout << "unknown command: " << line << "\n type 'help' for avilable commands.\n\n";
    }

    // std::cout<<"you typed -> "<<line<<std::endl;
  }

  return 0;
}

void trim_spaces(std::string &line)
{

  while (!line.empty() && std::isspace(static_cast<unsigned char>(line.front())))
    line.erase(0, 1);
  while (!line.empty() && std::isspace(static_cast<unsigned char>(line.back())))
    line.pop_back();
}

bool valid_key(std::string key){
  if (key.empty())
      {
        std::cout << "error 101: key cannot be empty.\n\n";
       return false;
      }
      else if (key.find(" ") != std::string::npos)
      {
        std::cout << "error 102: key cannot contain spaces\n\n";
        return false;
      }
  return true;
}

void load_store(std::unordered_map<std::string, std::string> $store){
// std::fstream st = FILE
}

void save_store(std::unordered_map<std::string, std::string> $store){

}