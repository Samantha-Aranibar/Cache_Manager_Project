/**
 * @file milestone2.cpp
 * @brief This file contains the 'main' function. Program execution begins and ends here.
 *
 * @details
 * This program reads and parses a configuration JSON file `milestone2_config.json` to determine:
 * - Input file path
 * - Output file path
 * - Error log file path
 * - Hash table size
 *
 * It then loads the input JSON, which includes a list of test cases, and processes each test case
 * by performing operations on a hash table and printing/logging the results.
 *
 * The file: "milestones2_config.json" is in the following format:
 *
                {
                    "Milestone2": [
                        {
                            "files": [
                                {
                                    "inputFile": "milestone2.json",
                                    "outputFile": "generatedOutputFile.txt",
                                    "errorLogFile":"logFile.txt"
                                }
                            ],
                            "defaultVariables": [
                                {
                                    "FIFOListSize": 5,
                                    "hashTableSize": 101
                                }
                            ]
                        }
                    ]
                }
 * The inputFile has the following format:
 * ```
 * {
 *     "hashTable": [
 *         {
 *             "testCase1": [
 *                 { "isEmpty": {} },
 *                 { "add": { "key": 20, "fullName": "John Doe", ... } },
 *                 ...
 *             ]
 *         }
 *     ]
 * }
 * ```
 *
 * @date 09/23/24 - Created by ChatGPT
 * @date 01/10/25 - Modified by H. Hui: added separate files, defines, and comments
 * @date 05/31/25 - modified by H. Hui: added additional doxygen style comments
 */

#define _CRT_SECURE_NO_WARNINGS
#define CONFIG_FILE "milestone2_config.json"

#include <iostream>
#include <fstream>
#include <string>

#include "json.hpp"
#include "hash_table.h"

using json = nlohmann::json;

/// Global output file stream used for logging
std::ofstream _outFile;

/**
 * @brief Gets a reference to the global output file stream.
 * @return Reference to the output file stream.
 */
std::ofstream& getOutFile() {
    return _outFile;
}

/**
 * @brief Sets the output file stream to a new file path.
 *
 * If an output file is already open, it is closed before opening the new one.
 *
 * @param filePath The path to the output file.
 */
void setOutFile(const std::string& filePath) {
    if (_outFile.is_open()) {
        _outFile.close();
    }

    _outFile.open(filePath);
    if (!_outFile.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
    }
}

/**
 * @brief Logs a message to both the console and the output file.
 *
 * @param message The message to be logged.
 */
void logToFileAndConsole(std::string message) {
    std::ofstream& outFile = getOutFile();

    std::cout << message << std::endl;
    outFile << message << std::endl;
}

/**
 * @brief Processes a single test case by applying a sequence of operations to a hash table.
 *
 * Each operation is read from a JSON array, and may include:
 * - isEmpty
 * - contains
 * - getNumberOfItems
 * - add
 * - remove
 * - clear
 *
 * @param hashTable Pointer to the HashTable object.
 * @param testCaseName Name of the test case from JSON.
 * @param testCaseArray JSON array of operations to process.
 */
void processTestCase(HashTable* hashTable, const std::string& testCaseName, const json& testCaseArray) {
    std::ofstream& outFile = getOutFile();

    logToFileAndConsole("\nProcessing " + testCaseName + "\n");

    for (size_t i = 0; i < testCaseArray.size(); ++i) {
        const json& entry = testCaseArray[i];

        for (json::const_iterator it = entry.begin(); it != entry.end(); ++it) {
            const std::string& actionName = it.key();
            const json& details = it.value();

            if (actionName == "isEmpty") {
                logToFileAndConsole("isEmpty returned: " + std::to_string(hashTable->isEmpty()));
            }
            else if (actionName == "contains") {
                int key = details["key"];
                logToFileAndConsole("contains key " + std::to_string(key) + ": " + std::to_string(hashTable->contains(details["key"])));
            }
            else if (actionName == "getNumberOfItems") {
                logToFileAndConsole("getNumberOfItems: " + std::to_string(hashTable->getNumberOfItems()));
            }
            else if (actionName == "add") {
                HashNode* newNode = new HashNode(details["key"], details["fullName"], details["address"], details["city"], details["state"], details["zip"]);
                hashTable->add(details["key"], newNode);
                int key = details["key"];
                logToFileAndConsole("add key: " + std::to_string(key));
            }
            else if (actionName == "remove") {
                int key = details["key"];
                hashTable->remove(key);
                logToFileAndConsole("remove key: " + std::to_string(key));
            }
            else if (actionName == "printTable") {
                hashTable->printTable();
            }
            else if (actionName == "clear") {
                hashTable->clear();
                logToFileAndConsole("clear hash table\n");
            }
        }
    }
}

/**
 * @brief Entry point of the program.
 *
 * This function performs the following steps:
 * 1. Loads configuration from `milestone2_config.json`
 * 2. Opens and parses the input JSON file
 * 3. Initializes a hash table using the configured size
 * 4. Iterates through test cases, processes each one using `processTestCase()`
 * 5. Prints and clears the hash table after each test case
 *
 * @return 0 if execution was successful; 1 if a file failed to open.
 */
int main() {
    // Load the configuration file
    std::ifstream configFile(CONFIG_FILE);
    if (!configFile.is_open()) {
        std::cerr << "Error opening config file!" << std::endl;
        return 1;
    }

    json config;
    configFile >> config;

    // Retrieve file paths
    std::string inputFilePath = config["Milestone2"][0]["files"][0]["inputFile"];
    std::string outputFilePath = config["Milestone2"][0]["files"][0]["outputFile"];
    std::string errorFilePath = config["Milestone2"][0]["files"][0]["errorLogFile"];

    // Retrieve hash table size
    int HASH_SIZE = config["Milestone2"][0]["defaultVariables"][0]["hashTableSize"];

    // Create the hash table
    HashTable* hashTable = new HashTable(HASH_SIZE);

    // Load the input test data file
    std::ifstream inputFile(inputFilePath);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the file: " << inputFilePath << ".\n";
        return 1;
    }

    // Set output file path (used across multiple files)
    setOutFile(outputFilePath);
    std::ofstream& outFile = getOutFile();

    json data;
    inputFile >> data;

    // Process test cases
    for (size_t i = 0; i < data["hashTable"].size(); ++i) {
        const json& testCase = data["hashTable"][i];
        for (json::const_iterator it = testCase.begin(); it != testCase.end(); ++it) {
            const std::string& testCaseName = it.key();
            const json& testCaseArray = it.value();

            processTestCase(hashTable, testCaseName, testCaseArray);
            hashTable->clear();
        }
    }

    // Clean up
    configFile.close();
    inputFile.close();
    outFile.close();

    return 0;
}
