#pragma once
#include <cstdint>
#include <string>
#include "expat.h"
#include "Vector.h"
#include "RTTI.H"
#include "Hashmap.h"

namespace Library
{

	//Forward declaration
	class IXmlParseHelper;

	class XmlParseMaster
	{
	public:


		/**
		Embedded class  that represents data all helper share with each other
		and with the master parser. 
		*/
		class  SharedData : public RTTI
		{
			RTTI_DECLARATIONS(SharedData, RTTI);
		public:
			/**
			Constructor
			*/
			SharedData();

			/**
			Delete copy constructor. This funcitonality is dealt with by Clone()
			*/
			SharedData(const SharedData& rhs) = delete;

			/**
			Delete assignment operator
			*/
			SharedData& operator=(const SharedData& rhs) = delete;

			/**
			'Virtual constructor' which returns the address of a shared data object which has the same internal state as this, except it is ready for a fresh file

			@return a pointer to the new shared data instance
			*/
			virtual SharedData* Clone();

			/**
			Given the address of a parse master, assign it to be our master

			@param address the address of the XmlParseMaster to set as our master
			*/
			void SetXmlParseMaster(XmlParseMaster* address);

			/**
			Get a pointer to our master

			@return the address of the current master of the data
			*/
			XmlParseMaster* GetXmlParseMaster();

			/**
			Increment the nesting depth counter. Called upon the start of each element
			*/
			void IncrementDepth();

			/**
			Decrement a nesting depth counter. This gets called upon the end of each element
			*/
			void DecrementDepth();

			/**
			Get the current nesting depth of this data
			*/
			std::uint32_t Depth();

		private:
			/**
			The current nesting depth
			*/
			std::uint32_t mDepth;

			/**
			The parse master this data references
			*/
			XmlParseMaster* mMaster;
		};

	public:

		/**
		Constructor

		@param address the address of a SharedData used to initialize
		*/
		XmlParseMaster(SharedData* initData);

		/**
		Destructor. Only deletes memory of cloned helpers
		*/
		~XmlParseMaster();

		/**
		Delete copy constructor. This funcitonality is dealt with by Clone()
		*/
		XmlParseMaster(const XmlParseMaster& rhs) = delete;

		/**
		Delete assignment operator
		*/
		XmlParseMaster& operator=(const XmlParseMaster& rhs) = delete;

		/**
		Duplicate this object and return its address. Performs the usual operations of copy ctor, including duplicating all helpers and the SharedData. Helpers can duplicate
		themselves using their own virutal constructor. The object returned should be ready for parsing a fresh file. Marks the object as a clone.

		@return the address of a newly made copy of the object
		*/
		XmlParseMaster* Clone();

		/**
		Given a reference to an IXmlParseHelper object, add it to our list of helpers

		@param newHelper the helper to be added to the list
		*/
		void AddHelper(IXmlParseHelper* newHelper);

		/**
		Given a reference to an IXmlParseHelper object, remove it from our list of helpers

		@param toRemove the helper to be removed from the list
		*/
		void RemoveHelper(IXmlParseHelper* toRemove);

		/**
		Parse a buffer of XML data. This is a thin wrapper around expat's parse call

		@param buffer a character buffer of XML data to parse
		@param length the number of characters in the buffer
		@param isEnd a bool indicating whether this is the last chunk of text for the file
		*/
		void Parse(const char* buffer, std::uint32_t length, bool isEnd);

		/**
		Given a filename, read the file and parse it

		@param filename the name of the file to read in and parse
		*/
		void ParseFromFile(std::string filename);

		/*
		Return the path for the file being parsed passed into ParseFromFile

		@return the path for the file being parsed
		*/
		std::string GetFileName();

		/**
		Return the address of the shared data associated with this object

		@return the address of our shared data
		*/
		SharedData* GetSharedData();

		/**
		Given the address of a shared data object, associate it with this object

		@param newSharedData the address of a shared data objcet to be associated with this object
		*/
		void SetSharedData(SharedData* newSharedData);

	private:
		/**
		Callback that Expat will call to handle XML start elements. Implements the chain of responsibility design pattern
		*/
		static void StartElementHandler(void *data, const char *el, const char **attr);

		/**
		Callback that expat will call to handle XML end elemetns. This implements the chain of responsibility design pattern
		*/
		static void EndElementHandler(void  *data, const char *el);

		/**
		Callback that Expat will call to handle XML character data. This implements the chain of responsibility design pattern.
		*/
		static void CharDataHandler(void *data, const char* content, int length);

		/**
		Expat parser used by the parsemaster
		*/
		XML_Parser mParser;

		/**
		Shared data that is filled out by this parser
		*/
		SharedData *mSharedData;

		/**
		Vector of helpers to  send our data to from the parser
		*/
		Vector<IXmlParseHelper*> mHelpers;

		/**
		Current filename
		*/
		std::string mFileName;

		/**
		Flag set when cloned to confirm that allocated data must be deleted
		*/
		bool mIsClone;

	};
}