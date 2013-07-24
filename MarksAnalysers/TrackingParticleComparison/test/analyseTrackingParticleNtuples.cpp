#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cmath>
#include "MarksAnalysers/TrackingParticleComparison/src/TrackingParticleNtuple.pb.h"
#include <TFile.h>
#include <TH1F.h>

namespace // Use the unnamed namespace for things only used in this file
{
	struct Vector
	{
		float x,y,z;
	};

	float distanceBetweenVectors( ::Vector vector1, ::Vector vector2 );

	/** @brief Checks both SimTracks only for that they are from the same event and have the same G4 ID.
	 * @author Mark Grimes (mark.grimes@bristol.ac.uk)
	 * @date 13/Jun/2013
	 */
	bool operator==( const tpanalyserproto::SimTrack& simTrack1, const tpanalyserproto::SimTrack& simTrack2 );

	/** @brief Finds a TrackingParticle in the suplied collection that has the same event and g4track ID as the
	 * supplied TrackingParticle.
	 *
	 * There could theoretically be more than one in the collection, but only the first is returned. If nothing
	 * is found then NULL is returned.
	 *
	 * @author Mark Grimes (mark.grimes@bristol.ac.uk)
	 * @date 13/06/2013
	 */
	const tpanalyserproto::TrackingParticle* findMatchingTrackingParticle( const tpanalyserproto::TrackingParticle& particleToFind, const tpanalyserproto::TrackingParticleCollection& collection );

	class PlotSet
	{
	public:
		PlotSet();
		void book( TDirectory* pDirectory );
		void fill( const tpanalyserproto::TrackingParticle* pParticle );
	protected:
		TH1* p3DDistanceFromOrigin_;
		TH1* pLongitudinalDistanceFromOrigin_;
		TH1* pTransverseDistanceFromOrigin_;
	};

	class ComparisonPlotSet
	{
	public:
		ComparisonPlotSet();
		void book( TDirectory* pDirectory );
		void fill( const tpanalyserproto::TrackingParticle* pParticle1, const tpanalyserproto::TrackingParticle* pParticle2 );
	protected:
		TH1* pDifferenceIn3DDistanceFromOrigin_;
		TH1* pDifferenceInLongitudinalDistanceFromOrigin_;
		TH1* pDifferenceInTransverseDistanceFromOrigin_;
		TH1* pRatioIn3DDistanceFromOrigin_;
		TH1* pRatioInLongitudinalDistanceFromOrigin_;
		TH1* pRatioInTransverseDistanceFromOrigin_;
		TH1* p3DDistanceBetween_;
		TH1* pLongitudinalDistanceBetween_;
		TH1* pTransverseDistanceBetween_;
	};

	class Analyser
	{
	public:
		Analyser( const std::string& outputFilename );
		~Analyser();
		void analyseEvent( const tpanalyserproto::Event& event1, const tpanalyserproto::Event& event2 );
	private:
		TFile* pFile_;
		::PlotSet allOfSample1_;
		::PlotSet allOfSample2_;
		::PlotSet matchedSample1_;
		::PlotSet matchedSample2_;
		::PlotSet onlyInSample1_;
		::PlotSet onlyInSample2_;
		::PlotSet allOfSample1Pileup_;
		::PlotSet allOfSample2Pileup_;
		::PlotSet allOfSample1Signal_;
		::PlotSet allOfSample2Signal_;
		::ComparisonPlotSet comparisonMatchedSample1ToSample2_;
	};


} // end of the unnamed namespace


int main( int argc, char* argv[] )
{
	if( argc!=3 )
	{
		std::string executableName=argv[0];
		size_t lastSlashPosition=executableName.find_last_of('/');
		if( lastSlashPosition!=std::string::npos ) executableName=executableName.substr( lastSlashPosition+1, std::string::npos );
		std::cerr << "   Usage: " << executableName << " <ntuple filename 1> <ntuple filename 2>" << std::endl;
		return -1;
	}

	const std::string filename1( argv[1] );
	const std::string filename2( argv[2] );

	try
	{
		tpanalyserproto::Sample ntuple1;
		tpanalyserproto::Sample ntuple2;

		std::ifstream inputFile;

		inputFile.open( filename1, std::ios::in | std::ios::binary );
		if( !inputFile.is_open() ) throw std::runtime_error( "Unable to open file "+filename1 );
		ntuple1.ParseFromIstream( &inputFile );
		inputFile.close();

		inputFile.open( filename2, std::ios::in | std::ios::binary );
		if( !inputFile.is_open() ) throw std::runtime_error( "Unable to open file "+filename2 );
		ntuple2.ParseFromIstream( &inputFile );
		inputFile.close();

		::Analyser eventAnalyser( "analysisHistograms.root" );

		std::cout << "Ntuple1 has " << ntuple1.event_size() << " events, and ntuple2 has " << ntuple2.event_size() << std::endl;
		for( int eventNumber=0; eventNumber<ntuple1.event_size() && eventNumber<ntuple1.event_size(); ++eventNumber )
		{
			std::cout << "Analysing event " << eventNumber << std::endl;
			eventAnalyser.analyseEvent( ntuple1.event(eventNumber), ntuple2.event(eventNumber) );
		}
	}
	catch( std::exception& error )
	{
		std::cerr << "Exception caught: " << error.what() << std::endl;
	}

	return 0;
}


namespace // Unnamed namespace
{
	float distanceBetweenVectors( ::Vector vector1, ::Vector vector2 )
	{
		::Vector difference{ vector1.x-vector2.x, vector1.y-vector2.y, vector1.z-vector2.z };
		return std::sqrt( difference.x*difference.x + difference.y*difference.y + difference.z*difference.z );
	}

	bool operator==( const tpanalyserproto::SimTrack& simTrack1, const tpanalyserproto::SimTrack& simTrack2 )
	{
		return simTrack1.event()==simTrack2.event()
			&& simTrack1.bunch_crossing()==simTrack2.bunch_crossing()
			&& simTrack1.track_id()==simTrack2.track_id();
	}

	const tpanalyserproto::TrackingParticle* findMatchingTrackingParticle( const tpanalyserproto::TrackingParticle& particleToFind, const tpanalyserproto::TrackingParticleCollection& collection )
	{
		for( const auto& trackingParticle : collection.tracking_particle() )
		{
			for( const auto& simTrack : trackingParticle.sim_track() )
			{
				for( const auto& simTrackToFind : particleToFind.sim_track() )
				{
					if( simTrack==simTrackToFind ) return &trackingParticle;
				}
			}
		} // end of loop of TrackingParticles in the collection

		// If control got this far then the whole collection has been searched
		// and it couldn't be found.
		return NULL;
	}

	PlotSet::PlotSet() : p3DDistanceFromOrigin_(NULL)
	{
		/* Just want to set one pointer to NULL in the initialiser list, so that I can check the histograms have been booked. */
	}

	void PlotSet::book( TDirectory* pDirectory )
	{
		p3DDistanceFromOrigin_=new TH1F( "distanceFromOrigin3D", "3D vertex distance from origin", 100, 0, 50 );
		pLongitudinalDistanceFromOrigin_=new TH1F( "distanceFromOriginLong", "Longitudinal vertex distance from origin", 100, 0, 50 );
		pTransverseDistanceFromOrigin_=new TH1F( "distanceFromOriginTrans", "Transverse vertex distance from origin", 100, 0, 50 );

		p3DDistanceFromOrigin_->SetDirectory( pDirectory );
		pLongitudinalDistanceFromOrigin_->SetDirectory( pDirectory );
		pTransverseDistanceFromOrigin_->SetDirectory( pDirectory );
	}

	void PlotSet::fill( const tpanalyserproto::TrackingParticle* pParticle )
	{
		if( p3DDistanceFromOrigin_==NULL ) throw std::runtime_error( "PlotSet::fill - histograms have not been booked" );

		::Vector origin{ 0, 0, 0 };
		::Vector vertex{ pParticle->parent_vertex().position_x(), pParticle->parent_vertex().position_y(), pParticle->parent_vertex().position_z() };

		p3DDistanceFromOrigin_->Fill( distanceBetweenVectors( origin, vertex ) );
		pLongitudinalDistanceFromOrigin_->Fill( vertex.z );
		pTransverseDistanceFromOrigin_->Fill( distanceBetweenVectors( origin, ::Vector{ vertex.x, vertex.y, 0 } ) );
	}

	ComparisonPlotSet::ComparisonPlotSet() : pDifferenceIn3DDistanceFromOrigin_(NULL)
	{
		/* Just want to set one pointer to NULL in the initialiser list, so that I can check the histograms have been booked. */
	}

	void ComparisonPlotSet::book( TDirectory* pDirectory )
	{
		pDifferenceIn3DDistanceFromOrigin_=new TH1F( "differenceIn3DDistanceFromOrigin", "Difference between 3D distances from origin", 50, -0.004, 0.004 );
		pDifferenceInLongitudinalDistanceFromOrigin_=new TH1F( "differenceInLongitudinalDistanceFromOrigin", "Difference between longitudinal distances from origin", 50, -0.004, 0.004 );
		pDifferenceInTransverseDistanceFromOrigin_=new TH1F( "differenceInTransverseDistanceFromOrigin", "Difference between transverse distances from origin", 50, -0.004, 0.004 );
		pRatioIn3DDistanceFromOrigin_=new TH1F( "ratioOf3DDistanceFromOrigin", "Ratio of 3D distances from origin", 100, 0, 20 );
		pRatioInLongitudinalDistanceFromOrigin_=new TH1F( "ratioOfLongitudinalDistanceFromOrigin", "Ratio of longitudinal distances from origin", 100, 0, 20 );
		pRatioInTransverseDistanceFromOrigin_=new TH1F( "ratioOfTransverseDistanceFromOrigin", "Ratio of transverse distances from origin", 100, 0, 20 );
		p3DDistanceBetween_=new TH1F( "distanceBetween3D", "3D distance between vertices", 50, 0, 0.005 );
		pLongitudinalDistanceBetween_=new TH1F( "distanceBetweenLongitudinal", "Longitudinal distance between vertices", 50, 0, 0.005 );
		pTransverseDistanceBetween_=new TH1F( "distanceBetweenTransverse", "Transverse distance between vertices", 50, 0, 0.005 );

		pDifferenceIn3DDistanceFromOrigin_->SetDirectory( pDirectory );
		pDifferenceInLongitudinalDistanceFromOrigin_->SetDirectory( pDirectory );
		pDifferenceInTransverseDistanceFromOrigin_->SetDirectory( pDirectory );
		pRatioIn3DDistanceFromOrigin_->SetDirectory( pDirectory );
		pRatioInLongitudinalDistanceFromOrigin_->SetDirectory( pDirectory );
		pRatioInTransverseDistanceFromOrigin_->SetDirectory( pDirectory );
		p3DDistanceBetween_->SetDirectory( pDirectory );
		pLongitudinalDistanceBetween_->SetDirectory( pDirectory );
		pTransverseDistanceBetween_->SetDirectory( pDirectory );
	}

	void ComparisonPlotSet::fill( const tpanalyserproto::TrackingParticle* pParticle1, const tpanalyserproto::TrackingParticle* pParticle2 )
	{
		if( pDifferenceIn3DDistanceFromOrigin_==NULL ) throw std::runtime_error( "ComparisonPlotSet::fill - histograms have not been booked" );

		::Vector origin{ 0, 0, 0 };
		::Vector vertex1{ pParticle1->parent_vertex().position_x(), pParticle1->parent_vertex().position_y(), pParticle1->parent_vertex().position_z() };
		::Vector vertex2{ pParticle2->parent_vertex().position_x(), pParticle2->parent_vertex().position_y(), pParticle2->parent_vertex().position_z() };

		pDifferenceIn3DDistanceFromOrigin_->Fill( distanceBetweenVectors(origin,vertex1)-distanceBetweenVectors(origin,vertex2) );
		pDifferenceInLongitudinalDistanceFromOrigin_->Fill( std::fabs(vertex1.z)-std::fabs(vertex2.z) );
		pDifferenceInTransverseDistanceFromOrigin_->Fill( distanceBetweenVectors(origin,::Vector{vertex1.x,vertex1.y,0})-distanceBetweenVectors(origin,::Vector{vertex2.x,vertex2.y,0}) );
		pRatioIn3DDistanceFromOrigin_->Fill( distanceBetweenVectors(origin,vertex1)/distanceBetweenVectors(origin,vertex2) );
		pRatioInLongitudinalDistanceFromOrigin_->Fill( std::fabs(vertex1.z)/std::fabs(vertex2.z) );
		pRatioInTransverseDistanceFromOrigin_->Fill( distanceBetweenVectors(origin,::Vector{vertex1.x,vertex1.y,0})/distanceBetweenVectors(origin,::Vector{vertex2.x,vertex2.y,0}) );
		p3DDistanceBetween_->Fill( distanceBetweenVectors(vertex1,vertex2) );
		pLongitudinalDistanceBetween_->Fill( vertex1.z-vertex2.z );
		pTransverseDistanceBetween_->Fill( distanceBetweenVectors(::Vector{vertex1.x,vertex1.y,0},::Vector{vertex2.x,vertex2.y,0}) );
	}

	Analyser::Analyser( const std::string& outputFilename )
	{
		pFile_=TFile::Open( outputFilename.c_str(), "RECREATE" );
		TDirectory* pSubDirectory;

		pSubDirectory=pFile_->mkdir( "allOfSample1" );
		allOfSample1_.book( pSubDirectory );

		pSubDirectory=pFile_->mkdir( "allOfSample2" );
		allOfSample2_.book( pSubDirectory );

		pSubDirectory=pFile_->mkdir( "matchedSample1" );
		matchedSample1_.book( pSubDirectory );

		pSubDirectory=pFile_->mkdir( "matchedSample2" );
		matchedSample2_.book( pSubDirectory );

		pSubDirectory=pFile_->mkdir( "onlyInSample1" );
		onlyInSample1_.book( pSubDirectory );

		pSubDirectory=pFile_->mkdir( "onlyInSample2" );
		onlyInSample2_.book( pSubDirectory );

		pSubDirectory=pFile_->mkdir( "allOfSample1Pileup" );
		allOfSample1Pileup_.book( pSubDirectory );

		pSubDirectory=pFile_->mkdir( "allOfSample2Pileup" );
		allOfSample2Pileup_.book( pSubDirectory );

		pSubDirectory=pFile_->mkdir( "allOfSample1Signal" );
		allOfSample1Signal_.book( pSubDirectory );

		pSubDirectory=pFile_->mkdir( "allOfSample2Signal" );
		allOfSample2Signal_.book( pSubDirectory );

		pSubDirectory=pFile_->mkdir( "comparisonMatchedSample1ToSample2" );
		comparisonMatchedSample1ToSample2_.book( pSubDirectory );
	}

	Analyser::~Analyser()
	{
		pFile_->Write();
		pFile_->Close();
		delete pFile_;
	}

	void Analyser::analyseEvent( const tpanalyserproto::Event& event1, const tpanalyserproto::Event& event2 )
	{
		std::vector< std::pair<const tpanalyserproto::TrackingParticle*,const tpanalyserproto::TrackingParticle*> > matchingParticles;
		std::vector<const tpanalyserproto::TrackingParticle*> particlesOnlyInNtuple1;
		std::vector<const tpanalyserproto::TrackingParticle*> particlesOnlyInNtuple2;

		std::cout << " sample 1 size=" << event1.tracking_particle_collection(0).tracking_particle_size()
				<< " sample 2 size=" << event2.tracking_particle_collection(0).tracking_particle_size() << std::endl;

		for( const auto& trackingParticle : event1.tracking_particle_collection(0).tracking_particle() )
		{
			const tpanalyserproto::TrackingParticle* pMatchingParticle=::findMatchingTrackingParticle( trackingParticle, event2.tracking_particle_collection(0) );
			if( pMatchingParticle!=NULL ) matchingParticles.push_back( std::make_pair(&trackingParticle,pMatchingParticle) );
			else particlesOnlyInNtuple1.push_back( &trackingParticle );
		}

		for( const auto& trackingParticle : event2.tracking_particle_collection(0).tracking_particle() )
		{
			const tpanalyserproto::TrackingParticle* pMatchingParticle=::findMatchingTrackingParticle( trackingParticle, event1.tracking_particle_collection(0) );
			if( pMatchingParticle==NULL ) particlesOnlyInNtuple2.push_back( &trackingParticle );
			// should already have all matching particles from the check on event1
		}

		std::cout << "matchingParticles.size()=" << matchingParticles.size()
				<< " particlesOnlyInNtuple1.size()=" << particlesOnlyInNtuple1.size()
				<< " particlesOnlyInNtuple2.size()=" << particlesOnlyInNtuple2.size() << std::endl;

		for( const auto& matchedPair : matchingParticles )
		{
			const auto& pTrackingParticle1=matchedPair.first;
			const auto& pTrackingParticle2=matchedPair.second;

			allOfSample1_.fill( pTrackingParticle1 );
			allOfSample2_.fill( pTrackingParticle2 );
			matchedSample1_.fill( pTrackingParticle1 );
			matchedSample2_.fill( pTrackingParticle2 );
			comparisonMatchedSample1ToSample2_.fill( pTrackingParticle1, pTrackingParticle2 );

			if( pTrackingParticle1->sim_track(0).event()==0 && pTrackingParticle1->sim_track(0).bunch_crossing()==0 ) allOfSample1Signal_.fill( pTrackingParticle1 );
			else allOfSample1Pileup_.fill( pTrackingParticle1 );

			if( pTrackingParticle2->sim_track(0).event()==0 && pTrackingParticle2->sim_track(0).bunch_crossing()==0 ) allOfSample2Signal_.fill( pTrackingParticle2 );
			else allOfSample2Pileup_.fill( pTrackingParticle2 );
		}

		for( const auto& pTrackingParticle : particlesOnlyInNtuple1 )
		{
			allOfSample1_.fill( pTrackingParticle );
			onlyInSample1_.fill( pTrackingParticle );
		}

		for( const auto& pTrackingParticle : particlesOnlyInNtuple2 )
		{
			allOfSample2_.fill( pTrackingParticle );
			onlyInSample2_.fill( pTrackingParticle );
		}
	}

} // end of the unnamed namespace
