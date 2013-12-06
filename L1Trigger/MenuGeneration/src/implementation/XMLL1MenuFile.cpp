#include "./XMLL1MenuFile.h"

#include <fstream>
#include <stdexcept>
#include "l1menu/TriggerMenu.h"
#include "l1menu/ITrigger.h"
#include "./MenuRateImplementation.h"

l1menu::implementation::XMLL1MenuFile::XMLL1MenuFile( std::ostream& outputStream ) : pOutputStream_(&outputStream)
{
}

l1menu::implementation::XMLL1MenuFile::XMLL1MenuFile( const std::string& filename, bool outputOnly ) : pOutputStream_(nullptr)
{
	if( outputOnly ) filenameForOutput_=filename;
	else outputFile_.parseFromFile(filename);
}

l1menu::implementation::XMLL1MenuFile::~XMLL1MenuFile()
{
	std::ofstream outputFile;
	if( !filenameForOutput_.empty() )
	{
		outputFile.open( filenameForOutput_ );
		if( outputFile.is_open() ) pOutputStream_=&outputFile;
	}

	if( pOutputStream_!=nullptr ) outputFile_.outputToStream( *pOutputStream_ );
}

void l1menu::implementation::XMLL1MenuFile::add( const l1menu::TriggerMenu& menu )
{
	l1menu::tools::XMLElement rootElement=outputFile_.rootElement();
	convertToXML( menu, rootElement );
}

void l1menu::implementation::XMLL1MenuFile::add( const l1menu::IMenuRate& menuRate )
{
	l1menu::tools::XMLElement rootElement=outputFile_.rootElement();
	convertToXML( menuRate, rootElement );
}

std::vector< std::unique_ptr<l1menu::TriggerMenu> > l1menu::implementation::XMLL1MenuFile::getMenus()
{
	std::vector<l1menu::tools::XMLElement> childElements=outputFile_.rootElement().getChildren("TriggerMenu");
	if( childElements.empty() ) throw std::runtime_error( "XMLL1MenuFile::getRates - file does not contain a \"TriggerMenu\" child element." );

	std::vector< std::unique_ptr<l1menu::TriggerMenu> > returnValue;
	for( const auto& menuElement : childElements )
	{
		std::unique_ptr<l1menu::TriggerMenu> pNewMenu( new l1menu::TriggerMenu );

		std::vector<l1menu::tools::XMLElement> triggerElements=menuElement.getChildren("Trigger");
		for( const auto& triggerElement : triggerElements )
		{
			std::vector<l1menu::tools::XMLElement> parameterElements=triggerElement.getChildren("name");
			if( parameterElements.size()!=1 ) throw std::runtime_error( "Trigger doesn't have one and only one subelement called 'name'" );
			std::string triggerName=parameterElements.front().getValue();

			parameterElements=triggerElement.getChildren("version");
			if( parameterElements.size()!=1 ) throw std::runtime_error( "Trigger doesn't have one and only one subelement called 'version'" );
			size_t version=parameterElements.front().getIntValue();

			l1menu::ITrigger& newTrigger=pNewMenu->addTrigger( triggerName, version );
			// Now loop over all of the parameters and set them
			parameterElements=triggerElement.getChildren("parameter");
			for( const auto& parameterElement : parameterElements )
			{
				std::string parameterName=parameterElement.getAttribute("name");
				float parameterValue=parameterElement.getFloatValue();
				newTrigger.parameter(parameterName)=parameterValue;
			}
		}

		returnValue.push_back( std::move(pNewMenu) );
	}

	return returnValue;
}

std::vector< std::unique_ptr<l1menu::IMenuRate> > l1menu::implementation::XMLL1MenuFile::getRates()
{
	std::vector<l1menu::tools::XMLElement> childElements=outputFile_.rootElement().getChildren("MenuRate");
	if( childElements.empty() ) throw std::runtime_error( "XMLL1MenuFile::getRates - file does not contain a \"MenuRate\" child element." );

	std::vector< std::unique_ptr<l1menu::IMenuRate> > returnValue;
	for( const auto& element : childElements )
	{
		std::unique_ptr<l1menu::IMenuRate> pNewRate( new l1menu::implementation::MenuRateImplementation( element ) );
		returnValue.push_back( std::move(pNewRate) );
	}

	return returnValue;
}

l1menu::tools::XMLElement l1menu::implementation::XMLL1MenuFile::convertToXML( const l1menu::TriggerMenu& object, l1menu::tools::XMLElement& parent )
{
	l1menu::tools::XMLElement thisElement=parent.createChild( "TriggerMenu" );

	for( size_t index=0; index<object.numberOfTriggers(); ++index )
	{
		convertToXML( object.getTrigger(index), thisElement );
	}

	return thisElement;
}

l1menu::tools::XMLElement l1menu::implementation::XMLL1MenuFile::convertToXML( const l1menu::IMenuRate& object, l1menu::tools::XMLElement& parent )
{
	l1menu::tools::XMLElement thisElement=parent.createChild( "MenuRate" );
	thisElement.setAttribute( "formatVersion", 0 );

	thisElement.createChild( "totalFraction" ).setValue( object.totalFraction() );
	thisElement.createChild( "totalFractionError" ).setValue( object.totalFractionError() );
	thisElement.createChild( "totalRate" ).setValue( object.totalRate() );
	thisElement.createChild( "totalRateError" ).setValue( object.totalRateError() );

	// Loop over all of the trigger rates and add those to the file
	for( const auto& pTriggerRate : object.triggerRates() )
	{
		convertToXML( *pTriggerRate, thisElement );
	}

	return thisElement;
}

l1menu::tools::XMLElement l1menu::implementation::XMLL1MenuFile::convertToXML( const l1menu::ITriggerRate& object, l1menu::tools::XMLElement& parent )
{
	l1menu::tools::XMLElement thisElement=parent.createChild( "TriggerRate" );
	thisElement.setAttribute( "formatVersion", 0 );

	thisElement.createChild( "fraction" ).setValue( object.fraction() );
	thisElement.createChild( "fractionError" ).setValue( object.fractionError() );
	thisElement.createChild( "rate" ).setValue( object.rate() );
	thisElement.createChild( "rateError" ).setValue( object.rateError() );
	thisElement.createChild( "pureFraction" ).setValue( object.pureFraction() );
	thisElement.createChild( "pureFractionError" ).setValue( object.pureFractionError() );
	thisElement.createChild( "pureRate" ).setValue( object.pureRate() );
	thisElement.createChild( "pureRateError" ).setValue( object.pureRateError() );

	convertToXML( object.trigger(), thisElement );

	return thisElement;
}

l1menu::tools::XMLElement l1menu::implementation::XMLL1MenuFile::convertToXML( const l1menu::ITriggerDescription& object, l1menu::tools::XMLElement& parent )
{
	l1menu::tools::XMLElement thisElement=parent.createChild( "Trigger" );
	thisElement.setAttribute( "formatVersion", 0 );

	thisElement.createChild( "name" ).setValue( object.name() );
	// Need a cast because the compiler doesn't like going from unsigned int to int
	thisElement.createChild( "version" ).setValue( static_cast<int>( object.version() ) );

	for( const auto& parameterName : object.parameterNames() )
	{
		l1menu::tools::XMLElement parameterElement=thisElement.createChild( "parameter" );
		parameterElement.setAttribute( "name", parameterName );
		parameterElement.setValue( object.parameter( parameterName ) );
	}

	return thisElement;
}
