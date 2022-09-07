#include "pch.h"
#include "MemoryStream.h"
#include "logger.h"

void WriteMemoryStream::Write(const std::string& inString)
{
	size_t elementCount = inString.size();
	Write(elementCount);
	Write(inString.data(), elementCount * sizeof(char));
}

void WriteMemoryStream::ReallocBuffer(uint32_t inNewLength)
{
	mBuffer = static_cast<char*>(std::realloc(mBuffer, inNewLength));
	if(mBuffer == nullptr)
	{
		//log
	}
	mCapacity = inNewLength;
}

WriteMemoryStream::WriteMemoryStream()
	: mBuffer(nullptr)
	, mHead(0)
	, mCapacity(0)
{
	ReallocBuffer(32);
}

WriteMemoryStream::~WriteMemoryStream()
{
	std::free(mBuffer);
}

void WriteMemoryStream::Write(const void* inData, size_t inByteCount)
{
	const uint32_t resultHead = mHead + static_cast<uint32_t>(inByteCount);
	if (resultHead > mCapacity) // 공간 부족할 시
	{
		ReallocBuffer(std::max(mCapacity * 2, resultHead)); // 새 공간 할당
	}
	
	std::memcpy(mBuffer + mHead, inData, inByteCount);
	
	mHead = resultHead;
}


ReadMemoryStream::ReadMemoryStream(char* inBuffer, uint32_t inByteCount)
	: mBuffer(inBuffer)
	, mHead(0)
	, mCapacity(inByteCount)
{
}

ReadMemoryStream::~ReadMemoryStream()
{
	std::free(mBuffer);
}

void ReadMemoryStream::Read(void* outData, uint32_t inByteCount)
{
	uint32_t resultHead = mHead + inByteCount;
	if (resultHead > mCapacity)
	{
		//handle error, no data to read!
		//...
	}

	std::memcpy(outData, mBuffer + mHead, inByteCount);

	mHead = resultHead;
}
