#include "l1menu/IL1MenuFile.h"

#include <stdexcept>
#include "implementation/XMLL1MenuFile.h"
#include "implementation/OldL1MenuFile.h"

/** @file
 *
 * Although IL1MenuFile is an abstract interface there are some static methods to get the
 * concrete instances. These are defined here.
 */

std::unique_ptr<l1menu::IL1MenuFile> l1menu::IL1MenuFile::getOutputFile( l1menu::IL1MenuFile::FileFormat fileFormat, std::ostream& outputStream )
{
	if( fileFormat==l1menu::IL1MenuFile::FileFormat::XML ) return std::unique_ptr<l1menu::IL1MenuFile>( new l1menu::implementation::XMLL1MenuFile(outputStream) );
	if( fileFormat==l1menu::IL1MenuFile::FileFormat::CSV ) return std::unique_ptr<l1menu::IL1MenuFile>( new l1menu::implementation::OldL1MenuFile(outputStream,',') );
	if( fileFormat==l1menu::IL1MenuFile::FileFormat::OLD ) return std::unique_ptr<l1menu::IL1MenuFile>( new l1menu::implementation::OldL1MenuFile(outputStream,' ') );
	else throw std::logic_error( "Unimplemented value for l1menu::IL1MenuFile::FileFormat" );
}

std::unique_ptr<l1menu::IL1MenuFile> l1menu::IL1MenuFile::getOutputFile( FileFormat fileFormat, const std::string& filename )
{
	if( fileFormat==l1menu::IL1MenuFile::FileFormat::XML ) return std::unique_ptr<l1menu::IL1MenuFile>( new l1menu::implementation::XMLL1MenuFile(filename,true) );
	if( fileFormat==l1menu::IL1MenuFile::FileFormat::CSV ) return std::unique_ptr<l1menu::IL1MenuFile>( new l1menu::implementation::OldL1MenuFile(filename,',') );
	if( fileFormat==l1menu::IL1MenuFile::FileFormat::OLD ) return std::unique_ptr<l1menu::IL1MenuFile>( new l1menu::implementation::OldL1MenuFile(filename,' ') );
	else throw std::logic_error( "Unimplemented value for l1menu::IL1MenuFile::FileFormat" );
}

std::unique_ptr<l1menu::IL1MenuFile> l1menu::IL1MenuFile::getInputFile( l1menu::IL1MenuFile::FileFormat fileFormat, const std::string& inputFilenam )
{
	if( fileFormat==l1menu::IL1MenuFile::FileFormat::XML ) return std::unique_ptr<l1menu::IL1MenuFile>( new l1menu::implementation::XMLL1MenuFile(inputFilenam,false) );
	if( fileFormat==l1menu::IL1MenuFile::FileFormat::CSV ) return std::unique_ptr<l1menu::IL1MenuFile>( new l1menu::implementation::OldL1MenuFile(inputFilenam,',') );
	if( fileFormat==l1menu::IL1MenuFile::FileFormat::OLD ) return std::unique_ptr<l1menu::IL1MenuFile>( new l1menu::implementation::OldL1MenuFile(inputFilenam,' ') );
	else throw std::logic_error( "Unimplemented value for l1menu::IL1MenuFile::FileFormat" );
}
