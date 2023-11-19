#pragma once
#include <string>
#include <vector>
#include <sstream>

namespace ArgumentParser {

    class IntArg {
    public:
        IntArg& AddIntArgument(const std::string& string_for_int);
        IntArg& AddIntArgument(const char short_name, const std::string& string_for_int);
        IntArg& AddIntArgument(const std::string& string_for_int, const std::string& message);
        int GetIntValue(const std::string& string_for_int) const;
        int GetIntValue(const std::string& string_for_int, size_t ind) const;
        IntArg& MultiValue();
        IntArg& MultiValue(const size_t& min_args_count);
        IntArg& Default(const int default_value);
        IntArg& StoreValues(std::vector<int>& store_int);
        IntArg& Positional();
    private:
        std::vector<bool> is_default;
        std::vector<bool> is_store;
        std::vector<std::vector<int>*> ptrs_to_stores;
        std::vector<char> short_keys;
        std::vector<std::string> keys;
        std::vector<int> values;
        std::vector<bool> is_multi;
        std::vector<std::vector<int>> multivalues;
        std::vector<size_t> min_count_of_args;
        std::vector<bool> is_message;
        std::vector<std::string> messages;
        bool is_positional;
        size_t count_of_positionals = 0;
        std::string which_arg_is_positional;
        std::string last_added_argument;
        friend class ArgParser;
    };

    class FlagArg {
    public:
        FlagArg& AddFlag(const char short_name, const std::string& string_for_flag);
        FlagArg& AddFlag(const char short_name, const std::string& string_for_flag, const std::string& message);
        FlagArg& AddFlag(const std::string& string_for_flag, const std::string& message);
        bool GetFlag(const std::string& string_for_flag) const;
        FlagArg& Default(const bool default_bool);
        FlagArg& StoreValue(bool& store_bool);
    private:
        std::vector<bool> is_default;
        std::vector<bool> is_store;
        std::vector<bool*> ptrs_to_store;
        std::vector<char> short_keys;
        std::vector<std::string> keys;
        std::vector<bool> values;
        std::vector<bool> is_message;
        std::vector<std::string> messages;
        std::string last_added_argument;
        friend class ArgParser;
    };

    class StringArg {
    public:
        StringArg& AddStringArgument(const std::string& string_for_string);
        StringArg& AddStringArgument(const char short_name, const std::string& string_for_string);
        StringArg& AddStringArgument(const char short_name, const std::string& string_for_string, const std::string& message);
        std::string GetStringValue(const std::string& string_for_string) const;
        StringArg& MultiValue();
        StringArg& MultiValue(const size_t& min_args_count);
        StringArg& Default(const std::string& default_string);
        StringArg& StoreValue(std::string& store_str);
    private:
        std::vector<bool> is_default;
        std::vector<bool> is_store;
        std::vector<std::string*> ptrs_to_store;
        std::vector<char> short_keys;
        std::vector<std::string> keys;
        std::vector<std::string> values;
        std::vector<bool> is_multi;
        std::vector<std::vector<std::string>> multivalues;
        std::vector<size_t> min_count_of_args;
        std::string last_added_argument;
        friend class ArgParser;
    };

    class ArgParser {
    private:
        IntArg class_int_for_parser;
        FlagArg class_flag_for_parser;
        StringArg class_string_for_parser;
        const char* name_of_this_parser;
        bool is_help_is_requested;
        std::vector<const char*> commands_for_help;
    public:
        ArgParser(const char* name_of_this_parser);
        bool Parse(int argc, char** argv);
        bool Parse(std::vector<std::string> values);
        IntArg& AddIntArgument(const std::string& string_for_int);
        IntArg& AddIntArgument(const char short_name, const std::string& string_for_int);
        IntArg& AddIntArgument(const std::string& string_for_int, const std::string& message);
        int GetIntValue(const std::string& string_for_int) const;
        int GetIntValue(const std::string& string_for_int, size_t ind) const;
        FlagArg& AddFlag(const char short_name, const std::string& string_for_flag);
        FlagArg& AddFlag(const char short_name, const std::string& string_for_flag, const std::string& message);
        FlagArg& AddFlag(const std::string& string_for_flag, const std::string& message);
        bool GetFlag(const std::string& string_for_flag) const;
        StringArg& AddStringArgument(const std::string& string_for_string);
        StringArg& AddStringArgument(const char short_name, const std::string& string_for_string);
        StringArg& AddStringArgument(const char short_name, const std::string& string_for_string, const std::string& message);
        std::string GetStringValue(const std::string& string_for_string) const;
        bool Help();
        void AddHelp(const char h, const char* help, const char* text);
        std::string HelpDescription() const;
    };

}