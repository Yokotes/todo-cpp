#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;


void load_todos(vector<string> *todos) {
  ifstream file("./data");

  todos->clear();

  string line;
  while(getline(file, line)) {    
    todos->push_back(line);
  }

  file.close();
}

void save_todos(vector<string> *todos) {
  string saved_todos;
  ofstream file("./data", ofstream::out | ofstream::trunc);
  
  for (size_t i = 0; i < todos->size(); i++) {
    saved_todos += todos->at(i) + '\n';
  }

  file << saved_todos;
  file.close();
}

void print_todos(vector<string> *todos) {
  if (todos->size() < 1) cout << "There is no todos yet.\n";
  else {
    cout << "Todos:\n";
    for (size_t i = 0; i < todos->size(); i++) {
      cout << i + 1 << ". " << todos->at(i) << '\n'; 
    }
  }
}

void add_todo(vector<string> *todos, string *text) {
  size_t command_size = 4;
  string todo_text = text->substr(command_size);
  
  if (todo_text.size() < 1) {
    cout << "There is no todo text.\n";
    return;
  }

  todos->push_back("[ ] " + todo_text);
}

void remove_todo(vector<string> *todos, string *text) {
  if (todos->size() < 1) {
    cout << "There is no todo.\n";
    return;
  }
  
  size_t command_size = 7;
  int id = stoi(text->substr(command_size)) - 1;

  if (id < 0 || id >= todos->size()) {
    cout << "There is no todo with this [id].\n";
    return;
  }

  todos->erase(todos->begin() + id );
}

void check_todo(vector<string> *todos, string *text) {
  if (todos->size() < 1) {
    cout << "There is no todo.\n";
    return;
  }
  
  size_t command_size = 6;
  int id = stoi(text->substr(command_size)) - 1;

  if (id < 0 || id >= todos->size()) {
    cout << "There is no todo with this [id].\n";
    return;
  }

  string todo_text = todos->at(id);
  int mark_pos = todo_text.find('[');
  todo_text[mark_pos+1] = 'X';

  (*todos)[id] = todo_text;

  return;
}

void uncheck_todo(vector<string> *todos, string *text) {
  if (todos->size() < 1) {
    cout << "There is no todo.\n";
    return;
  }
  
  size_t command_size = 8;
  int id = stoi(text->substr(command_size)) - 1;
  if (id < 0 || id >= todos->size()) {
    cout << "There is no todo with this [id].\n";
    return;
  }

  string todo_text = todos->at(id);
  int mark_pos = todo_text.find('X');
  todo_text[mark_pos] = ' ';

  (*todos)[id] = todo_text;

  return;
}

int main() {
  vector<string> todos;
  string command;

  cout << "Welcome to Todo App!\n\n";
  
  load_todos(&todos);
  print_todos(&todos);

  while(command != "quit") {
    cout << '\n' << "> ";
    getline(cin, command);

    if (command == "quit") continue;
    else if (command.rfind("help", 0) == 0) {
      cout << "Command list:\n- add [text] - Add new todo\n- check [id] - Mark todo as checked\n- uncheck [id] - Mark todo as unchecked\n- remove [id] - Remove todo\n";
      continue;
    }
    else if (command.rfind("add", 0) == 0) add_todo(&todos, &command);
    else if (command.rfind("remove", 0) == 0) remove_todo(&todos, &command);
    else if (command.rfind("check", 0) == 0) check_todo(&todos, &command);
    else if (command.rfind("uncheck", 0) == 0) uncheck_todo(&todos, &command);
    else {
      cout << "Unknown command.\nEnter 'help' to see a list of commands.\n\n";
      continue;
    };

    cout << '\n';
    print_todos(&todos);
  }

  cout << "\nQuited.\n";

  save_todos(&todos);

  cout << "All todos saved.\n";
}