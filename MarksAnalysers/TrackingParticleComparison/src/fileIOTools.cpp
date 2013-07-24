#include "MarksAnalysers/TrackingParticleComparison/interface/fileIOTools.h"

#include <stdexcept>
#include <fcntl.h>
#include <iostream>
#include "MarksAnalysers/TrackingParticleComparison/src/TrackingParticleNtuple.pb.h"
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/gzip_stream.h>

namespace // unnamed namespace
{
	/** @brief Sentry that closes a Unix file descriptor when it goes out of scope.
	 * @author Mark Grimes (mark.grimes@bristol.ac.uk)
	 * @date 07/Jun/2013
	 */
	class UnixFileSentry
	{
	public:
		UnixFileSentry( int fileDescriptor ) : fileDescriptor_(fileDescriptor) {}
		~UnixFileSentry() { close(fileDescriptor_); }
	private:
		int fileDescriptor_;
	};

	const std::string FILE_FORMAT_MAGIC_NUMBER="tpanalyserproto::Sample";

} // end of the unnamed namespace


void tpanalyser::saveSampleToFile( const tpanalyserproto::Sample& sample, const std::string& filename )
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	// Open the file. Parameters are filename, write ability and create, rw-r--r-- permissions.
	int fileDescriptor = open( filename.c_str(), O_WRONLY | O_CREAT, 0644 );
	if( fileDescriptor==0 ) throw std::runtime_error( "ReducedSample save to file - couldn't open file" );
	::UnixFileSentry fileSentry( fileDescriptor ); // Use this as an exception safe way of closing the output file

	// Setup the protobuf file handlers
	google::protobuf::io::FileOutputStream fileOutput( fileDescriptor );

	// I want the magic number and file format identifier uncompressed, so
	// I'll write those before switching to using gzipped output.
	{ // Block to make sure codedOutput is destructed before the gzip version is created
		google::protobuf::io::CodedOutputStream codedOutput( &fileOutput );

		// Write a magic number at the start of all files
		codedOutput.WriteString( ::FILE_FORMAT_MAGIC_NUMBER );
		// Write an integer that specifies what version of the file format I'm using. I
		// have no intention of changing the format but I might as well keep the option
		// open.
		codedOutput.WriteVarint32( 1 );
	}

	google::protobuf::io::GzipOutputStream gzipOutput( &fileOutput );
	google::protobuf::io::CodedOutputStream codedOutput( &gzipOutput );

	// Write the size of the sample into the file...
	codedOutput.WriteVarint64( sample.ByteSize() );
	// ...and then write the sample
	sample.SerializeToCodedStream( &codedOutput );
}

void tpanalyser::loadSampleFromFile( tpanalyserproto::Sample& sample, const std::string& filename )
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	// Open the file with read ability
	int fileDescriptor = open( filename.c_str(), O_RDONLY );
	if( fileDescriptor==0 ) throw std::runtime_error( "loadSampleFromFile() - couldn't open file" );
	::UnixFileSentry fileSentry( fileDescriptor ); // Use this as an exception safe way of closing the input file
	google::protobuf::io::FileInputStream fileInput( fileDescriptor );

	// First read the magic number at the start of the file and make sure it
	// matches what I expect. This is uncompressed so I'll wrap it in a block
	// to make sure the CodedInputStream is destructed before creating a new
	// one with gzip input.
	{
		google::protobuf::io::CodedInputStream codedInput( &fileInput );

		// As a read buffer, I'll create a string the correct size (filled with an arbitrary
		// character) and read straight into that.
		std::string readMagicNumber;
		if( !codedInput.ReadString( &readMagicNumber, FILE_FORMAT_MAGIC_NUMBER.size() ) ) throw std::runtime_error( "ReducedSample initialise from file - error reading magic number" );
		if( readMagicNumber!= ::FILE_FORMAT_MAGIC_NUMBER ) throw std::runtime_error( "loadSampleFromFile() - tried to initialise with a file that is not the correct format" );

		google::protobuf::uint32 fileformatVersion;
		if( !codedInput.ReadVarint32( &fileformatVersion ) ) throw std::runtime_error( "loadSampleFromFile() - error reading file format version" );
		// So far I only have (and ever expect to have) one version of the file
		// format, imaginatively versioned "1". You never know though...
		if( fileformatVersion>1 ) std::cerr << "Warning: Attempting to read a tpanalyserproto::Sample with version " << fileformatVersion << " with code that only knows up to version 1." << std::endl;
	}

	google::protobuf::io::GzipInputStream gzipInput( &fileInput );
	google::protobuf::io::CodedInputStream codedInput( &gzipInput );

	// Disable warnings on this input stream (second parameter, -1). The
	// first parameter is the default. I'll change this if necessary later.
	size_t totalBytesLimit=67108864;
	codedInput.SetTotalBytesLimit( totalBytesLimit, -1 );

	google::protobuf::uint64 messageSize;

	// Read the size of the Sample
	if( !codedInput.ReadVarint64( &messageSize ) ) throw std::runtime_error( "loadSampleFromFile() - error reading message size for header" );
	google::protobuf::io::CodedInputStream::Limit readLimit=codedInput.PushLimit(messageSize);
	if( !sample.ParseFromCodedStream( &codedInput ) ) throw std::runtime_error( "loadSampleFromFile() - some unknown error while reading header" );
	codedInput.PopLimit(readLimit);
}
