#include "CreateNtuple.h"

#include <iostream>
#include <fstream>
#include <FWCore/Framework/interface/MakerMacros.h>
#include <FWCore/Framework/interface/Event.h>
#include <SimDataFormats/TrackingAnalysis/interface/TrackingParticle.h>

#include "MarksAnalysers/TrackingParticleComparison/src/TrackingParticleNtuple.pb.h"


namespace tpanalyser
{
	DEFINE_FWK_MODULE(CreateNtuple);
}

namespace // use the unnamed namespace for things only used in this file
{
	/** @brief Fills the supplied protobuf SimTrack representation with the information from the supplied SimTrack.
	 * @author Mark Grimes (mark.grimes@bristol.ac.uk)
	 * @date 12/Jun/2013
	 */
	void fillProtoObjectFromSimTrack( tpanalyserproto::SimTrack* pProtoSimTrack, const SimTrack& simTrack );

	/** @brief Fills the supplied protobuf TrackingVertex representation with the information from the supplied TrackingVertex.
	 * @author Mark Grimes (mark.grimes@bristol.ac.uk)
	 * @date 12/Jun/2013
	 */
	void fillProtoObjectFromTrackingVertex( tpanalyserproto::TrackingVertex* pProtoTV, const TrackingVertex& trackingVertex );

	/** @brief Fills the supplied protobuf TrackingParticle representation with the information from the supplied TrackingParticle.
	 * @author Mark Grimes (mark.grimes@bristol.ac.uk)
	 * @date 12/Jun/2013
	 */
	void fillProtoObjectFromTrackingParticle( tpanalyserproto::TrackingParticle* pProtoTP, const TrackingParticle& trackingParticle );

	//
	// Definitions below
	//

	void fillProtoObjectFromTrackingParticle( tpanalyserproto::TrackingParticle* pProtoTP, const TrackingParticle& trackingParticle )
	{
		for( const auto& simTrack : trackingParticle.g4Tracks() )
		{
			fillProtoObjectFromSimTrack( pProtoTP->add_sim_track(), simTrack );
		}

		fillProtoObjectFromTrackingVertex( pProtoTP->mutable_parent_vertex(), *trackingParticle.parentVertex() );

		for( const auto& decayVertex : trackingParticle.decayVertices() )
		{
			fillProtoObjectFromTrackingVertex( pProtoTP->add_decay_vertex(), *decayVertex );
		}

		pProtoTP->set_pdg_id( trackingParticle.pdgId() );
	}

	void fillProtoObjectFromSimTrack( tpanalyserproto::SimTrack* pProtoSimTrack, const SimTrack& simTrack )
	{
		pProtoSimTrack->set_event( simTrack.eventId().event() );
		pProtoSimTrack->set_bunch_crossing( simTrack.eventId().bunchCrossing() );
		pProtoSimTrack->set_track_id( simTrack.trackId() );
		pProtoSimTrack->set_charge( simTrack.charge() );
		pProtoSimTrack->set_mom_x( simTrack.momentum().X() );
		pProtoSimTrack->set_mom_y( simTrack.momentum().Y() );
		pProtoSimTrack->set_mom_z( simTrack.momentum().Z() );
		pProtoSimTrack->set_type( simTrack.type() );
	}

	void fillProtoObjectFromTrackingVertex( tpanalyserproto::TrackingVertex* pProtoTV, const TrackingVertex& trackingVertex )
	{
		pProtoTV->set_position_x( trackingVertex.position().X() );
		pProtoTV->set_position_y( trackingVertex.position().Y() );
		pProtoTV->set_position_z( trackingVertex.position().Z() );
	}
} // end of the unnamed namespace



tpanalyser::CreateNtuple::CreateNtuple( const edm::ParameterSet& config )
	: inputTag_( config.getParameter<edm::InputTag>("inputCollection") ),
	  ntupleFilename_( config.getParameter<std::string>("ntupleFilename") )
{
	// No operation other than the initialiser list
}

tpanalyser::CreateNtuple::~CreateNtuple()
{
	// No operation
}

void tpanalyser::CreateNtuple::fillDescriptions( edm::ConfigurationDescriptions& descriptions )
{
	// I don't really know what this method is for.
}

void tpanalyser::CreateNtuple::beginJob()
{
	// Reset the pointer with a new object.
	pNtuple_.reset( new tpanalyserproto::Sample );
}

void tpanalyser::CreateNtuple::analyze( const edm::Event& event, const edm::EventSetup& setup )
{
	edm::Handle< std::vector<TrackingParticle> > hTrackingParticles;
	event.getByLabel( inputTag_, hTrackingParticles );

	tpanalyserproto::Event* pEvent=pNtuple_->add_event();
	tpanalyserproto::TrackingParticleCollection* pCollection=pEvent->add_tracking_particle_collection();

	for( const auto& trackingParticle : *hTrackingParticles )
	{
		fillProtoObjectFromTrackingParticle( pCollection->add_tracking_particle(), trackingParticle );
	}

	std::cout << pNtuple_->event_size() << " events. Most recent has " << pEvent->tracking_particle_collection(0).tracking_particle_size() << " TrackingParticles." << std::endl;
}

void tpanalyser::CreateNtuple::endJob()
{
	std::ofstream outputFile( ntupleFilename_, std::ios::binary );
	if( !outputFile.is_open() ) throw std::runtime_error( "Couldn't open the output file "+ntupleFilename_ );

	if( !pNtuple_->SerializeToOstream( &outputFile ) ) throw std::runtime_error( "Had some error while streaming the ntuple to the output file "+ntupleFilename_ );
}
