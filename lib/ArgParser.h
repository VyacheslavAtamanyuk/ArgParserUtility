#pragma once
#include <string>
#include <vector>
#include <sstream>

namespace ArgumentParser {

    class IntArgument {
    public:
        IntArgument& AddIntArgument(const std::string& value);
        IntArgument& AddIntArgument(const char short_name, const std::string& value);
        IntArgument& AddIntArgument(const std::string &value, const std::string& message);
        int GetIntValue(const std::string& value) const;
        int GetIntValue(const std::string& value, size_t ind) const;
        IntArgument& MultiValue();
        IntArgument& MultiValue(const size_t min_args_count);
        IntArgument& Default(const int default_value);
        IntArgument& StoreValues(std::vector<int>& store_int);
        IntArgument& Positional();
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

    class FlagArgument {
    public:
        FlagArgument& AddFlag(const char short_name, const std::string& value);
        FlagArgument& AddFlag(const char short_name, const std::string& value, const std::string& message);
        FlagArgument& AddFlag(const std::string& value, const std::string& message);
        bool GetFlag(const std::string& value) const;
        FlagArgument& Default(const bool default_bool);
        FlagArgument& StoreValue(bool &store_bool);
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

    class StringArgument {
    public:
        StringArgument& AddStringArgument(const std::string& value);
        StringArgument& AddStringArgument(const char short_name, const std::string& value);
        StringArgument& AddStringArgument(const char short_name, const std::string& value, const std::string& message);
        std::string GetStringValue(const std::string& value) const;
        StringArgument& MultiValue();
        StringArgument& MultiValue(const size_t min_args_count);
        StringArgument& Default(const std::string& default_string);
        StringArgument& StoreValue(std::string& store_str);
    private:
        std::vector<bool> is_default;

        std::vector<bool> is_store;
        std::vector<std::string *> ptrs_to_store;

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
    public:
        ArgParser(const char* name);

        bool Parse(int argc, char **argv);
        bool Parse(const std::vector<std::string>& values);

        IntArgument& AddIntArgument(const std::string& value);
        IntArgument& AddIntArgument(const char short_name, const std::string& value);
        IntArgument& AddIntArgument(const std::string& value, const std::string& message);
        int GetIntValue(const std::string& value) const;
        int GetIntValue(const std::string& value, size_t ind) const;

        FlagArgument& AddFlag(const char short_name, const std::string& value);
        FlagArgument& AddFlag(const char short_name, const std::string& value, const std::string& message);
        FlagArgument& AddFlag(const std::string& value, const std::string& message);
        bool GetFlag(const std::string& value) const;

        StringArgument& AddStringArgument(const std::string& value);
        StringArgument& AddStringArgument(const char short_name, const std::string& value);
        StringArgument& AddStringArgument(const char short_name, const std::string& value, const std::string& message);
        std::string GetStringValue(const std::string& value) const;

        bool Help() const;
        void AddHelp(const char h, const char* help, const char* text);
        std::string HelpDescription() const;
    private:
        IntArgument class_int_for_parser;
        FlagArgument class_flag_for_parser;
        StringArgument class_string_for_parser;

        const char* name;
        bool is_help_is_requested;
        std::vector<const char*> commands_for_help;
    };
}