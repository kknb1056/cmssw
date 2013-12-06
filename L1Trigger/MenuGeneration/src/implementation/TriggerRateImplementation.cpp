#include "TriggerRateImplementation.h"

#include <cmath>
#include "MenuRateImplementation.h"
#include "l1menu/TriggerTable.h"
#include "l1menu/ITrigger.h"
#include "l1menu/tools/XMLElement.h"
#include "l1menu/tools/fileIO.h"

l1menu::implementation::TriggerRateImplementation::TriggerRateImplementation( const l1menu::ITrigger& trigger, float fraction, float fractionError, float rate, float rateError, float pureFraction, float pureFractionError, float pureRate, float pureRateError )
	: fraction_(fraction), fractionError_(fractionError),
	  rate_(rate), rateError_(rateError),
	  pureFraction_(pureFraction), pureFractionError_(pureFractionError),
	  pureRate_(pureRate), pureRateError_(pureRateError)
{
	pTrigger_=std::move( l1menu::TriggerTable::instance().copyTrigger(trigger) );
}

l1menu::implementation::TriggerRateImplementation::TriggerRateImplementation( TriggerRateImplementation&& otherTriggerRate ) noexcept
	: pTrigger_( std::move(otherTriggerRate.pTrigger_) ),
	  fraction_(otherTriggerRate.fraction_),
	  fractionError_(otherTriggerRate.fractionError_),
	  rate_(otherTriggerRate.rate_),
	  rateError_(otherTriggerRate.rateError_),
	  pureFraction_(otherTriggerRate.pureFraction_),
	  pureFractionError_(otherTriggerRate.pureFractionError_),
	  pureRate_(otherTriggerRate.pureRate_),
	  pureRateError_(otherTriggerRate.pureRateError_)
{
	// No operation besides the initialiser list
}

l1menu::implementation::TriggerRateImplementation& l1menu::implementation::TriggerRateImplementation::operator=( TriggerRateImplementation&& otherTriggerRate ) noexcept
{
	pTrigger_=std::move( otherTriggerRate.pTrigger_ );
	fraction_=otherTriggerRate.fraction_;
	fractionError_=otherTriggerRate.fractionError_;
	rate_=otherTriggerRate.rate_;
	rateError_=otherTriggerRate.rateError_;
	pureFraction_=otherTriggerRate.pureFraction_;
	pureFractionError_=otherTriggerRate.pureFractionError_;
	pureRate_=otherTriggerRate.pureRate_;
	pureRateError_=otherTriggerRate.pureRateError_;
	return *this;
}

l1menu::implementation::TriggerRateImplementation::~TriggerRateImplementation()
{
	// No operation
}

const l1menu::ITriggerDescription& l1menu::implementation::TriggerRateImplementation::trigger() const
{
	return *pTrigger_;
}

float l1menu::implementation::TriggerRateImplementation::fraction() const
{
	return fraction_;
}

float l1menu::implementation::TriggerRateImplementation::fractionError() const
{
	return fractionError_;
}

float l1menu::implementation::TriggerRateImplementation::rate() const
{
	return rate_;
}

float l1menu::implementation::TriggerRateImplementation::rateError() const
{
	return rateError_;
}

float l1menu::implementation::TriggerRateImplementation::pureFraction() const
{
	return pureFraction_;
}

float l1menu::implementation::TriggerRateImplementation::pureFractionError() const
{
	return pureFractionError_;
}

float l1menu::implementation::TriggerRateImplementation::pureRate() const
{
	return pureRate_;
}

float l1menu::implementation::TriggerRateImplementation::pureRateError() const
{
	return pureRateError_;
}
