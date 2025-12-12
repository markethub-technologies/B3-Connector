/*
* Copyright Onix Solutions Limited [OnixS]. All rights reserved.
*
* This software owned by Onix Solutions Limited [OnixS] and is protected by copyright law
* and international copyright treaties.
*
* Access to and use of the software is governed by the terms of the applicable OnixS Software
* Services Agreement (the Agreement) and Customer end user license agreements granting
* a non-assignable, non-transferable and non-exclusive license to use the software
* for it's own data processing purposes under the terms defined in the Agreement.
*
* Except as otherwise granted within the terms of the Agreement, copying or reproduction of any part
* of this source code or associated reference material to any other location for further reproduction
* or redistribution, and any amendments to this copyright notice, are expressly prohibited.
*
* Any reproduction or redistribution for sale or hiring of the Software not in accordance with
* the terms of the Agreement is a violation of copyright law.
*/

#pragma once

//! [CuiH]
#include <OnixS/B3/BOE/threading/Thread.h>
#include <OnixS/B3/BOE/threading/Mutex.h>
#include <OnixS/B3/BOE/threading/Guard.h>
#include <OnixS/B3/BOE/messaging/Typification.h>

#include "Book.h"

#include <iostream>
#include <string>
#include <vector>

namespace CUI {

// Utility class which provides facilities to notify a user
// about important events like an incoming message receipt.
struct Screen
{
    struct MessagePrinter
    {
        explicit MessagePrinter(const std::string& prefix) : prefix_(prefix) {}

        template <typename MessageType>
        void operator()(const MessageType& msg) const
        {
            info(prefix_, msg.toString());
        }

        std::string prefix_;
    };

    typedef Threading::Mutex Mutex;
    typedef Threading::Guard<Threading::Mutex> Guard;

    static Mutex& mutex()
    {
        static Mutex mutex;
        return mutex;
    }

    static std::string getInput()
    {
        std::string userInput;
        std::getline(std::cin, userInput);
        return userInput;
    }

    template <typename T>
    static T getInput(const T & defaultValue = T())
    {
        std::string userInput;
        std::getline(std::cin, userInput);

        if (userInput.empty())
            return defaultValue;
        else
        {
            Messaging::Int64 converted = Messaging::Int64();
            std::istringstream ss(userInput);
            ss >> converted;
            return static_cast<T>(converted);
        }
    }

    template <typename T>
    static void getInput(T & value, const T & defaultValue = T())
    {
        std::string userInput;
        std::getline(std::cin, userInput);

        if (userInput.empty())
            value = defaultValue;
        else
        {
            Messaging::Int64 converted = Messaging::Int64();
            std::istringstream ss(userInput);
            ss >> converted;
            value = static_cast<T>(converted);
        }
    }

    static void getInputLocalMktDate(LocalMktDate & value)
    {
        std::string userInput;
        std::getline(std::cin, userInput);

        Timestamp timestamp;

        if(fromStr(timestamp, userInput, TimestampFormat::YYYYMMDD))
            value = timestampToLocalMktDate(timestamp);
        else
            value = 0;
    }

    template <typename T>
    static void getInputChar(T & value, const T & defaultValue = T())
    {
        std::string userInput;
        std::getline(std::cin, userInput);

        if (userInput.empty())
            value = defaultValue;
        else
        {
            Messaging::Char converted = Messaging::Char();
            std::istringstream ss(userInput);
            ss >> converted;
            value = static_cast<T>(converted);
        }
    }

    static void info(const std::string& message)
    {
        info("INFO: ", message);
    }

    static void info(const std::string& prefix, const std::string& message)
    {
        Guard g(mutex());

        std::cout << std::endl << prefix << message << std::endl;
    }

    static void out(const std::string& message)
    {
        Guard g(mutex());

        std::cout << message << std::endl;
    }

    static void out(const std::string& prefix, const SbeMessage& message)
    {
        if (!processTypified(message, MessagePrinter(prefix)))
            info("Unknown message type.");
    }

    template <typename ItemType>
    static void outItems(const ItemType & items)
    {
        Guard g(mutex());

        for (size_t index = 0; index < items.size(); ++index)
            std::cout << (index + 1) << ") " << items[index].text << std::endl;
    }

    static bool shouldContinue()
    {
        {
            Guard g(mutex());
            std::cout << std::endl << "Press <Enter> to view next page or Enter 'quit' to abort current action: ";
        }

        const std::string userInput = getInput();

        {
            Guard g(mutex());
            std::cout << std::endl;
        }

        return userInput.empty();
    }
};

// Command execution status represents command execution feedback.

enum CommandExecutionStatus
{
    TerminateExecution,
    ContinueExecution,
    RepeatExecution
};

// Abstraction of the main menu for the application.
// Implemented as a template to simplify command handling.

template <typename Owner>
class Menu
{
public:
    // Command, which is invoked on a menu item selection.
    typedef void (Owner::*Command)(CommandExecutionStatus*);

    // Initializes an empty menu.
    explicit Menu(Owner* owner)
      : owner_(owner)
    {
    }

    // Utilizes resources.
    ~Menu()
    {
    }

    // Adds a new menu item to the menu.
    Menu& add(const std::string& text, const std::string& commandText, Command command)
    {
        items_.push_back(Item(text, commandText, command));
        return *this;
    }

    // Process user requests until any command terminates the execution.
    void processRequests() const
    {
        CommandExecutionStatus status = ContinueExecution;

        while (TerminateExecution != status)
        {
            outputItems();
            processRequest(&status);
        }
    }

private:
    // Menu item-related attributes.
    struct Item
    {
        Item(const std::string& itemText, const std::string& itemCommandText, Command itemCommand)
            : text(itemText)
            , commandText(itemCommandText)
            , command(itemCommand)
        {
        }

        Item(const Item& other)
            : text(other.text)
            , commandText(other.commandText)
            , command(other.command)
        {
        }

        std::string text;
        std::string commandText;
        Command command;
    };

    // Instance of the class whose members are invoked as menu commands.
    Owner* owner_;

    // Menu items.
    std::vector<Item> items_;

    // Outputs items' names onto the screen.
    // Assigns a sequence number to each item for future reference.
    void outputItems() const
    {
        Screen::info("Select operation you want to perform: ");

        Screen::outItems(items_);
    }

    // Invokes command associated with the menu item selected by the user.
    void processRequest(CommandExecutionStatus* status) const
    {
        Screen::out("Enter your choice : ");

        std::string userInput = Screen::getInput();

        const size_t selectedItemNumber = static_cast<size_t>(atoi(userInput.c_str()) - 1);

        if (items_.size() <= selectedItemNumber)
        {
            Screen::info("Invalid command requested. Repeat your choice.");
        }
        else
        {
            try
            {
                const Item& selectedItem = items_[selectedItemNumber];

                Screen::info(selectedItem.commandText);

                (owner_->*(selectedItem.command))(status);

                const unsigned int CommandExecutionTimeout = 500;

                // Wait for some timeout to give to complete the command
                // and print the corresponding responses to make the output more readable.
                Threading::ThisThread::sleep(CommandExecutionTimeout);
            }
            catch (const std::exception& ex)
            {
                Screen::info("ERROR: ", ex.what());
            }
        }
    }
};

// Abstraction of a list viewer, which outputs list items on a per-page basis.
// Implemented as a template to abstract from the list items type, which must support
// the ability to return its string presentation through the toString() member.
template <typename Stringable>
class ListViewer
{
public:
    typedef typename Samples::Book<Stringable>::EntryList StringableList;

    // Outputs list items on the screen.
    static void outputItems(const StringableList& items, size_t itemsPerPage)
    {
        if (0 == items.size())
        {
            Screen::info("No items available.");
        }
        else
        {
            size_t itemNumber = 0;
            size_t itemsToOutput = itemsPerPage;

            for (StringableListConstEntry itemPtr = items.begin(); itemPtr != items.end(); ++itemPtr)
            {
                if (0 == --itemsToOutput)
                {
                    itemsToOutput = itemsPerPage;

                    if (!Screen::shouldContinue())
                        return;
                }

                Screen::out(toStr(++itemNumber) + ") " + (*itemPtr)->toString() + ".");
            }
        }
    }

private:
    typedef typename StringableList::const_iterator StringableListConstEntry;
};

}
//! [CuiH]
