/*!
	\file TestBTree.cpp
	\date Monday May 18, 2009
	\author Gregory Diamos <gregory.diamos@gatech.edu>
	\brief The source file for the TestBTree class.
*/

#ifndef TEST_B_TREE_CPP_INCLUDED
#define TEST_B_TREE_CPP_INCLUDED

#include <test/TestBTree.h>
#include <implementation/BTree.h>
#include <implementation/Exception.h>
#include <implementation/ArgumentParser.h>
#include <vector>
#include <fstream>

namespace test
{

	bool TestBTree::testRandom()
	{
		return false;
	}

	bool TestBTree::testClear()
	{
		return false;
	}
	
	bool TestBTree::testComparisons()
	{
		return false;
	}
	
	void TestBTree::doBenchmark()
	{
		typedef hydrazine::BTree< unsigned int, unsigned int, 
			std::less<unsigned int>, hydrazine::MmapAllocator< 
			std::pair< const unsigned int, unsigned int > >, PAGE_SIZE > Tree;
		typedef std::vector< unsigned int > Vector;
		
		Tree tree;
		Vector vector( elements );
		
		unsigned int count = 0;
		for( Vector::iterator fi = vector.begin(); fi != vector.end(); ++fi )
		{
			*fi = count++;
		}
		
		for( Vector::iterator fi = vector.begin(); fi != vector.end(); ++fi )
		{
			tree.insert( std::make_pair( *fi, *fi ) );
			std::stringstream stream;
			stream << path << "/tree_" << *fi << ".dot";
			std::ofstream out( stream.str().c_str() );
			if( !out.is_open() )
			{
				throw hydrazine::Exception( "Could not open file " 
					+ stream.str() );
			}
			tree.toGraphViz( out );
		}
	
	}

	bool TestBTree::doTest()
	{
		if( benchmark )
		{
			doBenchmark();
			return true;
		}
		else
		{
			return testClear() && testComparisons() && testRandom();
		}
	}

	TestBTree::TestBTree()
	{
		name = "TestBTree";
		description = "A unit test for the BTree mapping data structure. ";
		description += "Test Points: 1) Randomly insert and remove elements ";
		description += "from a std::map and a BTree	assert that the final ";
		description += "versions have the exact same elements stored in the ";
		description += "same order. 2) Add elements and then clear the BTree. ";
		description += " Assert that there are no elements after the clear and";
		description += " that the correct number is reported by size after ";
		description += "each insertion. 3) Test each of the comparison ";
		description += "operators. 4) Do not run any tests, simply add a ";
		description += "sequence to the tree and write it out to graph viz ";
		description += "files after each operaton.";
	}

}

int main( int argc, char** argv )
{
	hydrazine::ArgumentParser parser( argc, argv );
	test::TestBTree test;
	parser.description( test.testDescription() );

	parser.parse( "-s", "--seed", test.seed, 0, 
		"Seed for random tests, 0 implies seed with time." );
	parser.parse( "-v", "--verbose", test.verbose, false, 
		"Print out info after the test." );
	parser.parse( "-b", "--benchmark", test.benchmark, false,
		"Rather than testing, print out the tree after several changes." );
	parser.parse( "-e", "--elements", test.elements, 10,
		"The number of elements to add to the tree." );
	parser.parse( "-p", "--path", test.path, "temp",
		"Relative path to store graphviz representations of the tree." );
	parser.parse();
	
	test.test();
	
	return test.passed();
	
}

#endif

