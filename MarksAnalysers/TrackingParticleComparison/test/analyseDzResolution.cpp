#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <memory>
#include <cmath>
#include "MarksAnalysers/TrackingParticleComparison/src/TrackingParticleNtuple.pb.h"
#include "MarksAnalysers/TrackingParticleComparison/interface/fileIOTools.h"
#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TObjArray.h>

namespace // Use the unnamed namespace for things only used in this file
{
	/** @brief TH2 That will fit y slices and produce TH1s of the sigma and mean.
	 *
	 * Note that if GetDirectory() for each of the plots is not NULL during destruction
	 * the histograms are deleted.
	 *
	 * @author Mark Grimes (mark.grimes@bristol.ac.uk)
	 * @date 23/Jul/3013
	 */
	class FittedTH2
	{
	public:
		FittedTH2( TDirectory* pDirectory, const std::string& name, const std::string& title, size_t numXBins, float xLowerEdge, float xUpperEdge, size_t numYBins, float yLowerEdge, float yUpperEdge, bool logarithmicXBinning=false );
		virtual ~FittedTH2();
		void fill( float x, float y, float weight=1 );
		void fit();
	private:
		TH2* pMainHistogram_;
		TH1* pSigmaHistogram_;
		TH1* pMeanHistogram_;
	};

	class ResolutionPlots
	{
	public:
		ResolutionPlots();
		void book( TDirectory* pDirectory );
		void setPtCuts( float lowerCut, float upperCut );
		void fill( const tpanalyserproto::MatchedTrack& track );
		void calculateSigmaAndMean();
	protected:
		void calculateSigmaAndMean( TH2* pInputHistogram, TH1* pOutputMeanHistogram, TH1* pOutputSigmaHistogram );
		float lowerPtCut_;
		float upperPtCut_;

		TH1* pReconstructedDxy_;
		TH1* pReconstructedDz_;
		TH1* pSimulatedDxy_;
		TH1* pSimulatedDz_;

		std::unique_ptr<FittedTH2> pDxyVersusEta_;
		std::unique_ptr<FittedTH2> pDxyVersusPt_;
		std::unique_ptr<FittedTH2> pDzVersusEta_;
		std::unique_ptr<FittedTH2> pDzVersusPt_;

		static const size_t numberOfEtaBins_;
		static const float minimumEta_;
		static const float maximumEta_;
		static const size_t numberOfPtBins_;
		static const float minimumPt_;
		static const float maximumPt_;
		static const size_t numberOfDxyBins_;
		static const float minimumDxy_;
		static const float maximumDxy_;
		static const size_t numberOfDzBins_;
		static const float minimumDz_;
		static const float maximumDz_;
		static const size_t numberOfXYBins_;
		static const float minimumXY_;
		static const float maximumXY_;
		static const size_t numberOfZBins_;
		static const float minimumZ_;
		static const float maximumZ_;
	};

	class Analyser
	{
	public:
		Analyser( const std::string& outputFilename );
		~Analyser();
		void analyseEvent( const tpanalyserproto::Event& event );
	private:
		void addResolutionPlotCollection( std::string newDirectoryName="" );
		std::vector< std::vector<ResolutionPlots> > resolutionPlotsForCollections_;
		TFile* pFile_;
		TH1* pBeamSpotRadius_;
		TH1* pBeamSpotZ_;
		static const size_t numberOfRadiusBins_;
		static const float minimumRadius_;
		static const float maximumRadius_;
		static const size_t numberOfZBins_;
		static const float minimumZ_;
		static const float maximumZ_;
	};


} // end of the unnamed namespace


int main( int argc, char* argv[] )
{
	if( argc<2 )
	{
		std::string executableName=argv[0];
		size_t lastSlashPosition=executableName.find_last_of('/');
		if( lastSlashPosition!=std::string::npos ) executableName=executableName.substr( lastSlashPosition+1, std::string::npos );
		std::cerr << "   Usage: " << executableName << " <ntuple filename> [ntuple filename [ntuple filename [...] ] ]" << std::endl;
		return -1;
	}


	for( int argument=1; argument<argc; ++argument )
	{
		const std::string inputFilename( argv[argument] );

		try
		{
			//
			// Create an output name by replacing the ".proto" at the end of the
			// input name with ".root".
			//
			const std::string suffixToReplace=".proto";
			std::string outputFilename;
			if( inputFilename.rfind(suffixToReplace)==inputFilename.size()-suffixToReplace.size() )
			{
				// Chop off the suffix
				outputFilename=inputFilename.substr( 0, inputFilename.size()-suffixToReplace.size() );
				// and add the new suffix
				outputFilename+=".root";
			}
			else outputFilename=inputFilename+".root";

			//
			// Load the sample from disk
			//
			tpanalyserproto::Sample ntuple;
			tpanalyser::loadSampleFromFile( ntuple, inputFilename );

			::Analyser eventAnalyser( outputFilename );

			std::cout << "Ntuple in file " << inputFilename << " has " << ntuple.event_size() << " events" << std::endl;
			for( int eventNumber=0; eventNumber<ntuple.event_size(); ++eventNumber )
			{
				//std::cout << "Analysing event " << eventNumber << std::endl;
				eventAnalyser.analyseEvent( ntuple.event(eventNumber) );
			}
		}
		catch( std::exception& error )
		{
			std::cerr << "Exception caught while processing " << inputFilename << " : " << error.what() << std::endl;
		}
	}

	return 0;
}


namespace // Unnamed namespace
{
	const size_t ResolutionPlots::numberOfEtaBins_=50;
	const float ResolutionPlots::minimumEta_=-2.5;
	const float ResolutionPlots::maximumEta_=2.5;
	const size_t ResolutionPlots::numberOfPtBins_=40;
	const float ResolutionPlots::minimumPt_=0.1;
	const float ResolutionPlots::maximumPt_=1000;
	const size_t ResolutionPlots::numberOfDxyBins_=100;
	const float ResolutionPlots::minimumDxy_=-25;
	const float ResolutionPlots::maximumDxy_=25;
	const size_t ResolutionPlots::numberOfDzBins_=60;
	const float ResolutionPlots::minimumDz_=-30;
	const float ResolutionPlots::maximumDz_=30;
	const size_t ResolutionPlots::numberOfXYBins_=60;
	const float ResolutionPlots::minimumXY_=-0.5;
	const float ResolutionPlots::maximumXY_=0.5;
	const size_t ResolutionPlots::numberOfZBins_=60;
	const float ResolutionPlots::minimumZ_=-0.5;
	const float ResolutionPlots::maximumZ_=0.5;

	const size_t Analyser::numberOfRadiusBins_=60;
	const float Analyser::minimumRadius_=0;
	const float Analyser::maximumRadius_=0.5;
	const size_t Analyser::numberOfZBins_=60;
	const float Analyser::minimumZ_=-0.5;
	const float Analyser::maximumZ_=0.5;

	FittedTH2::FittedTH2( TDirectory* pDirectory, const std::string& name, const std::string& title, size_t numXBins, float xLowerEdge, float xUpperEdge, size_t numYBins, float yLowerEdge, float yUpperEdge, bool logarithmicXBinning )
	{
		if( logarithmicXBinning )
		{
			std::vector<Double_t> logarithmicBins;
			float logMin=std::log10( xLowerEdge );
			float logMax=std::log10( xUpperEdge );
			for( size_t bin=0; bin<=numXBins; ++bin )
			{
				logarithmicBins.push_back( std::pow( 10, logMin+bin*(logMax-logMin)/numXBins) );
			}

			pMainHistogram_=new TH2F( name.c_str(), title.c_str(), numXBins, &logarithmicBins[0], numYBins, yLowerEdge, yUpperEdge );
			pMainHistogram_->SetDirectory( pDirectory );

			pMeanHistogram_=new TH1F( (name+"Mean").c_str(), (title+" mean").c_str(), numXBins, &logarithmicBins[0] );
			pMeanHistogram_->SetDirectory( pDirectory );

			pSigmaHistogram_=new TH1F( (name+"Sigma").c_str(), (title+" sigma").c_str(), numXBins, &logarithmicBins[0] );
			pSigmaHistogram_->SetDirectory( pDirectory );
		}
		else
		{
			pMainHistogram_=new TH2F( name.c_str(), title.c_str(), numXBins, xLowerEdge, xUpperEdge, numYBins, yLowerEdge, yUpperEdge );
			pMainHistogram_->SetDirectory( pDirectory );

			pMeanHistogram_=new TH1F( (name+"Mean").c_str(), (title+" mean").c_str(), numXBins, xLowerEdge, xUpperEdge );
			pMeanHistogram_->SetDirectory( pDirectory );

			pSigmaHistogram_=new TH1F( (name+"Sigma").c_str(), (title+" sigma").c_str(), numXBins, xLowerEdge, xUpperEdge );
			pSigmaHistogram_->SetDirectory( pDirectory );
		}
	}

	FittedTH2::~FittedTH2()
	{
		//fit();
		if( pMainHistogram_->GetDirectory()!=NULL ) delete pMainHistogram_;
		if( pMeanHistogram_->GetDirectory()!=NULL ) delete pMeanHistogram_;
		if( pSigmaHistogram_->GetDirectory()!=NULL ) delete pSigmaHistogram_;
	}

	void FittedTH2::fill( float x, float y, float weight )
	{
		pMainHistogram_->Fill( x, y, weight );
	}

	void FittedTH2::fit()
	{
		TObjArray slices;
		// All of these parameters except "slices" are the defaults for the method
		pMainHistogram_->FitSlicesY( 0, 0, -1, 0, "QNR", &slices );

		TH1* pTempMeanHistogram=dynamic_cast<TH1*>( slices[1] );
		TH1* pTempSigmaHistogram=dynamic_cast<TH1*>( slices[2] );

		for( int bin=1; bin<pMainHistogram_->GetNbinsX()-1; ++bin )
		{
			pMeanHistogram_->SetBinContent( bin, pTempMeanHistogram->GetBinContent( bin ) );
			pMeanHistogram_->SetBinError( bin, pTempMeanHistogram->GetBinError( bin ) );
			pSigmaHistogram_->SetBinContent( bin, pTempSigmaHistogram->GetBinContent( bin ) );
			pSigmaHistogram_->SetBinError( bin, pTempSigmaHistogram->GetBinError( bin ) );
		}
	}

	ResolutionPlots::ResolutionPlots() : lowerPtCut_(-1), upperPtCut_(-1)
	{
		// No operation besides the initialiser list
	}

	void ResolutionPlots::book( TDirectory* pDirectory )
	{
		const bool logarithmicXAxis=true; // Just to make function calls easier to read

		pReconstructedDxy_=new TH1F( "reconstructedDxy", "reconstructed dxy", numberOfXYBins_, minimumXY_, maximumXY_ );
		pReconstructedDz_=new TH1F( "reconstructedDz", "reconstructed dz", numberOfZBins_, minimumZ_, maximumZ_ );
		pSimulatedDxy_=new TH1F( "simulatedDxy", "simulated dxy", numberOfXYBins_, minimumXY_, maximumXY_ );
		pSimulatedDz_=new TH1F( "simulatedDz", "simulated dz", numberOfZBins_, minimumZ_, maximumZ_ );

		pReconstructedDxy_->SetDirectory( pDirectory );
		pReconstructedDz_->SetDirectory( pDirectory );
		pSimulatedDxy_->SetDirectory( pDirectory );
		pSimulatedDz_->SetDirectory( pDirectory );

		pDxyVersusEta_.reset( new FittedTH2( pDirectory, "dxResolutionVersusEta", "dx resolution versus eta", numberOfEtaBins_, minimumEta_, maximumEta_, numberOfDxyBins_, minimumDxy_, maximumDxy_ ) );
		pDxyVersusPt_.reset( new FittedTH2( pDirectory, "dxResolutionVersusPt", "dx resolution versus pt", numberOfPtBins_, minimumPt_, maximumPt_, numberOfDxyBins_, minimumDxy_, maximumDxy_, logarithmicXAxis ) );
		pDzVersusEta_.reset( new FittedTH2( pDirectory, "dzResolutionVersusEta", "dz resolution versus eta", numberOfEtaBins_, minimumEta_, maximumEta_, numberOfDzBins_, minimumDz_, maximumDz_ ) );
		pDzVersusPt_.reset( new FittedTH2( pDirectory, "dzResolutionVersusPt", "dz resolution versus pt", numberOfPtBins_, minimumPt_, maximumPt_, numberOfDzBins_, minimumDz_, maximumDz_, logarithmicXAxis ) );
	}

	void ResolutionPlots::setPtCuts( float lowerCut, float upperCut )
	{
		lowerPtCut_=lowerCut;
		upperPtCut_=upperCut;
	}

	void ResolutionPlots::fill( const tpanalyserproto::MatchedTrack& track )
	{
		if( pDxyVersusEta_.get()==NULL ) throw std::runtime_error( "ResolutionPlots::fill - histograms have not been booked" );

		if( track.has_pt() )
		{
			if( lowerPtCut_!=-1 && track.pt()<lowerPtCut_ ) return;
			if( upperPtCut_!=-1 && track.pt()>upperPtCut_ ) return;
		}

		pReconstructedDxy_->Fill( track.dxy_reconstructed() );
		pReconstructedDz_->Fill( track.dz_reconstructed() );
		pSimulatedDxy_->Fill( track.dxy_simulated() );
		pSimulatedDz_->Fill( track.dz_simulated() );

		pDxyVersusEta_->fill( track.eta(), track.dxy_reconstructed()-track.dxy_simulated() );
		pDxyVersusPt_->fill( track.pt(), track.dz_reconstructed()-track.dz_simulated() );
		pDzVersusEta_->fill( track.eta(), track.dz_reconstructed()-track.dz_simulated() );
		pDzVersusPt_->fill( track.pt(), track.dz_reconstructed()-track.dz_simulated() );
	}

	void ResolutionPlots::calculateSigmaAndMean()
	{
		pDxyVersusEta_->fit();
		pDxyVersusPt_->fit();
		pDzVersusEta_->fit();
		pDzVersusPt_->fit();
	}

	Analyser::Analyser( const std::string& outputFilename )
	{
		pFile_=TFile::Open( outputFilename.c_str(), "RECREATE" );

		pBeamSpotRadius_=new TH1F( "beamSpotRadius", "beam spot radius in xy", numberOfRadiusBins_, minimumRadius_, maximumRadius_ );
		pBeamSpotZ_=new TH1F( "beamSpotZ", "beam spot z", numberOfZBins_, minimumZ_, maximumZ_ );
		pBeamSpotRadius_->SetDirectory( pFile_ );
		pBeamSpotZ_->SetDirectory( pFile_ );
	}

	Analyser::~Analyser()
	{
		for( auto& plotCollection : resolutionPlotsForCollections_ )
		{
			for( auto& resolutionPlot : plotCollection )
			{
				resolutionPlot.calculateSigmaAndMean();
			}
		}

		pFile_->Write();
		pFile_->Close();
		delete pFile_;
	}

	void Analyser::analyseEvent( const tpanalyserproto::Event& event )
	{
		//
		// Analyse the beam spot
		//
		pBeamSpotRadius_->Fill( std::sqrt( event.beam_spot().position_x()*event.beam_spot().position_x() + event.beam_spot().position_y()*event.beam_spot().position_y() ) );
		pBeamSpotZ_->Fill( event.beam_spot().position_z() );

		//
		// Analyse the track collections
		//
		for( size_t collectionNumber=0; collectionNumber<static_cast<size_t>(event.matched_track_collection_size()); ++collectionNumber )
		{
			const auto& matchedTrackCollection=event.matched_track_collection(collectionNumber);

			// Make sure there is a collection created for this sample
			if( collectionNumber>=resolutionPlotsForCollections_.size() )
			{
				std::string name;
				if( matchedTrackCollection.has_name() ) name=matchedTrackCollection.name();
				addResolutionPlotCollection( name );
			}
			auto& resolutionPlots=resolutionPlotsForCollections_[collectionNumber];

			for( const auto& matchedTrack : matchedTrackCollection.matched_track() )
			{
				for( auto& resolutionPlot : resolutionPlots )
				{
					resolutionPlot.fill( matchedTrack );
				}
			}
		}

	}

	void Analyser::addResolutionPlotCollection( std::string newDirectoryName )
	{
		std::stringstream stringConverter;

		// If the user didn't supply a directory name, create a default one
		if( newDirectoryName.empty() )
		{
			stringConverter << "Collection_" << resolutionPlotsForCollections_.size();
			newDirectoryName=stringConverter.str();
		}

		std::cout << "Adding plots for collection named " << newDirectoryName << "\n";

		TDirectory* pMainDirectory=pFile_->mkdir( newDirectoryName.c_str() );
		resolutionPlotsForCollections_.push_back( std::vector< ::ResolutionPlots>() );
		std::vector< ::ResolutionPlots>& resolutionPlots=resolutionPlotsForCollections_.back();

		TDirectory* pSubDirectory=pMainDirectory->mkdir( "wholeSample" );
		resolutionPlots.push_back( ResolutionPlots() );
		resolutionPlots.back().book( pSubDirectory );


		std::vector< std::pair<float,float> > ptCuts;
		ptCuts.push_back( std::make_pair( 1, 1000 ) );
		ptCuts.push_back( std::make_pair( 10, 1000 ) );
		ptCuts.push_back( std::make_pair( 100, 1000 ) );

		for( const auto& cuts : ptCuts )
		{
			stringConverter.str("");
			stringConverter << "ptBetween" << cuts.first << "And" << cuts.second;
			pSubDirectory=pMainDirectory->mkdir( stringConverter.str().c_str() );
			resolutionPlots.push_back( ResolutionPlots() );
			resolutionPlots.back().book( pSubDirectory );
			resolutionPlots.back().setPtCuts( cuts.first, cuts.second );
		}

	}

} // end of the unnamed namespace
