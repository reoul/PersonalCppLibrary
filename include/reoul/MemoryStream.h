#pragma once
#include <string>

class WriteMemoryStream;
class ReadMemoryStream;

class IConvertToBytes
{
public:
	virtual ~IConvertToBytes() = default;
	virtual void ToBytes(WriteMemoryStream& writeStream) = 0;
};

class IConvertToData
{
public:
	virtual ~IConvertToData() = default;
	virtual void ToData(ReadMemoryStream& readStream) = 0;
};

class WriteMemoryStream
{
public:
	WriteMemoryStream();
	WriteMemoryStream(const WriteMemoryStream&) = delete;
	~WriteMemoryStream();

	//get a pointer to the data in the stream
	inline const char* GetBufferPtr() const;
	inline uint32_t GetLength() const;
	void Write(const void* inData, size_t inByteCount);

	template <typename T>
	void Write(T inData);

	/*void Write(const std::vector< int >& inIntVector)
	{
		const size_t elementCount = inIntVector.size();
		Write(elementCount);
		Write(inIntVector.data(), elementCount * sizeof(int));
	}

	template< typename T >
	void Write(const std::vector< T >& inVector)
	{
		const uint32_t elementCount = inVector.size();
		Write(elementCount);
		for (const T& element : inVector)
		{
			Write(element);
		}
	}*/

	void Write(const std::string& inString);

private:
	void ReallocBuffer(uint32_t inNewLength);

	char* mBuffer;
	uint32_t mHead;
	uint32_t mCapacity;
};

class ReadMemoryStream
{
public:
	ReadMemoryStream() = delete;
	ReadMemoryStream(char* inBuffer, uint32_t inByteCount);
	ReadMemoryStream(const ReadMemoryStream&) = delete;
	~ReadMemoryStream();

	inline uint32_t GetRemainingDataSize() const;
	void Read(void* outData, uint32_t inByteCount);

	template <typename T>
	void Read(T& outData);

	/*template< typename T >
	void Read(std::vector< T >& outVector)
	{
		size_t elementCount;
		Read(elementCount);
		outVector.resize(elementCount);
		for (const T& element : outVector)
		{
			Read(element);
		}
	}*/

private:
	char* mBuffer;
	uint32_t mHead;
	uint32_t mCapacity;
};

const char* WriteMemoryStream::GetBufferPtr() const
{
	return mBuffer;
}

uint32_t WriteMemoryStream::GetLength() const
{
	return mHead;
}

template <typename T>
void WriteMemoryStream::Write(T inData)
{
	static_assert(std::is_arithmetic<T>::value || std::is_enum<T>::value, "Generic Write only supports primitive data types");
	Write(&inData, sizeof(inData));
}

uint32_t ReadMemoryStream::GetRemainingDataSize() const
{
	return mCapacity - mHead;
}

template <typename T>
void ReadMemoryStream::Read(T& outData)
{
	static_assert(std::is_arithmetic<T>::value || std::is_enum<T>::value, "Generic Read only supports primitive data types");
	Read(&outData, sizeof(outData));
}
