#include "MarksAnalysers/TrackingParticleComparison/interface/TPComparisonNtuple.h"

#include <stdexcept>
#include <iostream>
#include "MarksAnalysers/TrackingParticleComparison/src/TrackingParticleNtuple.pb.h"
#include "MarksAnalysers/TrackingParticleComparison/interface/fileIOTools.h"


namespace tpanalyser
{
	/** @brief Pimple to hold the private members of TPComparisonNtuple.
	 * @author Mark Grimes (mark.grimes@bristol.ac.uk)
	 * @date 18/Jul/2013
	 */
	class TPComparisonNtuplePrivateMembers
	{
	public:
		std::string filename;
		tpanalyserproto::Sample ntuple;
		tpanalyserproto::Event* pCurrentEvent;
		tpanalyserproto::MatchedTrackCollection* pCurrentCollection;
	};
} // end of the tpanalyser namespace



tpanalyser::TPComparisonNtuple::TPComparisonNtuple( const std::string filename )
	: pImple_( new TPComparisonNtuplePrivateMembers )
{
	pImple_->filename=filename;
	pImple_->pCurrentEvent=NULL;
}

tpanalyser::TPComparisonNtuple::~TPComparisonNtuple()
{
//	std::cout << "Writing file with " << pImple_->ntuple.event_size() << " events, first of which has " << pImple_->ntuple.event(0).matched_track_collection_size() << " matched track collections" << std::endl;
//	std::ofstream outputFile( pImple_->filename, std::ios::binary );
//	if( !outputFile.is_open() ) throw std::runtime_error( "Couldn't open the output file "+pImple_->filename );
//
//	if( !pImple_->ntuple.SerializeToOstream( &outputFile ) ) throw std::runtime_error( "Had some error while streaming the ntuple to the output file "+pImple_->filename );


	tpanalyser::saveSampleToFile( pImple_->ntuple, pImple_->filename );
}

void tpanalyser::TPComparisonNtuple::newEvent()
{
	pImple_->pCurrentEvent=pImple_->ntuple.add_event();
	pImple_->pCurrentCollection=pImple_->pCurrentEvent->add_matched_track_collection();
}

void tpanalyser::TPComparisonNtuple::setBeamSpot( float x, float y, float z )
{
	if( pImple_->pCurrentEvent==NULL ) newEvent();

	tpanalyserproto::TrackingVertex* pBeamSpot=pImple_->pCurrentEvent->mutable_beam_spot();
	pBeamSpot->set_position_x(x);
	pBeamSpot->set_position_y(y);
	pBeamSpot->set_position_z(z);
}

void tpanalyser::TPComparisonNtuple::setCurrentMatchedTrackCollection( size_t collectionNumber )
{
	if( pImple_->pCurrentEvent==NULL ) newEvent();

	// Make sure there are enough collections
	while( pImple_->pCurrentEvent->matched_track_collection_size()<=static_cast<int>(collectionNumber) ) pImple_->pCurrentEvent->add_matched_track_collection();

	// Then set the current collection to the correct number
	pImple_->pCurrentCollection=pImple_->pCurrentEvent->mutable_matched_track_collection( collectionNumber );
}

void tpanalyser::TPComparisonNtuple::setCollectionName( const std::string& name )
{
	if( pImple_->pCurrentEvent==NULL ) newEvent();
	pImple_->pCurrentCollection->set_name( name );
}

void tpanalyser::TPComparisonNtuple::addMatchedTrack( float dxyReconstructed, float dzReconstructed, float dxySimulated, float dzSimulated, float eta, float pt )
{
	if( pImple_->pCurrentEvent==NULL ) newEvent();

	tpanalyserproto::MatchedTrack* pMatchedTrack=pImple_->pCurrentCollection->add_matched_track();
	pMatchedTrack->set_eta( eta );
	pMatchedTrack->set_pt( pt );
	pMatchedTrack->set_dxy_reconstructed( dxyReconstructed );
	pMatchedTrack->set_dz_reconstructed( dzReconstructed );
	pMatchedTrack->set_dxy_simulated( dxySimulated );
	pMatchedTrack->set_dz_simulated( dzSimulated );
}
