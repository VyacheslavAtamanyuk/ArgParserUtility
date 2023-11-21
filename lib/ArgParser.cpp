#include "ArgParser.h"
#include <iostream>
#include <string>

using namespace ArgumentParser;

const int kHereIsValueStart = 3;

// Методы класса IntArgument

IntArgument& IntArgument::AddIntArgument(const std::string& str) {
    short_keys.push_back(' ');
    keys.push_back(str);
    values.resize(keys.size());
    multivalues.resize(keys.size());
    is_multi.resize(keys.size());
    is_default.resize(keys.size());
    is_store.resize(keys.size());
    ptrs_to_stores.resize(keys.size());
    min_count_of_args.resize(keys.size());
    messages.resize(keys.size());
    is_message.push_back(false);
    last_added_argument = str;
    return *this;
}

IntArgument& IntArgument::AddIntArgument(char short_name, const std::string& str) {
    short_keys.push_back(short_name);
    keys.push_back(str);
    values.resize(keys.size());
    multivalues.resize(keys.size());
    is_multi.resize(keys.size());
    is_default.resize(keys.size());
    is_store.resize(keys.size());
    ptrs_to_stores.resize(keys.size());
    min_count_of_args.resize(keys.size());
    messages.resize(keys.size());
    is_message.push_back(false);
    last_added_argument = str;
    return *this;
}

IntArgument& IntArgument::AddIntArgument(const std::string& string_for_int, const std::string& message) {
    short_keys.push_back(' ');
    keys.push_back(string_for_int);
    values.resize(keys.size());
    multivalues.resize(keys.size());
    is_multi.resize(keys.size());
    is_default.resize(keys.size());
    is_store.resize(keys.size());
    ptrs_to_stores.resize(keys.size());
    min_count_of_args.resize(keys.size());
    messages.resize(keys.size());
    messages.back() = message;
    is_message.push_back(true);
    last_added_argument = string_for_int;
    return *this;
}

int IntArgument::GetIntValue(const std::string& string_for_int) const{
    int i = 0;
    while (keys[i] != string_for_int && i < keys.size()) {
        i++;
    }
    return values[i];
}

int IntArgument::GetIntValue(const std::string& string_for_int, size_t ind) const{
    for (int i = 0; i < keys.size(); ++i) {
        if (keys[i] == string_for_int) {
            return multivalues[i][ind];
        }
    }
}

IntArgument& IntArgument::MultiValue() {
    for (int i = 0; i < keys.size(); ++i) {
        if (keys[i] == last_added_argument) {
            is_multi[i] = true;
            min_count_of_args[i] = 1;
            break;
        }
    }
    return *this;
}

IntArgument& IntArgument::MultiValue(const size_t min_args_count) {
    for (int i = 0; i < keys.size(); ++i) {
        if (keys[i] == last_added_argument) {
            is_multi[i] = true;
            min_count_of_args[i] = min_args_count;
            break;
        }
    }
    return *this;
}

IntArgument& IntArgument::Default(const int default_value) {
    for (int i = 0; i < keys.size(); ++i) {
        if (keys[i] != last_added_argument) {
            continue;
        }
        if (keys[i] == last_added_argument) {
            if (is_multi[i]) {
                multivalues[i].push_back(default_value);
            } else {
                values[i] = default_value;
            }
            is_default[i] = true;
            break;
        }
    }
    return *this;
}

IntArgument& IntArgument::StoreValues(std::vector<int>& store_int) {
    for (int i = 0; i < keys.size(); ++i) {
        if (keys[i] == last_added_argument) {
            is_store[i] = true;
            ptrs_to_stores[i] = &store_int;
            break;
        }
    }
    return *this;
}

IntArgument& IntArgument::Positional() {
    is_positional = true;
    count_of_positionals++;
    which_arg_is_positional = last_added_argument;
    return *this;
}

//Методы класса FlagArgument

FlagArgument& FlagArgument::AddFlag(const char short_name, const std::string& string_for_flag) {
    short_keys.push_back(short_name);
    keys.push_back(string_for_flag);
    values.resize(keys.size());
    messages.resize(keys.size());
    is_message.resize(keys.size());
    is_message.push_back(false);
    is_default.resize(keys.size());
    is_store.resize(keys.size());
    ptrs_to_store.resize(keys.size());
    last_added_argument = string_for_flag;
    return *this;
}

FlagArgument& FlagArgument::AddFlag(const char short_name, const std::string &string_for_flag, const std::string &message) {
    short_keys.push_back(short_name);
    keys.push_back(string_for_flag);
    values.resize(keys.size());
    messages.resize(keys.size());
    messages.back() = message;
    is_message.resize(keys.size());
    is_message.push_back(true);
    is_default.resize(keys.size());
    is_store.resize(keys.size());
    ptrs_to_store.resize(keys.size());
    last_added_argument = string_for_flag;
    return *this;
}

FlagArgument& FlagArgument::AddFlag(const std::string& string_for_flag, const std::string& message) {
    short_keys.push_back(' ');
    keys.push_back(string_for_flag);
    values.resize(keys.size());
    messages.resize(keys.size());
    messages.back() = message;
    is_message.resize(keys.size());
    is_message.push_back(true);
    is_default.resize(keys.size());
    is_store.resize(keys.size());
    ptrs_to_store.resize(keys.size());
    last_added_argument = string_for_flag;
    return *this;
}

bool FlagArgument::GetFlag(const std::string& string_for_flag) const{
    for (int i = 0; i < keys.size(); ++i) {
        if (keys[i] == string_for_flag) {
            return values[i];
        }
    }
}

FlagArgument& FlagArgument::Default(const bool default_bool) {
    for (int i = 0; i < keys.size(); ++i) {
        if (keys[i] == last_added_argument) {
            values[i] = default_bool;
            is_default[i] = true;
            break;
        }
    }
    return *this;
}

FlagArgument& FlagArgument::StoreValue(bool& store_bool) {
    for (int i = 0; i < keys.size(); ++i) {
        if (keys[i] == last_added_argument) {
            is_store[i] = true;
            ptrs_to_store[i] = &store_bool;
            break;
        }
    }
    return *this;
}

//Методы класса StringArgument

StringArgument& StringArgument::AddStringArgument(const std::string &string_for_string) {
    short_keys.push_back(' ');
    keys.push_back(string_for_string);
    values.resize(keys.size());
    multivalues.resize(keys.size());
    is_multi.resize(keys.size());
    is_default.resize(keys.size());
    is_store.resize(keys.size());
    ptrs_to_store.resize(keys.size());
    min_count_of_args.resize(keys.size());
    last_added_argument = string_for_string;
    return *this;
}

StringArgument& StringArgument::AddStringArgument(const char short_name, const std::string &string_for_string) {
    short_keys.push_back(short_name);
    keys.push_back(string_for_string);
    values.resize(keys.size());
    multivalues.resize(keys.size());
    is_multi.resize(keys.size());
    is_default.resize(keys.size());
    is_store.resize(keys.size());
    ptrs_to_store.resize(keys.size());
    min_count_of_args.resize(keys.size());
    last_added_argument = string_for_string;
    return *this;
}

StringArgument& StringArgument::AddStringArgument(const char short_name, const std::string& string_for_string, const std::string& message) {
    short_keys.push_back(short_name);
    keys.push_back(string_for_string);
    values.resize(keys.size());
    multivalues.resize(keys.size());
    is_multi.resize(keys.size());
    multivalues.back().push_back(message);
    is_multi.back() = true;
    is_default.resize(keys.size());
    is_store.resize(keys.size());
    ptrs_to_store.resize(keys.size());
    min_count_of_args.resize(keys.size());
    last_added_argument = string_for_string;
    return *this;
}

std::string StringArgument::GetStringValue(const std::string& string_for_string) const{
    for (int i = 0; i < keys.size(); ++i) {
        if (keys[i] == string_for_string) {
            return values[i];
        }
    }
}

StringArgument& StringArgument::MultiValue() {
    for (int i = 0; i < keys.size(); ++i) {
        if (keys[i] == last_added_argument) {
            is_multi[i] = true;
            break;
        }
    }
    return *this;
}

StringArgument& StringArgument::MultiValue(const size_t min_args_count) {
    for (int i = 0; i < keys.size(); ++i) {
        if (keys[i] == last_added_argument) {
            is_multi[i] = true;
            min_count_of_args[i] = min_args_count;
            break;
        }
    }
    return *this;
}

StringArgument& StringArgument::Default(const std::string& default_string) {
    for (int i = 0; i < keys.size(); ++i) {
        if (keys[i] == last_added_argument) {
            if (is_multi[i]) {
                multivalues[i].push_back(default_string);
            } else {
                values[i] = default_string;
            }
            is_default[i] = true;
        }
    }
    return *this;
}

StringArgument& StringArgument::StoreValue(std::string& store_str) {
    for (int i = 0; i < keys.size(); ++i) {
        if (keys[i] == last_added_argument) {
            is_store[i] = true;
            ptrs_to_store[i] = &store_str;
            break;
        }
    }
    return *this;
}


// Методы класса ArgParser

ArgParser::ArgParser(const char* name) {
    ArgParser::name = name;
}

bool ArgParser::Parse(const std::vector<std::string>& values) {
    for (int i = 1; i < values.size(); ++i) {
        bool is_it_string_value = false;
        bool is_it_flag_value = false;
        bool is_it_int_value = false;
        size_t ind_for_int_key;
        size_t ind_for_str_key;
        size_t ind_for_flag_key;
        if (values[i][0] == '-' && values[i][1] == '-') {
            std::string key;
            int j = 2;
            while (values[i][j] != '=' && j < values[i].size()) {
                key.push_back(values[i][j]);
                ++j;
            }
            for (int x = 0; x < class_int_for_parser.keys.size(); ++x) {
                if (class_int_for_parser.keys[x] == key) {
                    continue;
                }
                is_it_int_value = true;
                ind_for_int_key = x;
                break;
            }
            for (int x = 0; x < class_flag_for_parser.keys.size(); ++x) {
                if (class_flag_for_parser.keys[x] != key) {
                    continue;
                }
                is_it_flag_value = true;
                ind_for_flag_key = x;
                break;
            }
            for (int x = 0; x < class_string_for_parser.keys.size(); ++x) {
                if (class_string_for_parser.keys[x] != key) {
                    continue;
                }
                is_it_string_value = true;
                ind_for_str_key = x;
                break;
            }
            ++j;
            if (is_it_int_value) {
                const char* new_str = values[i].c_str();
                char* p_end{};
                int our_value = std::strtol(new_str + j, &p_end, 10);
                if (!class_int_for_parser.is_multi[ind_for_int_key]) {
                    class_int_for_parser.values[ind_for_int_key] = our_value;
                } else {
                    class_int_for_parser.multivalues[ind_for_int_key].push_back(our_value);
                    if (class_int_for_parser.is_store[ind_for_int_key]) {
                        class_int_for_parser.ptrs_to_stores[ind_for_int_key]->push_back(our_value);
                    }
                }
            } else if (is_it_string_value) {
                if (!class_string_for_parser.is_multi[ind_for_str_key]) {
                    class_string_for_parser.values[ind_for_str_key] = values[i].substr(j);
                    if (class_string_for_parser.is_store[ind_for_str_key]) {
                        *class_string_for_parser.ptrs_to_store[ind_for_str_key] = values[i].substr(j);
                    }
                } else {
                    class_string_for_parser.multivalues[ind_for_str_key].push_back(values[i].substr(j));
                }
            } else if (is_it_flag_value) {
                class_flag_for_parser.values[ind_for_flag_key] = true;
                if (class_flag_for_parser.is_store[ind_for_flag_key]) {
                    *class_flag_for_parser.ptrs_to_store[ind_for_flag_key] = true;
                }
            }
        } else if (values[i][0] == '-' && values[i][1] != '-') {
            char short_name = values[i][1];
            std::string value;
            for (int x = 0; x < class_string_for_parser.short_keys.size(); ++x) {
                if (class_string_for_parser.short_keys[x] != short_name) {
                    continue;
                }
                is_it_string_value = true;
                ind_for_str_key = x;
                break;
            }
            for (int x = 0; x < class_int_for_parser.short_keys.size(); ++x) {
                if (class_int_for_parser.short_keys[x] != short_name) {
                    continue;
                }
                is_it_int_value = true;
                ind_for_int_key = x;
                break;
            }
            for (int x = 0; x < class_flag_for_parser.short_keys.size(); ++x) {
                if (class_flag_for_parser.short_keys[x] != short_name) {
                    continue;
                }
                is_it_flag_value = true;
                ind_for_flag_key = x;
                break;
            }
            if (is_it_string_value) {
                if (!class_string_for_parser.is_multi[ind_for_str_key]) {
                    class_string_for_parser.values[ind_for_str_key] = values[i].substr(kHereIsValueStart);
                } else {
                    class_string_for_parser.multivalues[ind_for_str_key].push_back(values[i].substr(kHereIsValueStart));
                    if (class_string_for_parser.is_store[ind_for_str_key]) {
                        *class_string_for_parser.ptrs_to_store[ind_for_str_key] = values[i].substr(kHereIsValueStart);
                    }
                }
            } else if (is_it_int_value) {
                const char* new_str = values[i].c_str();
                char* p_end{};
                long our_value = std::strtol(new_str + kHereIsValueStart, &p_end, 10);
                if (!class_int_for_parser.is_multi[ind_for_int_key]) {
                    class_int_for_parser.values[ind_for_int_key] = our_value;
                } else {
                    class_int_for_parser.multivalues[ind_for_int_key].push_back(our_value);
                    if (class_int_for_parser.is_store[ind_for_int_key]) {
                        class_int_for_parser.ptrs_to_stores[ind_for_int_key]->push_back(our_value);
                    }
                }
            } else if (is_it_flag_value) {
                for (size_t lets_turn_on_flags = 1; lets_turn_on_flags < values[i].size(); ++lets_turn_on_flags) {
                    for (size_t search_flag = 0; search_flag < class_flag_for_parser.short_keys.size(); ++search_flag) {
                        if (class_flag_for_parser.short_keys[search_flag] != values[i][lets_turn_on_flags]) {
                            continue;
                        }
                        class_flag_for_parser.values[search_flag] = true;
                        if (class_flag_for_parser.is_store[search_flag]) {
                            *class_flag_for_parser.ptrs_to_store[search_flag] = true;
                        }
                    }
                }
            }
        } else if (values[i][0] != '-') {
            for (int j = 0; j < class_int_for_parser.keys.size(); ++j) {
                if (class_int_for_parser.keys[j] != class_int_for_parser.which_arg_is_positional) {
                    continue;
                }
                class_int_for_parser.ptrs_to_stores[j]->push_back(std::stoi(values[i]));
                if (class_int_for_parser.is_multi[j]) {
                    class_int_for_parser.multivalues[j].push_back(std::stoi(values[i]));
                }
            }
        }
    }
    if (values.size() == 1) {
        for (int x = 0; x < class_int_for_parser.keys.size(); ++x) {
            if (!class_int_for_parser.is_default[x]) {
                return false;
            }
        }
        for (int x = 0; x < class_string_for_parser.keys.size(); ++x) {
            if (!class_string_for_parser.is_default[x]) {
                return false;
            }
        }
        for (int x = 0; x < class_flag_for_parser.keys.size(); ++x) {
            if (!class_flag_for_parser.is_default[x]) {
                return false;
            }
        }
    }
    for (int x = 0; x < std::max(class_string_for_parser.keys.size(), class_int_for_parser.keys.size()); ++x) {
        if (x < class_int_for_parser.keys.size() && class_int_for_parser.is_multi[x] && (class_int_for_parser.multivalues[x].size() < class_int_for_parser.min_count_of_args[x])) {
            return false;
        }
        if (x < class_string_for_parser.keys.size() && class_string_for_parser.is_multi[x] && (class_string_for_parser.multivalues[x].size() < class_string_for_parser.min_count_of_args[x])) {
            return false;
        }
    }
    if (class_int_for_parser.count_of_positionals > 1) {
        return false;
    }
    return true;
}

bool ArgParser::Parse(int argc, char** argv){
    std::vector<std::string> new_vector(argv, argc + argv);
    return ArgParser::Parse(new_vector);
}

IntArgument& ArgParser::AddIntArgument(const std::string &str) {
    return class_int_for_parser.AddIntArgument(str);
}

IntArgument& ArgParser::AddIntArgument(const char short_name, const std::string &string_for_int) {
    return class_int_for_parser.AddIntArgument(short_name, string_for_int);
}

IntArgument& ArgParser::AddIntArgument(const std::string& string_for_int, const std::string& message) {
    return class_int_for_parser.AddIntArgument(string_for_int, message);
}

int ArgParser::GetIntValue(const std::string &string_for_int) const {
    return class_int_for_parser.GetIntValue(string_for_int);
}

int ArgParser::GetIntValue(const std::string &string_for_int, size_t ind) const {
    return class_int_for_parser.GetIntValue(string_for_int, ind);
}

FlagArgument& ArgParser::AddFlag(const char short_name, const std::string &string_for_flag) {
    return class_flag_for_parser.AddFlag(short_name, string_for_flag);
}

FlagArgument& ArgParser::AddFlag(const char short_name, const std::string &string_for_flag, const std::string &message) {
    return class_flag_for_parser.AddFlag(short_name, string_for_flag, message);
}

FlagArgument& ArgParser::AddFlag(const std::string &string_for_flag, const std::string &message) {
    return class_flag_for_parser.AddFlag(string_for_flag, message);
}

bool ArgParser::GetFlag(const std::string &string_for_flag) const{
    return class_flag_for_parser.GetFlag(string_for_flag);
}

StringArgument& ArgParser::AddStringArgument(const std::string& string_for_string) {
    return class_string_for_parser.AddStringArgument(string_for_string);
}

StringArgument& ArgParser::AddStringArgument(const char short_name, const std::string &string_for_string) {
    return class_string_for_parser.AddStringArgument(short_name, string_for_string);
}

StringArgument& ArgParser::AddStringArgument(const char short_name, const std::string& string_for_string, const std::string& message) {
    return class_string_for_parser.AddStringArgument(short_name, string_for_string, message);
};

std::string ArgParser::GetStringValue(const std::string& string_for_string) const{
    return class_string_for_parser.GetStringValue(string_for_string);
}

bool ArgParser::Help() const{
    return ArgParser::is_help_is_requested;
}

void ArgParser::AddHelp(const char h, const char* help, const char* text) {
    ArgParser::is_help_is_requested = true;
    ArgParser::commands_for_help.push_back(&h);
    ArgParser::commands_for_help.push_back(help);
    ArgParser::commands_for_help.push_back(text);
}

std::string ArgParser::HelpDescription() const{
    std::ostringstream data;
    data << ArgParser::name << '\n';
    data << ArgParser::commands_for_help[2] << '\n';
    data << '\n';
    for (int i = 0; i < class_string_for_parser.keys.size(); ++i) {
        if (class_string_for_parser.short_keys[i] != ' ') {
            data << '-' << class_string_for_parser.short_keys[i] << ",  ";
        }
        if (!class_string_for_parser.keys[i].empty()) {
            data << ",  --" << class_string_for_parser.keys[i] << "=<string>,  " << class_string_for_parser.values[i] << ",  ";
        }
        if (class_string_for_parser.is_multi[i]) {
            data << "[repeated, min args = " << class_string_for_parser.min_count_of_args[i] << "]";
        }
        data << '\n';
    }
    for(int i = 0; i < class_flag_for_parser.keys.size(); ++i) {
        if (class_flag_for_parser.short_keys[i] != ' ') {
            data << '-' << class_flag_for_parser.short_keys[i] << ",  ";
        }
        if (!class_flag_for_parser.keys[i].empty()) {
            data << "--" << class_flag_for_parser.keys[i] << ",  " << class_flag_for_parser.values[i] << ",  ";
        }
        if (class_flag_for_parser.is_message[i]) {
            data << class_flag_for_parser.messages[i] << ",  ";
        }
        if (class_flag_for_parser.is_default[i]) {
            data << "[default = " << class_flag_for_parser.values[i] << "]";
        }
        data << '\n';
    }
    for (int i = 0; i < class_int_for_parser.keys.size(); ++i) {
        if (class_int_for_parser.short_keys[i] != ' ') {
            data << '-' << class_int_for_parser.short_keys[i] << ",  ";
        }
        if (!class_int_for_parser.keys[i].empty()) {
            data << "--" << class_int_for_parser.keys[i] << "=<int>,  " << class_int_for_parser.values[i] << ",  ";
        }
        if (class_int_for_parser.is_message[i]) {
            data << class_int_for_parser.messages[i] << ",  ";
        }
        if (class_int_for_parser.is_default[i]) {
            data << "[default = ";
            if (!class_int_for_parser.is_multi[i]) {
                data << class_int_for_parser.values[i] << "]";
            } else {
                data << '{';
                for (int j = 0; j < class_int_for_parser.multivalues[i].size(); ++j) {
                    data << class_int_for_parser.multivalues[i][j] << ' ';
                }
                data << "}]";
            }
        }
        data << '\n';
    }
    data << '-' << commands_for_help[0] << ", --" << commands_for_help[1] << " Display this help and exit '\n'";
    return data.str();
}
