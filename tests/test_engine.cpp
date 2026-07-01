#include "catch.hpp"
#include "trie.h"
#include "graph.h"

SCENARIO("Trie correctly stores and retrieves streets IDs", "[trie]")
{
    GIVEN("A newly created, empty Trie")
    {
        Trie myTrie;

        WHEN("A single street is inserted")
        {
            myTrie.insert("Strada Bucium" , "10392");
            THEN("It can be found using the same name")
            {
                REQUIRE(myTrie.search("Strada Bucium") == "10392");
            }
        }

        WHEN("Multiple streets with similar prefixes are inserted")
        {
            myTrie.insert("Bulevardul Unirii", "103");
            myTrie.insert("Bulevardul Aviatorilor", "104");
            THEN("Both streets are accurately retrieved without overlap")
            {
                REQUIRE(myTrie.search("Bulevardul Unirii") == "103");
                REQUIRE(myTrie.search("Bulevardul Aviatorilor") == "104");
            }
        }

        WHEN("Searching for a street that does not exist")
        {
            THEN("It returns 'NOT_FOUND' for missing streets")
            {
                REQUIRE(myTrie.search("Piata Unirii") == "NOT_FOUND");
            }
        }
    }
}

SCENARIO("Graph handles basic node inseration", "[graph]")
{
    GIVEN("An initialized graph system")
    {
        Graph myGraph;
        WHEN("Noeds are added to the system")
        {
            std::string placeA = "Piata Romana";
            std::string placeB = "Universitate";
            REQUIRE_NOTHROW(myGraph.AddNode(placeA, placeB, 1.5));
        }
    }
}

SCENARIO("Dijkstra calculates the shortest path correctly", "[graph][dijkstra]")
{
    GIVEN("A simple graph with known distances")
    {
        Graph myGraph;

        std::string Start = "Piata Unirii";
        std::string Intermediar = "Lapusneanu";
        std::string Stop = "Copou";

        myGraph.AddNode(Start, Intermediar, 1.0);
        myGraph.AddNode(Intermediar, Stop, 2.0);
        myGraph.AddNode(Start, Stop, 5.0);

        WHEN("Requesting the shortest path") 
        {
            std::vector<std::string> result = myGraph.Dijkstra(Start, Stop);
            
            THEN("The path should be correct") 
            {
                REQUIRE(result.size() == 3.0);
                REQUIRE(result[0] == Start);
                REQUIRE(result[2] == Stop);
            }
        }
    }
}