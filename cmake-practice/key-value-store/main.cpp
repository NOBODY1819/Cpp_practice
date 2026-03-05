// Key-value store

#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <unordered_map>
#include <fstream>

void trim_spaces(std::string &line); //trims leading/trailing spaces
bool valid_key(const std::string& key); // check if key has spaces or isempty
void load_store(std::unordered_map<std::string, std::string> &store); // load the data from file to store
void save_store(const std::unordered_map<std::string, std::string> &store); // sace the data from store to file
std::string lower(std::string word);

int main()
{

  std::cout << "Simple Key-Value store\n";
  std::cout << "Type 'quit' to exit.\n\n";
  
  std::string line;
  std::unordered_map<std::string, std::string> store; // declared a variable container to store pairs
  load_store(store);

  while (true)
  {
    std::cout << " > ";
    std::getline(std::cin, line); // getting whole line as input

    trim_spaces(line);

    if (line.empty()) continue;


    size_t first_space = line.find(" "); // get positon of first space
    std::string command = (first_space == std::string::npos)? line : line.substr(0, first_space);

    // convert command to lowercase
    for (char &c : command)
    {
      c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }

    if (command == "quit") // exit
    {
      std::cout << "\nGoodBye!\n";
      save_store(store);
      break;
    }
    else if (command == "help") //help message
    {
      std::cout << "\nAvailable Commands\n";
      std::cout << "\tset/s <key> <value>  - store a key-value pair\n";
      std::cout << "\tget/g <key>          - retrieve value for key\n";
      std::cout << "\tdelete/d <key>       - remove key\n";
      std::cout << "\trename/rn <old_key> <new_key> - update <old_key> to <new_key>\n";
      std::cout << "\tsearch/srch/f <key>   - search <key> in store\n";
      std::cout << "\tlist                 - show stored key-value paired\n";
      std::cout << "\tcount                - show the number of keys\n";
      std::cout << "\tclear                - clear the store\n";
      std::cout << "\tsave                 - save to the store\n";
      std::cout << "\thelp                 - shows available commands\n";
      std::cout << "\tquit                 - exit the program\n";
    }
    else if(command == "list") // view key-values
    {
      std::cout << "key-value stored\n\n ---<start>---\n";
      for(const auto& it: store){
        std::cout << it.first << " : " << it.second <<std::endl;
      }
      std::cout << " ---<end>---\n\n";
    }
    else if(command == "clear") // clear all key-value
    {
      size_t old_size = store.size();
      store.clear();
      std::cout<<"cleared "<< old_size << " entries from store.\n\n";
    }
    else if(command == "count") // find number of key-values
    {
      std::cout << "Total key in store: " << store.size() <<"\n\n";
    }
    else if(command == "save") // save in store
    {
      save_store(store);
    }
    else if (command == "set" || command == "s") 
    {
      if (first_space == std::string::npos)
      {
        std::cout << "error 10: no key provided\n\tusage - set/s <key> <value>\n";
        continue;
      }
      command = line.substr(first_space + 1);
      trim_spaces(command);

      size_t second_space = command.find(" "); // get position of second space
      if (second_space == std::string::npos)
      {
        std::cout << "error 1: no 'value' for set command. \n usage: set/s <key> <value>\n\n";
        continue;
      }

      std::string key, value;
      key = command.substr(0, second_space);    // key - substring till second space
      value = command.substr(second_space + 1); // value everything from second space+1 till line ends.

      trim_spaces(key);
      trim_spaces(value);
      
      if(key.empty()){
        std::cout << "error: key cannot be empty\n\n";
        continue;
      }

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
        std::cout<<"error 30: no key provided\n\tusage: delete <key> (or d <key>)\n\n";
        continue;
      }
      std::string key = line.substr(first_space+1);
      trim_spaces(key);

      if(!valid_key(key)) 
      {
        std::cout << "error 31: key not valid\n\n";
        continue;
      }
      
      auto it = store.find(key);

      if(it != store.end()){
        std::cout<<"delete: \""<<key<<"\" -> \""<<it->second<<"\"\n\n";
        store.erase(key);
      }
      else{
        std::cout<<"Not found: \""<<key<<"\"\n\n";
      }
    }
    else if(command == "rename" || command == "rn")
    {
      if(first_space == std::string::npos){
        std::cout<<"error 40: no <old_key> provided\n\tusage: rename <old_key> <new_key>\n\n";
        continue;
      }
      
      command = line.substr(first_space+1);
      trim_spaces(command);

      size_t second_space = command.find(" ");
      if(second_space == std::string::npos){
        std::cout << "error 41: no <new_key> provided\n\tusage: rename <old_key> <new_key>\n\n";
        continue;
      }
      std::string old_key = command.substr(0, second_space);
      std::string new_key = command.substr(second_space+1);

      trim_spaces(old_key);
      trim_spaces(new_key);

      if(old_key.empty() || new_key.empty()){
        std::cout<<"error 42: invalid key\n\n";
        continue;
      }
      auto it = store.find(old_key);
      if(it == store.end()){
        std::cout << "error 44: no entry with key \"" << old_key << "\" in store.\n\n";
        continue; 
      }
      
      store[new_key] = it->second;
      store.erase(old_key);   
      std::cout << "renamed: \"" << old_key << "\" (" << it->second << ") -> \"" << new_key << "\"\n\n";
    }
    else if(command == "search" || command == "srch" || command == "f"){
      if(first_space==std::string::npos){
        std::cout << "error 51: no substring key provied.\n\tusage: search/srch/f <key>\n\n";
        continue;
      }
      
      std::string term = line.substr(first_space+1);
      trim_spaces(term);

      if(term.empty()){
        std::cout << "error52: search term cannot be empty.\n\t usage: search/srch/f <key>\n\n";
        continue;
      }
      if(!valid_key(term)){
        continue;
      }
      term = lower(term);
      int match_found = 0;
      std::cout<< "Searching for \"" <<term <<"\" ...\n";

      for(const auto &pair: store){
        std::string key = lower(pair.first);
        if(key.find(term) != std::string::npos){
          std::cout << "\"" <<pair.first <<"\" -> \"" <<pair.second <<"\"\n";
          match_found++;
      }}
      if(match_found==0){
        std::cout<<"No match found\n\n";
      }else{
        std::cout << "\n Found "<< match_found<< " match(es).\n";
      }
      std::cout<<"\n";
    }
    else
    {
      std::cout << "unknown command: " << line << "\n type 'help' for avilable commands.\n\n";
    }

    // std::cout<<"you typed -> "<<line<<std::endl;
  }
  return 0;
}

void trim_spaces(std::string& line)
{
  while (!line.empty() && std::isspace(static_cast<unsigned char>(line.front())))
    line.erase(0, 1);
  while (!line.empty() && std::isspace(static_cast<unsigned char>(line.back())))
    line.pop_back();
}

bool valid_key(const std::string& key){
  if (key.empty())
      {
        std::cout << "error: key cannot be empty.\n\n";
       return false;
      }
      else if (key.find(" ") != std::string::npos)
      {
        std::cout << "error: key cannot contain spaces\n\n";
        return false;
      }
  return true;
}

void load_store(std::unordered_map<std::string, std::string> &store){
  std::ifstream store_file("store.txt");
  if(!store_file.is_open()){
    std::cout<<"no previous data found (store.txt not present)\n\n";
    return;
  }
  
  std::string line;
  while(std::getline(store_file, line)){
    size_t colon = line.find(':');
    if(colon != std::string::npos){
      std::string key = line.substr(0, colon);
      std::string value = line.substr(colon+1);
      trim_spaces(key);
      trim_spaces(value);
      if(!key.empty())
        store[key] = value;
       }
    }
  std::cout<<"loaded "<< store.size() << " entries from store.txt successfully...\n\n";
  store_file.close();
  return;
}

void save_store(const std::unordered_map<std::string, std::string>& store){
  std::ofstream store_file("store.txt");
  if(!store_file.is_open()){
    std::cout<<"error: cannot write to store.txt\n\n";
    return;
  }
  for(const auto& pair: store){
    store_file<<pair.first<<":"<<pair.second<<std::endl;
  }
  std::cout<<"saved " << store.size() << " entries to store.txt\n\n";
  store_file.close();
  return;
}

std::string lower(std::string word){
  std::string str;
  for(char &c: word){
    str += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
  }
  return str;
}