#pragma once
#include <string>
#include <vector>
#include <sstream>

namespace ArgumentParser {

    class IntArgument {
    public:
        IntArgument(const std::string& name);
        IntArgument(const char short_name, const std::string& name);
        IntArgument(const std::string& name, const std::string& the_message);
    private:
        bool is_default = false;

        bool is_store = false;
        std::vector<int>* ptr_to_store = nullptr;

        char short_key = ' ';
        std::string key = " ";
        int value = 0;

        bool is_multi = false;
        std::vector<int> multivalues;
        size_t min_count_of_args = 0;

        bool is_message = false;
        std::string message = " ";

        bool is_positional = false;

        friend class ArgParser;
    };

    class FlagArgument {
    public:
        FlagArgument(const char short_name, const std::string& name);
        FlagArgument(const char short_name, const std::string& name, const std::string& the_message);
        FlagArgument(const std::string& name, const std::string& the_message);
    private:
        bool is_default = false;

        bool is_store = false;
        bool* ptr_to_store = nullptr;

        char short_key = ' ';
        std::string key = " ";
        bool value = false;

        bool is_message = false;
        std::string message = " ";

        friend class ArgParser;
    };

    class StringArgument {
    public:
        StringArgument(const std::string& name);
        StringArgument(const char short_name, const std::string& name);
        StringArgument(const char short_name, const std::string& name, const std::string& the_message);
    private:
        bool is_default = false;

        bool is_store = false;
        std::string* ptr_to_store = nullptr;

        char short_key = ' ';
        std::string key = " ";
        std::string value = " ";

        bool is_multi = false;
        std::vector<std::string> multivalues;
        size_t min_count_of_args = 0;

        friend class ArgParser;
    };

    class ArgParser {
    public:
        ArgParser(const char* name);

        bool Parse(int argc, char **argv);
        bool Parse(const std::vector<std::string>& args);

        ArgParser& MultiValue();
        ArgParser& MultiValue(const size_t min_args_count);
        ArgParser& Default(const int default_val);
        ArgParser& Default(const char* default_val);
        ArgParser& Default(const bool default_val);

        ArgParser& AddIntArgument(const std::string& name);
        ArgParser& AddIntArgument(const char short_name, const std::string& name);
        ArgParser& AddIntArgument(const std::string& name, const std::string& the_message);
        int GetIntValue(const std::string& name) const;
        int GetIntValue(const std::string& name, size_t ind) const;
        ArgParser& StoreValues(std::vector<int>& store_name);
        ArgParser& Positional();

        ArgParser& AddFlag(const char short_name, const std::string& name);
        ArgParser& AddFlag(const char short_name, const std::string& name, const std::string& the_message);
        ArgParser& AddFlag(const std::string& name, const std::string& the_message);
        bool GetFlag(const std::string& name) const;
        ArgParser& StoreValue(bool &store_name);

        ArgParser& AddStringArgument(const std::string& name);
        ArgParser& AddStringArgument(const char short_name, const std::string& name);
        ArgParser& AddStringArgument(const char short_name, const std::string& name, const std::string& the_message);
        std::string GetStringValue(const std::string& name) const;
        ArgParser& StoreValue(std::string& store_name);

        bool Help() const;
        void AddHelp(const char h, const char* help, const char* text);
        std::string HelpDescription() const;
    private:
        std::vector<IntArgument> int_args;
        std::vector<FlagArgument> flag_args;
        std::vector<StringArgument> string_args;

        size_t count_of_int_positionals = 0;

        const char* str_with_last_type = "";

        const char* parser_name = " ";
        bool is_help_is_requested = false;
        std::vector<const char*> commands_for_help;

        friend class IntArgument;
        friend class StringArgument;
        friend class FlagArgument;
    };
}