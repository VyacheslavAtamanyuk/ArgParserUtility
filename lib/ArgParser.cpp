#include "ArgParser.h"
#include <iostream>
#include <string>

using namespace ArgumentParser;

const int kHereIsValueStart = 3;

// Конструкторы класса IntArgument

IntArgument::IntArgument(const std::string& val) {
    key = val;
}

IntArgument::IntArgument(const char short_value, const std::string& val) {
    short_key = short_value;
    key = val;
}

IntArgument::IntArgument(const std::string& val, const std::string& the_message) {
    key = val;
    message = the_message;
}


//Конструкторы класса FlagArgument

FlagArgument::FlagArgument(const char short_val, const std::string &val) {
    short_key = short_val;
    key = val;
}

FlagArgument::FlagArgument(const std::string &val, const std::string &the_message) {
    key = val;
    message = the_message;
}

FlagArgument::FlagArgument(const char short_val, const std::string &val, const std::string &the_message) {
    short_key = short_val;
    key = val;
    message = the_message;
}

//Конструкторы класса StringArgument

StringArgument::StringArgument(const std::string &name) {
    key = name;
}

StringArgument::StringArgument(const char short_name, const std::string &name) {
    short_key = short_name;
    key = name;
}

StringArgument::StringArgument(const char short_name, const std::string &name, const std::string &the_message) {
    short_key = short_name;
    key = name;
    multivalues.push_back(the_message);
}


// Методы класса ArgParser

ArgParser::ArgParser(const char* another_name) {
    parser_name = another_name;
}

bool ArgParser::Parse(const std::vector<std::string>& args) {
    for (int i = 1; i < args.size(); ++i) {
        bool is_it_string_value = false;
        bool is_it_flag_value = false;
        bool is_it_int_value = false;
        size_t ind_for_int_key;
        size_t ind_for_str_key;
        size_t ind_for_flag_key;
        if (args[i][0] == '-' && args[i][1] == '-') {
            std::string parser_key;
            int j = 2;
            while (args[i][j] != '=' && j < args[i].size()) {
                parser_key.push_back(args[i][j]);
                ++j;
            }
            for (int x = 0; x < int_args.size(); ++x) {
                if (int_args[x].key != parser_key) {
                    continue;
                }
                is_it_int_value = true;
                ind_for_int_key = x;
                break;
            }
            for (int x = 0; x < flag_args.size(); ++x) {
                if (flag_args[x].key != parser_key) {
                    continue;
                }
                is_it_flag_value = true;
                ind_for_flag_key = x;
                break;
            }
            for (int x = 0; x < string_args.size(); ++x) {
                if (string_args[x].key != parser_key) {
                    continue;
                }
                is_it_string_value = true;
                ind_for_str_key = x;
                break;
            }
            ++j;
            if (is_it_int_value) {
                const char* new_str = args[i].c_str();
                char* p_end{};
                int our_value = std::strtol(new_str + j, &p_end, 10);
                if (!int_args[ind_for_int_key].is_multi) {
                    int_args[ind_for_int_key].value = our_value;
                } else {
                    int_args[ind_for_int_key].multivalues.push_back(our_value);
                    if (int_args[ind_for_int_key].is_store) {
                        int_args[ind_for_int_key].ptr_to_store->push_back(our_value);
                    }
                }
            } else if (is_it_string_value) {
                if (!string_args[ind_for_str_key].is_multi) {
                    string_args[ind_for_str_key].value = args[i].substr(j);
                    if (string_args[ind_for_str_key].is_store) {
                        *string_args[ind_for_str_key].ptr_to_store = args[i].substr(j);
                    }
                } else {
                    string_args[ind_for_str_key].multivalues.push_back(args[i].substr(j));
                }
            } else if (is_it_flag_value) {
                flag_args[ind_for_flag_key].value = true;
                if (flag_args[ind_for_flag_key].is_store) {
                    *flag_args[ind_for_flag_key].ptr_to_store = true;
                }
            }
        } else if (args[i][0] == '-' && args[i][1] != '-') {
            char short_name = args[i][1];
            std::string value;
            for (int x = 0; x < string_args.size(); ++x) {
                if (string_args[x].short_key != short_name) {
                    continue;
                }
                is_it_string_value = true;
                ind_for_str_key = x;
                break;
            }
            for (int x = 0; x < int_args.size(); ++x) {
                if (int_args[x].short_key != short_name) {
                    continue;
                }
                is_it_int_value = true;
                ind_for_int_key = x;
                break;
            }
            for (int x = 0; x < flag_args.size(); ++x) {
                if (flag_args[x].short_key != short_name) {
                    continue;
                }
                is_it_flag_value = true;
                ind_for_flag_key = x;
                break;
            }
            if (is_it_string_value) {
                if (!string_args[ind_for_str_key].is_multi) {
                    string_args[ind_for_str_key].value = args[i].substr(kHereIsValueStart);
                } else {
                    string_args[ind_for_str_key].multivalues.push_back(args[i].substr(kHereIsValueStart));
                    if (string_args[ind_for_str_key].is_store) {
                        *string_args[ind_for_str_key].ptr_to_store = args[i].substr(kHereIsValueStart);
                    }
                }
            } else if (is_it_int_value) {
                const char* new_str = args[i].c_str();
                char* p_end{};
                long our_value = std::strtol(new_str + kHereIsValueStart, &p_end, 10);
                if (!int_args[ind_for_int_key].is_multi) {
                    int_args[ind_for_int_key].value = our_value;
                } else {
                    int_args[ind_for_int_key].multivalues.push_back(our_value);
                    if (int_args[ind_for_int_key].is_store) {
                        int_args[ind_for_int_key].ptr_to_store->push_back(our_value);
                    }
                }
            } else if (is_it_flag_value) {
                for (size_t lets_turn_on_flags = 1; lets_turn_on_flags < args[i].size(); ++lets_turn_on_flags) {
                    for (size_t search_flag = 0; search_flag < flag_args.size(); ++search_flag) {
                        if (flag_args[search_flag].short_key != args[i][lets_turn_on_flags]) {
                            continue;
                        }
                        flag_args[search_flag].value = true;
                        if (flag_args[search_flag].is_store) {
                            *flag_args[search_flag].ptr_to_store = true;
                        }
                    }
                }
            }
        } else if (args[i][0] != '-') {
            for (int j = 0; j < int_args.size(); ++j) {
                if (!int_args[j].is_positional) {
                    continue;
                }
                int_args[j].ptr_to_store->push_back(std::stoi(args[i]));
                if (int_args[j].is_multi) {
                    int_args[j].multivalues.push_back(std::stoi(args[i]));
                }
            }
        }
    }
    if (args.size() == 1) {
        for (int x = 0; x < int_args.size(); ++x) {
            if (!int_args[x].is_default) {
                return false;
            }
        }
        for (int x = 0; x < string_args.size(); ++x) {
            if (!string_args[x].is_default) {
                return false;
            }
        }
        for (int x = 0; x < flag_args.size(); ++x) {
            if (!flag_args[x].is_default) {
                return false;
            }
        }
    }
    for (int x = 0; x < std::max(string_args.size(), int_args.size()); ++x) {
        if (x < int_args.size() && int_args[x].is_multi && (int_args[x].multivalues.size() < int_args[x].min_count_of_args)) {
            return false;
        }
        if (x < string_args.size() && string_args[x].is_multi && (string_args[x].multivalues.size() < string_args[x].min_count_of_args)) {
            return false;
        }
    }
    if (count_of_int_positionals > 1) {
        return false;
    }
    return true;
}

bool ArgParser::Parse(int argc, char** argv){
    std::vector<std::string> new_vector(argv, argc + argv);
    return ArgParser::Parse(new_vector);
}

// MultiValue и Default рассмотрены отдельно

ArgParser& ArgParser::MultiValue() {
    if (str_with_last_type == "string") {
        ArgParser::string_args.back().is_multi = true;
        ArgParser::string_args.back().min_count_of_args = 1;
    } else if (str_with_last_type == "int") {
        int_args.back().is_multi = true;
        int_args.back().min_count_of_args = 1;
    }
    return *this;
}

ArgParser& ArgParser::MultiValue(const size_t min_args_count) {
    if (str_with_last_type == "string") {
        ArgParser::string_args.back().is_multi = true;
        ArgParser::string_args.back().min_count_of_args = min_args_count;
    } else if (str_with_last_type == "int") {
        int_args.back().is_multi = true;
        int_args.back().min_count_of_args = min_args_count;
    }
    return *this;
}

ArgParser& ArgParser::Default(const int default_val) {
    int_args.back().is_default = true;
    if (int_args.back().is_multi) {
        int_args.back().multivalues.push_back(default_val);
    } else {
        int_args.back().value = default_val;
    }
    return *this;
}

ArgParser& ArgParser::Default(const char* default_val) {
    ArgParser::string_args.back().is_default = true;
    if (ArgParser::string_args.back().is_multi) {
        ArgParser::string_args.back().multivalues.push_back(default_val);
    } else {
        ArgParser::string_args.back().value = default_val;
    }
    return *this;
}

ArgParser& ArgParser::Default(const bool default_val) {
    flag_args.back().is_default = true;
    flag_args.back().value = default_val;
    return *this;
}

//Методы для типа int

ArgParser& ArgParser::AddIntArgument(const std::string& val) {
    IntArgument new_arg(val);
    int_args.push_back(new_arg);
    str_with_last_type = "int";
    return *this;
}

ArgParser& ArgParser::AddIntArgument(char short_val, const std::string& val) {
    IntArgument new_arg(short_val, val);
    int_args.push_back(new_arg);
    str_with_last_type = "int";
    return *this;
}

ArgParser& ArgParser::AddIntArgument(const std::string& val, const std::string& the_message) {
    IntArgument new_arg(val, the_message);
    int_args.push_back(new_arg);
    str_with_last_type = "int";
    return *this;
}

int ArgParser::GetIntValue(const std::string& val) const{
    int i = 0;
    while (int_args[i].key != val && i < int_args.size()) {
        ++i;
    }
    return int_args[i].value;
}

int ArgParser::GetIntValue(const std::string& val, size_t ind) const{
    int i = 0;
    while (int_args[i].key != val && i < int_args.size()) {
        ++i;
    }
    return int_args[i].multivalues[ind];
}

ArgParser& ArgParser::StoreValues(std::vector<int>& store_int) {
    int_args.back().is_store = true;
    int_args.back().ptr_to_store = &store_int;
    return *this;
}

ArgParser& ArgParser::Positional() {
    int_args.back().is_positional = true;
    count_of_int_positionals++;
    return *this;
}

// Методы для типа bool

ArgParser& ArgParser::AddFlag(const char short_val, const std::string& val) {
    FlagArgument new_arg(short_val, val);
    flag_args.push_back(new_arg);
    str_with_last_type = "flag";
    return *this;
}

ArgParser& ArgParser::AddFlag(const char short_val, const std::string& val, const std::string& the_message) {
    FlagArgument new_arg(short_val, val, the_message);
    flag_args.push_back(new_arg);
    str_with_last_type = "flag";
    return *this;
}

ArgParser& ArgParser::AddFlag(const std::string& val, const std::string& the_message) {
    FlagArgument new_arg(val, the_message);
    flag_args.push_back(new_arg);
    str_with_last_type = "flag";
    return *this;
}

bool ArgParser::GetFlag(const std::string& val) const{
    int i = 0;
    while (flag_args[i].key != val && i < flag_args.size()) {
        ++i;
    }
    return flag_args[i].value;
}

ArgParser& ArgParser::StoreValue(bool& store_bool) {
    flag_args.back().is_store = true;
    flag_args.back().ptr_to_store = &store_bool;
    return *this;
}

//Методы для типа string

ArgParser& ArgParser::AddStringArgument(const std::string& val) {
    StringArgument new_arg(val);
    string_args.push_back(new_arg);
    str_with_last_type = "string";
    return *this;
}

ArgParser& ArgParser::AddStringArgument(const char short_val, const std::string& val) {
    StringArgument new_arg(short_val, val);
    string_args.push_back(new_arg);
    str_with_last_type = "string";
    return *this;
}

ArgParser& ArgParser::AddStringArgument(const char short_val, const std::string& val, const std::string& the_message) {
    StringArgument new_arg(short_val, val, the_message);
    string_args.push_back(new_arg);
    str_with_last_type = "string";
    return *this;
}

std::string ArgParser::GetStringValue(const std::string& name) const{
    int i = 0;
    while (ArgParser::string_args[i].key != name && i < ArgParser::string_args.size()) {
        ++i;
    }
    return ArgParser::string_args[i].value;
}

ArgParser& ArgParser::StoreValue(std::string& store_str) {
    string_args.back().is_store = true;
    string_args.back().ptr_to_store = &store_str;
    return *this;
}

// Help commands

bool ArgParser::Help() const{
    return is_help_is_requested;
}

void ArgParser::AddHelp(const char h, const char* help, const char* text) {
    is_help_is_requested = true;
    commands_for_help.push_back(&h);
    commands_for_help.push_back(help);
    commands_for_help.push_back(text);
}

std::string ArgParser::HelpDescription() const{
    std::ostringstream data;
    data << parser_name << '\n';
    data << commands_for_help[2] << '\n';
    data << '\n';
    for (int i = 0; i < string_args.size(); ++i) {
        if (string_args[i].short_key != ' ') {
            data << '-' << string_args[i].short_key << ",  ";
        }
        if (string_args[i].key != " ") {
            data << ",  --" << string_args[i].key << "=<string>,  " << string_args[i].value << ",  ";
        }
        if (string_args[i].is_multi) {
            data << "[repeated, min args = " << string_args[i].min_count_of_args << "]";
        }
        data << '\n';
    }
    for (int i = 0; i < flag_args.size(); ++i) {
        if (flag_args[i].short_key != ' ') {
            data << '-' << flag_args[i].short_key << ",  ";
        }
        if (flag_args[i].key != " ") {
            data << "--" << flag_args[i].key << ",  " << flag_args[i].value << ",  ";
        }
        if (flag_args[i].is_message) {
            data << flag_args[i].message << ",  ";
        }
        if (flag_args[i].is_default) {
            data << "[default = " << flag_args[i].value << "]";
        }
        data << '\n';
    }
    for (int i = 0; i < int_args.size(); ++i) {
        if (int_args[i].short_key != ' ') {
            data << '-' << int_args[i].short_key << ",  ";
        }
        if (int_args[i].key != " ") {
            data << "--" << int_args[i].key << "=<int>,  " << int_args[i].value << ",  ";
        }
        if (int_args[i].is_message) {
            data << int_args[i].message << ",  ";
        }
        if (int_args[i].is_default) {
            data << "[default = ";
            if (!int_args[i].is_multi) {
                data << int_args[i].value << "]";
            } else {
                data << '{';
                for (int j = 0; j < int_args[i].multivalues.size(); ++j) {
                    data << int_args[i].multivalues[j] << ' ';
                }
                data << "}]";
            }
        }
        data << '\n';
    }
    data << '-' << commands_for_help[0] << ", --" << commands_for_help[1] << " Display this help and exit '\n'";
    return data.str();
}
